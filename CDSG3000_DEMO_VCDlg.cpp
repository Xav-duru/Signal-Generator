#include "CDSG3000_DEMO_VCDlg.h"

// Encapsulate the read and write operations of VISA.
// 1) Encapsulate the write operation of VISA for easier operation.

#include <iostream>
#include "CDSG3000_DEMO_VCDlg.h"
#include <WinUser.h>
#include <format>
//#include <Python.h>

using namespace std;


bool CDSG3000_DEMO_VCDlg::InstrWrite(CString strAddr, CString strContent) //write function
{
	cout << "InstrWrite Start" << endl;

	ViSession defaultRM, instr;
	ViStatus status;
	ViUInt32 retCount;
	char* SendBuf = NULL;
	char* SendAddr = NULL;
	bool bWriteOK = false;
	CString str;
	//Change the address's data style from CString to char*
	SendAddr = strAddr.GetBuffer(strAddr.GetLength());
	strcpy_s(SendAddr, strAddr.GetLength()+1, strAddr);
	strAddr.ReleaseBuffer();
	//Change the command's data style from CString to char*
	SendBuf = strContent.GetBuffer(strContent.GetLength());
	strcpy_s(SendBuf, strContent.GetLength()+1, strContent);
	strContent.ReleaseBuffer();
	//open the VISA instrument
	status = viOpenDefaultRM(&defaultRM);
	if (status < VI_SUCCESS)
	{
		MessageBox(NULL, "No VISA instrument was opened !", NULL, MB_OKCANCEL);
		return false;
	}
	status = viOpen(defaultRM, SendAddr, VI_NULL, VI_NULL, &instr);
	//write command to the instrument


	status = viWrite(instr, (unsigned char*)SendBuf, strlen(SendBuf), &retCount);
	//close the instrument
	status = viClose(instr);
	status = viClose(defaultRM);
	cout << "InstrWrite Done" << endl;

	return bWriteOK;
}
// 2) Encapsulate the read operation of VISA for easier operation.
bool CDSG3000_DEMO_VCDlg::InstrRead(CString strAddr, CString* pstrResult)
//Read from the instrument
{
	cout << "InstrRead Start" << endl;

	ViSession defaultRM, instr;
	ViStatus status;
	ViUInt32 retCount;
	char* SendAddr = NULL;
	unsigned char RecBuf[MAX_REC_SIZE];
	bool bReadOK = false;
	CString str;
	//Change the address's data style from CString to char*
	SendAddr = strAddr.GetBuffer(strAddr.GetLength());
	strcpy_s(SendAddr, strAddr.GetLength()+1, strAddr);
	strAddr.ReleaseBuffer();
	memset(RecBuf, 0, MAX_REC_SIZE);
	//open the VISA instrument
	status = viOpenDefaultRM(&defaultRM);
	if (status < VI_SUCCESS)
	{
		// Error Initializing VISA...exiting 
		MessageBox(NULL, "No VISA instrument was opened !", NULL, MB_OKCANCEL);
		return false;
	}
	//open the instrument
	status = viOpen(defaultRM, SendAddr, VI_NULL, VI_NULL, &instr);
	//read from the instrument
	status = viRead(instr, RecBuf, MAX_REC_SIZE, &retCount);
	//close the instrument
	status = viClose(instr);
	status = viClose(defaultRM);
	(*pstrResult).Format("%s", RecBuf);

	cout << "InstrRead Done" << endl;

	return bReadOK;
}

// Add the control message response codes.
// 1) Connect the instrument
void CDSG3000_DEMO_VCDlg::OnConnect()
{
	// TODO: Add your control notification handler code here


	ViStatus status;
	ViSession defaultRM;
	char motif[4] = "?*";
	ViString expr = motif;

	cout << "OnConnect Start" << endl;
	
		ViPFindList findList = new unsigned long;
		ViPUInt32 retcnt = new unsigned long;
		ViChar instrDesc[1000];
		CString strSrc = "";
		CString strInstr = "";
		unsigned long i = 0;
		bool bFindDSG = false;
		status = viOpenDefaultRM(&defaultRM);
		if (status < VI_SUCCESS)
		{
			// Error Initializing VISA...exiting
			MessageBox(NULL,"No VISA instrument was opened ! ", NULL, MB_OKCANCEL);
			return;
		}
		memset(instrDesc, 0, 1000);

		// Find resource
		status = viFindRsrc(defaultRM, expr, findList, retcnt, instrDesc);
		//cout << "OnConnect step 1" << " status=" << status << " expr=" << expr <<  "retcnt=" << retcnt << " instrDesc=" << instrDesc << endl;
		for (i = 0; i < (*retcnt); i++)
		{
			// Get instrument name
			strSrc.Format("%s", instrDesc);
			InstrWrite(strSrc, "*IDN?");
			::Sleep(200);
			InstrRead(strSrc, &strInstr);
			cout << strInstr << endl;

			// If the instrument(resource) belongs to the DSG series then jump out from the loop
			strInstr.MakeUpper();
			if (strInstr.Find("DSG") >= 0)
			{
				bFindDSG = true;
				m_strInstrAddr = strSrc;
				break;
			}
			//Find next instrument
			status = viFindNext(*findList, instrDesc);
		}
		if (bFindDSG == false)
		{
			MessageBox(NULL,"Didn't find any DSG!",NULL, MB_OKCANCEL);
		}
		UpdateData(false);

		strSrc.Format("%s", instrDesc);
		InstrWrite(strSrc, ":TRIGger:PULSe[:IMMediate]");
		::Sleep(200);
		InstrRead(strSrc, &strInstr);
		cout << "Result = " << strInstr << endl;
	//*strSrc = "USB0";
	cout << "OnConnect Done" << endl;
}
// 2) Write Operation


void CDSG3000_DEMO_VCDlg::OnSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (m_strInstrAddr.IsEmpty())
	{
		MessageBox(NULL, "Please connect to the instrument first!", NULL, MB_OKCANCEL);
	}
	//InstrWrite(m_strInstrAddr, command);
	m_strResult.Empty();
	UpdateData(false);
}

// 3) Read Operation
void CDSG3000_DEMO_VCDlg::OnRead()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	InstrRead(m_strInstrAddr, &m_strResult);
	UpdateData(false);
}
void CDSG3000_DEMO_VCDlg::UpdateData(bool ordre)
{
	if (ordre == true and mutex == false)
	{
		mutex = true;
	}
	if (ordre == false and mutex == true)
	{
		mutex = false;
	}
}

/*
int main()
{
	CDSG3000_DEMO_VCDlg generator;
	int x;
    cout << "Type a number: "; // Type a number and press enter
	cin >> x; // Get user input from the keyboard
	cout << "Your number is: " << x;	//CString cs_USB_address = "";
	// Utiliser x en paramètre d'entrée pour OnConnect ?
	generator.OnConnect();
	return 0;
}
*/

/*
LRESULT WindowProc(HWND phwnd, UINT upMsg, WPARAM pwParam, LPARAM plParam)
{

	int width = LOWORD(plParam);  // Macro to get the low-order word.
	int height = HIWORD(plParam); // Macro to get the high-order word.

	// Respond to the message:

	return(0);
}
*/
