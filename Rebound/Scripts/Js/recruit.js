var recr_timer;

function main_recruit()
{
    if( window.location.href.includes(".recruitee.com/o/") )
    {
        //alert(location.hostname);
        recr_timer = setInterval(recr_timeoutMain, 2000);
    }
}

function recr_timeoutMain()
{
    var fullname_objs  = $('*[placeholder="Full name"]');
    // include email address
    var email_objs     = $('*[placeholder*="email address"]');
    var phone_objs     = $('*[placeholder*="phone number"]');

    //alert(phone_objs.val().length);
    if( fullname_objs.length )
    {
        if( fullname_objs.val()=="" )
        {
            fullname_objs.attr('value', "Bijan Binaee");
        }
    }
    
    if( email_objs.length )
    {
        if( email_objs.val()=="" )
        {
            //email_objs.attr('value', "bijan@binaee.com");
            const typeInto = (el, data) => {
            // Note the use of the InputEvent constructor
                const e = new InputEvent('input', {
                    inputType: 'insertText',
                    data,
                })
                
                // Manually add the text to element.value
                el.value += data
                
                // Fire the event like you were doing
                el.dispatchEvent(e);
                //alert(data);
            }

            // Get element
            //const el = email_objs;
            const el = document.getElementById('input-candidate.email-6');

            // Example "typeInto" usage: call for each letter in the string below
            'example@example.com'.split('').forEach(letter => {
            typeInto(el, letter)
            });
        }
    }
    
    if( phone_objs.length )
    {
        if( phone_objs.val().length<6 )
        {
            //phone_objs.attr('value', "+31633009005");
            //phone_objs.val("+31633009005").trigger('change');
            phone_objs.focus();
            //var ev = new Event("input",
            //                  { bubbles: true, cancelable: true })
            //phone_objs.dispatchEvent(ev);
        }
    }
}