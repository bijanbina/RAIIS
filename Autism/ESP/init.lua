buffer = ""
rainbow_r = 0;
rainbow_g = 100;
rainbow_b = 200;
rainbow_direction_r = 1;
rainbow_direction_g = 1;
rainbow_direction_b = -1;

--timer table
--tmr0: rainbow
--tmr3: connect to test device
--tmr5: connect tabledofile("include.lua");
dofile("wifi.lua");
dofile("command_list.lua");

function interpret(conn,string)
    command = string:sub(1,1) --get first char
    print(command)
    if      command == "1" then 
        print("light on");
        lightOn()
    elseif  command == "2" then
        print("music on");
        --play last music
        --FIXME
        --play a default
        play(1)
    elseif  command == "3" then
        print("change color");
        --print(tostring(string:len()));
    if (string:len() >= 10) then
            -- tear down and convert to int
            color_r = tonumber(string:sub(2,4))
            color_g = tonumber(string:sub(5,7))
            color_b = tonumber(string:sub(8,10))
            print(color_r,color_g,color_b);
            changeColor(color_r,color_g,color_b);
        else
            conn:send("error: color format is not right\n");
        end
    elseif  command == "4" then
        print("change track");
        if (string:len() == 2)  or (string:len() == 4) then
            tracknumber = tonumber(string:sub(2,2))
            print(tracknumber);
            play(tracknumber)
        else
            conn:send("error: track format is not right\n");
         end
    elseif  command == "5" then
        print("stand by");
        music_off()
        lightOff()
    elseif  command == "6" then
        print("music off");
        music_off()
    elseif  command == "7" then
        print("light off");
        lightOff()
    elseif  command == "8" then
        print("rainbow");
        rainbow()
    elseif  command == "20" then
        print("Device Checking...");
        respond_new_device(conn)
    end
end

function onReceive(conn,receive)
    if (receive == nil or receive == '') then
        return
        print("Receive Data is not nil")
    end
    lastInter = 1
    for i=1,receive:len() do
        if receive:sub(i,i) == '\n' then
            --print("recieve is: ",receive:len())
            buffer = buffer .. receive:sub(lastInter,i-1)
            --print("buffer is: ",buffer)
            interpret(conn,buffer)
            buffer = ""
            lastInter = i+1
        end
    end
    buffer = buffer .. receive:sub(lastInter,receive:len())
    conn:send("command:")
end

print("Version: 0.83")
bootup()

