
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
            print("The END\n")
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
    wifi.sta.config("Mahdi","12345678")
    tmr.alarm (1,100,1,function() con_to_server() print("connecting...") end)
end

function con_to_server()
    if(wifi.sta.getip() ~= NULL) then
        print("connected to AP")
        conn = net.createConnection(net.TCP, false)
        conn:on("receive", function(conn,pl) a=pl print(pl) onReceive(pl) end)
        conn:on("connection", function(conn) print("connected") tmr.stop(1) end)
        conn:on("reconnection", function(conn) print("reconnected") end)
        conn:on("disconnection", function(conn) print("disconnected") end)
        conn:connect(7778, "192.168.43.1")
    
    end
end

function onReceive(receive)
--[[
    command=tonumber(receive)
    if command<1000 then
        lightOn(command)
    elseif command==1000 then
        play(4)
    end
--]]
    command = receive:sub(1,1) --get first char
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
        -- tear down and convert to int
        color_r = tonumber(receive:sub(2,4))
        color_g = tonumber(receive:sub(5,7))
        color_b = tonumber(receive:sub(8,11))
        print(color_r,color_g,color_b);
        changeColor(color_r,color_g,color_b);
    elseif  command == "4" then
        print("change track");
        tracknumber = tonumber(receive:sub(2,2))
        print(tracknumber);
        play(tracknumber)
    elseif  command == "5" then
        print("stand by");
        --light off
        --music off
    end
end

connect()
