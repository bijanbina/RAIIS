var linkedin_timer;
var linkedin_page1_done = 0;

function main_linkedin()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    linkedin_timer = setInterval(linkedin_timeoutMain, 2000);
}

function linkedin_timeoutMain()
{
    //if( window.location.href.includes("bestel") )
    //{
    //    if( ijburg_page1_done )
    //    {
    //        var delivery_btn = $("button:contains('Search')");
    //        if( $(delivery_btn).length )
    //        {
    //            delivery_btn[0].click();
    //            ijburg_page1_done = 1;
    //        }
    //    }
    //    else
    //    {
    //        var delivery_btn = $("a:contains('Delivery')");
    //        if( $(delivery_btn).length )
    //        {
    //            delivery_btn[0].click();
    //            ijburg_page1_done = 1;
    //        }
    //    }
    //}
    if( window.location.href.includes("jobs/search/") )
    {
        var phone_num = $("label:contains('Mobile phone number')");
        phone_num = phone_num.next("input");
        if( phone_num.length )
        {
            //console.log(phone_num);
            if( phone_num.val().length<6 )
            {
                phone_num.focus();
                typeNative("633009005");
                return 1;
            }
        }
        var notif_objs = $("label:contains('to stay up to date with their page.')");
        notif_objs = notif_objs.parent();
        notif_objs = notif_objs.find("input[type='checkbox']");
        if( notif_objs.length )
        {
            notif_objs.prop('checked', false);
        }
    }
    else
    {
    }
    //else if( gacc_page1_done && gacc_page2_done && gacc_page3_done )
    //{
    //    clearInterval(gacc_timer);
    //}
}
