
device_id = 1;
start_search = 0;
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
            ip="192.168.4.205",
            netmask="255.255.255.0",
            gateway="192.168.4.255"
        }
        wifi.sta.setip(cfg)
        wifi.sta.config("JAB","12345678")
        wifi.sta.connect()
        tmr.alarm (5,333,1,con_to_server)
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
        tmr.stop(5)
        print("connected to AP")
        print("IP Address: ",wifi.sta.getip())
        if (_G[start_search] == 0) then --if search is not started
          print("inside search")
        	_G[start_search] = 1	--lets do it
					srv = net.createConnection(net.TCP, 0)
					srv:on("receive", onRecieve_test_device)
					srv:connect(80,"192.168.4." .. (19+_G[device_id]))
					srv:on("connection", connected_test_device)
        	tmr.alarm (3,333,tmr.ALARM_AUTO,timesUp_test_device)
        else --free ip is founded
        	createServer()
            print("Fuck You")
            print(_G[start_search])
        end
		end
end

function connected_test_device(sck, c)
    sck:send("20\n")
end

function onRecieve_test_device(sck, c)
		tmr.stop(3)
    print(c)
    _G[device_id] = _G[device_id] + 1
    srv = net.createConnection(net.TCP, 0)
		srv:on("receive", onRecieve_test_device)
		srv:connect(80,"192.168.4." .. (19+_G[device_id]))
		srv:on("connection", connected_test_device)
  	tmr.alarm (3,333,tmr.ALARM_AUTO,timesUp_test_device)
end

function timesUp_test_device()
	  tmr.stop(3)
    print("Times up")
    --assume id is free
    _G[device_id] = _G[device_id] + 1
	  wifi.sta.disconnect()
		cfg =
		{
			  ip="192.168.4." .. (19+_G[device_id]),
			  netmask="255.255.255.0",
			  gateway="192.168.4.255"
		}
	
	  wifi.sta.setip(cfg)
	  wifi.sta.config("JAB","12345678")
	  wifi.sta.connect()
	  tmr.alarm (5,333,1,con_to_server)
end
