function send(a)
    gpio.write(clk,gpio.LOW)
    tmr.delay(2000)
   -- print(gpio.read(clk)..gpio.read(rst)..gpio.read(di))
    for j=15,0,-1 do
		gpio.write(clk,gpio.LOW)
        tmr.delay(50)
        gpio.write(di,a[j])
        tmr.delay(50)
        gpio.write(clk,gpio.HIGH)
        tmr.delay(100)
		if j>0 then
			tmr.delay(2)
        --    print("The END\n")
		end
	end
	tmr.delay(20000)
end

function init(addr)
    clk=0
    di=1
    rst=2
    cntr=0
    j=15
    local a={}
    for i=0,15,1 do
        t=addr%2
        addr=addr/2
        t=math.floor(t)
        if t==0 then
            a[i]=gpio.LOW
        else
            a[i]=gpio.HIGH
        end
    end
    gpio.mode(clk,gpio.OUTPUT)
    gpio.mode(di,gpio.OUTPUT)
    gpio.mode(rst,gpio.OUTPUT)
    gpio.write(clk,gpio.HIGH)
    gpio.write(di,gpio.HIGH)
    gpio.write(rst,gpio.HIGH)
    return a
end

function lightOn()
    pwm.setup(6,100,100) 
    pwm.setup(7,100,100) 
    pwm.setup(8,100,100)
    pwm.start(6) 
    pwm.start(7) 
    pwm.start(8)
end

function lightOff()
    pwm.stop(6) 
    pwm.stop(7) 
    pwm.stop(8)
end

function changeColor( r, g, b )
    pwm.setduty(6,r) 
    pwm.setduty(7,g) 
    pwm.setduty(8,b) 
end
function play(n) --n: music number
    array=init(n);
    send(array);
end

function connect()
    wifi.setmode(wifi.STATION)
    --wifi.sta.config("Mahdi","12345678")
    print("connect")
    cfg =
    {
        ip="172.18.132.81",
        netmask="255.255.255.0",
        gateway="172.18.132.1"
    }
    wifi.sta.setip(cfg)
    wifi.sta.config("ECE-Department","toB0rnot2be")
    wifi.sta.connect()
    print("hi")
    tmr.alarm (5,333,1,function() con_to_server() end)
end

function createServer()
	sv = net.createServer(net.TCP, 28700)
	sv:listen(7778, clientConnected)
end

function clientConnected(conn)
	  conn:on("receive", onReceive)
	  conn:send("Welcome\n")
end

function con_to_server()
    if(wifi.sta.getip() ~= NULL) then
        print("connected to AP")
        print("IP Address: ",wifi.sta.getip())
		createServer()
        tmr.stop(5)
    end
end

function music_off()
--[[clk=0
    di=1
    rst=2
    cntr=0
    gpio.mode(clk,gpio.OUTPUT)
    gpio.mode(di,gpio.OUTPUT)
    gpio.mode(rst,gpio.OUTPUT)
    gpio.write(clk,gpio.HIGH)
    gpio.write(di,gpio.HIGH)
    gpio.write(rst,gpio.HIGH)
--]]
	play(0xFFFF);
end

function onReceive(conn,receive)
--[[
    command=tonumber(receive)
    if command<1000 then
        lightOn(command)
    elseif command==1000 then
        play(4)
    end
--]]
    if (receive == nil or receive == '') then
        return
        print("Receive Data is not nil")
    end
    command = receive:sub(1,1) --get first char
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
        --print(tostring(receive:len()));
        if (receive:len() == 11) or (receive:len() == 13) then
            -- tear down and convert to int
            color_r = tonumber(receive:sub(2,4))
            color_g = tonumber(receive:sub(5,7))
            color_b = tonumber(receive:sub(8,11))
            print(color_r,color_g,color_b);
            changeColor(color_r,color_g,color_b);
        else
            conn:send("error: color format is not right\n");
        end
    elseif  command == "4" then
        print("change track");
        if (receive:len() == 2)  or (receive:len() == 4) then
            tracknumber = tonumber(receive:sub(2,2))
            print(tracknumber);
            play(tracknumber)
        else
            conn:send("error: track format is not right\n");
         end
    elseif  command == "5" then
        print("stand by");
        --light off
        --music off
        music_off()
        lightOff()
    elseif  command == "6" then
        print("music off");
        music_off()
        lightOff()
    elseif  command == "7" then
        print("switch off");
        music_off()
        lightOff()
    end
    conn:send("command:")
end

print("Version: 0.12")
connect()
