#include "time_config.h"
#include "file_config.h"
#include "setting.h"
#include <ESP8266WiFi.h>

#include <time.h>               //���������� � ������
void initTime()
{
	HTTP.on("/Time", handleTime);     // ���������������� ����� ���������� �� ������� ���� /Time
	HTTP.on("/TimeZone", handleTimeZone);    // ��������� ��������� ���� �� ������� ���� http://192.168.0.101/TimeZone?timezone=3
	timeSynch(timezone);
}
void timeSynch(int zone)
{
	if (WiFi.status() == WL_CONNECTED)
	{
		// ��������� ���������� � NTP ��������
		configTime(zone * 3600, 0, "pool.ntp.org", "ru.pool.ntp.org");
		int i = 0;
		Serial.println("\nWaiting for time");
		while (!time(nullptr) && i < 10)
		{
			Serial.print(".");
			i++;
			delay(1000);
		}
		Serial.println("");
		Serial.println("ITime Ready!");
		Serial.println(GetTime());
		Serial.println(GetDate());
	}
}
// ��������� ���������� ��������� ���� �� ������� ���� http://192.168.0.101/TimeZone?timezone=3
void handleTimeZone()
{
	timezone = HTTP.arg("timezone").toInt(); // �������� �������� timezone �� ������� ������������ � int ��������� � ���������� ����������
	saveConfig();
	HTTP.send(200, "text/plain", "OK");
}

void handleTime()
{
	timeSynch(timezone);
	HTTP.send(200, "text/plain", "OK"); // ���������� ����� � ����������
}

// ��������� �������� �������
String GetTime()
{
	time_t now = time(nullptr); // �������� ����� � ������� ���������� time.h
	String Time = ""; // ������ ��� ����������� �������
	Time += ctime(&now); // ����������� ����� � ������ ������� Thu Jan 19 00:55:35 2017
	int i = Time.indexOf(":"); //���� ������� ������� ������� :
	Time = Time.substring(i - 2, i + 6); // �������� �� ������ 2 ������� ����� �������� : � 6 �������� �����
	return Time; // ���������� ���������� �����
}

// ��������� ����
String GetDate()
{
	time_t now = time(nullptr); // �������� ����� � ������� ���������� time.h
	String Data = ""; // ������ ��� ����������� �������
	Data += ctime(&now); // ����������� ����� � ������ ������� Thu Jan 19 00:55:35 2017
	int i = Data.lastIndexOf(" "); //���� ������� ���������� ������� ������
	String Time = Data.substring(i - 8, i + 1); // �������� ����� � ������
	Data.replace(Time, ""); // ������� �� ������ 8 �������� ������� � ������
	return Data; // ���������� ���������� ����
}



