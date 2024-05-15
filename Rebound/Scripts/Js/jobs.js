var jobs_timer;

//These variables change to 1 in case of success 
jobs_firstname_st = 0;
jobs_lastname_st  = 0;
jobs_fullname_st  = 0;
jobs_phone_st     = 0;
jobs_email_st     = 0;
jobs_address_st   = 0;
jobs_username_st  = 0;

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
    if( jobs_phone_st==0 )
    {
        if( jobs_phone() )
        {
            return;
        }
    }
    if( jobs_address() )
    {
        return;
    }
    if( jobs_username_st==0 )
    {
        if( jobs_account() )
        {
            return;
        }
    }
    if( jobs_email_st==0 )
    {
        if( jobs_email() )
        {
            return;
        }
    }
    //clearInterval(jobs_timer);
}

function jobs_name()
{
    if( (jobs_firstname_st==1 && jobs_lastname_st==1) ||
         jobs_fullname_st==1 )
    {
        return 0;
    }

    ///////////////// Full Name /////////////////////
    var fullname_objs  = $('*[placeholder="Full name"]');
    if( fullname_objs.length )
    {
        if( fullname_objs.val()==="" )
        {
            fill_fullname(fullname_objs);
            return 1;
        }
    }
    fullname_objs = fill_form("Your Name");
    if( fullname_objs )
    {
        fill_fullname(fullname_objs);
        return 1;
    }
    fullname_objs = fill_form("Your name");
    if( fullname_objs )
    {
        fill_fullname(fullname_objs);
        return 1;
    }
    fullname_objs  = $('input[name="applicant_name"]');
    if( fullname_objs.length )
    {
        if( fullname_objs.val()==="" )
        {
            fill_fullname(fullname_objs);
            return 1;
        }
    }
    
    ///////////////// First Name /////////////////////
    //alert(firstname_objs.val().length);
    ///////////////// First Name /////////////////////
    var firstname_objs = fill_form("First Name");
    if( firstname_objs )
    {
        fill_firstname(firstname_objs);
        return 1;
    }
    firstname_objs = fill_form("Preferred Name");
    if( firstname_objs )
    {
        fill_firstname(firstname_objs);
        return 1;
    }
    firstname_objs  = $('*[placeholder="First name"]');
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            fill_firstname(firstname_objs);
            return 1;
        }
    }
    firstname_objs  = $('*[placeholder="First Name"]');
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            fill_firstname(firstname_objs);
            return 1;
        }
    }
    firstname_objs  = $('*[placeholder="First name*"]');
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            fill_firstname(firstname_objs);
            return 1;
        }
    }
    firstname_objs = find_elem("td", "First Name");
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
            fill_lastname(lastname_objs);
            return 1;
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
