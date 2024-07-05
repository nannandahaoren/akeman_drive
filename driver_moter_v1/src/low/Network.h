#ifndef NETWORK_H
#define NETWORK_H
#include <WiFi.h>

class Network
{
public:
  void setup();
  IPAddress localIP;
};

#endif
