var conf_is_join = 0;
function main_conf()
{
    join_timer = setInterval(conf_timeoutMain, 500);
} 

function shortcut_filter()
{
    return $(this).html() === "Shortcuts";
}

function conf_timeoutMain()
{
    var sh = $("div").filter(shortcut_filter);
    var pr = sh.parent().parent().parent();
    var apps = $('div[data-testid="space-apps"]');
    var ss = $("span:contains('Space settings')");
    var ss_pr = ss.parent().parent();
    var at = $("span:contains('Automation')");
    var at_pr = at.parent().parent();
    var ac = $("span:contains('All content')");
    var ac_pr = ac.parent().parent();
    var ad = $("span:contains('You‘re on the Free plan')");
    var ad_pr = ad.parent().parent();
    var ip = $("span:contains('Invite people')");
    var ip_pr = ip.parent().parent();

    pr.remove();
    ss_pr.remove();
    at_pr.remove();
    ac_pr.remove();
    ad_pr.remove();
    ip_pr.remove();
    apps.remove();

    if( ad.length )
    {
        clearInterval(gacc_timer);
    }
}