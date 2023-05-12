#!/usr/bin/php
<?php
$entityBody = stream_get_contents(STDIN);
// echo "Body = ", $entityBody, "\n";
parse_str($entityBody, $BODY);
?>

<?php
	$cwd = getcwd();
	$wdir = $cwd . '/data/cgi/php/saved_files/';
	// print_r($BODY);
	if ($_SERVER['REQUEST_METHOD'] == 'DELETE' && $BODY['file'] != '')
	{
		unlink($wdir . $BODY['file']);
	}
?>

<!DOCTYPE html>
<html>

<head>
	<meta charset="UTF-8">
	<title>Form 42 Webserv</title>
	<link href="/cgi/php/css/delete.css" rel="stylesheet">
</head>

<body>
<style> body {background-color: green;} </style>
<div> <a href="/cgi/php/main.php">Main</a> <a href="/cgi/php/upload.php">Upload</a> <a href="/cgi/php/post.php">Post</a> <a href="/cgi/php/delete.php">Delete</a> </div>
<h1>File Destroyer</h1>

<form action="delete.php" method="post" onsubmit="test()">
 	<label for="file"><p class="Select">Select a file to delete:</label>
  	<select name="file" id="file">
  		<option value="">Select a file</option></p>
		<?php
			$dir = scandir($wdir);
			foreach ($dir as $doc)
			{
				if ($doc != '.' && $doc != '..' && $doc != '.do_not_delete')
				{
					$op = fopen($wdir . $doc, 'r');
					echo '<option value="' . $doc . '">'. $doc .'</h1>';
				}
			}
		?>

	</select>
	<br><br>
	<input type="submit" value="delete">
</form>

<script>
	function test() {
		var _body = document.getElementById("file").value;
		fetch("delete.php",
		{
			method: 'DELETE',
			body: 'file=' + _body
		}
		);
	}
</script>

</body>
</html>
