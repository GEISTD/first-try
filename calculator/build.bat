@echo off
cd /d %~dp0
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
set "MSVC_BIN=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64"
set "PATH=%MSVC_BIN%;%PATH%"
if exist main.exe del /f /q main.exe
cl.exe /nologo /EHsc /std:c++17 /INCREMENTAL:NO main.cpp parser.cpp math_functions.cpp history_manager.cpp /Fe:main.exe
if errorlevel 1 (
    echo Build failed
    exit /b 1
)
if exist *.obj del /f /q *.obj
if exist *.pdb del /f /q *.pdb
if exist *.ilk del /f /q *.ilk
if exist *.json del /f /q *.json
echo Build succeeded
