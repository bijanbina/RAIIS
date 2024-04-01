var gacc_timer;
var gacc_page1_done = 0;
var gacc_page2_done = 0;
var gacc_page3_done = 0;
var gacc_is_present = 0;

function main_gaccount()
{
    if( window.location.href.includes("v3/signin/confirmidentifier") )
    {
        gacc_timer = setInterval(gacc_timeoutMain, 2000);
    }
}

function gacc_timeoutMain()
{
    var page1_txt   = "To help keep your account secure, Google needs to verify it’s you. Please sign in";
    var page1_query = "div:contains('" + page1_txt + "')";

    var page2_txt   = "Enter your password";
    var page2_query = "div:contains('" + page2_txt + "')";

    var page3_txt   = "Get a verification code from the ";
    var page3_query = "div:contains('" + page3_txt + "')";
    //alert($(page2_query).length);
    if( $(page1_query).length && gacc_page1_done==0 )
    {
        $("span:contains('Next')").click();
        gacc_page1_done = 1;
    }
    else if( $(page2_query).length && gacc_page2_done==0 )
    {
        $("span:contains('Next')").click();
        gacc_page2_done = 1;
    }
    else if( $(page3_query).length && gacc_page3_done==0 )
    {
        if( $("#totpPin").val()=="" )
        {
            var otp = getOTP("uw6idor4b77nyl5hfblfdrdw5cjosbix");
            $("#totpPin").val(otp);
        }
        else
        {
            $("span:contains('Next')").click();
            gacc_page3_done = 1;
        }
    }
    else if( gacc_page1_done && gacc_page2_done && gacc_page3_done )
    {
        clearInterval(gacc_timer);
    }
}

function dec2hex(s)
{
        return (s < 15.5 ? "0" : "") + Math.round(s).toString(16);
};

function hex2dec(s)
{
    return parseInt(s, 16);
};

function leftpad(s, l, p)
{
    if(l + 1 >= s.length)
    {
        s = Array(l + 1 - s.length).join(p) + s;
    }
    return s;
};

function base32tohex(base32)
{
    var base32chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    let bits = "";
    let hex = "";
    for(let i = 0; i < base32.length; i++)
    {
        var val = base32chars.indexOf(base32.charAt(i).toUpperCase());
        bits += leftpad(val.toString(2), 5, '0');
    }
    for(let i = 0; i + 4 <= bits.length; i+=4)
    {
        var chunk = bits.substr(i, 4);
        hex = hex + parseInt(chunk, 2).toString(16) ;
    }
    return hex;
};

function getOTP(secret)
{
    let otp;
    var epoch = Math.round(new Date().getTime() / 1000.0);
    var time = leftpad(dec2hex(Math.floor(epoch / 30)), 16, "0");
    var hmacObj = new jsSHA(time, "HEX");
    var hmac = hmacObj.getHMAC(base32tohex(secret), "HEX", "SHA-1", "HEX");
    var offset = hex2dec(hmac.substring(hmac.length - 1));
    otp = (hex2dec(hmac.substr(offset * 2, 8)) & hex2dec("7fffffff")) + "";
    otp = otp.substr(otp.length - 6, 6);
    return otp;
    //return time;
};