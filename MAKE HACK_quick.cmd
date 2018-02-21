cd %~dp0

copy FE8_clean.gba Terqles_M4FC.gba

cd "%~dp0Event Assembler"

Core A FE8 "-output:%~dp0Terqles_M4FC.gba" "-input:%~dp0ROM Buildfile.event"

pause
