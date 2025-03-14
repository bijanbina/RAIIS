var conf_rm_count = 0;
function main_conf()
{
    conf_rm_count = 2;
    join_timer = setInterval(conf_timeoutMain, 500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function conf_timeoutMain()
{
    if( 0<conf_rm_count)
    {
        // get sidebar navigation
        var nav = $("nav").last();
        var ap = nav.find("span").filter(html_filter("Apps"));
        var ap_pr = ap.parent().parent().parent().parent().parent().parent();
        var ss = nav.find("span:contains('Home')");
        var ss_pr = ss.parent().parent().parent().parent().parent();
        var ch = nav.find("span:contains('Company Hub')");
        var ch_pr = ch.parent().parent().parent().parent();
        var re = nav.find("span:contains('Recent')");
        var re_pr = re.parent().parent().parent().parent().parent();
        var st = nav.find("span:contains('Starred')");
        var st_pr = st.parent().parent().parent().parent().parent();
        var sp = nav.find("span:contains('For you')");
        var sp_pr = sp.parent().parent().parent().parent().parent();
        var id_pr = $("button[id='Content']").parent();

        //ss_pr.remove();
        ch_pr.remove();
        //re_pr.remove();
        //st_pr.remove();
        sp_pr.remove();
        //id_pr.remove();
        //ap_pr.remove();

        // Page
        var sh    = $("span:contains('Shortcuts')");
        var sh_pr = sh.parent().parent().parent().parent().parent();
        var se    = $("input[placeholder='Search by title']");
        var se_pr = se.parent().parent();
        var co    = $("span:contains('Content')");
        var co_pr = co.parent().parent().parent().parent();
        //var fb    = $("span:contains('Give feedback on the new navigation')");
        //var fb_pr = fb.parent().parent().parent().parent().parent().parent();
        var ip = nav.find("span:contains('Invite people')");
        var ip_pr = ip.parent().parent().parent();
        var ca = nav.find("span:contains('Calendars')");
        var ca_pr = ca.parent().parent().parent();
        var cr = nav.find("span").filter(html_filter("Create"));
        var cr_pr = cr.parent().parent().parent().parent().parent();
        sh_pr.remove();
        se_pr.remove();
        co_pr.remove();
        //fb_pr.remove();
        ip_pr.remove();
        ca_pr.remove();
        cr_pr.remove();

        conf_rm_count--;
    }
    
    // Add "Confluence" to the title if it's not already there
    if( !document.title.includes("Confluence") )
    {
        document.title += " - Confluence";
    }
}