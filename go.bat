@echo off
cls
call build.bat
echo.
echo /* --- build complete --- */
echo.
call "bin/lucca.exe"
