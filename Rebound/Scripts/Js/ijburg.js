var ijburg_timer;
var ijburg_page1_done = 0;
var gacc_page2_done = 0;
var gacc_page3_done = 0;
var gacc_is_present = 0;

function main_ijburg()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    ijburg_timer = setInterval(ijburg_timeoutMain, 2000);
}

function ijburg_timeoutMain()
{
    if( window.location.href.includes("bestel") )
    {
        if( ijburg_page1_done )
        {
            var delivery_btn = $("button:contains('Search')");
            if( $(delivery_btn).length )
            {
                delivery_btn[0].click();
                ijburg_page1_done = 1;
            }
        }
        else
        {
            var delivery_btn = $("a:contains('Delivery')");
            if( $(delivery_btn).length )
            {
                delivery_btn[0].click();
                ijburg_page1_done = 1;
            }
        }
    }
    else if( window.location.href.includes("user/login") )
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
        var login_btn = $("li:contains('Login')");
        if( $(login_btn).length )
        {
            login_btn[1].children[0].click();
        }
        
        var cat_div = $(".restaurant-categories");
        if( $(cat_div).length )
        {
            //alert($(login_btn).length);
            cat_div.remove();
        }
        
        cat_div = $(".restaurant-menu-categories");
        if( $(cat_div).length )
        {
            //alert($(cat_div).length);
            cat_div.remove();
        }
        
        //var select_id = "#option_3a5c84f6f3054c5cb5b7193abf1e51d7_1";
        //cat_div = $('#option_3a5c84f6f3054c5cb5b7193abf1e51d7_1 option:contains("Jasmin Rice")');
        //if( $(cat_div).length )
        //{
        //    var conceptName = $(select_id).find(":selected").text();
        //    alert(conceptName);
        //    cat_div.prop('selected', true)
        //}
    }
    //else if( gacc_page1_done && gacc_page2_done && gacc_page3_done )
    //{
    //    clearInterval(gacc_timer);
    //}
}
