var jobs_timer;

function main_jobs()
{
    jobs_timer = setInterval(jobs_timeoutMain, 1000);
}

function jobs_timeoutMain()
{
    if( document.hidden )
    {
        return;
    }
    var fullname_objs  = $('*[placeholder="Full name"]');
    // include email address
    var email_objs     = $('*[placeholder*="email address"]');
    var phone_objs     = $('*[placeholder*="phone number"]');
    var firstname_objs  = $('*[placeholder="First name"]');
    var lastname_objs  = $('*[placeholder="Last name"]');

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
    
    if( firstname_objs.length )
    {
        if( firstname_objs.val()=="" )
        {
            firstname_objs.focus();
            typeNative("Bijan");
            return;
        }
    }
    
    if( lastname_objs.length )
    {
        if( lastname_objs.val()=="" )
        {
            lastname_objs.focus();
            typeNative("Binaee");
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