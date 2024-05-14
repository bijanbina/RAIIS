var huisart_timer;
var huisart_page1_done = 0;

function main_huisart()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    huisart_timer = setInterval(huisart_timeoutMain, 2000);
}

function huisart_timeoutMain()
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
    if( window.location.href.includes("portaal/login/") )
    {
        //var login_btn = $("button:contains('Continue')");
        //if( $(login_btn).length )
        //{
        //    //alert($(login_btn).length);
        //    login_btn.click();
        //}
        //var input_user = $("iframe");
        //console.log(input_user);
        //console.log(input_user.html());
        var inputElement = document.getElementById("no_table_name");

        // Check if the element was found
        if (inputElement) {
            console.log("Input element found:", inputElement);
        } else {
            console.log("Input element with id 'no_table_name' not found.");
        }
        //input_user = input_user.find("input[type='email']");
        //input_user.attr('autocomplete', 'on');
        
        //// Trigger the browser's autocomplete suggestion
        //input_user.focus();
    }
    else
    {
        var login_btn = $("li:contains('Login')");
        if( $(login_btn).length )
        {
            //window.location.href = 'https://huisartsendezomerlinde.mijngezondheidsapp.nl/login';
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
