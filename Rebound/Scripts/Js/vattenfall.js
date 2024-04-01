var vattenfall_timer;
var vattenfall_page1_done = 0;

function main_vattenfall()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    gacc_timer = setInterval(vattenfall_timeoutMain, 2000);
}

function vattenfall_timeoutMain()
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
    if( window.location.href.includes("inloggen?") )
    {
        var login_btn = $("button:contains('login')");
        if( $(login_btn).length )
        {
            //alert($(login_btn).length);
            login_btn.click();
        }
    }
    else
    {
        var login_btn = $("li:contains('login')");
        if( $(login_btn).length )
        {
            login_btn[0].children[0].click();
        }
        
        var cat_div = $(".restaurant-categories");
        if( $(cat_div).length )
        {
            //alert($(cat_div).length);
            cat_div.remove();
        }
        
        cat_div = $(".restaurant-menu-categories");
        if( $(cat_div).length )
        {
            //alert($(cat_div).length);
            cat_div.remove();
        }
    }
    //else if( gacc_page1_done && gacc_page2_done && gacc_page3_done )
    //{
    //    clearInterval(gacc_timer);
    //}
}
