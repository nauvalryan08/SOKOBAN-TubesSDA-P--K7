@echo off
setlocal enabledelayedexpansion

echo Compiling SOKOBANGAME...

REM Create BUILD directory if it doesn't exist
if not exist ..\BUILD mkdir ..\BUILD

REM Collect all .c files into SRC variable
set SRC=..\main.c

for %%d in (..\\VIEW ..\\STRUCTURES "..\\GAMEPLAY\\ARENA_LOGIC" "..\\GAMEPLAY\\GAME_LOGIC" "..\\GAMEPLAY\\REPLAY_LOGIC" ..\\DATABASE "..\\UTILS\\include" "..\\UTILS\\sound" "..\\UTILS\\validator" "..\\UTILS\\auth" ..\\ASSETS) do (
    for %%f in (%%d\*.c) do (
        if exist "%%f" set SRC=!SRC! %%f
    )
)

REM Include paths
set INCLUDES=-I.. -I..\\VIEW -I..\\STRUCTURES -I..\\GAMEPLAY -I..\\GAMEPLAY\\ARENA_LOGIC -I..\\GAMEPLAY\\GAME_LOGIC -I..\\GAMEPLAY\\REPLAY_LOGIC -I..\\DATABASE -I..\\FILEDATA -I..\\UTILS\\include -I..\\UTILS\\sound -I..\\UTILS\\validator -I..\\UTILS\\auth -I..\\ASSETS

REM Libraries and flags
set LIBS=-Llib -lpdcurses -lwinmm

REM Compile
gcc -o ..\\BUILD\\SOKOBANGAME.exe %SRC% %INCLUDES% %LIBS%
if %ERRORLEVEL% EQU 0 (
    echo Compile Berhasil!
    echo Program berada di: ..\BUILD\SOKOBANGAME.exe
) else (
    echo Compile Gagal :/
    exit /b 1
)