// 
// 
// 

#include "setting.h"


Ticker flipper;

// ������ ��� ���������� � web �������� 
ESP8266HTTPUpdateServer httpUpdater;

// Web ��������� ��� ����������
ESP8266WebServer HTTP;

// ��� �������� �������
File fsUploadFile;

// ���������� ���������� wifi
String _ssid       = "SSID";      // ��� �������� SSID
String _password   = "PASSWORD";  // ��� �������� ������ ����
String _ssidAP     = "LuckyBox";  // SSID AP ����� �������
String _passwordAP = "12345678";  // ������ ����� �������
String SSDP_Name   = "LuckyBox";  // ��� SSDP
String jsonConfig  = "{}";
int port = 80;

int timezone = 3;                 // ������� ���� GTM
int DS_Count;
float temperature1 = 5.0;           // ����������� 1
float temperature2 = 5.0;           // ����������� 2
float temperature3 = 5.0;           // ����������� 3
float temperature4 = 5.0;           // ����������� 4
float temperature5 = 5.0;           // ����������� 5
float temperature6 = 5.0;           // ����������� 6
float temperature7 = 5.0;           // ����������� 7
float temperature8 = 5.0;           // ����������� 8
float pressure = 760.0;				// ��������
bool  pressureStatus = 0;
int readTempInterval;				// ������� ������� ��� ������ ������� ����������� ���� ��������� ���������

bool settingAlarm = false;        // ����������� ������� �������
int temp_in[120];                 // ����� ������� �� �������