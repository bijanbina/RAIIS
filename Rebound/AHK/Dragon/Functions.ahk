re_getNum(text)
{
    if ( text=="one" )
    {
        return 1
    }
    else if( text=="two" )
    {
        return 2
    }
    else if( text=="three" )
    {
        return 3
    }
    else if( text=="four" )
    {
        return 4
    }
    else if( text=="five" )
    {
        return 5
    }
    else if( text=="six" )
    {
        return 6
    }
    else if( text=="seven" )
    {
        return 7
    }
    else if( text=="eight" )
    {
        return 8
    }
    else if( text=="nine" )
    {
        return 9
    }
    else if( text=="ten" )
    {
        return 10
    }
    else if( text=="eleven" )
    {
        return 11
    }
    else if( text=="twelve" )
    {
        return 12
    }
    else if( text=="thirteen" )
    {
        return 13
    }
    else if( text=="fourteen" )
    {
        return 14
    }
    else if( text=="fifteen" )
    {
        return 15
    }
    else if( text=="sixteen" )
    {
        return 16
    }
    else if( text=="seventeen" )
    {
        return 17
    }
    else if( text=="eighteen" )
    {
        return 18
    }
    else if( text=="nineteen" )
    {
        return 19
    }
    else if( text=="twenty" )
    {
        return 20
    }
    else
    {
        return -1
    }
}

re_getWheelSpeed(text)
{
    if( text=="one" )
    {
        return 14
    }
    else if( text=="two" )
    {
        return 16
    }
    else if( text=="three" )
    {
        return 20
    }
    else if( text=="four" )
    {
        return 24
    }
    else if( text=="five" )
    {
        return 30
    }
    else if( text=="six" )
    {
        return 36
    }
    else if( text=="seven" )
    {
        return 42
    }
    else if( text=="eight" )
    {
        return 50
    }
    else if( text=="nine" )
    {
        return 60
    }
    else if( text=="ten" )
    {
        return 70
    }
    else
    {
        MsgBox This command is not recognized %arg1% %text%.
    }
}
