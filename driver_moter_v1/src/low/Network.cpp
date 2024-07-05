 #include "Network.h"

 void Network::setup()
  {
    const char *ssid = "monster";
    const char *password = "lj112358";
    Serial.println("Start to Connecting WiFi");
    // 连接到WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.status());
    localIP = WiFi.localIP();
  }
