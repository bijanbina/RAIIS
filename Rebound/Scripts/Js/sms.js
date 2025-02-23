var sms_rm_count = 0;
function main_sms()
{
    join_timer = setInterval(sms_timeoutMain, 500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function sms_timeoutMain()
{
    var mt          = $('mws-conversation-snippet');
    var recent_span = mt.find("span").first();
    var sms_txt     = recent_span.text();
    var sms_digit   = (sms_txt.match(/\d/g) || []).join('');

    if( sms_digit )
    {
        console.log("h", sms_digit);
        navigator.clipboard.writeText(sms_digit)
                .then(() => alert("Copied!", sms_digit))
    }
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