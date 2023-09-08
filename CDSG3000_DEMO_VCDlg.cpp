#include "CDSG3000_DEMO_VCDlg.h"

// Encapsulate the read and write operations of VISA.
// 1) Encapsulate the write operation of VISA for easier operation.

#include <iostream>
#include "CDSG3000_DEMO_VCDlg.h"
#include <WinUser.h>
#include <format>
//#include <Python.h>

using namespace std;

////////////////////////////////////////////////////////////////////// InstrWrite //////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////// InstrRead ////////////////////////////////////////////////////////////////
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

	cout << "Result = " << pstrResult << endl;

	cout << "InstrRead Done" << endl;

	return bReadOK;
}

////////////////////////////////////////////////////////////////// OnConnect ////////////////////////////////////////////////////////////////
// 1) Connect the instrument
void CDSG3000_DEMO_VCDlg::OnConnect()
{
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
			cout << "m_strInstrAddr = " << m_strInstrAddr << endl;
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
	InstrWrite(strSrc, ":SYST:PRES");
	::Sleep(200);
	InstrRead(strSrc, &strInstr);
	cout << "Result = " << strInstr << endl;
	//*strSrc = "USB0";
	cout << "OnConnect Done" << endl;
}
// 2) Write Operation

/////////////////////////////////////////////////////////////////////// OnSend ///////////////////////////////////////////////////////////////
void CDSG3000_DEMO_VCDlg::OnSend(char frequency, signed lont int level)
{
	cout << "OnSend Start" << endl;

	ViStatus status;
	ViSession defaultRM;
	char motif[4] = "?*";
	ViString expr = motif;

	ViPFindList findList = new unsigned long;
	ViPUInt32 retcnt = new unsigned long;
	ViChar instrDesc[1000];
	CString strSrc = "";
	CString strInstr = "";
	unsigned long i = 0;
	bool bFindDSG = false;
	status = viOpenDefaultRM(&defaultRM);
	
	memset(instrDesc, 0, 1000);

	status = viFindRsrc(defaultRM, expr, findList, retcnt, instrDesc);

	/* Send frequency */
	CString FREQUENCY = ":FREQ ";
	CString GIGAHERTZ = "GHz";
	CString REQUEST_FREQUENCY = FREQUENCY + frequency + GIGAHERTZ;
	cout << REQUEST_FREQUENCY << endl;
	strSrc.Format("%s", instrDesc);

	InstrWrite(strSrc, REQUEST_FREQUENCY);
	::Sleep(200);
	InstrRead(strSrc, &strInstr);
	cout << "Result = " << strInstr << endl;

	/* Send level */
	CString LEVEL = ":LEV -";
	CString REQUEST_LEVEL = LEVEL + level;
	cout << REQUEST_LEVEL << endl;

	InstrWrite(strSrc, REQUEST_LEVEL);
	::Sleep(200);
	InstrRead(strSrc, &strInstr);
	cout << "Result = " << strInstr << endl;

	cout << "OnSend Done" << endl;

}
///////////////////////////////////////////////////////////////////// OnRead /////////////////////////////////////////////////////////////////
// 3) Read Operation
void CDSG3000_DEMO_VCDlg::OnRead()
{
	cout << "OnRead Start" << endl;
	CString strInstr = "";
	UpdateData(true);
	InstrRead(strSrc, &strInstr);
	cout << "strInstr = " << strInstr << endl;

	UpdateData(false);
	cout << "OnRead Done" << endl;

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

////////////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////////////////////////
int main()
{
	CDSG3000_DEMO_VCDlg generator;
	
	char frequency;
    cout << "Give me the frequency "; // Type the frequency and press enter
	cin >> frequency; // Get user input from the keyboard
	cout << "frequency: " << frequency;	

	signed long int level;
	cout << "Give me the level "; // Type the level and press enter
	cin >> level; // Get user input from the keyboard
	cout << "Level: " << level;
	//CString cs_USB_address = "";

	generator.OnConnect();
	generator.OnSend(frequency, level);

	return 0;
}


/*
LRESULT WindowProc(HWND phwnd, UINT upMsg, WPARAM pwParam, LPARAM plParam)
{

	int width = LOWORD(plParam);  // Macro to get the low-order word.
	int height = HIWORD(plParam); // Macro to get the high-order word.

	// Respond to the message:

	return(0);
}
*/
