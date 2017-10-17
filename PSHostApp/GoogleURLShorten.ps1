# This embedded PowerShell script uses the Google URL Shortener API to decode a URL.
# The script is called with a connected miaclient object, which is used to do RPC calls
# to the (emulated) MIxxx functions on the backend.
#
$apiKey = "AIzaSyDTPo98q-(truncated)"
# Obtain the task parameter from the server.
$shortUrl = $miaclient.MIGetTaskParam("shortUrl")
# Awkward way of loading assembly needed for UrlEncode:
[Reflection.Assembly]::LoadWithPartialName("System.Web") | Out-Null
$encodedShortUrl =  [System.Web.HttpUtility]::UrlEncode($shortUrl)
$uri = "https://www.googleapis.com/urlshortener/v1/url?shortUrl=" + $encodedShortUrl + "&key=" + $apiKey
# Make the HTTP request to Google.
$resp = Invoke-RestMethod -Method Get -Uri $uri 
# Parse out the desired piece of info from the response.
$longUrl = $resp.longUrl
# Send the longUrl to the backend server as a task parameter.
$miaclient.MISetTaskParam("longUrl", $longUrl)
$miaclient.MILogMsg("Google decoded " + $shortUrl + " to " + $longUrl)
