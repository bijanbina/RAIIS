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

    dismissTryCodexPromo();
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

function dismissTryCodexPromo(options = {}) {
    const maxMs = options.maxWaitMs ?? 20000;
    const deadline = Date.now() + maxMs;
  
    function regionLooksLikeTryCodex(el) {
      if (!el || !el.textContent) return false;
      const t = el.textContent;
      if (!/try\s*codex/i.test(t)) return false;
      // Avoid matching huge subtrees (e.g. whole sidebar)
      return t.length < 4000;
    }
  
    function findCloseInCodexRegion() {
      const roots = document.querySelectorAll(
        '[role="dialog"], [data-radix-dialog-content], [data-state="open"]'
      );
  
      for (const root of roots) {
        if (!regionLooksLikeTryCodex(root)) continue;
        const closeBtn =
          root.querySelector('button[aria-label="Close"]') ||
          root.querySelector('button[aria-label^="Close"]') ||
          root.querySelector('[data-testid*="close" i]');
        if (closeBtn && closeBtn.offsetParent !== null) {
          closeBtn.click();
          return true;
        }
      }
  
      // Banner/card not always role=dialog: find “Try Codex” and climb to a small wrapper
      const walker = document.createTreeWalker(document.body, NodeFilter.SHOW_ELEMENT);
      let node;
      while ((node = walker.nextNode())) {
        if (node.children && node.children.length === 0 && /try\s*codex/i.test(node.textContent || "")) {
          let p = node.parentElement;
          for (let i = 0; i < 12 && p; i++, p = p.parentElement) {
            if (!regionLooksLikeTryCodex(p)) continue;
            const btn =
              p.querySelector('button[aria-label="Close"]') ||
              p.querySelector('button[aria-label*="close" i]');
            if (btn && btn.offsetParent !== null) {
              btn.click();
              return true;
            }
          }
        }
      }
      return false;
    }
  
    if (findCloseInCodexRegion()) return Promise.resolve(true);
  
    return new Promise((resolve) => {
      const obs = new MutationObserver(() => {
        if (findCloseInCodexRegion()) {
          obs.disconnect();
          resolve(true);
        } else if (Date.now() > deadline) {
          obs.disconnect();
          resolve(false);
        }
      });
      obs.observe(document.documentElement, { childList: true, subtree: true });
      setTimeout(() => {
        obs.disconnect();
        resolve(findCloseInCodexRegion());
      }, maxMs);
    });
  }