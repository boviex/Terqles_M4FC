#include "gbafe.h"
#include "unit_mover.c"
#include "utility.c"

#define eventSlot pEventSlot_0
extern int eventSlot[];
#pragma long_calls
void PlaySound(int sound);
#pragma long_calls_off
void PlayScream() {
  PlaySound(0xE7);
};

void NewFadeInBlack(int duration);
void NewFadeOutBlack(int duration);

static const ProcCode ProcCode_Test[] = {
  PROC_SET_NAME("RAAAAAAH"),
  PROC_CALL_ROUTINE(LockGameLogic),   //wait for proc to be done before continuing
  PROC_CALL_ROUTINE_ARG(NewFadeInBlack, 0x10),
  PROC_YIELD,                         //when done fading
  PROC_CALL_ROUTINE(PlayScream),      //RAAAAAAH
  PROC_SLEEP(120),
  PROC_CALL_ROUTINE_ARG(NewFadeOutBlack, 0x10),
  PROC_YIELD,                         //when done fading
  PROC_CALL_ROUTINE(UnlockGameLogic), //ok done you can go about your business
  PROC_END
};

int alwaysFalse(){
  return 3;
}

#pragma long_calls
void TryRemoveUnitFromBallista(Unit* unit);
#pragma long_calls_off

int NewExitTargeting(Proc* proc){
  MoveUnitState* idk;
  action_data.actionIndex = 0x1; //wait
  Vector2 from = {
    action_data.xMove,
    action_data.yMove
  };
  Vector2 to = {
    action_data.xMove += 5,
    action_data.yMove += 3
  };
  active_unit->curHP -= 10;
  TryRemoveUnitFromBallista(active_unit);
  EndAllMoveUnits();

  //play brigand scream lol
  StartBlockingProc(ProcCode_Test, proc);
  idk = StartMoveUnitForUnit(active_unit);
  NewUnitMoveAnim(idk, from, to, 0);
  return 0x17;
};

void some_asmc() {
  eventSlot[0xC] = NextRN_100();
  StartProc(ProcCode_Test, PROC_TREE(3));
};
