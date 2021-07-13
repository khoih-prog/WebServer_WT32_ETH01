/****************************************************************************************************************************
  WebServer_WT32_ETH01_Impl.h - Dead simple web-server.
  For Ethernet shields using WT32_ETH01 (ESP32 + LAN8720)

  WebServer_WT32_ETH01 is a library for the Ethernet LAN8720 in WT32_ETH01 to run WebServer

  Based on and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_WT32_ETH01
  Licensed under MIT license
  Version: 1.2.0

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      05/07/2021 Initial coding for WT32_ETH01 (ESP32 + LAN8720)
  1.1.0   K Hoang      06/07/2021 Add SSL support and HTTPS, MQTTS examples
  1.2.0   K Hoang      12/07/2021 Add common code to library
 *****************************************************************************************************************************/

#pragma once

#ifndef WEBSERVER_WT32_ETH01_IMPL_H
#define WEBSERVER_WT32_ETH01_IMPL_H

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

    default:
      break;
  }
}

#endif    // WEBSERVER_WT32_ETH01_IMPL_H
