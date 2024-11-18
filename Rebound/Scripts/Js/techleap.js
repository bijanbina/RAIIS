var big_elem;
var scrol = 1;
var titles = [];
var csv_data = "";

function main_techleap()
{
	big_elem = document.getElementById('window-scrollbar').querySelector('div');
	join_timer = setInterval(tech_timeoutMain, 1000);
	csv_data  = "Name,Description,Link,Rank,Round,Location,";
	csv_data += "Range,Rounds,Tot Deal\n";
} 

function shortcut_filter()
{
    return $(this).html() === "Shortcuts";
}

function tech_timeoutMain()
{
	var num_read = 0;
	var query = $("div.virtual-list");
	var childs = query.find("div.table-list-item");
	var read_count = 0;
	while( typeof childs[num_read]!=='undefined' )
	{
		var title = childs.eq(num_read).find("div.type-element a").text();
		title = title.replace(/,/g, " ");
		if( jQuery.inArray(title, titles)===-1 )
		{
			var firm_link = "https://finder.techleap.nl";
			firm_link += childs.eq(num_read).find("div.type-element a").attr("href");
			var description = childs.eq(num_read).find("div.tw-line-clamp-2").text();
			description = description.replace(/,/g, " ");
			var rank = childs.eq(num_read).find("div.prominence-rank-column__rank").text();
			rank = rank.replace(/,/g, " ");
			var preferred = childs.eq(num_read).find("div.preferredRound").text();
			preferred = preferred.replace(/,/g, " ");
			var loc = childs.eq(num_read).find("div.hqLocations").text();
			loc = loc.replace(/,/g, " ");
			var deal = childs.eq(num_read).find("div.dealSizeEnhanced").text();
			deal = deal.replace(/,/g, " ");
			var num_round = childs.eq(num_read).find("div.investorNumberOfRoundsIndustry").text();
			num_round = num_round.replace(/,/g, " ");
			var participate = childs.eq(num_read).find("div.investorTotalFundingEnhanced").text();
			participate = participate.replace(/,/g, " ");

			//console.log(title, rank, preferred, loc, deal, num_round, participate);
			//console.log(title, firm_link);
			var csv_line = title + "," + description + "," + firm_link + "," + rank + "," + preferred + ",";
			csv_line += loc + "," + deal + "," + num_round + "," + participate + "\n";
			csv_data += csv_line;
			titles.push(title);
			read_count++;
		}
		num_read++;
	}

	if( num_read>1 && read_count===0 )
	{
		if( scrol )
		{
			if( canScrollDown() )
			{
				console.log("num = " + num_read, "title ln= " + titles.length, big_elem.scrollTop);
				big_elem.scrollBy(0, 2000);
				big_elem.focus();
				num_read = 0;
			}
			else
			{
				scrol = 0;
			}
		}
		else
		{
			clearInterval(join_timer);
			console.log(csv_data);
			//create_csv();
		}
	}
	
}

function canScrollDown()
{
	//if( big_elem.scrollTop + big_elem.clientHeight<10000 )
	//{
	//	return 1;
	//}
	//return 0;
	return big_elem.scrollTop + big_elem.clientHeight < big_elem.scrollHeight;
}
