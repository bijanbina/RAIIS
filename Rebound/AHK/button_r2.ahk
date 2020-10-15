WinGet, WinProcessName, ProcessName, A
if (WinProcessName = "firefox.exe")
{
  MouseGetPos, xpos, ypos
  height_half = 600
  mouse_dist := ypos - height_half
  if (mouse_dist < -20 or mouse_dist > 19)
  {
    MouseMove, 0, 10, , R
  }
  else if (mouse_dist = -20 or mouse_dist = 16)
  {
    MouseMove, 0, 4, , R
  }
  else if (mouse_dist = -16 or mouse_dist > 10)
  {
    MouseMove, 0, 2, , R
  }
  else
  {
    MouseMove, 0, 26, , R
  }
  ;MouseGetPos, xpos, ypos
  ;mouse_dist := ypos - height_half
  ;FileAppend, r2: %mouse_dist%`n, D:\Sajad\TEST.txt
}
else
{

}
Return
