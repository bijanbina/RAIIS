function send(a)
    gpio.write(clk,gpio.LOW)
    tmr.delay(2000)
    for j=15,0,-1 do
        gpio.write(clk,gpio.LOW)
        tmr.delay(50)
        gpio.write(di,a[j])
        tmr.delay(50)
        gpio.write(clk,gpio.HIGH)
        tmr.delay(100)
        if j>0 then
            tmr.delay(2)
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
    pwm.setduty(6,b) --abi
    pwm.setduty(7,r)   --ghermez
    pwm.setduty(8,g)  --sabz
end

function createAP()
    print("Create AP")
    wifi.setmode(wifi.SOFTAP)
    cfg={}
    cfg.ssid=wifi_name
    cfg.pwd=wifi_pass
    wifi.ap.config(cfg)
    cfg_ip =
    {
      ip="192.168.1." .. (20+device_id),
      netmask="255.255.255.0",
      gateway="192.168.1.21"
    }
    print("Server Address: " .. cfg_ip.ip)
    wifi.ap.setip(cfg_ip)
    dhcp_config ={}
    dhcp_config.start = "192.168.1.100"
    wifi.ap.dhcp.config(dhcp_config)
    createServer()
end

function wifiSetup(t)
    wifiFound = 0
    for k,v in pairs(t) do
        if k == wifi_name then
            wifiFound = 1
        end
    end
    if wifiFound == 1 then
        print("WiFi found")
        wifi.setmode(wifi.STATION)
        cfg =
        {
            ip="192.168.1." .. (20+device_id),
            netmask="255.255.255.0",
            gateway="192.168.1.21"
        }
        wifi.sta.setip(cfg)
        wifi.sta.config(wifi_name,wifi_pass)
        wifi.sta.connect()
        tmr.alarm (5,333,1,con_to_server)
        
    else
        tmr.alarm(2, 5000, tmr.ALARM_SINGLE, createAP)
        print("Timer Created")
    end
end

function bootup()
    wifi.setmode(wifi.STATION)
    wifi.sta.getap(wifiSetup)
end

function createServer()
    sv = net.createServer(net.TCP, 28700)
    sv:listen(7778, clientConnected)
    print("Port opened on 7778")
end

function clientConnected(conn)
      conn:on("receive", onReceive)
      conn:send("command:")
      print("Client Connected")
end

function con_to_server()
    if(wifi.sta.getip() ~= NULL) then
        tmr.stop(5)
        print("connected to AP")
        print("IP Address: ",wifi.sta.getip())
            createServer()
        print("Server Ready")
        end
end

function play(n) --n: music number
    array=init(n);
    send(array);
end

function music_off()
    play(0xFFFF);
end

function rainbow_timer()
    if _G[rainbow_r] > 150 then
        rainbow_direction_r = -1
    elseif _G[rainbow_r] < 3 then
        rainbow_direction_r = 1
    end
    if _G[rainbow_g] > 150 then
        rainbow_direction_g = -1
    elseif _G[rainbow_g] < 3 then
        rainbow_direction_g = 1
    end
    if _G[rainbow_b] > 150 then
        rainbow_direction_b = -1
    elseif _G[rainbow_b] < 3 then
        rainbow_direction_b = 1
    end
    _G[rainbow_r] = _G[rainbow_r] + rainbow_direction_r * 1;
    _G[rainbow_g] = _G[rainbow_g] + rainbow_direction_g * 1;
    _G[rainbow_b] = _G[rainbow_b] + rainbow_direction_b * 1;
    changeColor(_G[rainbow_r],_G[rainbow_g],_G[rainbow_b])
    -- print (_G[rainbow_r],_G[rainbow_g],_G[rainbow_b])
end

function rainbow()
    _G[rainbow_r] = 0;
    _G[rainbow_g] = 70;
    _G[rainbow_b] = 150;
    rainbow_direction_r = 1;
    rainbow_direction_g = 1;
    rainbow_direction_b = -1;
    tmr.alarm(0, 100, tmr.ALARM_AUTO, rainbow_timer)
end

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
            conn:send("error: color format is not right\r\ncommand:");
        end
    elseif  command == "4" then
        print("change track");
        if (string:len() == 2)  or (string:len() == 4) then
            tracknumber = tonumber(string:sub(2,2))
            print(tracknumber);
            play(tracknumber)
        else
            conn:send("error: track format is not right\r\ncommand:");
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
    end
end

function onReceive(conn,receive)
    if (receive == nil or receive == '') then
        return
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


