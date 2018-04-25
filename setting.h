// setting.h

#ifndef _SETTING_h
#define _SETTING_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <FS.h>
#include <Ticker.h>
#include <ESP8266HTTPUpdateServer.h> 
#include <ESP8266WebServer.h>

extern Ticker flipper;

// $B'0'R'l'V'\'d(B $B'U']'q(B $B'`'R'_'`'S']'V'_'Z'q(B $B'c(B web $B'c'd'b'Q'_'Z'h'm(B
extern ESP8266HTTPUpdateServer httpUpdater;

// Web $B'Z'_'d'V'b'f'V'['c(B $B'U']'q(B $B'e'c'd'b'`'['c'd'S'Q(B
extern ESP8266WebServer HTTP;

// $B'%']'q(B $B'f'Q'[']'`'S'`'[(B $B'c'Z'c'd'V'^'m(B
extern File fsUploadFile;

// $B'0'a'b'V'U'V']'q'V'^(B $B'a'V'b'V'^'V'_'_'m'V(B wifi
extern String _ssid;
extern String _password;
extern String _ssidAP;
extern String _passwordAP;
extern String SSDP_Name;
extern String jsonConfig;
extern int port;
extern int timezone;
extern int DS_Count;
extern float temperature1;
extern float temperature2;
extern float temperature3;
extern float temperature4;
extern float temperature5;
extern float temperature6;
extern float temperature7;
extern float temperature8;
extern float pressure;
extern bool  pressureStatus;
extern int readTempInterval;
extern bool settingAlarm;
extern int modeWiFi;
extern int timeWiFiReconnect;

#endif

