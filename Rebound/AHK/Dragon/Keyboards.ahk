#Include Functions.ahk

arg1=%1%

if ( arg1="bottom" )
{
    Send, ^{End}
}
else if( arg1 =="delete" )
{
    Send, {Delete}
}
else if( arg1 =="departure" )
{
    RegWrite, REG_SZ, HKEY_CURRENT_USER\Software\WBT\Rebound, Direction, stop
    Send, {Esc}
}
else if( arg1 =="dive" )
{
    Send, {Down}
}
else if( arg1 =="end" )
{
    Send, {End}
}
else if( arg1="next" )
{
    Send, {PgDn}
}
else if( arg1="love" )
{
    Send, ^{Left}
    Send, {Left}
}
else if( arg1="makeup" )
{
    Send, {AppsKey}
}
else if( arg1="replace" )
{
    Send, {End}
    Send, {Shift down}{Home}{Shift up}
    Send, ^v
}
else if( arg1="roger" )
{
    Send, ^{Right}
}
else if( arg1="sim" )
{
    Send, {Space}
}
else if( arg1="sky" )
{
    Send, {Up}
}
else if( arg1="slap" )
{
    Send, {Enter}
}
else if( arg1="top" )
{
    Send, ^{Home}
}
