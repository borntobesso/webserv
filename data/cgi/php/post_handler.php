#!/usr/bin/php
<?php

    $fileContent = file_get_contents('/mnt/nfs/homes/sojung/Documents/projets/42_webserv/srcs/webserver/.file');

    print "<html>\n";
    print "<head>\n";
    print "<title>User info POST ok</title>\n";
    print "</head>\n";
    print "<body>\n";
    print $fileContent;


?>