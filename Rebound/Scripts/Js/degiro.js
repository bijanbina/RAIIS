var degiro_timer;
var degiro_page1_done = 0;

function main_degiro()
{
    if( window.location.href.includes("/login/") )
    {
        degiro_timer = setInterval(degiro_timeoutMain, 2000);
    }
}

function degiro_timeoutMain()
{
    var login_btn = $("button:contains('Login')");
    console.log(login_btn.length);
    if( login_btn.length )
    {
        login_btn.click();
    }
}
