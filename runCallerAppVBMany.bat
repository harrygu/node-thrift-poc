%echo off
if %1a==a (set limit=100) else (set limit=%1)
del vbout.txt
echo %limit% calls to CallerAppVB 
call timecmd.bat for /L %%%%j IN (1, 1, %limit%) DO CallerAppVB\bin\Debug\CallerAppVB.exe >>vbout.txt
wc vbout.txt
ntail -5 vbout.txt
