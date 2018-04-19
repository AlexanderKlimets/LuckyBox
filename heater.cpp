#include "heater.h"
#include "user_config.h"
#include "setting.h"
#include <ArduinoJson.h>

byte heaterStatus	=	0;		// ������ ���� (�������/��������)
int	heaterPower		=	0;		// �������� ���� � % �� 0 �� 100
int	reg				=	0;		// ���������� ��� ��������
int	tenRealPower	=	100;	// �������� ��� �� ���������� ����, ����� ���� �� 50% (��� ���������� ���� 160�) �� 135%(��� ���������� ���� 260�)
int	errorBr			=	0;      // ������ ���������� �� ��������� ����������
boolean outHeater;
unsigned long lastTime=0;       //����� ������� ���������
int State = LOW;

void ResOut();

void heaterLoop()
{
	if (heaterStatus)
	{
		if (lastTime + 250 <= millis())
		{
			if (State == LOW)
			{
				ResOut();
				State = HIGH;
			}
			else
			{
				ResOut();
				State = LOW;
			}
			lastTime = millis();
		}
	}
	else { digitalWrite(heater, 0); }
}

void ResOut()
{      // �������� ������� ResOut()��� ������ �������� ���������� ����� ���� (������ 10��)
	   //delay(1);         // �������� ������� ������������� ������ ���������� ��������� ����� ��� �������� ���������� ����� ���� 
	reg = heaterPower + errorBr;
	if (reg < 50)
	{
		outHeater=0;
		errorBr = reg;
	}
	else
	{
		outHeater=1;
		// ������ ���� ��������� ��������s ���������� ���b ����� 5�� ����� �������� ����� ����
		errorBr=reg - tenRealPower;
	}
	digitalWrite(heater, outHeater); //��� ����� ������� �������������� ���������� ���������� ����
	;
}

void initHeater()
{
	pinMode(heater, OUTPUT);
	digitalWrite(heater, LOW);
	//HeaterOff.attach_ms(10000, setPWM, 0);
	HTTP.on("/SetHeaterPower", handleSetHeaterPower);    // ��������� ������� ��� ������������ (������� Reflux)
	HTTP.on("/heater.json", handleHeaterJSON); // ������������ heater.json �������� ��� �������� ������ � web ���������
}


void handleSetHeaterPower()
{              //
	heaterPower = HTTP.arg("heaterPower").toInt();         // �������� �������� �������� ���� �� ������� � ��������� � ���������� ����������
	heaterStatus = HTTP.arg("heaterStatus").toInt();

	HTTP.send(200, "text/plain", "OK");   // ���������� ����� � ����������

}
void handleHeaterJSON()
{
	String root = "{}";  // ��������� ������ ��� �������� � ���� ������������ � json �������

	DynamicJsonBuffer jsonBuffer;
	JsonObject& json = jsonBuffer.parseObject(root);

	json["heaterPower"] = heaterPower;

	root = "";
	json.printTo(root);
	HTTP.send(200, "text/json", root);
}

