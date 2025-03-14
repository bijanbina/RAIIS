var sms_last = 0;
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
        var time_stamp = $('mws-relative-timestamp').first();
        var time_txt   = time_stamp.text();
        console.log("h", sms_digit, time_stamp, time_txt);
        if( time_txt.includes("min") || time_txt.includes("Now") )
        {
            if( sms_last!==sms_digit )
            {
                sms_last = sms_digit;
                sendPipe("sms", sms_digit);
            }
        }
    }
    //alert("hey");
}