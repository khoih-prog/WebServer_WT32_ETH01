/****************************************************************************************************************************
  WebServer_WT32_ETH01.h - Dead simple web-server.
  For Ethernet shields using WT32_ETH01 (ESP32 + LAN8720)

  WebServer_WT32_ETH01 is a library for the Ethernet LAN8720 in WT32_ETH01 to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_WT32_ETH01
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov
  
  Version: 1.5.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      05/07/2021 Initial coding for WT32_ETH01 (ESP32 + LAN8720)
  1.1.0   K Hoang      06/07/2021 Add SSL support and HTTPS, MQTTS examples
  1.2.0   K Hoang      12/07/2021 Add common code to library. Working only with core v1.0.6-
  1.3.0   K Hoang      23/10/2021 Making compatible with breaking core v2.0.0+
  1.4.0   K Hoang      27/11/2021 Auto detect ESP32 core version
  1.4.1   K Hoang      29/11/2021 Fix bug in examples to reduce connection time
  1.5.0   K Hoang      21/06/2022 Fix multiple-definitions linker error
  1.5.1   K Hoang      10/09/2022 Add example MQTT_And_OTA_Ethernet. Fix compile error for examples
 *****************************************************************************************************************************/

#pragma once

#ifndef WEBSERVER_WT32_ETH01_H
#define WEBSERVER_WT32_ETH01_H

//////////////////////////////////////////////////////////////

//#if !defined(USING_CORE_ESP32_CORE_V200_PLUS)
#if ( ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) ) && ( ARDUINO_ESP32_GIT_VER != 0x46d5afb1 ) )
  #define USING_CORE_ESP32_CORE_V200_PLUS      true
  
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using code for ESP32 core v2.0.0+ in WebServer_WT32_ETH01.h
  #endif
    
  #define WEBSERVER_WT32_ETH01_VERSION      	"WebServer_WT32_ETH01 v1.5.1 for core v2.0.0+"
#else
  #if (_ETHERNET_WEBSERVER_LOGLEVEL_ > 2)
    #warning Using code for ESP32 core v1.0.6- in WebServer_WT32_ETH01.h
  #endif
  
  #define WEBSERVER_WT32_ETH01_VERSION      	"WebServer_WT32_ETH01 v1.5.1 for core v1.0.6-"
#endif

#define WEBSERVER_WT32_ETH01_VERSION_MAJOR    1
#define WEBSERVER_WT32_ETH01_VERSION_MINOR    5
#define WEBSERVER_WT32_ETH01_VERSION_PATCH    1

#define WEBSERVER_WT32_ETH01_VERSION_INT      1005001

#if ESP32
  #warning Using ESP32 architecture for WebServer_WT32_ETH01
  #define BOARD_NAME      "WT32-ETH01"
#else  
  #error This code is designed to run on ESP32 platform! Please check your Tools->Board setting.
#endif

#include <Arduino.h>

#include "WebServer_WT32_ETH01_Debug.h"

//////////////////////////////////////////////////////////////

#include "WebServer_WT32_ETH01.hpp"
#include "WebServer_WT32_ETH01_Impl.h"

#endif    // WEBSERVER_WT32_ETH01_H
