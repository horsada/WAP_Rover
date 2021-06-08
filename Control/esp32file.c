#include <WiFi.h>
#include "SPI.h"
#include <stdio.h>
#include <HTTPClient.h>
//pin def for UART for energy
#define RXD2 16
#define TXD2 17
//pin def for UART for drive
#define TXD1 10
#define RXD1 9
//pin def for SPI for Vision, try using standard pin allignment
/*
#define VSPI_MISO   2
#define VSPI_MOSI   4
#define VSPI_SCLK   0
#define VSPI_SS     33
*/

//internet settings to connect to HTTPS server:
String serverName = "http://jsonplaceholder.typicode.com/comments?id=10"; //change this to server IP and port
int httpCode;
String payload;
HTTPClient http;

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
//not required, remove if going over mem
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);



// rover parameters:
//uint8_t for 8bit wide
uint8_t batterylevel;
uint8_t dist;
uint8_t driveinstr;
uint8_t newdriveinstr; //temp for new incoming drive instr
uint8_t poweron = 1; //when 0, while loop breaks and control shuts down
uint8_t estop = 0; //when 1, Rover stops moving altogether in order to avoid accident. Direct Communication from Vision to Drive
uint8_t warn = 0; //decided by vision for above.
String newdriveinstrimm; //intermediate via http communication


//fuction calls for rover functionality:

void initWiFi() { //initializes wifi connection
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


void setup() { //setups ESP32 controller connections: Wifi, SPI and UART
  Serial.begin(115200);
  while(!Serial)
  {}
  initWiFi();
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); //for energy, may need to change baud rate
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1); //for drive, figure out arduino uno max baud rate
  //server connection
}

void emergencystop() //direct communication between Vision and Drive. Used to stop rover if a blockage is detected
{
  if (warn == 1)
  {
    estop = 1;
  }
}

void batterycheck() //Energy - ESP32 - Command. Used to update GUI of battery level of the rover
{
  batterylevel = Serial1.read();
  Serial.print("Rover Battery level = ");
  Serial.println(batterylevel, DEC);
  sendbatteryinfo(batterylevel);
}

void sendbatteryinfo (int n) //sends info to server of above function
{
  //implement send to server. Server will have to figure out how to display raw data
}
void poweroff() //turns off ESP32
{
  poweron = 1; //implement on/off from HTTPS server
}

void receivedrivedist() //get distance travelled from arduino
{
  dist = Serial1.read(); //do I require to decode this info? also if 8bit count am I limited to 2^8?
  Serial.print("Distance Travelled = ");
  Serial.println(dist, DEC);
  senddistinfo(dist);

}

void senddistinfo(int n) //sends distance to GUI
{
  //implement send to server
}

void receivenewdriveinstr() //gets new instruction from the GUI
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

void httpget()
{


      http.begin(serverName);
      httpCode = http.GET();
      if (httpCode > 0) { //Check for the returning code

        //newdriveinstrimm = http.getString();
        //newdriveinstr = stoi(newdriveinstrimm);
        //Serial.println(httpCode);
        //Serial.println(newdriveinstr);
        payload = http.getString();

}else {

      Serial.println("Error with HTTP request, no instruction received.");
}
}


void senddriveinstr(uint8_t n) //where n comes from receivenewdriveinstr, sends to Drive Arduino
{
  Serial1.write(n); //is this required because base value of int is 16 bits long
}

//main execute loop
void loop ()
{

  Serial.println("starting up");
  setup();
  Serial.println("setup finished");
//rover function, will get stuck in while loop
  while (poweron)
  {
    batterycheck();
    emergencystop(warn);
    httpget();
    Serial.println(payload);
    //receivenewdriveinstr();
    //senddriveinstr(driveinstr);
  //  receivedrivedist();

  //  poweroff();
    //delay(2500);

  }
  Serial.println("rover turned off");


}
