#NoTrayIcon

arg1=%1%
val1=0

if (arg1 = "one")
{
    val1 = 10
}
else if (arg1 = "two")
{
    val1 = 20
}
else if (arg1 = "three")
{
    val1 = 30
}
else if (arg1 = "four")
{
    val1 = 40
}
else if (arg1 = "five")
{
    val1 = 50
}
else if (arg1 = "six")
{
    val1 = 60
}
else if (arg1 = "seven")
{
    val1 = 70
}
else if (arg1 = "eight")
{
    val1 = 80
}
else if (arg1 = "nine")
{
    val1 = 90
}
else if (arg1 = "ten")
{
    val1 = 100
}

if (arg1 = "lower")
{
  Send, {Volume_Down}
  sleep, 200
  Send, {Volume_Down}
  sleep, 200
  Send, {Volume_Down}
  sleep, 200
  Send, {Volume_Down}
}
else if (arg1 = "higher")
{
  Send, {Volume_Up}
  sleep, 200
  Send, {Volume_Up}
  sleep, 200
  Send, {Volume_Up}
  sleep, 200
  Send, {Volume_Up}
}
else
{
	SoundSet, %val1%
}
