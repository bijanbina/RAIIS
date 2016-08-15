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

function play(n) --n: music number
    array=init(n);
    send(array);
end
