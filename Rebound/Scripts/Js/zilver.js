var zilver_rm_count = 0;
function main_zilver()
{
    join_timer = setInterval(zilver_timeoutMain, 2500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function zilver_timeoutMain()
{
    if( window.location.href.includes("/inloggen") )
    {
        var login_btn = $("span:contains('Log in my silver cross')");
        login_btn = login_btn.parent();
        if( login_btn.length )
        {
            console.log("h", login_btn);
            //alert($(login_btn).length);
            login_btn[0].click();
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
    //var zilver_txt     = recent_span.text();
    //var zilver_digit   = (zilver_txt.match(/\d/g) || []).join('');

    //if( zilver_digit )
    //{
    //    console.log("h", zilver_digit);
    //    navigator.clipboard.writeText(zilver_digit)
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