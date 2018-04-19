#include "reflux_mode.h"
#include "setting.h"
#include <ArduinoJson.h>
// ������������

float settingColumn =101;         // ����������� ������������ ���������� �� ������� � �����
float temperatureStartPressure = 78;   //����������� ������� ������ ��� ������� ������������ ������������
float settingColumnShow = 0;
float temperatureAlcoholBoil = 0;

//��������� ������� ��� ������������
void initReflux()
{
	HTTP.on("/SetTemp", handleSetTemp);    // ��������� ������� ��� ������������ (������� Reflux)
	HTTP.on("/reflux.json", handleRefluxJSON); // ������������ reflux.json �������� ��� �������� ������ � web ���������
}

void handleSetTemp()
{              //
	settingColumn = HTTP.arg("setting").toFloat();         // �������� �������� ������� �� ������� � ��������� � ���������� ����������
	temperatureStartPressure = HTTP.arg("temperatureAlcoholBoil").toFloat();
	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������
}

void handleRefluxJSON()
{
	String root = "{}";  // ��������� ������ ��� �������� � ���� ������������ � json �������

	temperatureAlcoholBoil = 78.91 - ( 780 - pressure )*0.038; // ������ ����������� ������� ������ ��� ������ ��������
	settingColumnShow = settingColumn + ( temperatureAlcoholBoil - temperatureStartPressure ); // ������ ������� ��� ������������ ����������� ��������

																							   //AlarmSound (settingAlarm);

	DynamicJsonBuffer jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(root);

	json["temperature"] = temperature1;
	json["temperature2"] = temperature2;
	json["temperature3"] = temperature3;
	json["temperature4"] = temperature4;
	json["setting"] = settingColumnShow;
	json["settingAlarm"] = settingAlarm;
	json["temperatureAlcoholBoil"] = temperatureAlcoholBoil;
	json["pressure"] = pressure;
	json["temperatureStartPressure"] = temperatureStartPressure;

	root = "";
	json.printTo(root);
	HTTP.send(200, "text/json", root);
}

void refluxLoop()
{

	if (temperature2 >= settingColumnShow)
	{
		settingAlarm = true;
	}
	else
	{
		settingAlarm = false;
	}
}

