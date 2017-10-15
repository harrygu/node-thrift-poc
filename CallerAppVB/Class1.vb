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
        Try
            ' The user will have configured this task parameter to a value like "http://goo.gl/P79A".
            Dim shortUrl As String = miaClient.MIGetTaskParam("shortUrl")
            Dim apiKey As String = "AIzaSyDTPo98q-znej3o0uVYPowN6Njy565pIBw"

            Dim url As String = "https://www.googleapis.com/urlshortener/v1/url?shortUrl=" + HttpUtility.UrlEncode(shortUrl) + "&key=" + apiKey
            Dim targetURI As New Uri(url)
            Dim req As System.Net.HttpWebRequest = DirectCast(HttpWebRequest.Create(targetURI), System.Net.HttpWebRequest)
            If (req.GetResponse().ContentLength > 0) Then
                Dim streamR As New System.IO.StreamReader(req.GetResponse().GetResponseStream())
                Dim jsonResp As String = streamR.ReadToEnd()
                streamR.Close()

                ' Use a third-party JSON library to decode the response from Google.
                Dim objJson As JObject = JObject.Parse(jsonResp)
                Dim longURL As String = objJson.GetValue("longUrl")
                miaClient.MISetTaskParam("longUrl", longURL)
                miaClient.MILogMsg("Google API decoded " & shortUrl & " to " & longURL)
            End If
        Catch ex As System.Net.WebException
            miaClient.MILogMsg("VB: Exception: " & ex.Message)
        End Try
    End Sub
End Class
