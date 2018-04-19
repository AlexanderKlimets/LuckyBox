#include "file_config.h"
#include "user_config.h"
#include "setting.h"
#include <FS.h>
#include <ArduinoJson.h>

// �������� ������ ����������� � ����  config.json
bool loadConfig()
{
	// ��������� ���� ��� ������
	File configFile = SPIFFS.open("/config.json", "r");
	if (!configFile)
	{
		// ���� ���� �� ������
		Serial.println("Failed to open config file");
		//  ������� ���� ������� � ���� ����� �� ���������
		saveConfig();
		configFile.close();
		return false;
	}
	// ��������� ������ �����, ����� ������������ ���� �������� ������ 2048 �����
	size_t size = configFile.size();
	if (size > 2048)
	{
		Serial.println("Config file size is too large");
		configFile.close();
		return false;
	}

	// ��������� ���� ������������ � ���������� ����������
	jsonConfig = configFile.readString();
	configFile.close();
	// ����������� ����� ��� json ������ ����� ����� ����� �� ���� ����������� ��������������� ��� ESP8266
	DynamicJsonBuffer jsonBuffer;
	//  �������� ������ JSON ����� ��������� jsonBuffer
	//  ������ ������� �� ���������� ���������� String jsonConfig
	JsonObject& root = jsonBuffer.parseObject(jsonConfig);
	// ������ ����� �������� �������� �� root
	_ssidAP = root["ssidAPName"].as<String>(); // ��� �������� ������
	_passwordAP = root["ssidAPPassword"].as<String>();
	timezone = root["timezone"];               // ��� �������� �����
	SSDP_Name = root["SSDPName"].as<String>();
	_ssid = root["ssidName"].as<String>();
	_password = root["ssidPassword"].as<String>();
	return true;
}

// ������ ������ � ���� config.json
bool saveConfig()
{
	// ����������� ������ ��� json �������, ����� ����� ����� �� ���� �������������, ��������������� ��� ESP8266
	DynamicJsonBuffer jsonBuffer;
	//  �������� ������ JSON ����� ��������� jsonBuffer
	JsonObject& json = jsonBuffer.parseObject(jsonConfig);
	// ��������� ���� json
	json["SSDPName"] = SSDP_Name;
	json["ssidAPName"] = _ssidAP;
	json["ssidAPPassword"] = _passwordAP;
	json["ssidName"] = _ssid;
	json["ssidPassword"] = _password;
	json["timezone"] = timezone;

	// �������� ��������� json � ���������� ���������� json.printTo(jsonConfig);
	json.printTo(jsonConfig);
	// ��������� ���� ��� ������
	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile)
	{
		//Serial.println("Failed to open config file for writing");
		configFile.close();
		return false;
	}
	// ���������� ������ json � ����
	json.printTo(configFile);
	configFile.close();
	return true;
}



