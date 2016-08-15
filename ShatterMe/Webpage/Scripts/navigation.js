! function e(t, r, a) {
    function n(i, u) {
        if (!r[i]) {
            if (!t[i]) {
                var d = "function" == typeof require && require;
                if (!u && d) return d(i, !0);
                if (o) return o(i, !0);
                var f = new Error("Cannot find module '" + i + "'");
                throw f.code = "MODULE_NOT_FOUND", f
            }
            var l = r[i] = {
                exports: {}
            };
            t[i][0].call(l.exports, function(e) {
                var r = t[i][1][e];
                return n(r ? r : e)
            }, l, l.exports, e, t, r, a)
        }
        return r[i].exports
    }
    for (var o = "function" == typeof require && require, i = 0; i < a.length; i++) n(a[i]);
    return n
}({
    1: [function(e, t, r) {
        "use strict";

        function a(e) {
            return e && e.__esModule ? e : {
                "default": e
            }
        }
        var n = window.$,
            o = a(n);
        (0, o["default"])(".very-good-navigation-trigger").on("click", function(e) {
            e.preventDefault();
            var t = (0, o["default"])(".very-good-navigation-tabs a").add((0, o["default"])(".very-good-navigation-page")),
                r = (0, o["default"])("#very-good-navigation-page-" + (0, o["default"])(e.target).data("tab")).add((0, o["default"])(e.target));
            r.addClass("selected"), t.not(r).removeClass("selected")
        });
        var i = o["default"].trim(window.location.hash);
        i && (0, o["default"])('.very-good-navigation-tabs a[href$="' + i + '"]').trigger("click")
    }, {
        jquery: "jquery"
    }]
}, {}, [1]);
