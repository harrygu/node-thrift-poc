Imports System
Imports System.Uri
Imports System.Net
Imports System.Web

Imports Newtonsoft.Json.Linq
'Imports MIAScriptAPI

' Sample script to demonstrate the proof-of-concept that hosts VB.NET as a scripting language.
' This script is compiled and executed at runtime by a "client" that connects to a backend server
' that has the actual implementation of the MIxxx methods.

Public Class Class1
    Public Sub Sub1(miaClient As MIAScriptAPI.Client)
        Console.WriteLine("hi from trivial")
    End Sub
End Class
