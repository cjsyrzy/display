@mkdir build
@cd build

cmake -G "MinGW Makefiles" ..
@ if errorlevel 1 goto end

cmake --build .
@ if errorlevel 1 goto end

@REM @move .\mps_tool.exe ..\..\MPS_TOOL\mps_tool.exe

:end
@cd ..
@REM clean.bat
@REM @ exit
@REM @pause
