/*! shivie8 | @syranide | MIT license */ ! function shivIEDocumentElements(e) {
    if (e.documentMode < 9)
        for (var a = "abbr,article,aside,audio,bdi,canvas,data,datalist,details,dialog,figcaption,figure,footer,header,hgroup,main,mark,meter,nav,output,picture,progress,section,summary,template,time,video".split(","); a[0]; e.createElement(a.pop()));
}(document)
