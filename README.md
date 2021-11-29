## WebServer_WT32_ETH01

[![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WebServer_WT32_ETH01.svg)](https://github.com/khoih-prog/WebServer_WT32_ETH01/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WebServer_WT32_ETH01.svg)](http://github.com/khoih-prog/WebServer_WT32_ETH01/issues)

---
---

## Table of Contents


* [Why do we need this WebServer_WT32_ETH01 library](#why-do-we-need-this-webserver_wt32_eth01-library)
  * [Important notes](#Important-notes)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Libraries' Patches](#libraries-patches)
  * [1. For fixing ESP32 compile error](#1-for-fixing-esp32-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Usage](#usage)
  * [Class Constructor](#class-constructor)
  * [Basic Operation](#basic-operations)
  * [Advanced Options](#advanced-options)
  * [Other Function Calls](#other-function-calls)
* [Examples](#examples)
  * [Original Examples](#original-examples)
    * [ 1. AdvancedWebServer](examples/AdvancedWebServer)
    * [ 2. HelloServer](examples/HelloServer)
    * [ 3. HelloServer2](examples/HelloServer2)
    * [ 4. HttpBasicAuth](examples/HttpBasicAuth)
    * [ 5. **MQTTClient_Auth**](examples/MQTTClient_Auth)
    * [ 6. **MQTTClient_Basic**](examples/MQTTClient_Basic)
    * [ 7. **MQTT_ThingStream**](examples/MQTT_ThingStream)
    * [ 8. PostServer](examples/PostServer)
    * [ 9. SimpleAuthentication](examples/SimpleAuthentication)
    * [10. UdpNTPClient](examples/UdpNTPClient)
    * [11. UdpSendReceive](examples/UdpSendReceive)
    * [12. WebClient](examples/WebClient)
    * [13. WebClientRepeating](examples/WebClientRepeating)
    * [14. WebServer](examples/WebServer)
    * [15. **ESP32_FS_EthernetWebServer**](examples/ESP32_FS_EthernetWebServer)
    * [16. **serveStatic**](examples/serveStatic)
    * [17. **serveStaticLoadFile**](examples/serveStaticLoadFile)
  * [HTTPClient Examples](#httpclient-examples)
    * [ 1. Authorization](examples/HTTPClient/Authorization)
    * [ 2. BasicHttpClient](examples/HTTPClient/BasicHttpClient)
    * [ 3. BasicHttpsClient](examples/HTTPClient/BasicHttpsClient)
    * [ 4. StreamHttpClient](examples/HTTPClient/StreamHttpClient)
    * [ 5. node_test_server](examples/HTTPClient/node_test_server)
  * [HTTPS and MQTTS Examples](#https-and-mqtts-examples)
    * [ 1. MQTTClient_SSL](examples/SSL/MQTTClient_SSL)
    * [ 2. MQTTClient_SSL_Auth](examples/SSL/MQTTClient_SSL_Auth)
    * [ 3. MQTTClient_SSL_Complex](examples/SSL/MQTTClient_SSL_Complex)
    * [ 4. MQTTS_ThingStream](examples/SSL/MQTTS_ThingStream)
    * [ 5. WebClientMulti_SSL](examples/SSL/WebClientMulti_SSL)
    * [ 6. WebClient_SSL](examples/SSL/WebClient_SSL)
* [Example AdvancedWebServer](#example-advancedwebserver)
  * [File AdvancedWebServer.ino](#file-advancedwebserverino)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. AdvancedWebServer on ESP32_DEV with ETH_PHY_LAN8720](#1-advancedwebserver-on-esp32_dev-with-eth_phy_lan8720)
  * [ 2. ESP32_FS_EthernetWebServer on ESP32_DEV with ETH_PHY_LAN8720](#2-esp32_fs_ethernetwebserver-on-esp32_dev-with-eth_phy_lan8720)
  * [ 3. MQTT_ThingStream on ESP32_DEV with ETH_PHY_LAN8720](#3-mqtt_thingstream-on-esp32_dev-with-eth_phy_lan8720)
  * [ 4. MQTTClient_Auth on ESP32_DEV with ETH_PHY_LAN8720](#4-mqttclient_auth-on-esp32_dev-with-eth_phy_lan8720)
  * [ 5. MQTTClient_Basic on ESP32_DEV with ETH_PHY_LAN8720](#5-mqttclient_basic-on-esp32_dev-with-eth_phy_lan8720)
  * [ 6. WebClient on ESP32_DEV with ETH_PHY_LAN8720](#6-webclient-on-esp32_dev-with-eth_phy_lan8720)
  * [ 7. UdpNTPClient on ESP32_DEV with ETH_PHY_LAN8720](#7-udpntpclient-on-esp32_dev-with-eth_phy_lan8720)
  * [ 8. BasicHttpClient on ESP32_DEV with ETH_PHY_LAN8720](#8-basichttpclient-on-esp32_dev-with-eth_phy_lan8720)
  * [ 9. BasicHttpsClient on ESP32_DEV with ETH_PHY_LAN8720](#9-basichttpsclient-on-esp32_dev-with-eth_phy_lan8720)
  * [10. WebClientMulti_SSL on ESP32_DEV with ETH_PHY_LAN8720](#10-webclientmulti_ssl-on-esp32_dev-with-eth_phy_lan8720)
  * [11. MQTTClient_SSL_Complex on ESP32_DEV with ETH_PHY_LAN8720](#11-mqttclient_ssl_complex-on-esp32_dev-with-eth_phy_lan8720)
  * [12. MQTTS_ThingStream on ESP32_DEV with ETH_PHY_LAN8720](#12-mqtts_thingstream-on-esp32_dev-with-eth_phy_lan8720)
  * [13. MQTTClient_SSL on ESP32_DEV with ETH_PHY_LAN8720](#13-mqttclient_ssl-on-esp32_dev-with-eth_phy_lan8720)
  * [14. MQTTClient_SSL_Auth on ESP32_DEV with ETH_PHY_LAN8720](#14-mqttclient_ssl_auth-on-esp32_dev-with-eth_phy_lan8720)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Why do we need this [WebServer_WT32_ETH01 library](https://github.com/khoih-prog/WebServer_WT32_ETH01)

#### Important notes

ESP32 Core v2.0.0+ introduces new enum breaking almost all `WT32_ETH01` codes written for core v1.0.6-.

It's really strange to define a breaking enum `arduino_event_id_t` in [**WiFiGeneric.h**#L36-L78](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFiGeneric.h#L36-L78), compared to the old `system_event_id_t`, now placed in [**esp_event_legacy.h**#L29-L63](https://github.com/espressif/arduino-esp32/blob/master/tools/sdk/esp32/include/esp_event/include/esp_event_legacy.h#L29-L63)

It's better to preserve the old enum order and just adding new items **to do no harm to pre-2.0.0 codes**

- Releases v1.2.0- to be used for ESP32 core v1.0.6- only
- Releases v1.3.0 can be used for either ESP32 core v2.0.0+ or v1.0.6-. **Default is using core v2.0.0+**

To use with core v1.0.6-, just define in your sketch

```
#define USING_CORE_ESP32_CORE_V200_PLUS       false
```

- Releases v1.4.0+ can be used for either ESP32 core v2.0.0+ or v1.0.6-. **Autodetect core**


#### Features

This [**WebServer_WT32_ETH01 library**](https://github.com/khoih-prog/WebServer_WT32_ETH01) is a simple yet complete WebServer wrapper library for **ESP32-based WT32_ETH01** boards using LAN8720 Ethernet. The functions are similar and compatible to those of [`ESP32 WebServer`](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) and [`ESP8266WebServer`](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer) libraries to make life much easier to port sketches from ESP8266/ESP32.

This [**WebServer_WT32_ETH01 library**](https://github.com/khoih-prog/WebServer_WT32_ETH01) also provides high-level **HTTP(S), MQTT(S) and WebSockets Client** by using the functions from ESP32's [**HTTPClient Library**](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)

The library provides these features:

1. TCP Server and Client
2. UDP Server and Client
3. HTTP(S) Server and Client
4. HTTP(S) GET and POST requests, provides argument parsing, handles one client at a time.
5. **High-level HTTP(S) (GET, POST, PUT, PATCH, DELETE), MQTT(S) and WebSocket Client**.

Library is just a wrapper for:

1. [Ivan Grokhotkov's ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
2. [HTTPClient Library](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient)


#### Currently supported Boards

This [**WebServer_WT32_ETH01** library](https://github.com/khoih-prog/WebServer_WT32_ETH01) currently supports these following boards:

 1. **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet

---
---



## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ESP32 Core 2.0.1+`](https://github.com/espressif/arduino-esp32) for ESP32-based WT32_ETH01 boards using release v1.3.0+. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`ESP32 Core 1.0.6-`](https://github.com/espressif/arduino-esp32) for ESP32-based WT32_ETH01 boards using release v1.2.0- [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `WebServer_WT32_ETH01`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01) for more detailed instructions.

### Manual Install

1. Navigate to [WebServer_WT32_ETH01](https://github.com/khoih-prog/WebServer_WT32_ETH01) page.
2. Download the latest release `WebServer_WT32_ETH01-master.zip`.
3. Extract the zip file to `WebServer_WT32_ETH01-master` directory 
4. Copy the whole `WebServer_WT32_ETH01-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**WebServer_WT32_ETH01** library](https://platformio.org/lib/show/12512/WebServer_WT32_ETH01) by using [Library Manager](https://platformio.org/lib/show/12512/WebServer_WT32_ETH01/installation). Search for WebServer_WT32_ETH01 in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---


### Libraries' Patches

#### 1. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.16/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)


---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

#### Usage


#### Class Constructor

```cpp
  WebServer server(80);
```

Creates the WebServer_WT32_ETH01 class object.

*Parameters:* 
 
host port number: ``int port`` (default is the standard HTTP port 80)

#### Basic Operations

**Starting the server**

```cpp
  void begin();
```

**Handling incoming client requests**

```cpp
  void handleClient();
```

**Disabling the server**

```cpp
  void close();
  void stop();
```

Both methods function the same

**Client request handlers**

```cpp
  void on();
  void addHandler();
  void onNotFound();
  void onFileUpload();	
```

Example:

```cpp
  server.on("/", handlerFunction);
  server.onNotFound(handlerFunction);   // called when handler is not assigned
  server.onFileUpload(handlerFunction); // handle file uploads
```

**Sending responses to the client**

```cpp
  void send();
  void send_P();
```

`Parameters:`

`code` - HTTP response code, can be `200` or `404`, etc.

`content_type` - HTTP content type, like `"text/plain"` or `"image/png"`, etc.

`content` - actual content body

#### Advanced Options

**Getting information about request arguments**

```cpp
  const String & arg();
  const String & argName();
  int args();
  bool hasArg();
```

`Function usage:`

`arg` - get request argument value, use `arg("plain")` to get POST body
	
`argName` - get request argument name
	
`args` - get arguments count
	
`hasArg` - check if argument exist


**Getting information about request headers**

```cpp
  const String & header();
  const String & headerName();
  const String & hostHeader();
  int headers();
  bool hasHeader();
``` 
`Function usage:`

`header` - get request header value

`headerName` - get request header name

`hostHeader` - get request host header if available, else empty string
  
`headers` - get header count
	
`hasHeader` - check if header exist


**Authentication**

```cpp
  bool authenticate();
  void requestAuthentication();
```

`Function usage:`

`authenticate` - server authentication, returns true if client is authenticated else false

`requestAuthentication` - sends authentication failure response to the client

`Example Usage:`

```cpp

  if(!server.authenticate(username, password)){
    server.requestAuthentication();
  }
```

#### Other Function Calls

```cpp
  const String & uri();     // get the current uri
  HTTPMethod  method();     // get the current method 
  WiFiClient client();      // get the current client
  HTTPUpload & upload();    // get the current upload
  void setContentLength();  // set content length
  void sendHeader();        // send HTTP header
  void sendContent();       // send content
  void sendContent_P(); 
  void collectHeaders();    // set the request headers to collect
  void serveStatic();
  size_t streamFile();
```
---
---

### Examples:

#### Original Examples

 1. [AdvancedWebServer](examples/AdvancedWebServer)
 2. [HelloServer](examples/HelloServer)
 3. [HelloServer2](examples/HelloServer2)
 4. [HttpBasicAuth](examples/HttpBasicAuth)
 5. [**MQTTClient_Auth**](examples/MQTTClient_Auth)
 6. [**MQTTClient_Basic**](examples/MQTTClient_Basic)
 7. [**MQTT_ThingStream**](examples/MQTT_ThingStream)
 8. [PostServer](examples/PostServer)
 9. [SimpleAuthentication](examples/SimpleAuthentication)
10. [UdpNTPClient](examples/UdpNTPClient)
11. [UdpSendReceive](examples/UdpSendReceive)
12. [WebClient](examples/WebClient)
13. [WebClientRepeating](examples/WebClientRepeating)
14. [WebServer](examples/WebServer)
15. [**ESP32_FS_EthernetWebServer**](examples/ESP32_FS_EthernetWebServer).
16. [**serveStatic**](examples/serveStatic).
17. [**serveStaticLoadFile**](examples/serveStaticLoadFile).

#### HTTPClient Examples

 1. [Authorization](examples/HTTPClient/Authorization)
 2. [BasicHttpClient](examples/HTTPClient/BasicHttpClient)
 3. [BasicHttpsClient](examples/HTTPClient/BasicHttpsClient)
 4. [StreamHttpClient](examples/HTTPClient/StreamHttpClient)
 5. [node_test_server](examples/HTTPClient/node_test_server)

#### HTTPS and MQTTS Examples

 1. [MQTTClient_SSL](examples/SSL/MQTTClient_SSL)
 2. [MQTTClient_SSL_Auth](examples/SSL/MQTTClient_SSL_Auth)
 3. [MQTTClient_SSL_Complex](examples/SSL/MQTTClient_SSL_Complex)
 4. [MQTTS_ThingStream](examples/SSL/MQTTS_ThingStream)
 5. [WebClientMulti_SSL](examples/SSL/WebClientMulti_SSL)
 6. [WebClient_SSL](examples/SSL/WebClient_SSL)
 
---
---

### Example [AdvancedWebServer](examples/AdvancedWebServer)

#### File [AdvancedWebServer.ino](examples/AdvancedWebServer/AdvancedWebServer.ino)


```cpp
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#include <WebServer_WT32_ETH01.h>

WebServer server(80);

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

int reqCount = 0;                // number of requests received

void handleRoot()
{
#define BUFFER_SIZE     400

  char temp[BUFFER_SIZE];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int day = hr / 24;

  hr = hr % 24;

  snprintf(temp, BUFFER_SIZE - 1,
           "<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>AdvancedWebServer %s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>Hi from WebServer_WT32_ETH01!</h2>\
<h3>on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
<img src=\"/test.svg\" />\
</body>\
</html>", BOARD_NAME, BOARD_NAME, day, hr % 24, min % 60, sec % 60);

  server.send(200, F("text/html"), temp);
}

void handleNotFound()
{
  String message = F("File Not Found\n\n");

  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, F("text/plain"), message);
}

void drawGraph()
{
  String out;
  out.reserve(3000);
  char temp[70];

  out += F("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"310\" height=\"150\">\n");
  out += F("<rect width=\"310\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n");
  out += F("<g stroke=\"black\">\n");
  int y = rand() % 130;

  for (int x = 10; x < 300; x += 10)
  {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += F("</g>\n</svg>\n");

  server.send(200, F("image/svg+xml"), out);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  //while (!Serial && (millis() < 3000));

  Serial.print("\nStarting AdvancedWebServer on " + String(ARDUINO_BOARD));
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

  server.on(F("/"), handleRoot);
  server.on(F("/test.svg"), drawGraph);
  server.on(F("/inline"), []()
  {
    server.send(200, F("text/plain"), F("This works as well"));
  });

  server.onNotFound(handleNotFound);
  server.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(ETH.localIP());
}

void heartBeatPrint()
{
  static int num = 1;

  Serial.print(F("."));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     10000L

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void loop()
{
  server.handleClient();
  check_status();
}
```

---
---

### Debug Terminal Output Samples

#### 1. AdvancedWebServer on ESP32_DEV with ETH_PHY_LAN8720

The following are debug terminal output and screen shot when running example [AdvancedWebServer](examples/AdvancedWebServer) on ESP32_DEV with ETH_PHY_LAN8720 (WT32_ETH01)

<p align="center">
    <img src="https://github.com/khoih-prog/WebServer_WT32_ETH01/blob/main/pics/AdvancedWebServer.png">
</p>

```
Starting AdvancedWebServer on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+

ETH Started
ETH Connected
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.127, FULL_DUPLEX, 100Mbps
HTTP EthernetWebServer is @ IP : 192.168.2.127
..
```

---

#### 2. ESP32_FS_EthernetWebServer on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [ESP32_FS_EthernetWebServer](examples/ESP32_FS_EthernetWebServer)


```cpp
Starting ESP32_FS_EthernetWebServer on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+

ETH Started
ETH Connected
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.127, FULL_DUPLEX, 100Mbps
/home/kh/Arduino/libraries/LITTLEFS-master/src/lfs.c:1003:error: Corrupted dir pair at {0x0, 0x1}
E (4029) esp_littlefs: mount failed,  (-84)
E (4033) esp_littlefs: Failed to initialize LittleFS

HTTP server started @192.168.2.127
Open http://192.168.2.127/edit to see the file browser
handleFileRead: /
handleFileUpload Name: /CanadaFlag_1.png
handleFileUpload Size: 41214
handleFileUpload Name: /CanadaFlag_2.png
handleFileUpload Size: 8311
handleFileUpload Name: /CanadaFlag_3.jpg
handleFileUpload Size: 11156
handleFileUpload Name: /edit.htm.gz
handleFileUpload Size: 4116
handleFileUpload Name: /favicon.ico
handleFileUpload Size: 1150
handleFileUpload Name: /graphs.js.gz
handleFileUpload Size: 1971
handleFileUpload Name: /index.htm
handleFileUpload Size: 3721
handleFileRead: /
handleFileRead: /graphs.js
handleFileRead: /edit.htm
handleFileRead: /index.htm
handleFileList: /
handleFileList: [{"type":"file","name":"CanadaFlag_1.png"},{"type":"file","name":"CanadaFlag_2.png"},{"type":"file","name":"CanadaFlag_3.jpg"},{"type":"file","name":"edit.htm.gz"},{"type":"file","name":"favicon.ico"},{"type":"file","name":"graphs.js.gz"},{"type":"file","name":"index.htm"}]
handleFileRead: /CanadaFlag_1.png
```

and the screen shot of the WebServer

<p align="center">
    <img src="https://github.com/khoih-prog/WebServer_WT32_ETH01/blob/main/pics/ESP32_FS_EthernetWebServer.png">
</p>

---

#### 3. MQTT_ThingStream on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTT_ThingStream example](examples/MQTT_ThingStream)


```
Starting MQTT_ThingStream on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
```

---

#### 4. MQTTClient_Auth on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTClient_Auth example](examples/MQTTClient_Auth)


```
Starting MQTTClient_Auth on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on WT32-ETH01 with ETH_PHY_LAN8720
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on WT32-ETH01 with ETH_PHY_LAN8720
Message Send : MQTT_Pub => Hello from MQTTClient_Auth on WT32-ETH01 with ETH_PHY_LAN8720
Message arrived [MQTT_Pub] Hello from MQTTClient_Auth on WT32-ETH01 with ETH_PHY_LAN8720
```

---

#### 5. MQTTClient_Basic on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTClient_Basic example](examples/MQTTClient_Basic)

```
Starting MQTTClient_Basic on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
Message arrived [MQTT_Pub] Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
Message Send : MQTT_Pub => Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
Message arrived [MQTT_Pub] Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
Message Send : MQTT_Pub => Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
Message arrived [MQTT_Pub] Hello from MQTTClient_Basic on WT32-ETH01 with ETH_PHY_LAN8720
```

---


#### 6. WebClient on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [WebClient example](examples/WebClient)

```
Starting WebClient on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps

Starting connection to server...
Connected to server
HTTP/1.1 200 OK
Server: nginx/1.4.2
Date: Tue, 06 Jul 2021 04:36:48 GMT
Content-Type: text/plain
Content-Length: 2263
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Connection: close
Vary: Accept-Encoding
ETag: "524c23c7-8d7"
Accept-Ranges: bytes


           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

Disconnecting from server...
```

---

#### 7. UdpNTPClient on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [UdpNTPClient example](examples/UdpNTPClient)

```
Starting UdpNTPClient on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.0 for core v2.0.0+
ETH Started
ETH Connected
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.95
FULL_DUPLEX, 100Mbps
UDP Packet received, size 48
From 132.163.96.4, port 123
Seconds since Jan 1 1900 = 3847154050
Unix time = 1638165250
The UTC time is 5:54:10
UDP Packet received, size 48
From 132.163.96.4, port 123
Seconds since Jan 1 1900 = 3847154062
Unix time = 1638165262
The UTC time is 5:54:22
UDP Packet received, size 48
From 132.163.96.4, port 123
Seconds since Jan 1 1900 = 3847154074
Unix time = 1638165274
The UTC time is 5:54:34
UDP Packet received, size 48
From 132.163.96.4, port 123
Seconds since Jan 1 1900 = 3847154086
Unix time = 1638165286
The UTC time is 5:54:46

```

---

#### 8. BasicHttpClient on ESP32_DEV with ETH_PHY_LAN8720


The terminal output of **WT32_ETH01** running [BasicHttpClient example](examples/HTTPClient/BasicHttpClient)


```
Starting BasicHttpClient on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
[HTTP] begin...
[HTTP] GET...
[HTTP] GET... code: 200
<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
        
    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>    
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>
```

---

#### 9. BasicHttpsClient on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [BasicHttpsClient example](examples/HTTPClient/BasicHttpsClient)


```
Starting BasicHttpsClient on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 05:29:39 2021
[HTTPS] begin...
[HTTPS] GET...
[HTTPS] GET... code: 200
<HTML>
<HEAD>
  <!-- Created with AOLpress/2.0 -->
  <TITLE>Connection Header</TITLE>
</HEAD>
<BODY>
<P>
<IMG ALT="Jigsaw" BORDER="0" WIDTH="212" HEIGHT="49" SRC="/icons/jigsaw">
<H1>
  The <I>Connection</I> header
</H1>
<P>
This page will be served to you with the following headers:
<P>
<CODE>ExtensionHeader: ExtensionValue<BR>
Connection: ExtensionHeader</CODE>
<P>
If you're getting this page through a proxy, you should <I>not</I> see the
<I>ExtensionHeader</I> !
<P>
  <HR>
<BR>
<A HREF="mailto:jigsaw@w3.org">jigsaw@w3.org</A>
</BODY></HTML>


Waiting 10s before the next round...
```

---

#### 10. WebClientMulti_SSL on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [WebClientMulti_SSL example](examples/SSL/WebClientMulti_SSL)


```
Starting WebClientMulti_SSL on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 19:58:27 2021
Connecting to www.arduino.cc...
Took: 2312
HTTP/1.1 200 OK
Date: Tue, 06 Jul 2021 19:58:31 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Last-Modified: Wed, 02 Oct 2013 13:46:47 GMT
Vary: Accept-Encoding
Strict-Transport-Security: max-age=500; includeSubDomains
X-Content-Type-Options: nosniff
X-XSS-Protection: 1; mode=block
CF-Cache-Status: DYNAMIC
Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
Server: cloudflare
CF-RAY: 66ab6888bbc63fd9-YYZ
alt-svc: h3-27=":443"; ma=86400, h3-28=":443"; ma=86400, h3-29=":443"; ma=86400, h3=":443"; ma=86400

8d7

           `:;;;,`                      .:;;:.           
        .;;;;;;;;;;;`                :;;;;;;;;;;:     TM 
      `;;;;;;;;;;;;;;;`            :;;;;;;;;;;;;;;;      
     :;;;;;;;;;;;;;;;;;;         `;;;;;;;;;;;;;;;;;;     
    ;;;;;;;;;;;;;;;;;;;;;       .;;;;;;;;;;;;;;;;;;;;    
   ;;;;;;;;:`   `;;;;;;;;;     ,;;;;;;;;.`   .;;;;;;;;   
  .;;;;;;,         :;;;;;;;   .;;;;;;;          ;;;;;;;  
  ;;;;;;             ;;;;;;;  ;;;;;;,            ;;;;;;. 
 ,;;;;;               ;;;;;;.;;;;;;`              ;;;;;; 
 ;;;;;.                ;;;;;;;;;;;`      ```       ;;;;;`
 ;;;;;                  ;;;;;;;;;,       ;;;       .;;;;;
`;;;;:                  `;;;;;;;;        ;;;        ;;;;;
,;;;;`    `,,,,,,,,      ;;;;;;;      .,,;;;,,,     ;;;;;
:;;;;`    .;;;;;;;;       ;;;;;,      :;;;;;;;;     ;;;;;
:;;;;`    .;;;;;;;;      `;;;;;;      :;;;;;;;;     ;;;;;
.;;;;.                   ;;;;;;;.        ;;;        ;;;;;
 ;;;;;                  ;;;;;;;;;        ;;;        ;;;;;
 ;;;;;                 .;;;;;;;;;;       ;;;       ;;;;;,
 ;;;;;;               `;;;;;;;;;;;;                ;;;;; 
 `;;;;;,             .;;;;;; ;;;;;;;              ;;;;;; 
  ;;;;;;:           :;;;;;;.  ;;;;;;;            ;;;;;;  
   ;;;;;;;`       .;;;;;;;,    ;;;;;;;;        ;;;;;;;:  
    ;;;;;;;;;:,:;;;;;;;;;:      ;;;;;;;;;;:,;;;;;;;;;;   
    `;;;;;;;;;;;;;;;;;;;.        ;;;;;;;;;;;;;;;;;;;;    
      ;;;;;;;;;;;;;;;;;           :;;;;;;;;;;;;;;;;:     
       ,;;;;;;;;;;;;;,              ;;;;;;;;;;;;;;       
         .;;;;;;;;;`                  ,;;;;;;;;:         
                                                         
                                                         
                                                         
                                                         
    ;;;   ;;;;;`  ;;;;:  .;;  ;; ,;;;;;, ;;. `;,  ;;;;   
    ;;;   ;;:;;;  ;;;;;; .;;  ;; ,;;;;;: ;;; `;, ;;;:;;  
   ,;:;   ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;,`;, ;;  ;;  
   ;; ;:  ;;  ;;  ;;  ;; .;;  ;;   ,;,   ;;;;`;, ;;  ;;. 
   ;: ;;  ;;;;;:  ;;  ;; .;;  ;;   ,;,   ;;`;;;, ;;  ;;` 
  ,;;;;;  ;;`;;   ;;  ;; .;;  ;;   ,;,   ;; ;;;, ;;  ;;  
  ;;  ,;, ;; .;;  ;;;;;:  ;;;;;: ,;;;;;: ;;  ;;, ;;;;;;  
  ;;   ;; ;;  ;;` ;;;;.   `;;;:  ,;;;;;, ;;  ;;,  ;;;;   

0

LoopCount 1, Received 2876 bytes
Disconnecting.
Connecting to www.cloudflare.com...
Took: 2249
HTTP/1.1 200 OK
Date: Tue, 06 Jul 2021 19:58:54 GMT
Content-Type: text/plain
Transfer-Encoding: chunked
Connection: close
Access-Control-Allow-Origin: *
Server: cloudflare
CF-RAY: 66ab6913cedb3ff1-YYZ
X-Frame-Options: DENY
X-Content-Type-Options: nosniff
Expires: Thu, 01 Jan 1970 00:00:01 GMT
Cache-Control: no-cache

ba
fl=29f93
h=www.cloudflare.com
ip=45.72.193.56
ts=1625601534.066
visit_scheme=https
uag=SSLClientOverEthernet
colo=YYZ
http=http/1.1
loc=CA
tls=TLSv1.2
sni=plaintext
warp=off
gateway=off

0

LoopCount 2, Received 529 bytes
Disconnecting.

```

---

#### 11. MQTTClient_SSL_Complex on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTClient_SSL_Complex example](examples/SSL/MQTTClient_SSL_Complex)


```
Starting MQTTClient_SSL_Complex on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 18:14:02 2021
Attempting MQTT connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Complex on WT32-ETH01, millis = 5718
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Complex on WT32-ETH01, millis = 5718
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Complex on WT32-ETH01, millis = 10719
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Complex on WT32-ETH01, millis = 10719
```

---

#### 12. MQTTS_ThingStream on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTS_ThingStream example](examples/SSL/MQTTS_ThingStream)


```
Starting MQTTS_ThingStream on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 18:38:22 2021
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTTS_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTTS_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
```

---

#### 13. MQTTClient_SSL on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTClient_SSL example](examples/SSL/MQTTClient_SSL)


```
Starting MQTTClient_SSL on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 17:11:00 2021
Attempting MQTTS connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL on WT32-ETH01
```

---

#### 14. MQTTClient_SSL_Auth on ESP32_DEV with ETH_PHY_LAN8720

The terminal output of **WT32_ETH01** running [MQTTClient_SSL_Auth example](examples/SSL/MQTTClient_SSL_Auth)

```
Starting MQTTClient_SSL_Auth on ESP32_DEV with ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.4.1 for core v2.0.0+
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232, FULL_DUPLEX, 100Mbps
Waiting for NTP time sync: .
Current time: Tue Jul  6 18:05:14 2021
Attempting MQTTS connection to broker.emqx.io...connected
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message Send : MQTT_Pub => Hello from MQTTClient_SSL_Auth on WT32-ETH01
Message arrived [MQTT_Pub] Hello from MQTTClient_SSL_Auth on WT32-ETH01

```
---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---


### Issues ###

Submit issues to: [WebServer_WT32_ETH01 issues](https://github.com/khoih-prog/WebServer_WT32_ETH01/issues)

---

### TO DO

1. Bug Searching and Killing

### DONE

 1. Add support to ESP32-based **WT32_ETH01** using LAN8720 Ethernet
 2. Add SSL support
 3. Add HTTPS and MQTTS examples
 4. Support breaking ESP32 core v2.0.0+ as well as v1.0.6-
 5. Auto detect ESP32 core v1.0.6- or v2.0.0+ to use correct settings

---
---

### Contributions and Thanks


Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on the [Ivan Grokhotkov's ESP32 WebServer](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer) and [HTTPClient Library](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient) libraries.
2. Thanks to [Sardar Azari](https://github.com/gagulik) to make PR in [streamFile and serveStatic for ESP8266/ESP32 boards #22](https://github.com/khoih-prog/EthernetWebServer/pull/22) to add WebServer feature to serve static from LittleFS/SPIFFS for ESP32. The example [**serveStatic**](examples/serveStatic) and [**serveStaticLoadFile**](examples/serveStaticLoadFile) are also contributed by [Sardar Azari](https://github.com/gagulik).


<table>
  <tr>
    <td align="center"><a href="https://github.com/igrr"><img src="https://github.com/igrr.png" width="100px;" alt="igrr"/><br /><sub><b>⭐️ Ivan Grokhotkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/gagulik"><img src="https://github.com/gagulik.png" width="100px;" alt="gagulik"/><br /><sub><b>
Sardar Azari</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/WebServer_WT32_ETH01/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang


