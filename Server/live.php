	<meta http-equiv="refresh" content="30" /><?php
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

	$now = time(); // or your date as well
	$your_date = strtotime($fday);
	$datediff = $now - $your_date;

$datediff = round($datediff / (60 * 60 * 24));

	if($start2=="start" && $end2=="end"){
	}
	echo '
	<body style="background:#990000;">
		<div align="center" >
			<table align="center" width="90%" style="background:#990000;">

				<tr>
					<td colspan="3" align="center"><font size="20" style="color:white;font-family: Bauhaus 93;">HatchProTech</font></td></tr>
				<tr>
					<td colspan="3" align="center"><h4 style="color:white;">by KOUADRI</h2></td></tr>
				<tr>
					<td align="center" >
						<table style="width:180px;background:#999999; padding:10px;border:solid 1px grey; border-radius:2px;">
							<tr style="border:10px;"><td rowspan="2"><img src="t.png" width="25"></td><td align="center"> '.$t.'</td><td rowspan="2"> &#176;C </td></tr>
							<tr><td style="font-size:10px;"><u><i>Set:'.$tset.'-Max: '.$cooltset.' </i></u></td></tr></table>
					</td>
					<td align="center"  >
						<table style="width:180px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;">
							<tr><td rowspan="2"><img src="h.png" width="40"></td><td> '.$h.'</td><td rowspan="2"> % </td></tr>
							<tr><td style="font-size:10px;"><u><i>Set: '.$hset.'</i></u></td></tr></table>
					</td>
					<td align="center"  >
						<table style="width:180px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;">
							<tr><td rowspan="2"><img src="c.png" width="40"></td><td> '.$co2.'</td><td rowspan="2"> % </td></tr>
							<tr><td style="font-size:10px;"><u><i>Set: '.$co2set.'</i></u></td></tr></table>
					</td></tr>
				<tr>
					<td colspan="3" align="center"><br><br>
					<table style="width:180px;height:60px;background:#999999;  padding:10px; border:solid 1px grey; border-radius:2px;"><tr><td align="center">
						'.$date.'   '.$time.'<br>Day '.$datediff.'</td></tr></table>

					</td></tr>
				<tr>
					<td></td><td></td>
					<td align="right">
						<table style="background:#666666;  padding:10px; border:solid 1px grey; border-radius:2px;"><tr>
						<td style="border:10px;">
						<a href="index.php" style="text-decoration:none; color:black;">Main Menu</a></td></tr></table>
					</td>

	</body>'

	?>