var join_timer;
var gmail_is_min = 0;
var gmail_is_present = 0;

function main_gmail()
{
	join_timer = setInterval(gmail_timeoutMain, 1500);
}

async function gmail_timeoutMain()
{
	var ap =  $("span:contains('Action Required: One-time verification code')");
	var pr = ap[0].parentElement.parentElement.parentElement.parentElement;
	ap = ap.first();

	var time_elem = pr.children[7];
	var sms_txt     = ap.text();
    var sms_digit   = (sms_txt.match(/\d/g) || []).join('');
    
    if( sms_digit )
    {
        var time_txt   = time_elem.textContent;
        //console.log("h", sms_digit, time_txt);
        if( time_txt.includes(":") || time_txt.includes("Now") )
        {
            if( sms_last!==sms_digit )
            {
                sms_last = sms_digit;
                sendPipe("sms", sms_digit);
            }
        }
    }
}