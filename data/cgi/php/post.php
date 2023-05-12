#!/usr/bin/php
<?php
$entityBody = stream_get_contents(STDIN);
// echo "Body = ", $entityBody, "\n";
parse_str($entityBody, $BODY);
// print_r($BODY);
?>

<?php
	// print_r($BODY);
	$cwd = getcwd();
	$wdir = $cwd . '/data/cgi/php/';
	if ($_SERVER['REQUEST_METHOD'] == 'POST' && $BODY['filename'] != "")
	{
		$upload_dir = '/data/cgi/php/saved_files/';
		if ($_SERVER['UPLOAD_DIR'])
			$upload_dir = $_SERVER['UPLOAD_DIR'];
		$nfile = $BODY['filename'];
		$filename =  $cwd . $upload_dir . str_replace('"', "", $nfile);;
		$file = fopen($filename, "w") or die ("Unable to open file");
		fwrite($file, $BODY['content']);
	}
?>

<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8">
	<title>Form 42 Webserv</title>
	<link href="/cgi/php/css/post.css" rel="stylesheet">
</head>

<body>
		<style> body {background-color: green;} </style>
<div> <a href="/cgi/php/main.php">Main</a> <a href="/cgi/php/upload.php">Upload</a> <a href="/cgi/php/post.php">Post</a> <a href="/cgi/php/delete.php">Delete</a> </div>
	<?php
		$savedir = $wdir . 'saved_files/';
		$dir = scandir($savedir);
		foreach ($dir as $doc)
		{
			if ($doc != '.' && $doc != '..' && $doc != '.do_not_delete')
			{
				$op = fopen($savedir . $doc, 'r');
				echo' <style>
				h1 {}</style>';
				echo '<h1>' . $doc . '</h1>';
				echo' <style>
				h2 {}</style>';
				echo '<h2>' . fread($op, filesize($savedir . $doc)) . '</h2>';
				echo '<a href="'. 'saved_files/' . $doc .'" download>';
				echo '<img src="'. 'images/folder.jpeg' .'" alt="Download">';
			  	echo '</a>';
			}
		}
		
	?>
</body>

</html>
