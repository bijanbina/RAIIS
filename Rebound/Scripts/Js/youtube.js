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
    //var sk = $("div").filter(yt_skip_filter);
	var sk = document.querySelector('button.ytp-skip-ad-button');

	if( sk )
	{
		var rect = sk.getBoundingClientRect();
		var msg  = Math.round(rect.x) + "," + Math.round(rect.y) + ",";
		msg     += Math.round(rect.width) + "," + Math.round(rect.height);  
		sendPipe("click", msg);
	}
	//var pr = sk.parent();

    //if( pr.length )
    //{
    //    console.log(pr);
    //    pr.click();
    //    pr.trigger('click');;
    //}
}