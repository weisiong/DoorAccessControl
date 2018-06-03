#include <Arduino.h>
#include <Ethernet.h>
#include "HttpClient.h"
#include "WebClient.h"

// this must be unique
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// change to your network settings
IPAddress ip(192, 168, 1, 177);
IPAddress gateway(192, 168, 1, 253);
IPAddress subnet(255, 255, 255, 0);

EthernetClient net;

const char serverAddress[] = "192.168.1.138";  // server address
int port = 80;
HttpClient client = HttpClient(net, serverAddress, port);

int statusCode = 0;
String response;

void WEB_CLIENT::setup() {
  Serial.println(F("Setting Up Web Client..."));
  Ethernet.begin(mac, ip, gateway, gateway, subnet);

  Serial.println(Ethernet.localIP());
  delay(7000);
  Serial.println(F("Web Client Ready..."));
}

int WEB_CLIENT::webget(const String& URLPath, String& respBody, int& respCode)
{
  int ret = client.get(URLPath);
  if(ret==0)
  {
    respBody = client.responseBody();
  //respCode = client.responseStatusCode();
  //Serial.println("ret: " + String(ret));
  //Serial.println("respCode: " + String(respCode));
  //Serial.println("respBody: " + respBody);
  }
  client.stop();
  return ret;
}
