	<?php
	if(isset($_POST['tset']) AND $_POST['tset'] != "" ){
		$start3="Start";
		$tset=$_POST['tset'];
		$cooltset=$_POST['tset'];
		$hset=$_POST['hset'];
		$co2set=$_POST['co2set'];
		$cooltset=$_POST['cooltset'];
		$fday=$_POST['fday'];
		$end3="end";
$myfile = fopen("set.txt", "w") or die("Unable to open file!");
$txt = "$start3;$tset;$cooltset;$hset;$co2set;$fday;$end3";
fwrite($myfile, $txt);
fclose($myfile);
echo '<script>alert("Eregistré");</script>';
	}
	$data = file_get_contents( "live.txt" );
	$data = explode(";",$data);
	$start1=$data[0];
	$date=$data[1];
	$time=$data[2];
	$t=$data[3];
	$h=$data[4];
	$co2=$data[5];
	$end1=$data[6];
	if($start1=="start" && $end1=="end"){
	}
	$data = file_get_contents( "set.txt" );
	$data = explode(";",$data);
	$start2=$data[0];
	$tset=$data[1];
	$cooltset=$data[2];
	$hset=$data[3];
	$co2set=$data[4];
	$fday=$data[5];
	$end2=$data[6];

	if($start2=="start" && $end2=="end"){
	}

	echo '
	<body style="background:#990000;">
	
	<form id="setform" method="post">
		<div align="center" >
			<table align="center" width="90%" style="background:#990000;">

				<tr>
					<td colspan="3" align="center"><font size="20" style="color:white;font-family: Bauhaus 93;">HatchProTech</font></td></tr>
				<tr>
					<td colspan="3" align="center"><h4 style="color:white;">by KOUADRI</h2></td></tr>
				<tr>
					<td align="center" >
						<table style="width:180px;background:#999999; padding:10px;border:solid 1px grey; border-radius:2px;">
							<tr style="border:10px;"><td><img src="t.png" width="40"></td><td align="center"><input style="background:grey;width:60px;" name="tset"  autocomplete="off" value="'.$tset.'"> C</td></tr></table>
					</td>
					<td align="center"  >
						<table style="width:180px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;">
							<tr style="border:10px;"><td><img src="h.png" width="30"></td><td align="center"><input style="background:grey;width:60px;" name="hset"  autocomplete="off" value="'.$hset.'"> %</td></tr></table>
					</td>
					<td align="center"  >
						<table style="width:180px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;">
							<tr style="border:10px;"><td><img src="c.png" width="40"></td><td align="center"><input style="background:grey;width:60px;" name="co2set"  autocomplete="off" value="'.$co2set.'"> %</td></tr></table>
					</td></tr>
				<tr>
				<td align="center" ><br><br>
						<table style="width:180px;background:#999999; padding:10px;border:solid 1px grey; border-radius:2px;">
							<tr style="border:10px;"><td><img src="cooling.png" width="30"></td><td align="center"><input style="background:grey;width:60px;" name="cooltset"  autocomplete="off" value="'.$cooltset.'"> C</td></tr></table>
					</td>
					<td colspan="2" align="center"><br><br>
					<table style="width:180px;height:60px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;">
					<tr style="border:10px;"><td align="center">First day<br><input name="fday" style="background:grey; width:90px;"  autocomplete="off" value="'.$fday.'"></td></tr></table>


					</td></tr>
				<tr>
					<td align="center"><br>
						<table style="background:#666666;  padding:10px; border:solid 1px grey; border-radius:2px;"><tr>
						<td style="border:10px;">
						<a href="#" onclick="document.getElementById("setform").submit()" 
						style="text-decoration:none; color:black;">Reset</a></td></tr></table>
					</td>

					<td align="center"><br>
						<table style="background:#666666;  padding:10px; border:solid 1px grey; border-radius:2px;"><tr>
						<td style="border:10px;">
						<a href="#" onclick="document.getElementById(\'setform\').submit()" style="text-decoration:none; color:black;">Save</a></td></tr></table>
					</td>
					<td align="right">
						<table style="background:#666666;  padding:10px; border:solid 1px grey; border-radius:2px;"><tr>
						<td style="border:10px;">
						<a href="index.php" style="text-decoration:none; color:black;">Main Menu</a></td></tr></table>
					</td>
</form>
	</body>'

	?>