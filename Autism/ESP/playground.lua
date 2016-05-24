receive = "hello world\n"
receive = receive .. "what the\n fuck\n"
print(receive);
buffer = "hi "
command = receive:sub(1,1) --get first char
print("=========begin test=========")
lastInter = 1
for i=1,receive:len() do
    if receive:sub(i,i) == '\n' then
        buffer = buffer .. receive:sub(lastInter,i-1)
        print(buffer)
        buffer = ""
        lastInter = i+1
    end
end
buffer = buffer .. receive:sub(lastInter,receive:len())
print(buffer)
if      command == "1" then 
    print("light on");
elseif  command == "2" then
    print("music on");
    --play last music
    --FIXME
    --play a default
    play(1)
elseif  command == "3" then
    print("change color");
    --print(tostring(receive:len()));
elseif  command == "4" then
    print("change track");
elseif  command == "5" then
    print("stand by");
elseif  command == "6" then
    print("music off");
elseif  command == "7" then
    print("switch off");
end
