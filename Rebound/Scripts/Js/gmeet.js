var join_timer;
var gmeet_is_min = 0;
var gmeet_is_present = 0;

function main_gmeet()
{
    if( window.location.href.includes("authuser=1")==0 )
    {
        join_timer = setInterval(gmeet_timeoutMain, 500);
    }
}

async function gmeet_timeoutMain()
{
    //if( is_min==0 )
    //{
    //    var min_list = document.evaluate("//div[text()='Minimize']", document, null, XPathResult.ANY_TYPE, null );
    //    var min_div = min_list.iterateNext();

    //    var min_btn = min_div.parentElement.firstChild;

    //    if( min_btn!=null )
    //    {
    //        min_btn.click();
    //        is_min = 1;
    //    }
    //}

    //if( is_present==0 )
    //{
    //    /// Is Presenting
    //    var present_list = document.evaluate("//span[contains(., 'is presenting')]", document, null, XPathResult.ANY_TYPE, null );
    //    var pre_span = present_list.iterateNext();

    //    if( pre_span!=null )
    //    {
    //        pre_span.parentElement.parentElement.parentElement.parentElement.parentElement.parentElement.remove();
    //        is_present = 1;
    //    }
    //}

    var j_node;
    if( $("span:contains('Ask to join')").length==0 )
    {
        if( $("span:contains('Join now')").length==0 )
        {
            return;
        }
        else
        {
            j_node = $("span:contains('Join now')");
        }
    }
    else
    {
        j_node = $("span:contains('Ask to join')");
    }

    if( $('[data-tooltip="Turn off camera (ctrl + e)"]').length==1 )
    {
        await sleep(500);
        $('[data-tooltip="Turn off camera (ctrl + e)"]').click();
        await sleep(800);
        j_node.click();
        clearInterval(join_timer);
    }
}