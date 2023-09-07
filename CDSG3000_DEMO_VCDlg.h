#pragma once
#include <cstring>
#include <atlstr.h>
#include <atlwin.h>
#include <string>
#include <atltypes.h>
#include <iostream>
#include "visa.h"
#include "visatype.h"
#include "vpptype.h"

#define MAX_REC_SIZE 2048

class CDSG3000_DEMO_VCDlg
{
public:
	bool InstrWrite(CString, CString);
	bool InstrRead(CString, CString*);
	void OnConnect();
	void OnSend();
	void OnRead();
	void UpdateData(bool);


	CString m_strInstrAddr;
	CString m_strCommand;
	CString m_strResult;
	bool mutex = false;
};
LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

