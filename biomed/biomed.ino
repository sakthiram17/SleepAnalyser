 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#include<string.h>
#ifndef STASSID
#define STASSID "redmi"
#define STAPSK  "redmi1021"
#include <cstring>
#endif
#define _SSID "redmi"        
#define _PASSWORD "redmi1021"    
#define PROJECT_ID "sleepanalyzer2-b9951-default-rtdb"
int sensorpin = 7;
int switchpin = 5;
const int wifi_rest = 3;
char* sleeplist = "";
String sleeplist1;
char* timearray = "";
  Firebase firebase("sleepanalyzer2-b9951-default-rtdb");    
char* FIREBASE_HOST =  "your FIREBASE HOST";
char * FIREBASE_AUTH = "Your secret";
int t = 0;
String dayurl = "/Day";
String dataurl = "/data";
char index_html[] PROGMEM ={"<!doctype html>\n<html lang=\"en\">\n  <head>\n    <meta charset=\"utf-8\">\n    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=0.7\">\n<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n<style>\nbody {\n  font-size:16px;\n  color:#fff;\n\n\n  background-size:cover;\n  margin:0px;\n}\nhtml{\n  background: linear-gradient(to right top, #051937, #004d7a, #008793, #00bf72, #a8eb12) no-repeat center center fixed; \n  -webkit-background-size: cover;\n  -moz-background-size: cover;\n  -o-background-size: cover;\n  background-size: cover;\n\n}\n#centerbutton{\n  display: flex;\n  justify-content:center;\n}\n#centerrun{\n  display: flex;\n  justify-content:center;\n}\n#centerclock{\n  display: flex;\n  color:black;\n  justify-content:center;\n}\n\n#clock{\n  color:black;\n  font-size:25px; \n}\n\n\n.navbar{\n  width: 100%;\nbackground:black;\n\n  color:black;\n  width:100%;\n  font-size:20px;\n  opacity:0.9;\n  margin-botom:50px;\n  \n\n}\n.navbar li{\n  text-decoration:none;\n  display:inline;\n  padding: 20px;\n}\nli a{\n  text-decoration:none;\n  color:white;\n  padding:20px;\n\n}\nul{\n  list-style-type:none;\n  margin:0;\n  padding:20px 0px 20px 0px;\n}\n.navbar a:hover{\n  background:blue;\nopacity:1;\n}\n.navbar a:active{\nbackground-color:#0091ff;\nopacity:0.7;\n}\n@media (min-width: 992px) {\n  .col-lg-1, .col-lg-2, .col-lg-3, .col-lg-4, .col-lg-5, .col-lg-6, .col-lg-7, .col-lg-8, .col-lg-9, .col-lg-10, .col-lg-11, .col-lg-12 {\n    float: left;\n  }\n  .col-lg-1 {\n    width: 8.33%;\n  }\n  .col-lg-2 {\n    width: 16.66%;\n  }\n  .col-lg-3 {\n    width: 25%;\n  }\n  .col-lg-4 {\n    width: 33.33%;\n  }\n  .col-lg-5 {\n    width: 41.66%;\n  }\n  .col-lg-6 {\n    width: 50%;\n  }\n  .col-lg-7 {\n    width: 58.33%;\n  }\n  .col-lg-8 {\n    width: 66.66%;\n  }\n  .col-lg-9 {\n    width: 74.99%;\n  }\n  .col-lg-10 {\n    width: 83.33%;\n  }\n  .col-lg-11 {\n    width: 91.66%;\n  }\n  .col-lg-12 {\n    width: 100%;\n  }\n}\n#section1{\n  font-size:20px;\n}\n/********** Medium devices only **********/\n\n@media (max-width: 929px) {\n  .col-s-1, .col-s-2, .col-s-3, .col-s-4, .col-s-5, .col-s-6, .col-s-7, .col-s-8, .col-s-9, .col-s-10, .col-s-11, .col-s-12 {\n    float: left;\n  }\n  .col-s-1 {\n    width: 8.33%;\n  }\n  .col-s-2 {\n    width: 16.66%;\n  }\n  .col-s-3 {\n    width: 25%;\n  }\n  .col-s-4 {\n    width: 33.33%;\n  }\n  .col-s-5 {\n    width: 41.66%;\n  }\n  .col-s-6 {\n    width: 50%;\n  }\n  .col-s-7 {\n    width: 58.33%;\n  }\n  .col-s-8 {\n    width: 66.66%;\n  }\n  .col-s-9 {\n    width: 74.99%;\n  }\n  .col-s-10 {\n    width: 83.33%;\n  }\n  .col-s-11 {\n    width: 91.66%;\n  }\n  .col-s-12 {\n    width: 100%;\n  }\n}\n.section{\n  color: #002a69;\n  background-color:white;\n  margin: 20px;\n  padding: 0px 0px 0px 00px;\n  opacity: 0.8;\n height:600px;\n\n\n}\n*{\n  box-sizing: border-box;\n}\nspan{\n  background-color:black;\n  color:white;\n  width:100%;\n  display:block;\n  text-align:center;\n  font-size:30px;\n  padding:5px;\n\n}\n\n#prev{\n  position:relative;\n padding:10px 20px;\n float: left;\n margin-left:50px;\n background-color:#4CAF50;\n color:white;\n border:none;\n}\n#next{\nposition: relative;\n padding:10px 20px;\n float: right;\n margin-right: 50px;\n background-color:#4CAF50;\n color: white;\n border:none;\n}\n#button1{\n  background-color: #4CAF50; /* Green */\n  border: red;\n  color: white;\n  padding: 15px 32px;\n  text-align: center;\n  text-decoration: none;\n  font-size: 16px;\n\n}\n#button1:hover{\n  background-color:blue;\n  opacity:0.9;\n}\np{\n  \n}\nimg{\n\n}\nh1{\n  background-color:red;\n}\n#graph1{\n  display:inline;\n  align: center;\n  display: flex;\n  justify-content: center;\n    size:inherit;\n  \n}\n#graph2{\n  display:inline;\n align: center;\n display: flex;\n  justify-content: center;\n    size:inherit;\n\n}\n#bargraph{\n  display:inline;\n align: center;\n display: flex;\n  justify-content: center;\n  size:inherit;\n\n}\n#hidden{\n  display:none;\n}\np{\n  font-size:20px;\n}\n#working{\n  background-color:#e60000;\n  width:200px;\n   padding: 15px 32px;\n  text-align:center;\n  color:white;\n \n}\n</style>\n \n    <title>Sleep Analyser</title>\n   \n  </head>\n<body> \n<nav class =\"navbar\">\n<ul>\n<li><a href = \"192.168.73.43\">APP</a></li>\n<li><a href = \"https://sakthiram17.github.io/FirstRepo/projects/biomed/sleepinducer/home.html\">Guide</a></li>\n</ul>\n</nav>\n<div class=\"row\">\n  <div class=\"col-lg-6 col-md-6 col-s-12\">\n    <div class = \"section\" id =\"secion1\">\n    <span class = \"sectiont\">Data Fetcher</span>\n  <p id =\"text\">\n  <div id =\"centerbutton\">\n\n  <button id = \"button1\" type = \"button\">Get Sleep Analysis</button>\n</div>\n    \n  </p>\n <div id = \"centerrun\">\n  <p id =\"working\">The Device is not Running</p>\n  </div>\n  <div id = \"centerclock\">\n  <p id =\"clock\"></p>\n  </div>\n\n</div></div>\n\n <div class=\"col-lg-6 col-md-6 col-s-12\">\n    <div class = \"section\">\n    <span class = \"sectiont\">Movements detected</span>\n  <p>\n\n  <div id = \"graph1\"></div>\n     <button id = \"prev\" type = \"button\"><</button>\n   <button id = \"next\" type = \"button\">></button>\n  </p></div></div>\n \n <div class=\"col-lg-6 col-md-6 col-s-12\">\n    <div class = \"section\">\n    <span class = \"sectiont\">Distribution of Sleep</span>\n  <p>\n    <div id = \"graph2\"></div>\n  </p></div></div>\n  <div class=\"col-lg-6 col-md-6 col-s-12\">\n    <div class = \"section\">\n    <span class = \"sectiont\">Sleep Distribution Bar Chart</span>\n  <p>\n    <div id = \"bargraph\"></div>\n  </p></div></div>\n\n</div>\n \n<script src='https://cdn.plot.ly/plotly-2.4.2.min.js'></script> \n<script type=\"text/javascript\">\nnext_click = 0;\nprev_click = 0;\ndocument.getElementById(\"button1\").addEventListener(\"click\", Plot_Graphs);\nvar data_set = [];\nfunction setTime()\n{\nvar d = new Date();\nvar Hour = d.getHours();\nvar minute = d.getMinutes();\nvar second = d.getSeconds();\ndocument.getElementById(\"clock\").textContent =String(Hour)+':'+String(minute)+':'+String(second);}\nvar x = [];\nvar time = [];\nfor (var i = 0; i < 500; i ++) {\n  x[i] = Math.random();\n}\nvar trace = {\n    x: x,\n    type: 'histogram',\n  };\nvar data = [trace];\nvar data2 = [{\n  values: [19, 26, 55],\n  labels: ['REM Sleep', 'Deep Sleep', 'Light Sleep','Awake'],\n  type: 'pie'\n}];\nvar layout = {\n  autosize: true,\n  width: 400,\n  height: 400,\n  margin: {\n    l: 5,\n    r: 5,\n    b: 10,\n    t: 10,\n    pad: 4\n  },\n};\nvar data4 = [\n  {\n    x: ['REM SLeep (in hours)', 'Deep Sleep (in hours)', 'Light Sleep(in hours)','Awake (in hours)'],\n    y: [3, 4, 1,2],\n    type: 'bar',\n     marker: {\n    line: {\n      width: 2\n    }\n  }\n    \n  }\n];\n\ntime_iter = 0;\ntime = [];\nPlotly.newPlot('graph2', data2,layout);\nPlotly.newPlot('graph1', data,layout);\nPlotly.newPlot('bargraph',data4);\n\nsetInterval(function() {\n  \n  getData();\n    setTime();\n}, 1000); \nfunction getData() {\n  var xhttp = new XMLHttpRequest();\n  xhttp.onreadystatechange = function() {\n     var l = this.responseText.length;\n    if (this.readyState == 4 && this.status == 200&& (this.responseText[l-1]==0||this.responseText[l-1]==1)) {\n      data_set = this.responseText;\n      document.getElementById(\"working\").textContent = \"The Device is Running\";\n      document.getElementById(\"working\").style.backgroundColor = \"#4CAF50\";\n        var d = new Date();\n    var minutes = d.getMinutes();\n    var seconds = d.getSeconds();\n    var hours = d.getHours();\n    var temp = String(hours)+':'+String(minutes)+':'+String(seconds);\n    //time.push(temp);\n    }\n   \n    else if(this.responseText[l-1] == 's')\n    {\n      document.getElementById(\"working\").textContent = \"The Device is not Running\";\n      document.getElementById(\"working\").style.backgroundColor = \"#e60000\";\n    }\n  \n  };\n  xhttp.open(\"GET\", \"app\", true);\n  xhttp.send();\n\n}\n\n/*function getData() {\n  var xhttp = new XMLHttpRequest();\n  xhttp.onreadystatechange = function() {\n\n    if(this.responseText == \"stop\")\n    {\n      document.getElementById(\"working\").textContent = \"The Device is not Running\";\n      document.getElementById(\"working\").style.backgroundColor = \"#e60000\";\n    }\n\n    if (this.readyState == 4 && this.status == 200&& (this.responseText==0||this.responseText==1)) {\n      data_set.push(this.responseText);\n      document.getElementById(\"working\").textContent = \"The Device is Running\";\n      document.getElementById(\"working\").style.backgroundColor = \"#4CAF50\";\n        var d = new Date();\n    var minutes = d.getMinutes();\n    var seconds = d.getSeconds();\n    var hours = d.getHours();\n    time.push(String(hours)+\":\"+String(minutes)+\":\"+String(seconds));\n    }\n   \n  \n  };\n  xhttp.open(\"GET\", \"app\", true);\n  xhttp.send();\n  \n}*/\ndocument.getElementById(\"prev\").addEventListener(\"click\", move_prev);\ndocument.getElementById(\"next\").addEventListener(\"click\", move_next);\nfunction move_next()\n{ \n  if(next_click>prev_click)\n  {\n    alert(\"You are at the end of Graph\");\n  }\n  time1 = time.slice(data_set1.length-100,data.set1.length-1)\n  next_click = next_click+1;\n  data_set1 = data_set.split(\"\");\n new_data_set = data_set1.slice(data_set1.length-(prev_click-next_click)*100,data_set1.length-(prev_click-next_click-1)*100);\nvar data_0 = [\n  {\n    x: time1,\n    y: new_data_set,\n    type: 'bar'\n  }\n];\n\nPlotly.newPlot('graph1', data_0);\n}\nfunction move_prev()\n{ time1 = time.slice(data_set1.length-100,data_set1.length-1)\n  if((prev_click*99>data_set.length))\n  {\n    alert(\"You are at the end of Graph\");\n  }\n  prev_click = prev_click +1;\n  data_set1 = data_set.split(\"\");\n new_data_set = data_set1.slice(data_set1.length-(prev_click-next_click)*100,data_set1.length-(prev_click-next_click-1)*100)\nvar data_0 = [\n  {\n    x: time1,\n    y: new_data_set,\n    type: 'bar'\n  }\n];\n\nPlotly.newPlot('graph1', data_0);\n}\nfunction Plot_Graphs()\n{\n  if(data_set.length>1&&data_set!=null)\n  {\n  x = data_set.split(\"\");\n}\n//if(data_set.length<120)\n//{\n // alert(\"Device has ran for less than a hour please come back later\");\n // return;\n//}\n\n\n/*l2 = time.length;\nl1 = data_set.length;\nif(l1!=l2)\n{\n  while(l1!=l2){\n  start_time = time[0].split(\":\");\n  console.log(start_time[0]);\n  console.log(start_time[1]);\n  console.log(start_time[2]);\n  if((l1-l2)%60<60)\n  { seconds = String((parseInt(start_time[2])-(l1-l2)%60));\n    console.log(seconds);\n    if(parseInt(seconds)>0)\n    {\n    t = start_time[0]+\":\"+start_time[1]+\":\"+seconds;\n    }\n    else{\n      if(parseInt(start_time[1])-1<0){\n      var hours_fin = String(parseInt(start_time[0]) - 1);\n      t = hours_fin+\":\"+string(60-parseInt(start_time[1]))+\":\"+start_time[2];\n\n      }else{\n\n      seconds = String(60-parseInt(seconds));\n      var newmin = String(parseInt(start_time[1])-1);\n      t = start_time[0]+\":\"+newmin+\":\"+seconds;\n     console.log(seconds);}\n    }\n   l1 = l1-1;\n  }\n  else if(((l1-l2)%60)>=60&&((l1-l2)%60<3600))\n  {\n    var extramin = (l1-l2)%60;\n    var min_fin = -extramin + parseInt(start_time[1]);\n    if(min_fin<0)\n    {\n      if(start_time[0]<1)\n      {\n      var min_fin = String(min_fin-60);\n      hours_fin = String(24+hours_fin);\n      var hours_fin = String(parseInt(start_time[0]) - 1);\n      t = hours_fin+\":\"+min_fin+\":\"+start_time[2];\n      }\n      else{\n      var min_fin = String(min_fin-60);\n      var hours_fin = String(parseInt(start_time[0]) - 1);\n      t = hours_fin+\":\"+min_fin+\":\"+start_time[2];\n}\n    }\n    else{\n      t = start_time[0]+\":\"+min_fin+\":\"+start_time[2];\n    }\n    l1 = l1-1;\n}\nelse if((l1-l2)%60>=3600)\n{\nvar extrahour = (l1-l2)%3600;\nvar hour_fin = -extrahour + parseInt(start_time[0]);\nif(hours_fin>0)\n{\n t = hour_fin+\":\"+start_time[1]+\":\"+start_time[2];\n}\nelse{\nhours_fin = String(24+hours_fin);\n t = hour_fin+\":\"+start_time[1]+\":\"+start_time[2];\n\n}\nl1 = l1 - 1;\n}\n \n time.unshift(t);\n}\n}*/\nfor(var i = 0;i<data_set.length;i++)\n  {time.push(i+1);\n}\n\n\n\nvar rem_iter = 0;\nvar light_iter = 0;\nvar deep_sleep_iter = 0;\nvar time_step = 30;\nvar rem = 5*60;\nvar light = 2*60;\nvar no_sleep = 15*60;\nvar n_rem = 0;\nvar n_light = 0;\nvar n_none = 0;\nvar n_deep_sleep = 0;\nfor(var i = 0;i<data_set.length;i++)\n{\n  if(data_set[i] == '0')\n  {\n    rem_iter =rem_iter +1;\n    light_iter = light_iter +1;\n    deep_sleep_iter = deep_sleep_iter+1;\n  }\n  else{\n rem_iter = 0;\n    light_iter = 0;\n    deep_sleep_iter = 0;\n\n  }\n  if(rem_iter ==rem/time_step)\n  {\n    rem_iter = 0;\n    n_rem = n_rem+1\n  }\n  if(light_iter==light/time_step)\n  {\n    light_iter = 0;\n    n_light = n_light +1\n  }\n  if(deep_sleep_iter==no_sleep/time_step)\n  {\n\n  deep_sleep_iter = 0;\n  n_deep_sleep = n_deep_sleep + 1;\n  }\n}\ndata_set1 = data_set.split(\"\");\nplot_data_set = data_set1.slice(data_set.length-100,data_set.length-1);\nif(time.length>=100)\n{\ntime1 = time.slice(data_set.length-100,data_set.length-1);\nvar data_0 = [\n  {\n    x: time1,\n    y: plot_data_set,\n    type: 'bar'\n  }\n];\n}else{\n  var data_0 = [\n  {\n    x: time,\n    y: plot_data_set,\n    type: 'bar'\n  }\n];\n}\nvar total = x.length;\nvar rem_percent = (n_rem/total)*100;\nvar deep_percent = (n_deep_sleep/total)*100;\nvar light_percent = (n_light/total)*100;\nvar none_percent =  100 - rem_percent - deep_percent - light_percent;\nvar data_2 = [{\n  values: [rem_percent, deep_percent, light_percent,none_percent],\n  labels: ['REM Sleep', 'Deep Sleep', 'Light Sleep','Awake'],\n  type: 'pie'\n}];\nvar data4 = [\n  {\n    x: ['REM SLeep (in hours)', 'Deep Sleep (in hours)', 'Light Sleep(in hours)','Awake (in hours)'],\n    y: [rem_percent*total/360000,deep_percent*total/360000, light_percent*total/360000,none_percent*total/360000],\n    type: 'bar'\n  }\n];\n \nPlotly.newPlot('graph1', data_0);\nPlotly.newPlot('graph2', data_2,layout);\nPlotly.newPlot('bargraph', data4);\ndeep_percent = deep_percent.toFixed(0);\nif(deep_percent<80)\n{\ndocument.getElementById(\"text\").textContent = \"Your deep sleep percentage is \"+deep_percent+\"% .We Recommond you to use Sleep Inducer in mode I\";\n}\nelse if(deep_percent<50)\n{\ndocument.getElementById(\"text\").textContent = \"Your deep sleep percentage is \"+deep_percent+\"% .We Recommond you to use Sleep Inducer in mode II\";\n}\nelse if (deep_percent>=80){\n  document.getElementById(\"text\").textContent = \"Your deep sleep percentage is \"+deep_percent+\"% .You Sleep is good no need to use the device\";\n}\n\n}\n\n\n \n </script>\n\n</body>\n\n</html>"};
ESP8266WebServer server(80);

