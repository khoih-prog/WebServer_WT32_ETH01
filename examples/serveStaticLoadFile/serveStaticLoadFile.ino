/****************************************************************************************************************************
  serveStaticLoadFile.ino - Dead simple web-server for Ethernet shields
                            demoing the usage of serveStatic class method

                            Used to load files to prepare for serveStatic.ino

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
   1) Upload the contents of the data folder with MkSPIFFS Tool ("ESP8266 Sketch Data Upload" in Tools menu in Arduino IDE)
   2) or you can upload the contents of a folder if you CD in that folder and run the following command:
      for file in `\ls -A1`; do curl -F "file=@$PWD/$file" localIPAddress/edit; done
   3) access the sample web page at http://localIPAddress/
*****************************************************************************************************************************/

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

// LittleFS has higher priority than SPIFFS
#if ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) )
  #define USE_LITTLEFS    true
  #define USE_SPIFFS      false
#elif defined(ARDUINO_ESP32C3_DEV)
  // For core v1.0.6-, ESP32-C3 only supporting SPIFFS and EEPROM. To use v2.0.0+ for LittleFS
  #define USE_LITTLEFS          false
  #define USE_SPIFFS            true
#endif

#if USE_LITTLEFS
  // Use LittleFS
  #include "FS.h"

  // Check cores/esp32/esp_arduino_version.h and cores/esp32/core_version.h
  //#if ( ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(2, 0, 0) )  //(ESP_ARDUINO_VERSION_MAJOR >= 2)
  #if ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) )
    #if (_WIFIMGR_LOGLEVEL_ > 3)
      #warning Using ESP32 Core 1.0.6 or 2.0.0+
    #endif
    
    // The library has been merged into esp32 core from release 1.0.6
    #include <LittleFS.h>       // https://github.com/espressif/arduino-esp32/tree/master/libraries/LittleFS
    
    FS* filesystem =      &LittleFS;
    #define FileFS        LittleFS
    #define FS_Name       "LittleFS"
  #else
    #if (_WIFIMGR_LOGLEVEL_ > 3)
      #warning Using ESP32 Core 1.0.5-. You must install LITTLEFS library
    #endif
    
    // The library has been merged into esp32 core from release 1.0.6
    #include <LITTLEFS.h>       // https://github.com/lorol/LITTLEFS
    
    FS* filesystem =      &LITTLEFS;
    #define FileFS        LITTLEFS
    #define FS_Name       "LittleFS"
  #endif
  
#elif USE_SPIFFS
  #include <SPIFFS.h>
  FS* filesystem =      &SPIFFS;
  #define FileFS        SPIFFS
  #define FS_Name       "SPIFFS"
#else
  // Use FFat
  #include <FFat.h>
  FS* filesystem =      &FFat;
  #define FileFS        FFat
  #define FS_Name       "FFat"
#endif

#include <WebServer_WT32_ETH01.h>

WebServer server(80);

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

//holds the current upload
File fsUploadFile;

