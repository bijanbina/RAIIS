buffer = ""
rainbow_r = 0;
rainbow_g = 100;
rainbow_b = 200;
rainbow_direction_r = 1;
rainbow_direction_g = 1;
rainbow_direction_b = -1;

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

function wifiSetup(t)
    wifiFound = 0
    for k,v in pairs(t) do
        if k == "JAB" then
            wifiFound = 1
        end
    end
    if wifiFound == 1 then
        print("WiFi found")
        wifi.setmode(wifi.STATION)
        cfg =
        {
            ip="192.168.4.20",
            netmask="255.255.255.0",
            gateway="192.168.4.255"
        }
        wifi.sta.setip(cfg)
        wifi.sta.config("JAB","12345678")
        wifi.sta.connect()
        tmr.alarm (5,333,1,function() con_to_server() end)
    else
        print("Create AP")
        wifi.setmode(wifi.SOFTAP)
        cfg={}
        cfg.ssid="JAB"
        cfg.pwd="12345678"
        wifi.ap.config(cfg)
        createServer()
    end
end

function bootup()
    wifi.setmode(wifi.STATION)
    wifi.sta.getap(wifiSetup)
end

function createServer()
    sv = net.createServer(net.TCP, 28700)
    sv:listen(7778, clientConnected)
end

function clientConnected(conn)
      conn:on("receive", onReceive)
      conn:send("command:")
      print("Client Connected")
end

function con_to_server()
    if(wifi.sta.getip() ~= NULL) then
        print("connected to AP")
        print("IP Address: ",wifi.sta.getip())
        createServer()
        tmr.stop(5)
    end
end

function play(n) --n: music number
    array=init(n);
    send(array);
end
