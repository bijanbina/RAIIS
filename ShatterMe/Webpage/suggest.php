<?php $name = $email  = "";
function generateRandomString($length = 10) {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[rand(0, $charactersLength - 1)];
    }
    return $randomString;
}
$query = isset($_GET['q']) ? test_input($_GET['q']) : '';
	function test_input($data) {
		$data = trim($data);
		$data = stripslashes($data);
		$data = htmlspecialchars($data);
		return $data;
	}
$out = array("$query ", "$query ", "$query ", "$query ", "$query ", "$query ", "", "", "", "", "", "", "");
$out[1] .= generateRandomString(3);
$out[2] .= generateRandomString(3);
$out[3] .= generateRandomString(3);
$out[4] .= generateRandomString(3);
$out[5] .= generateRandomString(3);  ?>
{"group_order":["query"],"results":{"query":[
{"text":"<?php echo $out[1]; ?>","type":"query"},
{"text":"<?php echo $out[2]; ?>","type":"query"},
{"text":"<?php echo $out[3]; ?>","type":"query"},
{"text":"<?php echo $out[4]; ?>","type":"query"},
{"text":"<?php echo $out[5]; ?>","type":"query"}]}}
