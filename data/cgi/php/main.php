#!/usr/bin/php

<!DOCTYPE html>
<html lang="en">	
	
<head>
	<meta charset="UTF-8">
	<title>Form 42 Webserv</title>
	<link href="/cgi/php/css/main.css" rel="stylesheet">
</head>

<body>
<div> <a href="/cgi/php/main.php">Main</a> <a href="/cgi/php/upload.php">Upload</a> <a href="/cgi/php/post.php">Post</a> <a href="/cgi/php/delete.php">Delete</a> </div>
	<div class="Banner"></div>
	<style> body {background-color: green;} </style>
	<h1>MY SPECIAL NOTEPAD</h1>
	<form action="/cgi/php/post.php" method="post">
	<style>input[type=text], select{width: 300%;
  padding: 40px 80px;
  /*margin: 8px 0;*/
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;}
	</style><p class="Filename">Note title: <input type="text" name="filename"></p><br>
	<p class="Content">Content: <input type="text" name="content"></p></br>
	<div class="Submit"><input type="submit"></div>
	</form>
</body>

</html> 