void handleHtml1(){
  char data_c[] = ""; 
  int data = random(2);
  if(data == 1)
  {
   data_c[0] = '1';
    }
    else{
       data_c[0] = '0';
      }
  int is_on = digitalRead(D2);
if(is_on==1){
  server.send_P(200,"text/plane",sleeplist);
  strcat(sleeplist,data_c);
  firebase.setString("data",sleeplist);
  Serial.println(sleeplist);
  
  }
  else if (is_on==0){
    server.send_P(200,"text/plane","s");
    return;
  }
  }
void handleHtml(){
  
    server.send_P(200,"text/html",index_html);
  
  }

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
   
    
  Serial.println("");
 WiFi.begin(_SSID ,_PASSWORD);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 server.on("/", handleHtml);
  server.on("/app",handleHtml1);
    firebase.pushString("ip-addresss", WiFi.localIP().toString());
 // server.onNotFound(handleNotFound);

  // Hook examples
  /////////////////////////////////////////////////////////

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){

/*if(0){
  //digitalRead(wifi_reset)){
 String ssid = "";
  String password = "";
  ssid = firebase.getString("ssid");
   password = firebase.getString("password");
  WiFi.begin(ssid,password);

  
  }
*/
String day;

String dataurl = "/data";
int data = digitalRead(sensorpin);
day = firebase.getString(dayurl);
dataurl = dataurl+day;
String temp = "";
sleeplist1 = firebase.getString(dataurl);
 String data_c; 

  if(data == 1)
  {
   data_c= "1";
    }
    else{
       data_c = "0";
      }
sleeplist1 = sleeplist1 + data_c;
firebase.setString(day,sleeplist);


delay(1000);
  
}
