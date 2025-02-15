var gemini_rm_count = 0;
function main_gemini()
{
    join_timer = setInterval(gemini_timeoutMain, 500);
} 

function html_filter(text)
{
    return function() 
           {
               return $(this).html()===text;
           }
}

function gemini_timeoutMain()
{
    var mt = $('model-thoughts');
    console.log("h", mt.length);
    mt.remove();
    //alert("hey");
}