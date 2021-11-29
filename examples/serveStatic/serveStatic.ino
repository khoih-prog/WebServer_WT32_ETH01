/****************************************************************************************************************************
  serveStatic.ino - Dead simple web-server for Ethernet shields
                     demoing the usage of serveStatic class method
  v. 1.0
  Copyright (C) 2021 Sardar Azari
  https://www.qrz.com/db/ac8l

  Prior to the usage - use ESP8266/ESP32 Sketch data upoad tool to save the content of web-site to the SPIFFS flash memory.

  This example sketch is based on HTML templates from Robert Ulbricht: https://www.arduinoslovakia.eu
  https://github.com/RoboUlbricht/arduinoslovakia/tree/master/esp8266/simple_http_server_multiplepages_responsive_spiffs

  This code's core is based on HelloServer.ino example of this library by Khoi Hoang

  Some great examples of commercial use of serveStatic function can be seen and learned at uStepper's WiFiGUI project:
  https://github.com/uStepper/uStepperSWiFiGUI

  For Ethernet shields using WT32_ETH01 (ESP32 + LAN8720)

  WebServer_WT32_ETH01 is a library for the Ethernet LAN8720 in WT32_ETH01 to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_WT32_ETH01
  Licensed under MIT license
 *****************************************************************************************************************************/

/*****************************************************************************************************************************
   How To Use:
   1) Run the serveStaticLoadFile.ino
   2) Upload the contents of a folder if you changedir in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" localIPAddress/edit; done
   3) access the sample web page at http://localIPAddress/
*****************************************************************************************************************************/

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#define USE_LITTLEFS                true
#define USE_SPIFFS                  false

// For ESP32
#if USE_LITTLEFS
//LittleFS has higher priority
#include "FS.h"

// The library will be depreciated after being merged to future major Arduino esp32 core release 2.x
// At that time, just remove this library inclusion
#include <LITTLEFS.h>             // https://github.com/lorol/LITTLEFS

FS* filesystem =          &LITTLEFS;
#define CurrentFileFS     "LittleFS"
#define FileFS            LITTLEFS

#ifdef USE_SPIFFS
#undef USE_SPIFFS
#endif

#define USE_SPIFFS                  false
#elif USE_SPIFFS
#include "FS.h"
#include <SPIFFS.h>

FS* filesystem =          &SPIFFS;
#define FileFS            SPIFFS
#define CurrentFileFS     "SPIFFS"
#endif

#include <WebServer_WT32_ETH01.h>

WebServer server(80);

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

void initFS(void) 
{
  // Initialize LittleFS/SPIFFS file-system
#if (ESP32)
  // Format SPIFFS if not yet
  if (!FileFS.begin(true))
  {
    Serial.println(F("SPIFFS/LittleFS failed! Formatting."));
#else
  if (!FileFS.begin())
  {
    FileFS.format();
#endif
    
    if (!FileFS.begin())
    {
      while (true)
      {
#if USE_LITTLEFS
        Serial.println(F("LittleFS failed!. Please use SPIFFS."));
#else
        Serial.println(F("SPIFFS failed!. Please use LittleFS."));
#endif
        // Stay forever here as useless to go further
        delay(5000);
      }
    }
  }
}

void initWebserver(void) 
{
 
  // Web Page handlers
  server.serveStatic("/", FileFS, "/page1.html");
  server.serveStatic("/page2", FileFS, "/page2.html");
  server.serveStatic("/page3", FileFS, "/page3.html");

  // Other usage with various web site assets:
  // server.serveStatic("/assets/css/test.css", SPIFFS, "/assets/css/test.css"); // Style sheet
  // server.serveStatic("/assets/js/test_script.js", SPIFFS,"/assets/js/test_script.js"); // Javascript
  // server.serveStatic("/assets/font/fonticons.ttf", SPIFFS,"/assets/font/fonticons.ttf"); // font
  // server.serveStatic("/assets/picture.png", SPIFFS,"/assets/picture.png"); // Picture

  server.begin();
}

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  //while (!Serial && (millis() < 3000));

  Serial.print("\nStarting serveStatic demoing 'serveStatic' function on " + String(ARDUINO_BOARD));
  Serial.print(" using "); Serial.println(CurrentFileFS);
  Serial.println("With " + String(SHIELD_TYPE));
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

  initFS();
  initWebserver();

  Serial.println("HTTP server started");
}

void loop(void) 
{
  server.handleClient();
}
