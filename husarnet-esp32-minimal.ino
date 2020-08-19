#include <WiFi.h>
#include <Husarnet.h>

#if __has_include("credentials.h")
#include "credentials.h"
#else
// WiFi credentials
const char* ssid     = "wifi-ssid-1";
const char* password = "wifi-pass-for-ssid-1";

// Husarnet credentials
const char* hostName = "esp32basic";
const char* husarnetJoinCode = "fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/xxxxxxxxxxxxxxxxxxxxxx";
const char* dashboardURL = "app.husarnet.com";

// Hostname of your laptop hosting a server
const char* laptopHostname = "mylaptop1";
#endif

void setup()
{
  Serial.begin(115200);

  /* Connect to WiFi */
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("done\r\nlocal IP: %s", WiFi.localIP());

  /* Start Husarnet */
  Husarnet.selfHostedSetup(dashboardURL);
  Husarnet.join(husarnetJoinCode, hostName);
  Husarnet.start();

}

void loop()
{
    HusarnetClient client;
    uint8_t buf[100];
    int buf_s = 0;
    int cnt = 0;

    /* Try to connect to a server on port 8002 on your laptop */
    if (!client.connect(laptopHostname, 8002)) {
        Serial.printf("connection to \"%s\" failed\r\n", laptopHostname);
        delay(1000);
        return;
    }

    /* While connected send "Hello world!" + counter value */
    while(client.connected()) {
      buf_s = sprintf ((char*)buf, "Hello world! %d\r\n", cnt++);
      client.write(buf,buf_s);
      Serial.printf("sending: %s\r\n", (char*)buf);
      delay(1000);
    }
}
