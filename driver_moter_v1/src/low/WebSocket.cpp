#include "WebSocket.h"
WebSocketsServer webSocket = WebSocketsServer(81);

WebSocket globalSocket;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = webSocket.remoteIP(num);
    // send message to client
    Serial.printf("[%u] Connected!\n", num);
    // webSocket.sendTXT(num, "Connected");
    globalSocket.num = num;
  }
  break;

  case WStype_TEXT:
    if (globalSocket.callback != NULL)
    {
      globalSocket.callback(payload);
    }
    // Serial.printf("[%u] get Text: %s\n", num, payload);
    break;
  }
}

void WebSocket::setup()
{
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void WebSocket::loop()
{
  webSocket.loop();
}

void WebSocket::sendMessage(const char *msg)
{
  webSocket.sendTXT(globalSocket.num, msg);
}

void WebSocket::onMessage(OnEvent cb)
{
  callback = cb;
}
