
#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include <AsyncElegantOTA.h>


//FUNCOES PARA WEB CONTROL
// Replace with your network credentials
const char* ssid = "Oi_A822";
const char* password = "MchCM3TM";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create a WebSocket object

AsyncWebSocket ws("/ws");

String message = "";
String sliderValue1 = "0";
String sliderValue2 = "0";
String sliderValue3 = "0";
//String log = "0";


int dutyCycle1;
int dutyCycle2;
int dutyCycle3;


//Json Variable to Hold Slider Values
JSONVar sliderValues;

//Get Slider Values
String getSliderValues(){
  sliderValues["sliderValue1"] = String(sliderValue1);
  sliderValues["sliderValue2"] = String(sliderValue2);
  sliderValues["sliderValue3"] = String(sliderValue3);

  String jsonString = JSON.stringify(sliderValues);
  return jsonString; //preciso mostrar ISSO NA WEB
}

// Initialize SPIFFS
void initFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else{
   Serial.println("SPIFFS mounted successfully");
  }
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    //Enquanto está conectando fica piscando
    digitalWrite(2, 1);
    delay(250);
    digitalWrite(2, 0);
    delay(250);

    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  //Após conectar fica aceso
  digitalWrite(2, 1);
}

void notifyClients(String sliderValues) {
  ws.textAll(sliderValues);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    message = (char*)data;
    if (message.indexOf("1s") >= 0) {
      sliderValue1 = message.substring(2);
      dutyCycle1 = map(sliderValue1.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle1);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (message.indexOf("2s") >= 0) {
      sliderValue2 = message.substring(2);
      dutyCycle2 = map(sliderValue2.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle2);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }    
    if (message.indexOf("3s") >= 0) {
      sliderValue3 = message.substring(2);
      dutyCycle3 = map(sliderValue3.toInt(), 0, 100, 0, 255);
      Serial.println(dutyCycle3);
      Serial.print(getSliderValues());
      notifyClients(getSliderValues());
    }
    if (strcmp((char*)data, "getValues") == 0) {
      notifyClients(getSliderValues());
    }
}
}
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}