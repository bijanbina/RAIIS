var recr_timer;

function main_recruit()
{
    if( window.location.href.includes(".recruitee.com/o/") )
    {
        //alert(location.hostname);
        recr_timer = setInterval(recr_timeoutMain, 1000);
    }
}

function recr_timeoutMain()
{
    if( document.hidden )
    {
        return;
    }
    var fullname_objs  = $('*[placeholder="Full name"]:visible');
    // include email address
    var email_objs     = $('*[placeholder*="email address"]:visible');
    var phone_objs     = $('*[placeholder*="phone number"]:visible');

    //alert(phone_objs.val().length);
    if( fullname_objs.length )
    {
        if( fullname_objs.val()=="" )
        {
            fullname_objs.focus();
            typeNative("Bijan Binaee");
            return;
        }
    }
    
    if( email_objs.length )
    {
        if( email_objs.val()=="" )
        {
            email_objs.focus();
            typeNative("bijan@binaee.com");
            return;
        }
    }
    
    if( phone_objs.length )
    {
        if( phone_objs.val().length<6 )
        {
            phone_objs.focus();
            typeNative("633009005");
            return;
        }
    }
}