//format bytes
String formatBytes(size_t bytes)
{
  if (bytes < 1024)
  {
    return String(bytes) + "B";
  }
  else if (bytes < (1024 * 1024))
  {
    return String(bytes / 1024.0) + "KB";
  }
  else if (bytes < (1024 * 1024 * 1024))
  {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
  else
  {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename)
{
  if (server.hasArg("download"))
  {
    return "application/octet-stream";
  }
  else if (filename.endsWith(".htm"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".html"))
  {
    return "text/html";
  }
  else if (filename.endsWith(".css"))
  {
    return "text/css";
  }
  else if (filename.endsWith(".js"))
  {
    return "application/javascript";
  }
  else if (filename.endsWith(".png"))
  {
    return "image/png";
  }
  else if (filename.endsWith(".gif"))
  {
    return "image/gif";
  }
  else if (filename.endsWith(".jpg"))
  {
    return "image/jpeg";
  }
  else if (filename.endsWith(".ico"))
  {
    return "image/x-icon";
  }
  else if (filename.endsWith(".xml"))
  {
    return "text/xml";
  }
  else if (filename.endsWith(".pdf"))
  {
    return "application/x-pdf";
  }
  else if (filename.endsWith(".zip"))
  {
    return "application/x-zip";
  }
  else if (filename.endsWith(".gz"))
  {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool handleFileRead(String path)
{
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/"))
  {
    path += "index.htm";
  }

  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";

  if (filesystem->exists(pathWithGz) || filesystem->exists(path))
  {
    if (filesystem->exists(pathWithGz))
    {
      path += ".gz";
    }

    File file = filesystem->open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileDelete()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileDelete: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (!filesystem->exists(path))
  {
    return server.send(404, "text/plain", "FileNotFound");
  }

  filesystem->remove(path);
  server.send(200, "text/plain", "");
  path.clear();
}

void handleFileCreate()
{
  if (server.args() == 0)
  {
    return server.send(500, "text/plain", "BAD ARGS");
  }

  String path = server.arg(0);
  Serial.println("handleFileCreate: " + path);

  if (path == "/")
  {
    return server.send(500, "text/plain", "BAD PATH");
  }

  if (filesystem->exists(path))
  {
    return server.send(500, "text/plain", "FILE EXISTS");
  }

  File file = filesystem->open(path, "w");

  if (file)
  {
    file.close();
  }
  else
  {
    return server.send(500, "text/plain", "CREATE FAILED");
  }

  server.send(200, "text/plain", "");
  path.clear();
}

void handleFileUpload()
{
  if (server.uri() != "/edit")
  {
    return;
  }

  HTTPUpload& upload = server.upload();

  if (upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;

    if (!filename.startsWith("/"))
    {
      filename = "/" + filename;
    }

    Serial.print(F("handleFileUpload Name: ")); Serial.println(filename);
    fsUploadFile = filesystem->open(filename, "w");
    filename.clear();
  }
  else if (upload.status == UPLOAD_FILE_WRITE)
  {
    //Serial.print(F("handleFileUpload Data: ")); Serial.println(upload.currentSize);

    if (fsUploadFile)
    {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  }
  else if (upload.status == UPLOAD_FILE_END)
  {
    if (fsUploadFile)
    {
      fsUploadFile.close();
    }

    Serial.print(F("handleFileUpload Size: ")); Serial.println(upload.totalSize);
  }
}

void initFS()
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

void initWebserver()
{
  //load editor
  server.on("/edit", HTTP_GET, []()
  {
    if (!handleFileRead("/edit.htm"))
    {
      server.send(404, "text/plain", "FileNotFound");
    }
  });

  //create file
  server.on("/edit", HTTP_PUT, handleFileCreate);

  //delete file
  server.on("/edit", HTTP_DELETE, handleFileDelete);

  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []()
  {
    server.send(200, "text/plain", "");
  }, handleFileUpload);

  // Web Page handlers
  server.serveStatic("/", FileFS, "/page1.html");
  server.serveStatic("/page2", FileFS, "/page2.html");
  server.serveStatic("/page3", FileFS, "/page3.html");

  //server.serveStatic("/", SPIFFS, "/page1.html");
  //server.serveStatic("/page2", SPIFFS, "/page2.html");
  //server.serveStatic("/page3", SPIFFS, "/page3.html");

  // Other usage with various web site assets:
  // server.serveStatic("/assets/css/test.css", SPIFFS, "/assets/css/test.css"); // Style sheet
  // server.serveStatic("/assets/js/test_script.js", SPIFFS,"/assets/js/test_script.js"); // Javascript
  // server.serveStatic("/assets/font/fonticons.ttf", SPIFFS,"/assets/font/fonticons.ttf"); // font
  // server.serveStatic("/assets/picture.png", SPIFFS,"/assets/picture.png"); // Picture

  server.begin();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  //while (!Serial && (millis() < 3000));

  Serial.print("\nStarting serveStaticLoadFile demoing 'serveStatic' function on " + String(ARDUINO_BOARD));
  Serial.print(" using "); Serial.println(FS_Name);
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

void loop()
{
  server.handleClient();
}
