(function(e, t)
{
    typeof module != "undefined" && module.exports ? module.exports = t() : typeof define == "function" && define.amd ? define(t) : this[e] = t()
})("$script", function()
{
    function p(e, t)
    {
        for (var n = 0, i = e.length; n < i; ++n)
            if (!t(e[n])) return r;
        return 1
    }

    function d(e, t)
    {
        p(e, function(e)
        {
            return !t(e)
        })
    }

    function v(e, t, n)
    {
        function g(e)
        {
            return e.call ? e() : u[e]
        }

        function y()
        {
            if (!--h)
            {
                u[o] = 1, s && s();
                for (var e in f) p(e.split("|"), g) && !d(f[e], g) && (f[e] = [])
            }
        }
        e = e[i] ? e : [e];
        var r = t && t.call,
            s = r ? t : n,
            o = r ? e.join("") : t,
            h = e.length;
        return setTimeout(function()
        {
            d(e, function t(e, n)
            {
                if (e === null) return y();
                e = !n && e.indexOf(".js") === -1 && !/^https?:\/\//.test(e) && c ? c + e + ".js" : e;
                if (l[e]) return o && (a[o] = 1), l[e] == 2 ? y() : setTimeout(function()
                {
                    t(e, !0)
                }, 0);
                l[e] = 1, o && (a[o] = 1), m(e, y)
            })
        }, 0), v
    }

    function m(n, r)
    {
        var i = e.createElement("script"),
            u;
        i.onload = i.onerror = i[o] = function()
        {
            if (i[s] && !/^c|loade/.test(i[s]) || u) return;
            i.onload = i[o] = null;
            u = 1;
            l[n] = 2;
            r();
        };
        i.async = 1;
        i.src = h ? n + (n.indexOf("?") === -1 ? "?" : "&") + h : n;
        t.insertBefore(i, t.lastChild)
    }
    var e = document,
        t = e.getElementsByTagName("head")[0],
        n = "string",
        r = !1,
        i = "push",
        s = "readyState",
        o = "onreadystatechange",
        u = {},
        a = {},
        f = {},
        l = {},
        c, h;
    return v.get = m, v.order = function(e, t, n)
    {
        (function r(i)
        {
            i = e.shift(), e.length ? v(i, r) : v(i, t, n)
        })()
    }, v.path = function(e)
    {
        c = e
    }, v.urlArgs = function(e)
    {
        h = e
    }, v.ready = function(e, t, n)
    {
        e = e[i] ? e : [e];
        var r = [];
        return !d(e, function(e)
        {
            u[e] || r[i](e)
        }) && p(e, function(e)
        {
            return u[e]
        }) ? t() : ! function(e)
        {
            f[e] = f[e] || [], f[e][i](t), n && n(r)
        }(e.join("|")), v
    }, v.done = function(e)
    {
        v([null], e)
    }, v
});
(function()
{
    var e, t;
    e = window, t = document.head || document.getElementsByTagName("head")[0], e._loadScript = function(e, n)
    {
        var a = document.createElement("script"),
            c = !1;
        a.type = "text/javascript", a.async = !0, a.src = e, n && (a.onload = a.onreadystatechange = function()
        {
            c || this.readyState && "loaded" !== this.readyState && "complete" !== this.readyState || (c = !0, a.onload = a.onreadystatechange = null, t && a.parentNode && t.removeChild(a), a = void 0, n())
        }), t.insertBefore(a, t.firstChild)
    }, e._loadScripts = function(t, n)
    {
        var a, c, r;
        for (t = t.push ? t : [t], c = a = t.length, r = 0; c > r; r++) e._loadScript(t[r], function()
        {
            --a || n && n()
        })
    }, e._loadStyle = function(e)
    {
        var n;
        document.createStyleSheet ? "http" == e.slice(0, 4) ? document.createStyleSheet(e) : document.createStyleSheet().cssText = e : ("http" == e.slice(0, 4) ? (n = document.createElement("link"), n.rel = "stylesheet", n.type = "text/css", n.media = "screen", n.href = e) : (n = document.createElement("style"), n.type = "text/css", n.styleSheet ? n.styleSheet.cssText = e : n.appendChild(document.createTextNode(e))), t.insertBefore(n, t.firstChild))
    }, e._attachEvent = function(e, t, n, a)
    {
        e.addEventListener ? e.addEventListener(t, n, a || !1) : e.attachEvent && e.attachEvent("on" + t, n)
    }, e._dispatchEvent = function(e, t)
    {
        var n;
        document.createEvent ? (n = document.createEvent("HTMLEvents"), n.initEvent(t, !0, !0), n.eventName = t, e.dispatchEvent(n)) : (n = document.createEventObject(), n.eventType = n.eventName = t, n.preventDefault = function()
        {
            this.returnValue = !1
        }, e.fireEvent("on" + n.eventType, n))
    }
})();
