#include "wifi_config.h"
#include <ESP8266WiFi.h>
#include "setting.h"
#include "oled.h"

void initWifi()
{
	// ������� ����������� � ����� �������
	WiFi.mode(WIFI_STA);
	byte tries = 11;
	IPAddress Local_IP;
	WiFi.begin(_ssid.c_str(), _password.c_str());
	// ������ �������� ����������� �� ��� ��� ���� ������� tries
	// �� ������ ����� ���� ��� �� ������� �����������
	while (--tries && WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(1000);
	}
	if (WiFi.status() != WL_CONNECTED)
	{
		// ���� �� ������� ������������ ��������� � ������ AP
		Serial.println("");
		Serial.println("WiFi up AP");
		StartAPMode();
	}
	else
	{
		// ����� ������� ������������ ���������� ���������
		// � ����������� � ������� ����� IP
		Local_IP = WiFi.localIP();
		Serial.println("");
		Serial.println("WiFi connected");
		Serial.println("IP address: ");
		Serial.println(Local_IP);

		// ���� ���� ��������� ������� ��������� IP
		#if defined OLED_Display
		oledStartNormal();
		display.setTextSize(1);
		display.setCursor(20, 20);
		display.print("Local IP adress:");
		display.setCursor(32, 40);
		display.print(Local_IP);
		display.display();
		delay(5000);
		#endif
	}
}

bool StartAPMode()
{
	IPAddress apIP(192, 168, 4, 1);
	// ��������� WIFI
	WiFi.disconnect();
	// ������ ����� �� ����� ����� �������
	WiFi.mode(WIFI_AP);
	// ������ ��������� ����
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	// �������� WIFI � ������ ����� ������� � ������ � �������
	// ���������� � ���������� _ssidAP _passwordAP
	WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
	return true;
}



