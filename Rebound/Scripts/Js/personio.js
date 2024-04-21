var personio_timer;
var personio_page1_done = 0;

function main_personio()
{
    if( window.location.href.includes("login/index") )
    {
        personio_timer = setInterval(personio_timeoutMain, 2000);
    }
}

function personio_timeoutMain()
{
    var login_btn = $("div:contains('Login')");
    var login_btn_pr = login_btn.parent().parent();
    //alert(login_btn_pr.length);
    if( login_btn_pr.length )
    {
        login_btn_pr.last().click();
    }
}
