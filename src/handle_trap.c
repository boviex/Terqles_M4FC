#include "unit_mover.h"

typedef struct _TrapHandlerProc TrapHandlerProc;
struct _TrapHandlerProc {
	Proc header;
	
	Unit* pUnit;
	int   idk;
};

void HandleTrap(Proc* proc, Unit* unit, int idk);
void TrapHandlerCheck(TrapHandlerProc* proc);

static const Vector2 DirectionStepTable[] = {
	{ -1,  0 }, // left
	{ +1,  0 }, // right
	{  0, +1 }, // down
	{  0, -1 }  // up
};

static const uint8_t OppositeDirectionTable[] = {
	1, // left  -> right
	0, // right -> left
	3, // down  -> up
	2  // up    -> down
};

static const ProcCode ProcCode_TrapHandler[] = {
	PROC_SET_NAME("Stan:MovingTrapHandler"),
	PROC_YIELD,
	
	PROC_WHILE_ROUTINE(DoesMovingMoveUnitExist),
	
	PROC_LABEL(0),
	PROC_CALL_ROUTINE(TrapHandlerCheck),
	PROC_WHILE_ROUTINE(0x08078721), // Blocking MoveUnit Proc Exists
	PROC_GOTO(0),
	
	PROC_LABEL(1),
	PROC_END
};

int CanUnitBeOnPosition(Unit* unit, int x, int y) {
	if (x < 0 || y < 0)
		return 0; // position out of bounds
	
	if (x >= map_size.x || y >= map_size.y)
		return 0; // position out of bounds
	
	if (map_unit[y][x])
		return 0; // a unit is occupying this position
	
	if (map_hidden[y][x] & 1)
		return 0; // a hidden unit is occupying this position
	
	return CanUnitCrossTerrain(unit, map_terrain[y][x]);
}

Vector2 GetPushPosition(Unit* unit, int direction, int moveAmount) {
	Vector2 result = {
		unit->xPos,
		unit->yPos
	};
	
	const Vector2 step = DirectionStepTable[direction];
	
	while (CanUnitBeOnPosition(unit, (result.x + step.x), (result.y + step.y))) {
		result.x += step.x;
		result.y += step.y;
		
		if (!(--moveAmount))
			break;
		
		if (map_hidden[result.y][result.x] & 2) // check for a hidden trap such as a mine
			break;
	}
	
	return result;
}

void HandleTrap(Proc* proc, Unit* unit, int idk) {
	RefreshEntityMaps();
	EndAllMoveUnits();
	
	TrapHandlerProc* newProc = (TrapHandlerProc*) StartBlockingProc(ProcCode_TrapHandler, proc);
	
	newProc->pUnit = unit;
	newProc->idk   = idk;
}

void TrapHandlerCheck(TrapHandlerProc* proc) {
	Trap* trap = GetTrapAt(proc->pUnit->xPos, proc->pUnit->yPos);
	
	if (trap) {
		//~ NewUnitMoveAnim(proc->pUnit, OppositeDirectionTable[trap->data[0]], (Proc*) proc);
		
		Vector2 pos = GetPushPosition(proc->pUnit, trap->data[0], 0);
		
		if (pos.x == proc->pUnit->xPos && pos.y == proc->pUnit->yPos) {
			GotoProcLabel((Proc*) proc, 1);
		} else {
			// FIXME: write definitions for the whole AI pre-action struct thingy
			
			uint8_t* const pAIX = (uint8_t*) 0x0203AA96;
			uint8_t* const pAIY = (uint8_t*) 0x0203AA97;
			
			(*pAIX) = proc->pUnit->xPos = action_data.xMove = pos.x;
			(*pAIY) = proc->pUnit->yPos = action_data.yMove = pos.y;
		}
	} else
		GotoProcLabel((Proc*) proc, 1);
}
