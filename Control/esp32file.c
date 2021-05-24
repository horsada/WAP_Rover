#include <wifi.h>

const char* ssid = "PV";
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
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  WiFi.softAP(ssid2, pw2);
  //do we need int channel for this?

  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  initWiFi();
}

void uartcom()
{}

void command()
{}

void intra()
{}


void main ()
{
//loop to reconnect to wifi
if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
  Serial.print(millis());
  Serial.println("Reconnecting to WiFi...");
  WiFi.disconnect();
  WiFi.reconnect();
  previousMillis = currentMillis;
}

}
