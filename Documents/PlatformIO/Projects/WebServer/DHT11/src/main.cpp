#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
const char* ssid = "WLdc_2.4G";
const char* password = "cdip@2904";
#define DHTPIN D1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);
void setup() {
IPAddress local_IP(172,16,1,59); //Troque o IP
IPAddress gateway(172,16,1,254);
IPAddress subnet(255,255,255,0);
Serial.begin(9600);
dht.begin();
Serial.println();
Serial.println();
Serial.print("Conectando-se a ");
Serial.println(ssid);
if (!WiFi.config(local_IP, gateway, subnet)) {
Serial.println("STA Failed to configure");
}
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("Conexão WiFi estabelecida");
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
server.begin();
}
void loop() {
WiFiClient client = server.available();
if (!client) {
return;
}
// Ler a primeira linha da solicitação (exemplo: GET /path HTTP/1.1)
String request = client.readStringUntil('\r');
client.flush();
float h = dht.readHumidity();
float t = dht.readTemperature();
Serial.print("Umidade: "); Serial.println(h);
Serial.print("Temperatura: "); Serial.println(t);
String html = R"====(
<html>
<head>
<link href="https://fonts.googleapis.com/css2?family=Anton&display=swap"
rel="stylesheet">
<link rel="stylesheet"
href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
<style>
body {
font-family: 'Anton';
background: linear-gradient(to right, #83a4d4, #b6fbff);
color: #333;
height: 100vh;
display: flex;
flex-direction: column;
align-items: center;
justify-content: center;
}
h2 {
font-size: 2.5em;
}
p {
font-size: 2em;
}
fas {
font-size: 1.5em;
margin-right: 10px;
}
</style>
<script>
setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var readings = this.responseText.split(";");
            document.getElementById("humidity").innerHTML = readings[0] + " %";
            document.getElementById("temperature").innerHTML = readings[1] + " &deg;C";
        }
    };
    xhttp.open("GET", "/get-data", true);
    xhttp.send();
}, 2000); // Atualiza a cada 2 segundos
</script>
</head>
<body>
<h2>NodeMCU com DHT11</h2>
<h3>André Vinicius</h3>
<p><i class="fas fa-tint"></i> Umidade: <span id="humidity"></span></p>
<p><i class="fas fa-thermometer-half"></i> Temperatura: <span
id="temperature"></span></p>
</body>
</html>
)====";
// Verificar se a solicitação é para "/get-data"
if (request.indexOf("/get-data") != -1) {
client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
client.print(String(h) + ";" + String(t));
return;
}
// Se não for para "/get-data", servir a página HTML
else {
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();
client.print(html);
}
delay(1);
client.stop();
}