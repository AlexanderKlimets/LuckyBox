#include "http_config.h"
#include "setting.h"
#include "file_config.h"
#include "time_config.h"
#include <ArduinoJson.h>

void initHTTP(void)
{

	HTTP.on("/configs.json", handleConfigJSON); // ������������ configs.json �������� ��� �������� ������ � web ���������
												 // API ��� ����������
	HTTP.on("/ssdp", handleSetSSDP);     // ���������� ��� SSDP ���������� �� ������� ���� /ssdp?ssdp=proba
	HTTP.on("/ssid", handleSetSSID);     // ���������� ��� � ������ ������� �� ������� ���� /ssid?ssid=home2&password=12345678
	HTTP.on("/ssidap", handleSetSSIDAP); // ���������� ��� � ������ ��� ����� ������� �� ������� ���� /ssidap?ssidAP=home1&passwordAP=8765439
	HTTP.on("/restart", handleRestart);   // ������������ ������ �� ������� ���� /restart?device=ok

										   // ��������� ������� Update ��� ���������� �������� �� WiFi ��� 1�(256K SPIFFS) � ����
	httpUpdater.setup(&HTTP);
	// ��������� HTTP ������
	HTTP.begin();
}

// ������� API-Set
// ��������� SSDP ����� �� ������� ���� http://192.168.0.101/ssdp?ssdp=proba
void handleSetSSDP()
{
	SSDP_Name = HTTP.arg("ssdp"); // �������� �������� ssdp �� ������� ��������� � ���������� ����������
	saveConfig();                 // ������� ���������� ������ �� Flash
	HTTP.send(200, "text/plain", "OK"); // ���������� ����� � ����������
}
// ��������� ���������� ��� ����������� � ������� AP �� ������� ���� http://192.168.0.101/ssid?ssid=home2&password=12345678
void handleSetSSID()
{
	_ssid = HTTP.arg("ssid");            // �������� �������� ssid �� ������� ��������� � ���������� ����������
	_password = HTTP.arg("password");    // �������� �������� password �� ������� ��������� � ���������� ����������
	saveConfig();                        // ������� ���������� ������ �� Flash
	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������
}
//��������� ���������� ���������� ����� ������� �� ������� ���� http://192.168.0.101/ssidap?ssidAP=home1&passwordAP=8765439
void handleSetSSIDAP()
{              //
	_ssidAP = HTTP.arg("ssidAP");         // �������� �������� ssidAP �� ������� ��������� � ���������� ����������
	_passwordAP = HTTP.arg("passwordAP"); // �������� �������� passwordAP �� ������� ��������� � ���������� ����������
	saveConfig();                         // ������� ���������� ������ �� Flash
	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������
}


// ������������ ������ �� ������� ���� http://192.168.0.101/restart?device=ok
void handleRestart()
{
	String restart = HTTP.arg("device");          // �������� �������� device �� �������
	if (restart == "ok")
	{                         // ���� �������� ����� ��
		HTTP.send(200, "text / plain", "Reset OK"); // O��������� ����� Reset OK
		ESP.restart();                                // ������������� ������
	}
	else
	{                                        // �����
		HTTP.send(200, "text / plain", "No Reset"); // O��������� ����� No Reset
	}
}

void handleConfigJSON()
{
	String root = "{}";  // ��������� ������ ��� �������� � ���� ������������ � json �������
						 //{"SSDP":"LuckyBox","ssid":"LuckyBox","password":"12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101" � �.�.}
						 // ����������� ������ ��� json ������� ����� ����� ����� �� ���� �������������, ��������������� ��� ESP8266
	DynamicJsonBuffer jsonBuffer;
	//  �������� ������ JSON ����� ��������� jsonBuffer
	JsonObject& json = jsonBuffer.parseObject(root);
	// ��������� ���� json
	json["SSDP"] = SSDP_Name;
	json["ssidAP"] = _ssidAP;
	json["passwordAP"] = _passwordAP;
	json["ssid"] = _ssid;
	json["password"] = _password;
	json["timezone"] = timezone;
	json["ip"] = WiFi.localIP().toString();
	json["time"] = GetTime();
	json["date"] = GetDate();
	json["temperature"] = temperature1;
	json["temperature2"] = temperature2;
	json["temperature3"] = temperature3;
	json["temperature4"] = temperature4;
	//json["setting"] = settingColumn;
	//json["settingAlarm"] = settingAlarm;


	// �������� ��������� json � ���������� root
	root = "";
	json.printTo(root);
	HTTP.send(200, "text/json", root);
}


