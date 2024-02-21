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
else
{
    //alert(location.hostname);
    console.log(location.hostname);
}