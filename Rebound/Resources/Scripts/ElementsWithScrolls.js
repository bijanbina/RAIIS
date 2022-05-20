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

if( document.body.offsetHeight>window.innerHeight )
{
	big_elem = window;
}
else
{
	var max_height = 0;

	for( let i=0; i<s_elem.length ; i++ ) 
	{
		if( max_height<s_elem[i].offsetHeight )
		{
			big_elem   = s_elem[i];
			max_height = s_elem[i].offsetHeight;
		}
	};
}

function pageScroll(speed)
{
	big_elem.scrollBy(0,1);
	scroll_timer = setTimeout(pageScroll,1000/speed);
}

if( typeof scroll_timer === 'undefined' ) 
{
	pageScroll(1000);
}
else
{
	clearTimeout(scroll_timer);
	scroll_timer=undefined;
}