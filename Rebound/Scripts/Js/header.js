function sleep(ms)
{
    return new Promise(resolve => setTimeout(resolve, ms));
}

function shortcut_filter()
{
    return $(this).html() === "Shortcuts";
}