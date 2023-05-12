#!/usr/bin/php
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="UTF-8">
	<title>Form 42 Webserv</title>
	<link href="/cgi/php/css/upload.css" rel="stylesheet">	
</head> 
 
<body>
	<style> body {background-color: green;} </style>
	<div> <a href="/cgi/php/main.php">Main</a> <a href="/cgi/php/upload.php">Upload</a> <a href="/cgi/php/post.php">Post</a> <a href="/cgi/php/delete.php">Delete</a> </div>
	
    <h1>Uploader</h1>
  
    <form action="/cgi/php/post.php" method="post" enctype="multipart/form-data">       
        <label for="myfile"><p class="Select">Select a file:</label>
        <input type="file" id="myfile" name="myfile" />
        <br /><br />
        <input type="submit" /></p>
    </form>
</body>
  
</html>
