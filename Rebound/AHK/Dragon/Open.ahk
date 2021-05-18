#Include Functions.ahk

arg1=%1%

if ( arg1="cute" )
{
    Run, "C:\Qt\Qt5.12.10\Tools\QtCreator\bin\qtcreator.exe", ,
}
else if ( arg1="router" )
{
    Run, "C:\Softwares\AudioRouter\Audio.exe", ,
}
else if ( arg1="editor" )
{
    Run, "C:\Users\Bijan\AppData\Local\atom\atom.exe", ,
}
else if ( arg1="github" )
{
    Run, C:\Users\Bijan\AppData\Local\gitkraken\Update.exe --processStart gitkraken.exe, ,
}
else if ( arg1="skype" )
{
    Run, "C:\Program Files (x86)\Microsoft\Skype for Desktop\Skype.exe", ,
}
else if ( arg1="telegram" )
{
    Run, "C:\Users\Bijan\AppData\Roaming\Telegram Desktop\Telegram.exe", ,
}
else if ( arg1="torrent" )
{
    Run, "C:\Users\Bijan\AppData\Roaming\BitTorrent\BitTorrent.exe", ,
}
else if ( arg1="spotify" )
{
    Run, "C:\Users\Bijan\AppData\Roaming\Spotify\Spotify.exe", ,
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
