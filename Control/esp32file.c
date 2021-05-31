#include <WiFi.h>
#include "SPI.h"

#define RXD2 16
#define TXD2 17

#define TXD1 10
#define RXD1 9

const char* ssid = "Sindhu"; //change this to your wifi on integration side
const char* pw = "Butterchicken"; //likewise
//const char* ssid2 = "waplocal";
//const char* pw2 = "localwap";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

//Setting Static IP address, may need to change on integration side
IPAddress local_IP(192, 168, 1, 15);
//Setting Gateway IP address, may need to change on integration side
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

char start_char = ‘@’;
char end_char = ‘#’;
char sep_char = ‘:’;

int batterylevel;
int dist;
int driveinstr;


/*void uartsetup(){
  const uart_port_t uart_num = UART_NUM_2;
uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
    .rx_flow_ctrl_thresh = 122,
};
// Configure UART parameters
ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
}
*/

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pw);
  Serial.print("Connecting to WiFi:");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  while(!Serial)
  {}
  initWiFi();
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2); //for energy
  Serial2.begin(115200, SERIAL_8N1, RXD1, TXD1); //for drive
  //spi protocol for vision
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  //server connection
}

void batterycheck()
{
  batterylevel = Serial1.read();
  Serial.print("Rover Battery level = ");
  Serial.println(batterylevel, DEC);
  sendbatteryinfo(batterylevel);
}

void sendbatteryinfo (int n)
{
  //implement send to server. Server will have to figure out how to display raw data
}
void intra()
{}

void receivedrivedist()
{
  dist = Serial2.read();
  Serial.print("Distance Travelled = ");
  Serial.println(dist, DEC);
  senddistinfo(dist);

}

void senddistinfo(int n)
{
  //implement send to server
}

void receivenewdriveinstr()
{
  //implement receive from server
}

void senddriveinstr(int n)
{
  Serial2.write((n)val16);
}
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
  Serial.println("finished");
  while (1)
  {
    batterycheck();
    receivenewdriveinstr();
    senddriveinstr(driveinstr);
    receivedrivedist();

  }


}
