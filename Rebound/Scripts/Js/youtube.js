var yt_timer;

function yt_main()
{
    yt_timer = setInterval(yt_timeoutMain, 2500);
} 

function yt_skip_filter()
{
    return $(this).html() === "Skip";
}

function yt_timeoutMain()
{
    var sk = $("div").filter(yt_skip_filter);
    var pr = sk.parent();

    if( pr.length )
    {
        console.log(pr);
        pr.click();
    }
}