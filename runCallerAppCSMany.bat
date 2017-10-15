%echo off
if %1a==a (set limit=100) else (set limit=%1)
del csout.txt
echo %limit% calls to CallerAppCS 
call timecmd.bat for /L %%%%j IN (1, 1, %limit%) DO vc2017be\CallerAppCS\bin\Debug\CallerAppCS.exe c:\tmp\moveit\node-thrift-poc\callerappvb\class1.vb >>csout.txt
wc csout.txt
ntail -5 csout.txt
