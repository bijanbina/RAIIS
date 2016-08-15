
function lightOn()
    pwm.setup(6,100,100) 
    pwm.setup(7,100,100) 
    pwm.setup(8,100,100)
    pwm.start(6) 
    pwm.start(7) 
    pwm.start(8)
end

function lightOff()
    tmr.stop(0)
    pwm.stop(6) 
    pwm.stop(7) 
    pwm.stop(8)
end

function changeColor( r, g, b )
    pwm.setduty(6,b) 
    pwm.setduty(7,r) 
    pwm.setduty(8,g) 
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

function respond_new_device(conn)
		conn:send("1")
end
