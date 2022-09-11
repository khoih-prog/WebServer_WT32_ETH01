## WebServer_WT32_ETH01

[![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/WebServer_WT32_ETH01.svg)](https://github.com/khoih-prog/WebServer_WT32_ETH01/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/WebServer_WT32_ETH01.svg)](http://github.com/khoih-prog/WebServer_WT32_ETH01/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Releases v1.5.1](#releases-v151)
  * [Releases v1.5.0](#releases-v150)
  * [Releases v1.4.1](#releases-v141)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

#### Releases v1.5.1

1. Add example [MQTT_And_OTA_Ethernet](https://github.com/khoih-prog/WebServer_WT32_ETH01/tree/main/examples/MQTT_And_OTA_Ethernet) to demo how to use OTA. Check [Added MQTT and OTA over Ethernet example to examples folder #9](https://github.com/khoih-prog/WebServer_WT32_ETH01/pull/9)
2. Fix compile error for examples [serveStatic](https://github.com/khoih-prog/WebServer_WT32_ETH01/tree/main/examples/serveStatic) and [serveStaticLoadFile](https://github.com/khoih-prog/WebServer_WT32_ETH01/tree/main/examples/serveStaticLoadFile) to use built-in LittleFS library for new ESP32 cores
3. Fix compile error for examples [ESP32_FS_EthernetWebServer](https://github.com/khoih-prog/WebServer_WT32_ETH01/tree/main/examples/ESP32_FS_EthernetWebServer) if WT32_ETH01 is selected as A0 (and many pins) not defined in new ESP32 cores

#### Releases v1.5.0

1. Fix multiple-definitions linker error.
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project to avoid `multiple-definitions` linker error

#### Releases v1.4.1

1. Fix bug in examples to reduce connection time

#### Releases v1.4.0

##### Warning: Releases v1.4.0+ can be used and autodetect ESP32 core v2.0.0+ or v1.0.6-.

1. Auto detect ESP32 core
2. Renew examples

#### Releases v1.3.0

##### Warning: Releases v1.3.0+ can be used for either ESP32 core v2.0.0+ or v1.0.6-. Default is v2.0.0+ now

1. Making compatible either with breaking core v2.0.0+ or core v1.0.6-
2. Renew examples


#### Releases v1.2.0

##### Warning: Releases v1.2.0- to be used for ESP32 core v1.0.6- only

1. Add common code to library
2. Renew examples

#### Releases v1.1.0

1. Add SSL support
2. Add HTTPS and MQTTS examples

#### Releases v1.0.0

1. Initial coding to support WT32_ETH01 boards



