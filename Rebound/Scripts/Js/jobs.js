var jobs_timer;

function main_jobs()
{
    jobs_timer = setInterval(jobs_timeoutMain, 1000);
}
// 
function jobs_timeoutMain()
{
    if( document.hidden )
    {
        return;
    }

    if( jobs_name() )
    {
        return;
    }
    else if( jobs_phone() )
    {
        return;
    }
    else if( jobs_address() )
    {
        return;
    }
    else if( jobs_email() )
    {
        return;
    }
    clearInterval(jobs_timer);
}

function jobs_name()
{
    var fullname_objs  = $('*[placeholder="Full name"]');
    // include email address
    var firstname_objs  = $('*[placeholder="First name"]');
    var lastname_objs  = $('*[placeholder="Last name"]');

    if( fullname_objs.length )
    {
        if( fullname_objs.val()==="" )
        {
            fullname_objs.focus();
            typeNative("Bijan Binaee");
            return 1;
        }
    }
    else
    {
        fullname_objs = $("label:contains('Your Name')");
        fullname_objs = fullname_objs.next("input");
        console.log(fullname_objs);
        if( fullname_objs.length )
        {
            if( fullname_objs.val()==="" )
            {
                fullname_objs.focus();
                typeNative("Bijan Binaee");
                return 1;
            }
        }
    }
    
    //alert(firstname_objs.val().length);
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            firstname_objs.focus();
            typeNative("Bijan");
            return 1;
        }
    }
    else
    {
        firstname_objs = $("td:contains('First Name')");
        firstname_objs = firstname_objs.next("td");
        firstname_objs = firstname_objs.find("input[type='text']");
//        console.log(firstname_objs);
        if( firstname_objs.length )
        {
            if( firstname_objs.val()==="" )
            {
                firstname_objs.focus();
                typeNative("Bijan");
                return 1;
            }
        }
    }

    
    if( lastname_objs.length )
    {
        if( lastname_objs.val()==="" )
        {
            lastname_objs.focus();
            typeNative("Binaee");
            return 1;
        }
    }
    else
    {
        lastname_objs = $("td:contains('Last Name')");
        lastname_objs = lastname_objs.next("td");
        lastname_objs = lastname_objs.find("input[type='text']");
//        console.log(firstname_objs);
        if( lastname_objs.length )
        {
            if( lastname_objs.val()==="" )
            {
                lastname_objs.focus();
                typeNative("Binaee");
                return 1;
            }
        }
    }

    return 0;
}

function jobs_phone()
{
    var phone_objs     = $('*[placeholder*="phone number"]');

    if( phone_objs.length )
    {
        if( phone_objs.val().length<6 )
        {
            phone_objs.focus();
            typeNative("633009005");
            return 1;
        }
    }
    else
    {
        phone_objs = $("td:contains('Phone Number')");
        phone_objs = phone_objs.next("td");
        phone_objs = phone_objs.find("input[type='text']");
//        console.log(firstname_objs);
        if( phone_objs.length )
        {
            if( phone_objs.val()==="" )
            {
                phone_objs.focus();
                typeNative("633009005");
                return 1;
            }
        }
        else
        {
            phone_objs = $("label:contains('Your Tel Number')");
            phone_objs = phone_objs.next("input");
            if( phone_objs.length )
            {
                if( phone_objs.val()==="" )
                {
                    phone_objs.focus();
                    typeNative("+31633009005");
                    return 1;
                }
            }
        }
    }

    var phone_country_objs = $("td:contains('Country/Region Code')");
    phone_country_objs = phone_country_objs.next("td");
    phone_country_objs = phone_country_objs.find("select");
    var nl_options = phone_country_objs.find('option:contains("Netherlands")');
    if( nl_options.length )
    {
        nl_options.prop('selected', true);
//        return 1;
    }
    return 0;
}

function jobs_email()
{
    var email_objs = $('*[placeholder*="email address"]');

    if( email_objs.length )
    {
        if( email_objs.val()==="" )
        {
            email_objs.focus();
            typeNative("bijan@binaee.com");
            return 1;
        }
    }
    else
    {
        email_objs = $("td:contains('Email Address')");
        email_objs = email_objs.next("td");
        email_objs = email_objs.find("input[type='text']");
//        console.log(email_objs);
        if( email_objs.length )
        {
            if( email_objs[0].value==="" )
            {
                email_objs.off('paste');
                email_objs[0].focus();
                typeNative("bijan@binaee.com");
                return 1;
            }
        }
        else
        {
            email_objs = $("label:contains('Your Email')");
            email_objs = email_objs.next("input");
            if( email_objs.length )
            {
                if( email_objs.val()==="" )
                {
                    email_objs.focus();
                    typeNative("bijan@binaee.com");
                    return 1;
                }
            }
        }
    }

    // retype
    email_objs = $("td:contains('Retype Email Address')");
    email_objs = email_objs.next("td");
    email_objs = email_objs.find("input[type='text']");
    if( email_objs.length )
    {
        if( email_objs[0].value==="" )
        {
            email_objs[0].focus();
            email_objs[0].onpaste = null;
            typeNative("bijan@binaee.com");
            return 1;
        }
    }

    // notif
    var notif_objs = $("td:contains('Notification')");
    notif_objs = notif_objs.next("td");
    notif_objs = notif_objs.find("input[type='checkbox']");
    console.log(notif_objs);
    if( notif_objs.length )
    {
        notif_objs.prop('checked', false);
    }

    return 0;
}

function jobs_address()
{
    var country_objs = $("td:contains('Country/Region of Residence')");
    country_objs = country_objs.next("td");
    country_objs = country_objs.find("select");
    var nl_options = country_objs.find('option:contains("Netherlands")');
//    console.log(nl_options);
    if( nl_options.length )
    {
        nl_options.prop('selected', true);
//        return 1;
    }
    return 0;
}
