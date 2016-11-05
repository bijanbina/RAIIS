buffer = ""
rainbow_r = 0;
rainbow_g = 100;
rainbow_b = 200;
rainbow_direction_r = 1;
rainbow_direction_g = 1;
rainbow_direction_b = -1;
device_id = 1;
wifi_name = "JAB";
wifi_pass = "12345678";

--timer table
--tmr0: rainbow
--tmr1: Auto Ap Connect
--tmr2: createAP
--tmr5: con_to_server
dofile("functionV2.lc")

print("Version: 1.4")
bootup()
