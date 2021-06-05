#Include Functions.ahk

arg1=%1%
EnvGet, UserPath, USERPROFILE

if ( arg1="audacity" )
{
    Run, C:\Program Files (x86)\Audacity\audacity.exe, C:\Program Files (x86)\Audacity,
}
else if ( arg1="cute" )
{
    Run, "C:\Qt\Qt5.12.10\Tools\QtCreator\bin\qtcreator.exe", ,
}
else if ( arg1="element" )
{
    Run, C:\Users\Bijan\AppData\Local\element-desktop\Element.exe, C:\Users\Bijan\AppData\Local\element-desktop\app-1.7.29,
}
else if ( arg1="router" )
{
    Run, "C:\Softwares\AudioRouter\Audio.exe", ,
}
else if ( arg1="editor" )
{
    Run, %UserPath%\AppData\Local\atom\atom.exe, ,
}
else if ( arg1="github" )
{
    Run, %UserPath%\AppData\Local\gitkraken\Update.exe --processStart gitkraken.exe, ,
}
else if ( arg1="skype" )
{
    Run, "C:\Program Files (x86)\Microsoft\Skype for Desktop\Skype.exe", ,
}
else if ( arg1="telegram" )
{
    Run, "%UserPath%\AppData\Roaming\Telegram Desktop\Telegram.exe", ,
}
else if ( arg1="torrent" )
{
    Run, %UserPath%\AppData\Roaming\BitTorrent\BitTorrent.exe, ,
}
else if ( arg1="spotify" )
{
    Run, %UserPath%\AppData\Roaming\Spotify\Spotify.exe, ,
}
else if ( arg1="virtual" )
{
    Run, "D:\Program Files (x86)\VMware\VMware Workstation\vmware.exe", ,
}
else if ( arg1="words" )
{
    EnvGet, ReboundPath, RE_PATH
    Run, %ReboundPath%\..\..\Assistant\App\release\gallery.exe, %ReboundPath%\..\..\Assistant\App\release,
}
