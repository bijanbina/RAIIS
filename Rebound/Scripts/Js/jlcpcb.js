var jlcpcb_rm_count = 0;
function main_jlcpcb()
{
    jlcpcb_rm_count = 2;
    join_timer = setInterval(jlcpcb_timeoutMain, 5000);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function jlcpcb_timeoutMain()
{
	var list = document.querySelectorAll('[id^="el-popover-"]:not(.global-style-user-popover)');

	for( var i=1 ; i<list.length ; i++ )
	{
		//list[i].remove();
	}

	var homeDiv = $("#home_sign\\ in");
	if( homeDiv.length ) 
	{
		//homeDiv.trigger("mouseenter");
		window.location.href = "https://passport.jlcpcb.com/#/login?response_type=code&client_id=34495309ae47483ebf71827b5bcb591c&redirect_url=https%3A%2F%2Fjlcpcb.com%2Fapi%2Fauth%2Flogin%3F_t%3D1754921237854%2526spm%3DJlcpcb.Homepage%2526up_spm%3DJlcpcb.Loginpage.1003&state=xdnhVJ%2B2eczbnoK847%2B2A1P2QoVosK3%2FeZPps9Jm%2FUFJcxXy%2BfErLUDN7I%2FjaQ%2BWYNh4byhwAZ9hW9%2BNIgJpffpA%2FrXhTXm9cbNY4SsE%2FBhWnOB9kFA7QTy7WhInWrfQl20iA5N8eUKNsR6ENBxMKre7KIquREx5fvvBL8aVgAE0omrCSiiDuRFZq2QPiu0q&from=jlcpcb&registerLang=en";
	}

    if( window.location.href.includes("login?response_type") )
    {
        var login_btn = $("button.el-button.public-login-btn.el-button--default");
        if( $(login_btn).length )
        {
            //alert($(login_btn).length);
            login_btn[0].click();
        }
    }
}