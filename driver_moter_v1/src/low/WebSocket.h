#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H
#include <Arduino.h>

#include <WebSocketsServer.h>
typedef std::function<void(uint8_t * payload)> OnEvent;

class WebSocket
{
public:
  void setup();
  void loop();
  uint8_t num;
  void sendMessage(const char *msg);
  void onMessage(OnEvent cb);

  OnEvent callback = NULL;
};

#endif
