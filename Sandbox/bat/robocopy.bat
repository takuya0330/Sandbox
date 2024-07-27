@echo off
@setlocal

pushd %~dp0

set SRC_PATH=%1
set DST_PATH=%2
set TARGET=%3

robocopy %SRC_PATH% %DST_PATH% %TARGET%
if not %ERRORLEVEL%==1 ( goto :Error )

echo SUCCESS: robocopy successed.
exit /b 0

:Error
echo ERROR: robocopy failed. [ERRORLEVEL=%ERRORLEVEL%]
exit /b %ERRORLEVEL%