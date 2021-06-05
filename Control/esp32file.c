#include <WiFi.h>
#include "SPI.h"
//pin def for UART for energy
#define RXD2 16
#define TXD2 17
//pin def for UART for drive
#define TXD1 10
#define RXD1 9
//pin def for SPI for Vision
#define VSPI_MISO   2
#define VSPI_MOSI   4
#define VSPI_SCLK   0
#define VSPI_SS     33

static const int spiClk = 1000000;
//internet settings to connect to HTTPS server:

const char* ssid = "Sindhu"; //change this to your wifi on integration side
const char* pw = "Butterchicken"; //likewise
//const char* ssid2 = "waplocal";
//const char* pw2 = "localwap";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

//Setting Static IP address, may need to change on integration side
const IPAddress local_IP(192, 168, 1, 15);
//Setting Gateway IP address, may need to change on integration side
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

//char start_char = ‘@’;
//char end_char = ‘#’;
//char sep_char = ‘:’;

// rover parameters:
//uint8_t for 8bit wide
int batterylevel;
int dist;
int driveinstr;
int newdriveinstr; //temp for new incoming drive instr
int poweron = 1; //when 0, while loop breaks and control shuts down
int estop = 0; //when 1, Rover stops moving altogether in order to avoid accident. Direct Communication from Vision to Drive
int warn = 0; //decided by vision for above.
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

//fuction calls for rover functionality:

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
  Serial.print("WiFi connected.");
  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  while(!Serial)
  {}
  initWiFi();
  Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2); //for energy, may need to change baud rate
  Serial2.begin(115200, SERIAL_8N1, RXD1, TXD1); //for drive
  //spi protocol for vision
  //SCLK = 0, MISO = 2, MOSI = 4, SS = 33, check if this works for GPIO
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  pinMode(VSPI_SS, OUTPUT);
  //server connection
}

void emergencystop()
{
  if (warn == 1)
  {
    estop = 1;
  }
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
void poweroff()
{
  poweron = 1; //implement on/off from HTTPS server
}

void receivedrivedist()
{
  dist = Serial2.read(); //do I require to decode this info? also if 8bit count am I limited to 2^8?
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
  if (estop != 1)
  {
  driveinstr = "stop"; //get server write new instr implemented
  }

  else if (newdriveinstr !== "idle")
  {
    driveinstr = newdriveinstr;
  }
  else
    {
      driveinstr = 0;
    }

}

void senddriveinstr(int n) //where n comes from receivenewdriveinstr
{
  Serial2.write((n)val16); //is this required because base value of int is 16 bits long
}

//main execute loop
void loop ()
{
//loop to reconnect to wifi
//if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
  //Serial.print(millis());
  //Serial.println("Reconnecting to WiFi...");
  //WiFi.disconnect();
  //WiFi.reconnect();
  //previousMillis = currentMillis;
//setup section
  Serial.println("starting up");
  setup();
  Serial.println("setup finished");
//rover function, will get stuck in while loop
  while (poweron)
  {
    batterycheck();
    emergencystop(warn);
    receivenewdriveinstr();
    senddriveinstr(driveinstr);
    receivedrivedist();

    poweroff();

  }


}
