<?php 
if(isset($_GET['cod']) && isset($_GET['tag'])){
	$cod = $_GET['cod'];
	$tag = $_GET['tag'];

	$con = mysqli_connect('localhost', 'root', '', 'secdoorlock');
		if($cod == '0'){//Database empty
			$sql = 'SELECT * FROM tagids';
			$result = mysqli_query($con, $sql);
			if(mysqli_num_rows($result) == 0){
				echo json_encode(array('stat' => 1));
			}else{
				echo json_encode(array('stat' => 0));
			}
		}
		else if($cod == '1'){//INSERE UMA NOVA TAG
			$sql = "INSERT INTO `tagids`
			(`tagid`, `created`, `modified`)
			VALUES ('$tag', NOW(), NOW())";
			$result = mysqli_query($con, $sql);
			
			echo json_encode(array('stat' => 1));
		}
		else if($cod == '2'){//CONFERE SE A TAG EXISTE
			$sql = "SELECT * FROM `tagids` WHERE `tagid` = '$tag'";
			$result = mysqli_query($con, $sql);
			if(mysqli_num_rows($result) == 1){
				echo json_encode(array('stat' => 1));
			}else{
				echo json_encode(array('stat' => 0));
			}
		}else if($cod == '3'){
			$sql = "SELECT `users`.`username` FROM `tagids` INNER JOIN `tagids_users` ON `tagids`.`id` = `tagids_users`.`tagid_id` INNER JOIN `users` ON `users`.`id` = `tagids_users`.`user_id` WHERE `tagids`.`tagid` = '$tag' AND `users`.`role` = 'admin'";
			$result = mysqli_query($con, $sql);
			if(mysqli_num_rows($result) == 1){
				echo json_encode(array('stat' => 1));
				
			}else{
				echo json_encode(array('stat' => 0));
			}
		}else if($cod == '4'){
			$sql = "SELECT * FROM `tagids` INNER JOIN `tagids_users` ON `tagids`.`id` = `tagids_users`.`tagid_id` WHERE `tagids`.`tagid` = '$tag'";
			$result = mysqli_query($con, $sql);
			if(mysqli_num_rows($result) == 1){
				echo json_encode(array('stat' => 1));
				$row = mysqli_fetch_array($result);
				$tagid = $row['tagid_id'];
				$userid = $row['user_id'];

				$sql = "INSERT INTO `accesslogs`
				(`tagid_id`, `user_id`, `created`)
				VALUES ('$tagid', '$userid', NOW())";
				$result = mysqli_query($con, $sql);				
			}else{
				echo json_encode(array('stat' => 0));
			}

		}else if($cod == '5'){
			$sql = "SELECT * FROM `users` WHERE `role` = 'admin'";
			$result = mysqli_query($con, $sql);
			$row = mysqli_fetch_array($result);
			$userid = $row['id'];

			$sql = "SELECT * FROM `tagids` WHERE `tagid` = '$tag'";
			$result = mysqli_query($con, $sql);
			$row = mysqli_fetch_array($result);
			$tagid = $row['id'];

			$sql = "INSERT INTO `tagids_users`
			(`tagid_id`, `user_id`) VALUES ('$tagid', '$userid')";
			$result = mysqli_query($con, $sql);

			echo json_encode(array('stat' => 1));
		}else if($cod == '6'){
			$sql = "SELECT * FROM `tagids` WHERE `tagid` = '$tag'";
			$result = mysqli_query($con, $sql);
			$row = mysqli_fetch_array($result);
			$tagid = $row['id'];

			$sql = "DELETE FROM `tagids_users` WHERE `tagid_id` = '$tagid'";
			$result = mysqli_query($con, $sql);

			$sql = "DELETE FROM `tagids` WHERE `id` = '$tagid'";
			$result = mysqli_query($con, $sql);

			echo json_encode(array('stat' => 1));
		}

	}else{
		echo json_encode(array('stat' => "Campo nao definido"));
	}

	mysqli_close($con);
	?>