#pragma once
#include <cstring>

#include <string>
#include <iostream>
#include <atlstr.h>
#include <atlwin.h>
#include <atltypes.h>
#include "visa.h"
#include "visatype.h"
#include "vpptype.h"


#define MAX_REC_SIZE 2048
#define MAX_INSTRDESC_SIZE 1000

class RigolCom
{
public:
	RigolCom();

	bool InstrWrite(CString, CString);
	bool InstrRead(CString, CString*);
	//void OnConnect(CString&);
	//void OnSendFreAmp(CString, CString);
	void OnSendCommand(CString, CString&);
	//void OnRead(CString);
	void UpdateData(bool);
	//CString getFrequency();
	//CString getAmplitude();
	//CString getCommand();

	//CString m_strInstrAddr;
	//CString m_strCommand;
	//CString m_strResult;
	bool mutex = false;

	ViSession defaultRM, instr;
	ViStatus status;
	char motif[4] = "?*";
	ViString expr = motif;
	ViChar instrDesc[MAX_INSTRDESC_SIZE];
	ViUInt32 retCount;

	CString str;
	CString strSrc = "";
	CString strInstr = "";

	char* SendBuf = NULL;
	char* SendAddr = NULL;
	unsigned char RecBuf[MAX_REC_SIZE];
	unsigned long i = 0;
	bool bWriteOK = false;
	bool bReadOK = false;
	//bool bFindDSG = false;
};
LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

