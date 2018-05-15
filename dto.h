// dto.h

#ifndef _DTO_h
#define _DTO_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
// ��������� ��� �������� ������ �������
class dto
{

public:
	float temperatures[8];	// ������� �����������

	/*		���		*/
	float settingTank;		// ����������� ���������� ������� ����
	float heaterPower;		// ������������� �������� ����
	bool heaterStatus;		// ��������� ���� ���/����

	void init();
	String getJson();		// ��������� ������ ��� �������� � ���� ������������ � json �������
};


#endif

