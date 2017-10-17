%echo off
if %1a==a (set limit=100) else (set limit=%1)
del cstrout.txt
echo %limit% calls to CallerAppCS 
call timecmd.bat for /L %%%%j IN (1, 1, %limit%) DO CallerAppCS\bin\Debug\CallerAppCS.exe c:\tmp\moveit\node-thrift-poc\callerappvb\ClassTrivial.vb >>cstrout.txt
wc cstrout.txt
ntail -5 cstrout.txt
