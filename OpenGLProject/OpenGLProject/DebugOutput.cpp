#include "pch.h"
#include "DebugOutput.h"

// ����� ��忡�� ����� ���� �Լ��Դϴ�. �ѱ��� ��½ÿ� �����ϴ�
void trace1(const std::string& str1) {
	size_t size;
	wchar_t* wmsg1 = new wchar_t[strlen(str1.c_str()) + 1]; //memory allocation
	mbstowcs_s(&size, wmsg1, strlen(str1.c_str()) + 1, str1.c_str(), strlen(str1.c_str()) + 1);

	TRACE(wmsg1);
	delete[]wmsg1;
}

void trace2(const std::string& str1, const std::string& str2) {
	size_t size;
	wchar_t* wmsg1 = new wchar_t[strlen(str1.c_str()) + 1]; //memory allocation
	mbstowcs_s(&size, wmsg1, strlen(str1.c_str()) + 1, str1.c_str(), strlen(str1.c_str()) + 1);
	wchar_t* wmsg2 = new wchar_t[strlen(str2.c_str()) + 1]; //memory allocation
	mbstowcs_s(&size, wmsg2, strlen(str2.c_str()) + 1, str2.c_str(), strlen(str2.c_str()) + 1);

	TRACE(wmsg1, wmsg2);
	delete[]wmsg1;
	delete[]wmsg2;
}