var gitlab_timer;
var gitlab_page1_done = 0;

function main_gitlab()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    gitlab_timer = setInterval(gitlab_timeoutMain, 2000);
}

function gitlab_timeoutMain()
{
    //if( window.location.href.includes("bestel") )
    //{
    //    if( ijburg_page1_done )
    //    {
    //        var delivery_btn = $("button:contains('Search')");
    //        if( $(delivery_btn).length )
    //        {
    //            delivery_btn[0].click();
    //            ijburg_page1_done = 1;
    //        }
    //    }
    //    else
    //    {
    //        var delivery_btn = $("a:contains('Delivery')");
    //        if( $(delivery_btn).length )
    //        {
    //            delivery_btn[0].click();
    //            ijburg_page1_done = 1;
    //        }
    //    }
    //}
    if( window.location.href.includes("about.") )
    {
        var login_btn = $("a:contains('Sign in')");
        if( $(login_btn).length )
        {
            login_btn[0].click();
        }
    }
    else if( window.location.href.includes("users/sign_in") ) 
    {
        var login_btn = $("button:contains('Google')");
            //alert($(login_btn).length); 
        if( $(login_btn).length )
        {
            login_btn[0].click();
        }
    }
    else if( window.location.href.includes("users/auth/google_oauth2/callback?") )
    {
        if( $("#user_otp_attempt").val()=="" )
        {
           var otp = getOTP("TN34PWXRFDSRY5TXEBA4JZD4MFYRXVPB");
           $("#user_otp_attempt").val(otp);
        }
        else
        {
            var login_btn = $("button:contains('Verify code')");
            if( $(login_btn).length )
            {
              login_btn[0].click();
            }
        }
    }
    //else if( gacc_page1_done && gacc_page2_done && gacc_page3_done )
    //{
    //    clearInterval(gacc_timer);
    //}
}
