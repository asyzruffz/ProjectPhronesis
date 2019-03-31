@echo off
rem Post-Build Event:   call "$(ProjectDir)Resources\Shaders\compileshader.bat" "$(ProjectDir)$(IntDir)CompiledShaders\\" "$(OutDir)Shaders\\"
set OLDDIR=%CD%
cd /d "%~dp0"
if not exist "%1" mkdir "%1"
del /s /f /q "%1*.*" >nul
for /r %%i in (*.vert, *.tesc, *.tese, *.geom, *.frag, *.comp) do "%VULKAN_SDK%/Bin/glslangValidator.exe" -V "%%i" -o "%1%%~nxi.spv"
if not exist "%2" mkdir "%2"
for %%f in (%~dp1*) do fc /b %%f "%2%%~nxf" >nul 2>&1 || copy /y %%f "%2%%~nxf"
cd /d "%OLDDIR%"