#include "brewing_mode.h"
#include "heater.h"
#include "setting.h"
#include <ArduinoJson.h>
#include "time_config.h"

// ���������

// ���������� ��� ���� ���������
float pauseTemp1 = 48;
float pauseTemp2 = 64;
float pauseTemp3 = 72;
float pauseTemp4 = 78;

int pauseTime1 = 15;
int pauseTime2 = 40;
int pauseTime3 = 30;
int pauseTime4 = 5;

unsigned long currentTime=0;      // ���������� �������� �������
unsigned long processStartTime=0; // ����� ������ �������� ���������
int startBrewing = 0;     // ������ �������� ���������
int stepBrewing = 0;              // ���� ���������

void initBrewing()
{
	HTTP.on("/SettingBrewing", handleSettingBrewing);    // ��������� ������� ��� ����������� (������� Distillation)
	HTTP.on("/brewing.json", handleBrewingJSON); // ������������ distillation.json �������� ��� �������� ������ � web ���������
}

//��������� � ��������� ���������� ��� ���������
void handleSettingBrewing()
{
	pauseTemp1 = HTTP.arg("pauseTemp1").toFloat();         // �������� �������� ����������� �� ������� � ��������� � ���������� ����������
	pauseTemp2 = HTTP.arg("pauseTemp2").toFloat();
	pauseTemp3 = HTTP.arg("pauseTemp3").toFloat();
	pauseTemp4 = HTTP.arg("pauseTemp4").toFloat();

	pauseTime1 = HTTP.arg("pauseTime1").toInt();         // �������� �������� ������� ����� �� ������� � ��������� � ���������� ����������
	pauseTime2 = HTTP.arg("pauseTime2").toInt();         // �������� �������� ������� ����� �� ������� � ��������� � ���������� ����������
	pauseTime3 = HTTP.arg("pauseTime3").toInt();         // �������� �������� ������� ����� �� ������� � ��������� � ���������� ����������
	pauseTime4 = HTTP.arg("pauseTime4").toInt();         // �������� �������� ������� ����� �� ������� � ��������� � ���������� ����������

	startBrewing = HTTP.arg("startBrewing").toInt();             // �������� �������� ������ ��� ����� �� ������� � ��������� � ����������
	stepBrewing = HTTP.arg("stepBrewing").toInt();

	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������
}

void handleBrewingJSON()
{
	String root = "{}";  // ��������� ������ ��� �������� � ���� ������������ � json �������

	DynamicJsonBuffer jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(root);

	json["pauseTemp1"] = pauseTemp1;
	json["pauseTemp2"] = pauseTemp2;
	json["pauseTemp3"] = pauseTemp3;
	json["pauseTemp4"] = pauseTemp4;

	json["pauseTime1"] = pauseTime1;
	json["pauseTime2"] = pauseTime2;
	json["pauseTime3"] = pauseTime3;
	json["pauseTime4"] = pauseTime4;

	json["time"] = GetTime();
	json["temperature"] = temperature1;
	json["startBrewing"] = startBrewing;    // �������� �������� ������������� ��� ������� ��
	json["stepBrewing"] = stepBrewing;

	root = "";
	json.printTo(root);
	HTTP.send(200, "text/json", root);
}

void brewingLoop()
{

	currentTime = millis() / 1000;         // ������� ����� � ���.

	if (startBrewing)
	{
		switch (stepBrewing)
		{
			case 0:
				heaterStatus=0;
				//stepBrewing=0;       
				break;

			case 1:
				if (temperature1 < pauseTemp1) { heaterStatus = 1; }
				else
				{
					heaterStatus = 0;
					stepBrewing++;                                       // �������� ���������� ����� ����
					processStartTime = currentTime;
				}
				break;

			case 2:
				if (processStartTime + pauseTime1 * 60 < currentTime) { stepBrewing++; }
				else
				{
					heaterStatus=0;
					if (temperature1 < pauseTemp1) { heaterStatus = 1; }         //�������� ����������
				}
				break;

			case 3:
				if (temperature1 < pauseTemp2) { heaterStatus = 1; }
				else
				{
					heaterStatus = 0;
					stepBrewing++;
					processStartTime = currentTime;
				}
				break;

			case 4:
				if (processStartTime + pauseTime2 * 60 < currentTime) { stepBrewing++; }
				else
				{
					heaterStatus = 0;
					if (temperature1 < pauseTemp2) { heaterStatus = 1; }
				}
				break;

			case 5:
				if (temperature1 < pauseTemp3) { heaterStatus = 1; }
				else
				{
					heaterStatus = 0;
					stepBrewing++;
					processStartTime = currentTime;
				}
				break;

			case 6:
				if (processStartTime + pauseTime3 * 60 < currentTime) { stepBrewing++; }
				else
				{
					heaterStatus = 0;
					if (temperature1 < pauseTemp3) { heaterStatus = 1; }
				}
				break;

			case 7:
				if (temperature1 < pauseTemp4) { heaterStatus = 1; }
				else
				{
					heaterStatus = 0;
					stepBrewing++;
					processStartTime = currentTime;
				}
				break;

			case 8:
				if (processStartTime + pauseTime4 * 60 < currentTime)
				{
					stepBrewing = 0;
					heaterStatus = 0;
					startBrewing = 0;
				}
				else
				{
					heaterStatus = 0;
					if (temperature1 < pauseTemp4) { heaterStatus = 1; }
				}
				break;
		}
		// digitalWrite(heater, heaterStatus);

	}

}

