var jobs_timer;

//These variables change to 1 in case of success 
var jobs_firstname_st = 0;
var jobs_lastname_st  = 0;
var jobs_fullname_st  = 0;
var jobs_phone_st     = 0;
var jobs_email_st     = 0;
var jobs_address_st   = 0;
var jobs_username_st  = 0;

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
        console.log(fullname_objs.first());
        fill_fullname(fullname_objs.first());
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
    
    /////////////// First Name /////////////////////
    //alert(firstname_objs.val().length);
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
    firstname_objs = fill_form("Given Name");
    if( firstname_objs )
    {
        fill_firstname(firstname_objs);
        return 1;
    }
    firstname_objs  = $('*[placeholder="First name"]:visible');
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            fill_firstname(firstname_objs);
            return 1;
        }
    }
    firstname_objs  = $('*[placeholder="First Name"]:visible');
    if( firstname_objs.length )
    {
        if( firstname_objs.val()==="" )
        {
            fill_firstname(firstname_objs);
            return 1;
        }
    }
    firstname_objs  = $('*[placeholder="First name*"]:visible');
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
            fill_firstname(firstname_objs);
            return 1;
        }
    }

    ///////////////// Last Name /////////////////////
    var lastname_objs = fill_form("Last Name");
    if( lastname_objs )
    {
        fill_lastname(lastname_objs);
        return 1;
    }
    lastname_objs = fill_form("Surname");
    if( lastname_objs )
    {
        fill_lastname(lastname_objs);
        return 1;
    }
    lastname_objs = fill_form("Family Name");
    if( lastname_objs )
    {
        fill_lastname(lastname_objs);
        return 1;
    }
    lastname_objs  = $('*[placeholder="Last name"]');
    if( lastname_objs.length )
    {
        if( lastname_objs.val()==="" )
        {
            fill_lastname(lastname_objs);
            return 1;
        }
    }
    lastname_objs  = $('*[placeholder="Last Name"]');
    if( lastname_objs.length )
    {
        if( lastname_objs.val()==="" )
        {
            fill_lastname(lastname_objs);
            return 1;
        }
    }
    lastname_objs  = $('*[placeholder="Last name*"]');
    if( lastname_objs.length )
    {
        if( lastname_objs.val()==="" )
        {
            fill_lastname(lastname_objs);
            return 1;
        }
    }
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
    var phone_objs = fill_form("Mobile Telephone Number");
    if( phone_objs )
    {
        fill_phone(phone_objs);
        return 1;
    }
    phone_objs = fill_form("mobile number");
    if( phone_objs )
    {
        fill_phone(phone_objs);
        return 1;
    }
    phone_objs = fill_form("Primary Phone Number");
    if( phone_objs )
    {
        fill_phone(phone_objs);
        return 1;
    }
    phone_objs = fill_form("Phone Number");
    if( phone_objs )
    {
        fill_phone(phone_objs);
        return 1;
    }
    phone_objs = fill_form("Mobile");
    if( phone_objs )
    {
        fill_phone(phone_objs);
        console.log("5", phone_objs);
        return 1;
    }
    phone_objs     = $('*[placeholder*="phone number"]');
    if( phone_objs.length )
    {
        if( phone_objs.val().length<6 )
        {
            fill_phone(phone_objs);
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
                fill_phone(phone_objs);
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
                    fill_phone(phone_objs);
                    return 1;
                }
            }
        }
    }
    phone_objs  = $('input[name="phone"]:visible');
    if( phone_objs.length )
    {
        if( phone_objs.val()==="" )
        {
            fill_phone(phone_objs);
            console.log("9");
            return 1;
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
    var email_objs = fill_form("E-Mail");
    if( email_objs )
    {
        fill_email(email_objs.first());
        return 1;
    }
    email_objs = fill_form("Confirm E-Mail");
    if( email_objs )
    {
        fill_email(email_objs.first());
        return 1;
    }
    email_objs = fill_form("Email");
    if( email_objs )
    {
        fill_email(email_objs.first());
        return 1;
    }
    email_objs = fill_form("Email Address");
    console.log(email_objs);
    if( email_objs )
    {
        console.log(email_objs.first());
        fill_email(email_objs.first());
        return 1;
    }

    email_objs = $('*[placeholder*="email address"]:visible');
    if( email_objs.length )
    {
        if( email_objs.val()==="" )
        {
            fill_email(email_objs);
            return 1;
        }
    }
//    email_objs = $('*[placeholder*="Email"]');
//    if( email_objs.length )
//    {
//        if( email_objs.val()==="" )
//        {
//            fill_email(email_objs);
//            return 1;
//        }
//    }

//    email_objs = $("td:contains('Email Address')");
//    email_objs = email_objs.next("td");
//    email_objs = email_objs.find("input[type='text']");
////        console.log(email_objs);
//    if( email_objs.length )
//    {
//        if( email_objs[0].value==="" )
//        {
//            email_objs.off('paste');
//            fill_email(email_objs.first());
//            return 1;
//        }
//    }
//    else
//    {
//        email_objs = $("label:contains('Your Email')");
//        email_objs = email_objs.next("input");
//        if( email_objs.length )
//        {
//            if( email_objs.val()==="" )
//            {
//                email_objs.focus();
//                typeNative("bijan@binaee.com");
//                return 1;
//            }
//        }
//        else
//        {
//            email_objs = $("label:contains('Email Address')");
//            email_objs = email_objs.next("input");
//            if( email_objs.length )
//            {
//                if( email_objs.val()==="" )
//                {
//                    email_objs.focus();
//                    typeNative("bijan@binaee.com");
//                    return 1;
//                }
//            }
//        }
//    }
//    email_objs  = $('input[name="from_email"]');
//    if( email_objs.length )
//    {
//        if( email_objs.val()==="" )
//        {
//            fill_email(email_objs);
//            return 1;
//        }
//    }

    // retype
    email_objs = $("td:contains('Retype Email Address')");
    email_objs = email_objs.next("td");
    email_objs = email_objs.find("input[type='text']");
    if( email_objs.length )
    {
        if( email_objs[0].value==="" )
        {
            email_objs[0].onpaste = null;
            fill_email(email_objs.first());
            return 1;
        }
    }

    // notif
    var notif_objs = $("td:contains('Notification')");
    notif_objs = notif_objs.next("td");
    notif_objs = notif_objs.find("input[type='checkbox']");
    //console.log(notif_objs);
    if( notif_objs.length )
    {
        notif_objs.prop('checked', false);
    }
    notif_objs = $("label:contains('email notification')");
    notif_objs = notif_objs.parent();
    notif_objs = notif_objs.find("input[type='checkbox']");
    if( notif_objs.length )
    {
        notif_objs.prop('checked', false);
    }


    return 0;
}

function jobs_address()
{
    var address_objs = fill_form("Address Line 1");
    if( address_objs )
    {
        fill_address(address_objs);
        return 1;
    }
    address_objs = fill_form("Street Name");
    if( address_objs )
    {
        fill_street(address_objs);
        return 1;
    }
    address_objs = fill_form("House Number");
    if( address_objs )
    {
        fill_housenumber(address_objs);
        return 1;
    }
    address_objs = fill_form("City or Town");
    if( address_objs )
    {
        fill_city(address_objs);
        return 1;
    }
    address_objs = fill_form("City");
    if( address_objs )
    {
        fill_city(address_objs);
        return 1;
    }
    address_objs = fill_form("Postal Code");
    if( address_objs )
    {
        fill_postalcode(address_objs);
        return 1;
    }
    address_objs = fill_form("Post Code");
    if( address_objs )
    {
        fill_postalcode(address_objs);
        return 1;
    }

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

function jobs_account()
{
    var username_objs = fill_form("User Name");
    if( username_objs )
    {
        fill_username(username_objs);
        return 1;
    }
    return 0;
}
