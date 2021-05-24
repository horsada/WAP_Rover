#include <WiFi.h>

const char* ssid = "Sindhu";
const char* pw = "Butterchicken";
const char* ssid2 = "waplocal";
const char* pw2 = "localwap";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

//Setting Static IP address, may need to change on integration side
IPAddress local_IP(192, 168, 1, 184);
//Setting Gateway IP address, may need to change on integration side
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

void initWiFi() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, pw);
  Serial.print("Connecting to WiFi:");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }


  //WiFi.softAP(ssid2, pw2);


}


void setup() {
  Serial.begin(115200);
  initWiFi();
}

void command()
{}

void intra()
{}


void loop ()
{
//loop to reconnect to wifi
//if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
  //Serial.print(millis());
  //Serial.println("Reconnecting to WiFi...");
  //WiFi.disconnect();
  //WiFi.reconnect();
  //previousMillis = currentMillis;
  Serial.println("starting up");
  setup();
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Error: Could Not Connect to WiFi Network");
  }
  else
  {
    Serial.println("Success! connected to WiFi with local IP: ");
    Serial.println(WiFi.localIP());
  }


}
