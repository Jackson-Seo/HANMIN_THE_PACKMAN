#include "pch.h"
#include "ProPertiesWndCRT.h"
#include "Resource.h"

void ProPertiesWndCRT::createBtns(CWnd* cwnd, LONG left, LONG right) {
	checkBox = new CButton[6];
	
	for (int i = 0; i < 6; i++) {
		checkBox->Create(_T("¹öÆ°" + i), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, CRect(left, 30 + height*i, right, 30 + height*(i+1)), cwnd, ID_PROPERTIES_CHECKBOX1 +i);
	}
}