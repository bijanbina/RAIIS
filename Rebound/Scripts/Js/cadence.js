var cadence_rm_count = 0;
function main_cadence()
{
    join_timer = setInterval(cadence_timeoutMain, 500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
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
		console.log("h", login_btn);
        if( $(login_btn).length )
        {
            login_btn.click();
        }
    }
    else if( window.location.href.includes("/inloggen") )
    {
        var login_btn = $("span:contains('With username')");
        if( $(login_btn).length )
        {
                //alert($(login_btn).length);
            login_btn.click();
        }
        
        var login_btn = $("span:contains('With an SMS')");
        if( $(login_btn).length )
        {
            login_btn.click();
        }
    }
    //var mt          = $('mws-conversation-snippet');
    //var recent_span = mt.find("span").first();
    //var cadence_txt     = recent_span.text();
    //var cadence_digit   = (cadence_txt.match(/\d/g) || []).join('');

    //if( cadence_digit )
    //{
    //    console.log("h", cadence_digit);
    //    navigator.clipboard.writeText(cadence_digit)
    //            .then(() => console.log("Copied!"))
    //}
    //alert("hey");
}