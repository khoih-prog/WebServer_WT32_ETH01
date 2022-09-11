/****************************************************************************************************************************
  WebServer_WT32_ETH01_Impl.h - Dead simple web-server.
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

#ifndef WEBSERVER_WT32_ETH01_IMPL_H
#define WEBSERVER_WT32_ETH01_IMPL_H

//////////////////////////////////////////////////////////////

bool WT32_ETH01_eth_connected = false;

void WT32_ETH01_onEvent()
{
  WiFi.onEvent(WT32_ETH01_event);
}

void WT32_ETH01_waitForConnect()
{
  while (!WT32_ETH01_eth_connected)
    delay(100);
}

bool WT32_ETH01_isConnected()
{
  return WT32_ETH01_eth_connected;
}  

void WT32_ETH01_event(WiFiEvent_t event)
{
  switch (event)
  {
//#if USING_CORE_ESP32_CORE_V200_PLUS
#if ( ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) ) && ( ARDUINO_ESP32_GIT_VER != 0x46d5afb1 ) )
    // For breaking core v2.0.0
    // Why so strange to define a breaking enum arduino_event_id_t in WiFiGeneric.h
    // compared to the old system_event_id_t, now in tools/sdk/esp32/include/esp_event/include/esp_event_legacy.h
    // You can preserve the old enum order and just adding new items to do no harm
    case ARDUINO_EVENT_ETH_START:
      ET_LOG(F("\nETH Started"));
      //set eth hostname here
      ETH.setHostname("WT32-ETH01");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      ET_LOG(F("ETH Connected"));
      break;

    case ARDUINO_EVENT_ETH_GOT_IP:
      if (!WT32_ETH01_eth_connected)
      {
        ET_LOG3(F("ETH MAC: "), ETH.macAddress(), F(", IPv4: "), ETH.localIP());

        if (ETH.fullDuplex())
        {
          ET_LOG0(F("FULL_DUPLEX, "));
        }
        else
        {
          ET_LOG0(F("HALF_DUPLEX, "));
        }
        
        ET_LOG1(ETH.linkSpeed(), F("Mbps"));

        WT32_ETH01_eth_connected = true;
      }

      break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      ET_LOG("ETH Disconnected");
      WT32_ETH01_eth_connected = false;
      break;

    case ARDUINO_EVENT_ETH_STOP:
      ET_LOG("\nETH Stopped");
      WT32_ETH01_eth_connected = false;
      break;
      
#else
    // For old core v1.0.6-
    // Core v2.0.0 defines a stupid enum arduino_event_id_t, breaking any code for WT32_ETH01 written for previous core
    // Why so strange to define a breaking enum arduino_event_id_t in WiFiGeneric.h
    // compared to the old system_event_id_t, now in tools/sdk/esp32/include/esp_event/include/esp_event_legacy.h
    // You can preserve the old enum order and just adding new items to do no harm   
    case SYSTEM_EVENT_ETH_START:
      ET_LOG(F("\nETH Started"));
      //set eth hostname here
      ETH.setHostname("WT32-ETH01");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      ET_LOG(F("ETH Connected"));
      break;

    case SYSTEM_EVENT_ETH_GOT_IP:
      if (!WT32_ETH01_eth_connected)
      {
        ET_LOG3(F("ETH MAC: "), ETH.macAddress(), F(", IPv4: "), ETH.localIP());

        if (ETH.fullDuplex())
        {
          ET_LOG0(F("FULL_DUPLEX, "));
        }
        else
        {
          ET_LOG0(F("HALF_DUPLEX, "));
        }
        
        ET_LOG1(ETH.linkSpeed(), F("Mbps"));

        WT32_ETH01_eth_connected = true;
      }

      break;

    case SYSTEM_EVENT_ETH_DISCONNECTED:
      ET_LOG("ETH Disconnected");
      WT32_ETH01_eth_connected = false;
      break;

    case SYSTEM_EVENT_ETH_STOP:
      ET_LOG("\nETH Stopped");
      WT32_ETH01_eth_connected = false;
      break;
#endif

    default:
      break;
  }
}

#endif    // WEBSERVER_WT32_ETH01_IMPL_H
