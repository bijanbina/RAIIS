function hasScroller(elem) 
{
	var ovf = document.defaultView.getComputedStyle(elem, null)['overflow-y'];

	if( ovf=='scroll' || ovf=='auto' )
	{
		return elem.offsetHeight<elem.scrollHeight;
	}
	return false;
};

var s_elem = [].filter.call(document.querySelectorAll('*'), hasScroller);

var big_elem;

var b_scroll = document.defaultView.getComputedStyle(document.body, null)['overflow-y'];
if( b_scroll=='scroll' )
{
	big_elem = window;
}
else if( document.body.offsetHeight>window.innerHeight )
{
	big_elem = window;
}
else
{
	var max_size = 0;

	for( let i=0; i<s_elem.length ; i++ ) 
	{
		var elem_size = s_elem[i].offsetHeight;
		elem_size *= s_elem[i].offsetWidth;
		if( max_size<elem_size )
		{
			big_elem = s_elem[i];
			max_size = elem_size;
		}
	};
}

function pageScroll()
{
	big_elem.scrollBy(0, bt_step);
}

if( typeof scroll_timer === 'undefined' ) 
{
	var scroll_timer = setInterval(pageScroll, bt_speed);
}
else
{
	alert('fuck');
}