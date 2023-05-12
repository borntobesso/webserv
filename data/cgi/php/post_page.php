#!/usr/bin/php
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Sign up page</title>
    </head>
    
    <body>
        <form action="post_handler.php" target="_self" method="POST">
            <label for="username">Username:</label><br>
            <input type="text" id="username" name="username"><br>
            <label for="favcolor">Select your favorite color:</label>
            <input type="color" id="favcolor" name="favcolor">
            <input type="submit" value="Submit">
        </form>
    </body>
</html>