Imports Thrift.Transport
Imports Thrift.Protocol
Imports System.Net
Imports System.Web
Imports Newtonsoft.Json
Imports Newtonsoft.Json.Linq

' This obsolete PoC demonstrates VB.NET code that accesses backend functions via Thrift.
' It does not dynamically compile the PoC.

Module CallerAppVB
    Public Class CallerAppCS
        Private Shared Sub Execute(port As Integer)
            Try
                'Console.WriteLine("Entered CallerAppVB")
                'Dim trans As TTransport
                'trans = New TSocket("localhost", port)
                'trans = New TBufferedTransport(trans)
                'trans.Open()

                'Dim Protocol As TProtocol = New TBinaryProtocol(trans, True, True)

                'Dim miaclient As New MIAScriptAPI.Client(Protocol)
                'Console.WriteLine("Instantiated MIAScriptAPI.Client")

                'miaclient.MILogMsg("Greetings from CallerAppVB")

                Dim miaclient As MIAScriptAPI.Client = MIAScriptAPI.CreateMIAScriptAPI(port)

                miaclient.MISetTaskParam("lang", "VB.NET")

                Dim retrievedLang As String = miaclient.MIGetTaskParam("lang")
                'Console.WriteLine("MIGetTaskParam(""lang"") returned " & retrievedLang)
                miaclient.MILogMsg("MIGetTaskParam(""lang"") returned " & retrievedLang)


                Try
                    Dim shortUrl As String = "http://goo.gl/P79A" 'emb.MIGetTaskParam("shortUrl")
                    Dim apiKey As String = "AIzaSyDTPo98q-znej3o0uVYPowN6Njy565pIBw"
                    Dim req As System.Net.HttpWebRequest
                    Dim url As String = "https://www.googleapis.com/urlshortener/v1/url?shortUrl=" + HttpUtility.UrlEncode(shortUrl) + "&key=" + apiKey
                    Dim targetURI As New Uri(url)

                    req = DirectCast(HttpWebRequest.Create(targetURI), System.Net.HttpWebRequest)
                    If (req.GetResponse().ContentLength > 0) Then
                        Dim str As New System.IO.StreamReader(req.GetResponse().GetResponseStream())
                        Dim jsonResp As String = str.ReadToEnd()
                        str.Close()

                        Dim objJson As JObject = JObject.Parse(jsonResp)
                        Dim longURL As String = objJson.GetValue("longUrl")
                        Console.WriteLine("longURL=" & longURL)
                    End If
                Catch ex As System.Net.WebException
                    'Error in accessing the resource, handle it
                    Console.WriteLine("Exception: " & ex.Message)
                End Try

                'Console.WriteLine("About to close transport")
                'trans.Close()
            Catch e As Exception
                Console.WriteLine(e.Message)
            End Try
        End Sub

        Public Shared Sub Main(args As String())
            Dim port As Integer = 9090
            If args.Length > 0 Then
                port = UShort.Parse(args(0))
            End If
            Execute(port)
            Console.WriteLine("done.")
        End Sub

    End Class
End Module
