--receive = "1"
--receive = "2"
--receive = "3255241211"
receive = "43"
--receive = "5"
command = receive:sub(1,1) --get first char
if      command == "1" then 
    print("light on");
elseif  command == "2" then
    print("music on");
elseif  command == "3" then
    print("change color");
    -- tear down and convert to int
    color_r = tonumber(receive:sub(2,4))
    color_g = tonumber(receive:sub(5,7))
    color_b = tonumber(receive:sub(8,11))
    print(color_r,color_g,color_b);
elseif  command == "4" then
    print("change track");
    tracknumber = tonumber(receive:sub(2,2))
    print(tracknumber);
elseif  command == "5" then
    print("stand by");
end
