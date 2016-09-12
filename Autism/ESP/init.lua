buffer = ""
rainbow_r = 0;
rainbow_g = 100;
rainbow_b = 200;
rainbow_direction_r = 1;
rainbow_direction_g = 1;
rainbow_direction_b = -1;
device_id = 2;

--timer table
--tmr0: rainbow
--tmr2: createAP
--tmr5: con_to_server
dofile("function.lc")

print("Version: 1.22")
bootup()
