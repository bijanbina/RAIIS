var canada_rm_count = 0;
function main_canada()
{
    join_timer = setInterval(canada_timeoutMain, 2500);
} 


function canada_timeoutMain()
{
    if( window.location.href.includes("/en/login") )
    {
        var login_btn = $("#uci");
        if( login_btn.length )
        {
            //alert($(login_btn).length);
            login_btn.val("1107171737");
        }
    }
}