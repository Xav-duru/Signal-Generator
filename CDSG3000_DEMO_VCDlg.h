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
	void OnConnect(CString&);
	void OnSendFreAmp(CString, CString);
	void OnSendCommand(CString);
	void OnRead(CString);
	void UpdateData(bool);
	CString getFrequency();
	CString getAmplitude();
	CString getCommand();

	CString m_strInstrAddr;
	CString m_strCommand;
	CString m_strResult;
	bool mutex = false;
	CString strSrc;
};
LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

