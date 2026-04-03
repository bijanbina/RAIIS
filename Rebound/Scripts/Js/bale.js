var bale_timer;
var bale_page1_done = 0;

function main_bale()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
    }
    bale_timer = setInterval(bale_timeoutMain, 2000);
}
function bale_timeoutMain()
{
    var button = document.querySelector('[data-testid="confirm-button"]');
    console.log('helloooo');

    if( !button )
    {
        console.warn('Confirm button not found');
        return;
    }

    button.click();
}
