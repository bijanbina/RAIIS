var gcal_timer;
var gcal_page1_done = 0;
var gcal_page2_done = 0;
var gcal_page3_done = 0;
var gcal_is_present = 0;

function main_gcal()
{
    gcal_timer = setInterval(gcal_timeoutMain, 2000);
}

function gcal_timeoutMain()
{
    var mon = $('#drawerMiniMonthNavigator');
    var cal = mon[0];
    var ss = $("h2:contains('Time Insights')");
    var ss_pr = ss.parent().parent();

    cal.remove();
    ss_pr.remove();
    
    if( mon.length==0 )
    {
        clearInterval(join_timer);
    }
}

