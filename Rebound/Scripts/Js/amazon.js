var amazon_gmail = 0;
function main_amazon()
{
    join_timer = setInterval(amazon_timeoutMain, 500);
} 

function amazon_timeoutMain()
{
    if( window.location.href.includes("&referrer=prime") )
    {
        var ap =  $("span:contains('No thanks, continue and don't gain Amazon Prime benefits')");
        if( ap.length )
        {
				var login_btn = ap.last().parent();
				console.log("h", login_btn);
				if( $(login_btn).length )
				{
					login_btn[0].click();
                    return;
				}
        }
    }
}