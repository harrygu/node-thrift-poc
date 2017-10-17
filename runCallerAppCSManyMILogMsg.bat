%echo off
if %1a==a (set limit=100) else (set limit=%1)
set logfile=cslogout.txt
del %logfile%
echo %limit% calls to CallerAppCS 
call timecmd.bat for /L %%%%j IN (1, 1, %limit%) DO CallerAppCS\bin\Debug\CallerAppCS.exe c:\tmp\moveit\node-thrift-poc\callerappvb\ClassMILogMsg.vb >>%logfile%
wc %logfile%
ntail -5 %logfile%
