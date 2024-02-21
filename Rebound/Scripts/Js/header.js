function sleep(ms)
{
    return new Promise(resolve => setTimeout(resolve, ms));
}

function shortcut_filter()
{
    return $(this).html() === "Shortcuts";
}

async function click_join()
{
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