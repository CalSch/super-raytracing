:: @echo off
SETLOCAL ENABLEDELAYEDEXPANSION

:: this is also written by chatgpt so be warned

:: Define source and destination directories
set INCLUDE_SRC=base\include
set SRC_SRC=base\src
set DST_DIR=cardputer\rtx

:: Create destination directory if it doesn't exist
if not exist "%DST_DIR%" (
    mkdir "%DST_DIR%"
)

:: Copy all files from INCLUDE_SRC and SRC_SRC to DST_DIR
xcopy /E /I /H "%INCLUDE_SRC%\*" "%DST_DIR%"
xcopy /E /I /H "%SRC_SRC%\*" "%DST_DIR%"

:: Change file extensions from .c or .cpp to .ino in the destination directory
for /R "%DST_DIR%" %%F in (*.c *.cpp) do (
    set "file=%%F"
    set "newfile=!file:.c=.ino!"
    set "newfile=!newfile:.cpp=.ino!"
    ren "%%F" "!newfile!"
    echo Renamed "%%F" to "!newfile!"
)

echo All files copied and renamed successfully!
pause
