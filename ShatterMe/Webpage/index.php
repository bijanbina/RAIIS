<!doctype html>
<html class="modern-ie" lang="en-us">

<?php define('__ROOT__', "./");
define('PAGE', "Login");?>
  <head>
    <title>تنظیمات دستگاه</title>
    <link href="<?php echo __ROOT__?>CSS/google_fonts.css" rel="stylesheet" />
    <link rel="stylesheet" type="text/css" media="screen" href="<?php echo __ROOT__?>CSS/style.css" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" type="text/css" media="screen" href="<?php echo __ROOT__?>CSS/style_view.css" />
    <link rel="canonical" href="https://bijanserver.ir/" />
    <style>
      @font-face {
      font-family:"global-icons";
      src:url("Fonts/global-icons.eot");
      font-weight:normal;
      font-style:normal;
      }
      @font-face {
      font-family:"global-icons";
      src:url("<?php echo __ROOT__?>Fonts/global-icons.eot");
      src:url("<?php echo __ROOT__?>Fonts/global-icons-ie.eot#iefix") format("embedded-opentype"),
      url("<?php echo __ROOT__?>Fonts/global-icons.woff") format("woff"),
      url("<?php echo __ROOT__?>Fonts/global-icons.ttf") format("truetype"),
      url("<?php echo __ROOT__?>Fonts/global-icons.svg#global-icons") format("svg");
      font-weight:normal;
      font-style:normal;
      }
    </style>
    <link rel="stylesheet" type="text/css" media="screen" href="<?php echo __ROOT__?>CSS/auth.css" />
    
  </head>
  
  <body onbeforeunload="" class="section-home section-auth">
    <div class="topbar-space"></div>
    <div class="body">
    <h1>
      <a href="<?php echo __ROOT__?>" class="ut-logo" style="background-image: url(<?php echo __ROOT__?>Images/LogoUt.svg); display: none;">Ut File Server</a>
    </h1>

      <div class="content content-sectioned content-login">
        <section class="background">
          <div class="inner narrow">
          <a href="index.php">
            <h2>تنظیم دستگاه</h2>
					</a>
          </div>
          <div class="inner white narrow">
            <div class="row">
              <div class="col-md-12" id="form-container">
            <?php 
function test_input($data) 
{
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	echo "<div class=req-reply>";
	$ip = isset($_POST['ip']) ? test_input($_POST['ip']) : '';
	$mask = isset($_POST['mask']) ? test_input($_POST['mask']) : '';
	$gateway = isset($_POST['gateway']) ? test_input($_POST['gateway']) : '';
	$password = isset($_POST['password']) ? test_input($_POST['password']) : '';
	$ip      = ( "$ip" == '' ) ? shell_exec( "sed \"1\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$ip";
	$mask 	 = ( "$mask" == '' ) ? shell_exec( "sed \"2\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$mask";
	$gateway = ( "$gateway" == '' ) ? shell_exec( "sed \"3\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$gateway";
	if ( "$password" == "tiambms" )
	{
		if (filter_var("$ip", FILTER_VALIDATE_IP))
		{
			if (filter_var("$gateway", FILTER_VALIDATE_IP))
			{
				echo "Password Accepted</br>";
				echo "Change Setting to</br>";
				echo "	<table style=\"width:250px\">
				<tr>
					<td>IP Address:</td>
					<td>$ip</td>
				</tr>
				<tr>
					<td>Mask:</td>
					<td>$mask</td>
				</tr>
				<tr>
					<td>Gateway:</td>
					<td>$gateway</td>
				</tr>
				</table> ";
				//echo shell_exec( "whoami");
				//echo "Scripts/change_ip.sh $ip $mask $gateway";
				echo shell_exec( "Scripts/change_ip.sh \"$ip\" \"$mask\" \"$gateway\""); 
				echo "Rebooting System ...";
			}
			else
			{
				echo "You entered $gateway as gateway address which is wrong</br>go back and try again";
			}
		}
		else
		{
			echo "You entered $ip as Ip address which is wrong</br>go back and try again";
		}
	}
	else
	{
		echo "bad words</br>";
	}
	echo "</div>";
}
else
{
	echo '<form action="index.php" method="POST">
                  <div class="form-item form-item-text row">
                    <div class="form-item-text-label form-item-text-label-email"><label for="email">IP Address</label></div>
                    <div class="form-item-text-input form-item-text-input-email">
                      <div class="placeholder-wrapper">
                        <div class="placeholder" data-reactid=".1mkcpiancao.1.1.0.0"></div>
                        <input name="ip" autocomplete="off" value="" type="text" placeholder="';
  echo shell_exec( "sed \"1\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{print $2}'"); 
  echo '">
                      </div>
                    </div>
                  </div>
                  <div class="form-item form-item-text row">
                    <div class="form-item-text-label form-item-text-label-email"><label for="email">Mask</label></div>
                    <div class="form-item-text-input form-item-text-input-email">
                      <div class="placeholder-wrapper">
                        <div class="placeholder" data-reactid=".1mkcpiancao.1.1.0.0"></div>
                        <input name="mask" autocomplete="off" value="" type="text" placeholder="';
	echo shell_exec( "sed \"2\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{print $2}'");
	echo '">
                      </div>
                    </div>
                  </div>
                  <div class="form-item form-item-text row">
                    <div class="form-item-text-label form-item-text-label-email"><label for="email">Gateway</label></div>
                    <div class="form-item-text-input form-item-text-input-email">
                      <div class="placeholder-wrapper">
                        <div class="placeholder" data-reactid=".1mkcpiancao.1.1.0.0"></div>
                        <input name="gateway" autocomplete="off" value="" type="text" placeholder="';
	echo shell_exec( "sed \"3\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{print $2}'");
	echo '">
                      </div>
                    </div>
                  </div>
                  <div class="form-item form-item-password row">
                    <div class="form-item-password-label form-item-password-label-password"><label for="password">Password</label></div>
                    <div class="form-item-password-input form-item-password-input-password"><input name="password" value="" autocomplete="off" type="password"></div>
                  </div>
                  <div class="form-item row">
                    <div class="form-item-empty-label"></div>
                    <div class="form-item-empty-empty"><input type="submit" class="button button-primary" value="اعمال تغییرات"></div>
                    
                  </div>
                </form>';
} 
?>
              </div>
            </div>
          </div>
        </section>
      </div>
    </div>
  </body>
</html>
		
