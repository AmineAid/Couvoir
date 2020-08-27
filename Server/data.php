<?php
if(isset($_GET['t']) AND isset($_GET['h']) AND isset($_GET['mq']) AND isset($_GET['end'])){

$mq=$_GET['mq'];
$mq=$mq/10000;
$mq2=round($mq*100000)/100000;
$current = "". date('d-m-Y / H:i:s / '). " <b>T:</b> ". htmlspecialchars($_GET['t']). " / <b>H</b>: ". htmlspecialchars($_GET['h']). " / <b>MQ:</b> ". htmlspecialchars($mq2). "/ <b>Co2:</b> ". htmlspecialchars($co2). ".<br>";
file_put_contents("log.php", $current, FILE_APPEND);

/*

$start1=$data[0];
	$date=$data[1];
	$time=$data[2];
	$t=$data[3];
	$h=$data[4];
	$co2=$data[5];
	$end1=$data[6];

*/
//$current = "data;". date('d-m-Y;H:i:s;'). ";". htmlspecialchars($_GET['t']). ";". htmlspecialchars($_GET['h']). ";". htmlspecialchars($mq2). ";". htmlspecialchars($co2). ";end";
$current = "Start;". date('d-m-Y;H:i:s'). ";". htmlspecialchars($_GET['t']). ";". htmlspecialchars($_GET['h']). ";". htmlspecialchars($mq2). ";end";
file_put_contents("live.txt", $current);
echo file_get_contents( "set.txt" );
}

?>