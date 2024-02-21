var join_timer;
function main_gmeet()
{
    join_timer = setInterval(click_join, 100);
    var is_min = 0;
    var is_present = 0;

    const autoAdmit = (mutation) =>
    {
        if (!mutation.addedNodes)
            return

        if( is_min==0 )
        {
            var min_list = document.evaluate("//div[text()='Minimize']", document, null, XPathResult.ANY_TYPE, null );
            var min_div = min_list.iterateNext();

            var min_btn = min_div.parentElement.firstChild;

            if( min_btn!=null )
            {
                min_btn.click();
                is_min = 1;
            }
        }

        if( is_present==0 )
        {
            /// Is Presenting
            var present_list = document.evaluate("//span[contains(., 'is presenting')]", document, null, XPathResult.ANY_TYPE, null );
            var pre_span = present_list.iterateNext();

            if( pre_span!=null )
            {
                pre_span.parentElement.parentElement.parentElement.parentElement.parentElement.parentElement.remove();
                is_present = 1;
            }
        }

        const observer = new MutationObserver((mutations) => mutations.forEach(autoAdmit));

        // Options for the observer (which mutations to observe)
        const obs_config = { attributes: true, characterData: false, childList: true, subtree: true };

        observer.observe(document.body, obs_config);
    }
}