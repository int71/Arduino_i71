@echo off
net session >NUL 2>nul
if %errorlevel% neq 0 (
	@powershell -Command "Start-Process cmd -ArgumentList /C,'cd /D %cd%&""%~0""' -Verb Runas"
	exit
)
rmdir /S /Q "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino"
xcopy /E /I /K "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino.org" "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino"
pause
