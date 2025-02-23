var digid_rm_count = 0;
function main_digid()
{
    join_timer = setInterval(digid_timeoutMain, 500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function digid_timeoutMain()
{
    if( window.location.href.includes("/inloggen_ww") ||
        window.location.href.includes("/inloggen_sms") )
    {
        var login_btn = $("button:contains('Log in')");
        console.log("h", login_btn);
        if( $(login_btn).length )
        {
            //alert($(login_btn).length);
            login_btn.click();
        }
    }
    else if( window.location.href.includes("/sms_controleren") )
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
    //var digid_txt     = recent_span.text();
    //var digid_digit   = (digid_txt.match(/\d/g) || []).join('');

    //if( digid_digit )
    //{
    //    console.log("h", digid_digit);
    //    navigator.clipboard.writeText(digid_digit)
    //            .then(() => console.log("Copied!"))
    //}
    //alert("hey");
}

document.addEventListener("keydown", function(event) 
{ 
    if( event.ctrlKey && event.shiftKey && event.code==="KeyR" ) 
    { 
        var mic_query = 'button[class*="mdc-icon-button mat-mdc-icon-button mat-mdc-button-base mat-mdc-tooltip-trigger speech_dictation_mic_button"]'; 
        var mic_button = document.querySelector(mic_query); // Selects the button with class "rop" 
        if( mic_button ) 
        { 
            mic_button.click(); 
        } 
        else 
        { 
            console.log("Mic button not found."); 
        } 
        event.preventDefault(); // Prevent the default action (optional) 
    } 
    if( event.ctrlKey && event.shiftKey && event.code==="KeyU" ) 
    { 
        var send_query = 'button[class*="send-button"]'; 
        var send_button = document.querySelector(send_query); // Selects the button with class "rop" 
        if( send_button ) 
        { 
            send_button.click(); 
        } 
        else 
        { 
            console.log("Send button not found."); 
        } 
        event.preventDefault(); // Prevent the default action (optional) 
    } 
});