#Include Functions.ahk
arg1=%1%
arg2=%2%

count := re_getNum(arg2)
i := 0

while ( i<count )
{
    i := i+1
    if ( arg1=="next" )
    {
      Send, {Media_Next}
    }
    else if( arg1=="prev" )
    {
      Send, {Media_Prev}
    }
    sleep, 100
}

if ( arg1=="next" )
{
  Send, {Media_Prev}
}
else if( arg1=="prev" )
{
  Send, {Media_Prev}
}
