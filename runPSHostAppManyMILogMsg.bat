%echo off
if %1a==a (set limit=100) else (set limit=%1)
set logfile=pstrout.txt
del %logfile%
echo %limit% calls to PSHostApp 
call timecmd.bat for /L %%%%j IN (1, 1, %limit%) DO PSHostApp\bin\Debug\PSHostApp.exe C:\tmp\moveit\node-thrift-poc\PSHostApp\Sample1.ps1 >>%logfile%
wc %logfile%
ntail -5 %logfile%
