var gpt_btn;
var gpt_count = 0;
function main_gpt()
{
    gpt_btn = document.createElement("button");
    gpt_btn.type = "button";
    gpt_btn.textContent = "Magic";
    Object.assign(gpt_btn.style, {
      position: "fixed",
      right: "50px",
      top: "45px",
      padding: "5px 10px",
      borderRadius: "10px",
      border: "1px solid rgba(0,0,0,0.2)",
      background: "#111",
      color: "#fff",
      fontSize: "14px",
      cursor: "pointer",
      boxShadow: "0 8px 24px rgba(0,0,0,0.25)",
    });
  
    gpt_btn.addEventListener("click", clickGPT);
  
    document.body.appendChild(gpt_btn);
}

async function gpt_timeoutMain()
{
    console.log("gpt_count", gpt_count);
    if( gpt_count==0 )
    {
        sendPipe("gpt", 1);
        gpt_count = 1;
    }
    else if( gpt_count==1 )
    {
        img = document.querySelector('img[alt="Uploaded image"]');
        if( !img )
        {
            return;
        }

        // Fetch the image bytes (works for data:, blob:, and CORS-enabled http(s))
        res = await fetch(img.currentSrc || img.src);
        const blob = await res.blob();

        const mime = blob.type || "image/png";
        await navigator.clipboard.write([new ClipboardItem({ [mime]: blob })]);
        window.open("https://chatgpt.com/", "_blank", "noopener,noreferrer");
        gpt_count = 2;
    }
    else if( gpt_count==2 )
    {
        gpt_btn.textContent = "Magic";
        sendPipe("gpt", 2);
        clearInterval(join_timer);
    }
}

async function clickGPT()
{
    const el = document.querySelector("div.whitespace-pre-wrap");
    await navigator.clipboard.writeText(el.textContent);
    gpt_count = 0;
    gpt_btn.textContent = "Copying";

    join_timer = setInterval(gpt_timeoutMain, 500);
}