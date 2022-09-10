/****************************************************************************************************************************
  MQTT_And_OTA_Ethernet.ino 
    - Dead simple MQTT Client for Ethernet shields
    - Allows for new sketch compiled bin to be uploaded over HTTP using AsyncElegantOTA

  Based on MQTTClient_Auth
 *****************************************************************************************************************************/

/*
  Basic MQTT example (without SSL!) with Authentication
    This sketch demonstrates the basic capabilities of the library.
    It connects to an MQTT server then:
    - providing username and password
    - publishes "hello world" to the topic "outTopic"
    - subscribes to the topic "inTopic", printing out any messages
      it receives. NB - it assumes the received payloads are strings not binary
    It will reconnect to the server if the connection is lost using a blocking
    reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
    achieve the same result without blocking the main loop.

  To use OTA:   
    - Take note of what IP the board is on, you should be able to see this both in the serial monitor and in the MQTT messages when the board first starts.
    - In the Arduino IDE, go to Sketch > Export compiled binary
    - You should now see a build folder next to the MQTT_And_OTA_Ethernet.ino file
    - Go into build\esp32.esp32.esp32 folder
    - The file you will be uploading to do an OTA update is MQTT_And_OTA_Ethernet.ino.bin in that folder
    - Go to http://192.168.X.X/update with a browser (whatever your board IP is that you noted earlier.)
    - Click "Choose file" and browse to the MQTT_And_OTA_Ethernet.ino.bin that you made earlier when you clicked Export compiled binary
*/

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3            // Debug Level from 0 to 4

#include <WebServer_WT32_ETH01.h>         // https://github.com/khoih-prog/WebServer_WT32_ETH01/
#include <AsyncTCP.h>                     // https://github.com/me-no-dev/AsyncTCP
#include <ESPAsyncWebServer.h>            // https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncElegantOTA.h>              // https://github.com/ayushsharma82/AsyncElegantOTA

// Libraries also needed: https://github.com/knolleary/pubsubclient

AsyncWebServer server(80);

// Set according to your local network if you need static IP
// IPAddress myIP(192, 168, 1, 232);
// IPAddress myGW(192, 168, 1, 1);
// IPAddress mySN(255, 255, 255, 0);
// IPAddress myDNS(8, 8, 8, 8);

#include <PubSubClient.h>

// MQTT Settings
const char *mqttServer     = "192.168.1.25";                   // Broker address
const char *mqttBrokerUser = "YOUR_MQTT_USERNAME";             // Username to connect to your MQTT broker
const char *mqttBrokerPass = "YOUR_MQTT_PASSWORD";             // Password to connect to your MQTT broker
const char *ID             = "MQTTClient_SSL-Client";          // Name of our device, must be unique
const char *TOPIC          = "topics/test/esp32";              // Topic to publish to
const char *subTopic       = "topics/MQTT_Sub";                // Topic to subcribe to

WiFiClient    ethClient;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  //while (!Serial && (millis() < 3000));

  Serial.print("\nStarting MQTT_And_OTA_Ethernet on " + String(ARDUINO_BOARD));
  Serial.println(" with " + String(SHIELD_TYPE));
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  // ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();
  
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this use the
  // following to increase the buffer size:
  // client.setBufferSize(255);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();

  Serial.println();
  Serial.println("HTTP server started with MAC: " + ETH.macAddress() + ", at IPv4: " + ETH.localIP().toString());
  Serial.println();
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (unsigned int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

PubSubClient  client(mqttServer, 1883, callback, ethClient);

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqttServer);

    // Attempt to connect
    if (client.connect("arduino", mqttBrokerUser, mqttBrokerPass))
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from MQTTClient_SSL on " + String(BOARD_NAME) + ", at IPv4: " + ETH.localIP().toString();

      client.publish(TOPIC, data.c_str());

      //Serial.println("Published connection message successfully!");
      //Serial.print("Subcribed to: ");
      //Serial.println(subTopic);
      
      // ... and resubscribe
      client.subscribe(subTopic);
      // for loopback testing
      client.subscribe(TOPIC);
    }
    else
    {
      Serial.print("...failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

#define MQTT_PUBLISH_INTERVAL_MS       5000L

unsigned long lastMsg = 0;

void loop() 
{
  String data         = "Hello from v00 MQTT_And_OTA_Ethernet on: " + String(BOARD_NAME) + " with " + String(SHIELD_TYPE);
  const char *pubData = data.c_str();

  static unsigned long now;
 
  if (!client.connected()) 
  {
    reconnect();
  }

  // Sending Data
  now = millis();
  
  if (now - lastMsg > MQTT_PUBLISH_INTERVAL_MS)
  {
    lastMsg = now;

    if (!client.publish(TOPIC, pubData))
    {
      Serial.println("Message failed to send.");
    }

    Serial.print("Message Send : " + String(TOPIC) + " => ");
    Serial.println(data);
  }
  
  client.loop();
}
