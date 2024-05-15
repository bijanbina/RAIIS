function sleep(ms)
{
    return new Promise(resolve => setTimeout(resolve, ms));
}

function fill_form(label_text)
{
    var query = "label:contains('" + label_text + "')";
    var objs = $(query);
    if( objs.children().length>1 )
    {
        objs = objs.parent();
        objs = objs.find("input");
    }
    else
    {
        objs = objs.next("input");
        if( label_text=="Your text" )
        {
            console.log(objs);
        }
        if( objs.length==0 )
        {
            objs = $(query).parent();
            objs = objs.find("input");
        }
    }
    if( objs.length )
    {
        if( objs.first().val()==="" )
        {
            console.log(label_text + objs.length);
            return objs;
        }
    }
    return 0;
}

function find_elem(type, value)
{
    // Find the <td> elements with the exact HTML content
    var matchingTd = $(type).filter(function() 
    {
        return $(this).html() === value;
    });
    return matchingTd;
}