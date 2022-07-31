' Set your settings
strFileURL = "http://127.0.0.1:9222/json/list"
strHDLocation = "list.json"

' Fetch the file
Set objXMLHTTP = CreateObject("MSXML2.XMLHTTP")

objXMLHTTP.open "GET", strFileURL, false
objXMLHTTP.send()

If objXMLHTTP.Status = 200 Then
	Set objADOStream = CreateObject("ADODB.Stream")
	objADOStream.Open
	objADOStream.Type = 1 'adTypeBinary

	objADOStream.Write objXMLHTTP.ResponseBody
	objADOStream.Position = 0    'Set the stream position to the start

	Set objFSO = CreateObject("Scripting.FileSystemObject")
	If objFSO.Fileexists(strHDLocation) Then objFSO.DeleteFile strHDLocation
		Set objFSO = Nothing

	objADOStream.SaveToFile strHDLocation
	objADOStream.Close
	Set objADOStream = Nothing
End if

Set objXMLHTTP = Nothing
