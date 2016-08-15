function onClick_sidebarItem()
{
        $(this).toggleClass("checked");
}


/*
function hide_dropdown()
{
        $(this).removeClass("open");
}
*/
function loadPage()
{
    /*$(".btn-group").click(onClick_dropdown);
    $('.btn-group').blur(hide_dropdown);*/
    $(".serp-sidebar-item").click(onClick_sidebarItem);
}

$(document).ready(loadPage); 
