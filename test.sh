Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

printf "\n----- GET -----\n"

url="http://127.0.0.1:8000"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

url="http://127.0.0.1:8000/static/index.html"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

url="http://127.0.0.1:8000/cgi/php/main.php"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

url="http://127.0.0.1:8000/notfound"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

chmod 111 data/test/no_perm_file
url="http://127.0.0.1:8000/test/no_perm_file"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url
chmod 777 data/test/no_perm_file

url="http://127.0.0.1:8002"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

url="http://127.0.0.2:8004/static/index.html"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

url="http://127.0.0.1:8888/static/index.html"
echo -e "${Red}url : $url${White}"
curl -I -X GET $url

printf "\n----- POST -----\n"

url="http://127.0.0.1:8000/static"
echo -e "${Red}url : $url${White}"
curl -I -X POST $url

url="http://127.0.0.1:8004/"
echo -e "${Red}url : $url${White}"
curl -X POST $url -H "Content_Type:plain/text" --data "12345678912"
printf "\n\n"

url="http://127.0.0.1:8002/static"
echo -e "${Red}url : $url${White}"
curl -I -X POST $url

url="http://127.0.0.1:8002/static"
echo -e "${Red}url : $url${White}"
curl -X POST $url -H "Content_Type:plain/text" --data "coucou"

printf "\n\n----- DELETE -----\n"

echo "this is file 1" > data/test/file1 
echo "this is file 2" > data/test/file2 
echo "this is file 3" > data/test/file3 

url="http://127.0.0.1:8002/test/file1"
echo -e "${Red}url : $url${White}"
curl -I -X DELETE $url

url="http://127.0.0.2:8004/test/file2"
echo -e "${Red}url : $url${White}"
curl -I -X DELETE $url

printf "\n----- UNKNOWN -----\n"

url="http://127.0.0.1:8000"
echo -e "${Red}url : $url${White}"
curl -I -X UNKNOWN $url

url="http://127.0.0.1:8002"
echo -e "${Red}url : $url${White}"
curl -I -X WAZAH $url