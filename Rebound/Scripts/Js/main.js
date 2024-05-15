//alert(location.hostname);
if( location.hostname.includes("atlassian.net") )
{
    //alert("hi8");
    main_conf();
}
else if( location.hostname.includes("meet.google.com") )
{
    main_gmeet();
}
else if( location.hostname.includes("accounts.google.com") )
{
    main_gaccount();
}
else if( location.hostname.includes("calendar.google.com") )
{
    main_gcal();
}
else if( location.hostname.includes("www.youtube.com") )
{
    yt_main();
}
else if( location.hostname.includes("recruitee.com") )
{
    main_recruit();
}
else if( location.hostname.includes("ijburgeats.nl") )
{
    main_ijburg();
}
else if( location.hostname.includes("vattenfall.nl") )
{
    main_vattenfall();
}
else if( location.hostname.includes("www.huisartsendezomerlinde.nl") ||
         location.hostname.includes("mijngezondheidsapp.nl") )
{
    main_huisart();
}
else if( location.hostname.includes("gitlab.com") )
{
    main_gitlab();
}
else if( location.hostname.includes("qblox.personio.de") )
{
    main_personio();
}
else if( location.hostname.includes("www.linkedin.com") )
{
    main_linkedin();
}
else if( location.href.includes("job")    || 
         location.href.includes("career")  ||
         location.href.includes("recruit") ||
         location.hostname.includes("www.microtech-global.com") ||
         location.hostname.includes("www.aplitrak.com") )
{
    main_jobs();
}
else
{
    //alert(location.hostname);
    console.log(location.hostname);
}