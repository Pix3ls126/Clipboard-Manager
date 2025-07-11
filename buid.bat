@echo off
echo Building Clipboard Manager...
gcc -o clipboard_manager.exe main.c
if %ERRORLEVEL% == 0 (
    echo Build successful!
    echo Run clipboard_manager.exe to start the application
) else (
    echo Build failed!
)
pause
