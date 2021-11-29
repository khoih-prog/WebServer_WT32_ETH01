/****************************************************************************************************************************
  WebClientMulti_SSL.ino - Dead simple SSL WebClient for Ethernet shields

  For Ethernet shields using WT32_ETH01 (ESP32 + LAN8720)

  WebServer_WT32_ETH01 is a library for the Ethernet LAN8720 in WT32_ETH01 to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_WT32_ETH01
  Licensed under MIT license
 *****************************************************************************************************************************/

// This sketch connects to SSL websites (https://www.arduino.cc/asciilogo.txt) and (https://www.cloudflare.com/cdn-cgi/trace)

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#include <WebServer_WT32_ETH01.h>

#include <WiFiClientSecure.h>

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

#include "certificates.h"

// the two domains we want to query
char server1[] = "www.arduino.cc";
char server2[] = "www.cloudflare.com";
// and the queries we want to send to them
char query1[] = "GET /asciilogo.txt HTTP/1.1";
char query2[] = "GET /cdn-cgi/trace HTTP/1.1";

const uint16_t  server_port = 443;

// Initialize the SSL client library
WiFiClientSecure sslClient;

// Variables to measure
unsigned long beginMillis;
unsigned long byteCount = 0;
unsigned long loopCount = 0;

bool printWebData = true;  // set to false for better speed measurement

void connectSSL()
{
  static bool r = true;
  // cycle the server we want to connect to back and forth
  char* server;
  char* query;

  if (r)
  {
    server  = server1;
    query   = query1;
    sslClient.setCACert(rootCACertificate1);
  }
  else
  {
    server  = server2;
    query   = query2;
    sslClient.setCACert(rootCACertificate2);
  }

  r = !r;

  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  auto start = millis();

  if (sslClient.connect(server, server_port))
  {
    auto time = millis() - start;

    Serial.print("Took (ms): ");
    Serial.println(time);

    // Make a HTTP request:
    sslClient.println(query);
    sslClient.println("User-Agent: SSLClientOverEthernet");
    sslClient.print("Host: ");
    sslClient.println(server);
    sslClient.println("Connection: close");
    sslClient.println();
    sslClient.flush();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  beginMillis = millis();
}

// Not sure if WiFiClientSecure checks the validity date of the certificate.
// Setting clock just to be sure...
void setClock()
{
  configTime(0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);

  while (nowSecs < 8 * 3600 * 2)
  {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  //while (!Serial && (millis() < 3000));

  Serial.print("\nStarting WebClientMulti_SSL on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();

  setClock();

  // give the Ethernet shield a second to initialize:
  delay(2000);

  // connect!
  connectSSL();
}

#define BUFFER_SZ     2048

byte buffer[BUFFER_SZ + 1];

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  int len = sslClient.available();

  if (len > 0)
  {
    if (len > BUFFER_SZ)
      len = BUFFER_SZ;

    sslClient.read(buffer, len);

    if (printWebData)
    {
      Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    }

    byteCount = byteCount + len;
  }
  else
  {
    if (millis() - beginMillis > 10000)
    {
      Serial.print("LoopCount ");
      Serial.print(++loopCount);

      Serial.print(", Received ");
      Serial.print(byteCount);
      Serial.println(" bytes");

      // Reset
      byteCount = 0;
      
      Serial.println("Disconnecting.");
      sslClient.stop();
    }
  }

  // if the server's disconnected, stop the sslClient:
  if (!sslClient.connected())
  {
    //quick delay
    delay(10000);
    
    // connect again!
    connectSSL();
  }
}
