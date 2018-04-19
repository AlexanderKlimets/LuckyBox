#include "distillation_mode.h"
#include "setting.h"
#include "user_config.h"
#include "time_config.h"
#include <ArduinoJson.h>

//�����������

// ���������� ����������
bool settingAlarmDistillation = false;     // ���������� ������� �� ����������� ���� 
float settingTank = 100;                   // ����������� ���������� ������� ���� ��� ����������� ����� � �����-�����

void initDistillation()
{
	HTTP.on("/SetTempTank", handleSetTempTank);    // ��������� ������� ��� ����������� (������� Distillation)
	HTTP.on("/distillation.json", handleDistillationJSON); // ������������ distillation.json �������� ��� �������� ������ � web ���������
}

//��������� ������� ��� �����������
void handleSetTempTank()
{
	settingTank = HTTP.arg("SettingTank").toFloat();         // �������� �������� ������� �� ������� � ��������� � ���������� ����������
	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������
}

void handleDistillationJSON()
{
	String root = "{}";  // ��������� ������ ��� �������� � ���� ������������ � json �������

	DynamicJsonBuffer jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(root);

	json["temperature"] = temperature1;
	json["temperature2"] = temperature2;
	json["temperature3"] = temperature3;
	json["temperature4"] = temperature4;
	json["time"] = GetTime();
	json["settingTank"] = settingTank;
	json["settingAlarmDistillation"] = settingAlarmDistillation;

	root = "";
	json.printTo(root);
	HTTP.send(200, "text/json", root);
}

void distillationLoop()
{

	if (temperature1 >= settingTank)
	{
		settingAlarmDistillation = true;
		digitalWrite(buzzer, HIGH);
	}
	else
	{
		settingAlarmDistillation = false;
		digitalWrite(buzzer, LOW);
	}
}

