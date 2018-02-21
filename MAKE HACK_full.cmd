cd %~dp0

copy FE8_clean.gba Terqles_M4FC.gba

cd "%~dp0Tables"

echo: | (c2ea "%~dp0FE8_clean.gba")

cd "%~dp0Text"

echo: | (textprocess_v2 text_buildfile.txt)

cd "%~dp0Event Assembler"

Core A FE8 "-output:%~dp0Terqles_M4FC.gba" "-input:%~dp0ROM Buildfile.event"

cd "%~dp0ups"

ups diff -b "%~dp0FE8_clean.gba" -m "%~dp0Terqles_M4FC.gba" -o "%~dp0Terqles_M4FC.ups"

pause
