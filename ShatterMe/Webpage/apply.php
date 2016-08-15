<?php 
$ip = isset($_POST['ip']) ? test_input($_POST['ip']) : '';
$mask = isset($_POST['mask']) ? test_input($_POST['mask']) : '';
$gateway = isset($_POST['gateway']) ? test_input($_POST['gateway']) : '';
$password = isset($_POST['password']) ? test_input($_POST['password']) : '';
$ip      = ( "$ip" == '' ) ? shell_exec( "sed \"1\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$ip";
$mask 	 = ( "$mask" == '' ) ? shell_exec( "sed \"2\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$mask";
$gateway = ( "$gateway" == '' ) ? shell_exec( "sed \"3\"\"q;d\" Scripts/ip_address | awk -F \"=\" '{printf \"%s\",$2}'") : "$gateway";
function test_input($data) 
{
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
} ?>
<?php
if ( "$password" == "tiambms" )
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
}
else
{
	echo "bad words</br>";
}
?>
