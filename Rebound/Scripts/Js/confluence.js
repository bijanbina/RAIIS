var is_join = 0;
var is_min = 0;
var is_present = 0;

function main_conf()
{
    var is_join = 0;
    var is_min = 0;
    var is_present = 0;

    sleep(2000);

    const autoAdmit = (mutation) =>
    {
        if (!mutation.addedNodes)
        {
            return;
        }
        //var sh = $("div:contains('Shortcuts')");
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

        if( is_join==0 )
        {
            pr.remove();
            ss_pr.remove();
            at_pr.remove();
            ac_pr.remove();
            ad_pr.remove();
            apps.remove();

            if( ad.length )
            {
                is_join = 1;
            }
        }
    };

    const observer = new MutationObserver((mutations) => mutations.forEach(autoAdmit));

    // Options for the observer (which mutations to observe)
    const obs_config = { attributes: true, characterData: false, childList: true, subtree: true };

    observer.observe(document.body, obs_config);
}