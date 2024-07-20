$url = "https://binaee.com/ip"
$output = "ip"
$batPath = "rpi.bat"

$webclient = New-Object System.Net.WebClient
$webclient.DownloadFile($url, $output)

# Read the second line of the file
$secondLine = Get-Content -Path $output | Select-Object -Index 1
$ipAddress = $secondLine.Split(' ')[0]

# Output the extracted IP address
Write-Output $ipAddress
Remove-Item -Path $output -Force

# Define the content for the output file
$content = @"
@ECHO OFF
MODE con:cols=120 lines=30
:lolo
ssh -o StrictHostKeyChecking=no -q -D *:8888 -p 6702 bijan@$ipAddress
goto lolo
"@

# Write the content to the output file
Set-Content -Path $batPath -Value $content

Invoke-Expression -Command "& .\$batPath"
# Write-Host -NoNewLine 'Press any key to continue...';
# $null = $Host.UI.RawUI.ReadKey('NoEcho,IncludeKeyDown');
# Start-Sleep -Seconds 15.5