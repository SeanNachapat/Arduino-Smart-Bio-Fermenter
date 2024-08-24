// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = "";    // Network SSID (name)
const char PASS[]     = "";    // Network password (use for WPA, or use as key for WEP)

void onAlcoholChange();
void onPHChange();
void onTimerChange();
void onActionChange();
void onStatusChange();

float alcohol;
float pH;
CloudSchedule timer;
bool action;
bool status;

void initProperties(){

  ArduinoCloud.addProperty(alcohol, READWRITE, ON_CHANGE, onAlcoholChange);
  ArduinoCloud.addProperty(pH, READWRITE, ON_CHANGE, onPHChange);
  ArduinoCloud.addProperty(timer, READWRITE, ON_CHANGE, onTimerChange);
  ArduinoCloud.addProperty(action, READWRITE, ON_CHANGE, onActionChange);
  ArduinoCloud.addProperty(status, READWRITE, ON_CHANGE, onStatusChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);