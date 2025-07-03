var cadence_gmail = 0;
function main_cadence()
{
    join_timer = setInterval(cadence_timeoutMain, 500);
} 

function cadence_timeoutMain()
{
    if( window.location.href.includes("/CadenceEcomLogin") || 
        window.location.href.includes("/CadenceApplicationLoginScreen") )
    {
		var remember_me = $("input[type='checkbox']");
		//console.log(remember_me);
		if( remember_me.length )
		{
			if (remember_me.is(":checked"))
			{
				var login_btn = $("input[value='Log In']");
				console.log("h", login_btn);
				if( $(login_btn).length )
				{
					alert($(login_btn).length);
					login_btn.click();
                    return;
				}

                login_btn = $("input[value='Login']");
                if( $(login_btn).length )
                {
                    login_btn.click();
                    return;
                }
			}
			else
			{
				remember_me.prop('checked', true);
			}
		}
    }
    else if( window.location.href.includes("cadence.okta.com") )
    {
        var login_btn = $("input[value='Send me an email']");
        if( $(login_btn).length )
        {
                //alert($(login_btn).length);
            login_btn.click();
        }
        
        login_btn = document.querySelector("a[data-se='stay-signed-in-btn']");
		//console.log("h", login_btn);
        if( $(login_btn).length )
        {
            login_btn.click();
        }
		else if( cadence_gmail==0 )
		{
			var ap =  $("h2:contains('Verify with your email')");
			if( ap.length )
			{
				cadence_gmail = 1;
				requestEmailCode("cadence");
			}
		}
    }
}