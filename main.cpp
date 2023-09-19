
// Encapsulate the read and write operations of VISA.
// 1) Encapsulate the write operation of VISA for easier operation.

#include <iostream>
#include "CDSG3000_DEMO_VCDlg.h"
#include <WinUser.h>
#include <format>

#include "CDSG3000_DEMO_VCDlg.h"
#include <iostream>
#include <WinUser.h>
#include <format>
#include <Windows.h>
#ifdef _WIN32	
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
using namespace std;

/*
class SG_InputBox
{
public:
	static LPWSTR GetString(LPCTSTR szCaption, LPCTSTR szPrompt, LPCTSTR szDefaultText = (LPCSTR)L"");
};
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
void setTextAlignment(HWND, int);
void setTextAlignment(HWND hwnd, int textalignment);
#define REPORTERROR ReportError(__FUNCTION__)
void ReportError(const char* CallingFunction);


HINSTANCE hInst = GetModuleHandle(NULL);

WNDCLASSEX wcex;
HFONT m_hFont = NULL;
HWND  m_hWndParent = NULL;
HWND  m_hWndInputBox = NULL;
HWND  m_hWndPrompt = NULL;
HWND  m_hWndShowConnect = NULL;
HWND  m_hWndEdit = NULL;
HWND  m_hWndConnect = NULL;
HWND  m_hWndOK = NULL;
HWND  m_hWndCancel = NULL;
HBRUSH hbrBkgnd = NULL;

#define CLASSNAME					L"SG_Inputbox"
#define INPUTBOX_WIDTH 1000
#define INPUTBOX_HEIGHT 500
#define SOFT_BLUE RGB(206,214,240)
#define TEXTEDIT_HEIGHT	30 * ASPECT_RATIO_Y
#define BUTTON_HEIGHT	25 * ASPECT_RATIO_Y
#define BUTTON_WIDTH	120 * ASPECT_RATIO_X
// #define FONT_HEIGHT		20 * ASPECT_RATIO_Y
#define FONT_HEIGHT		25
#define TOP_EDGE        5
#define ASPECT_RATIO_X  2
#define ASPECT_RATIO_Y  3

#define PUSH_BUTTON					L"Button"
#define FONT_NAME					_T("Times")
#define TEXTEDIT_CLASS				L"edit"
#define SetFontToControl(n)			SendMessage((n), WM_SETFONT, (WPARAM)m_hFont, 5);
wchar_t m_String[320];
int cpt = 0;
CString USB_adress;
CString result = "";
static CDSG3000_DEMO_VCDlg proto;

LPWSTR GetString(LPCTSTR, LPCTSTR, LPCTSTR);

////////////////////////////////////////////////////////////// MAIN //////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "Debut du main " << endl;
	
	CString CSFrequency;
	CString CSAmplitude;
	CString CSCommand;


	proto.OnConnect(USB_adress);
	/*
	CSFrequency = proto.getFrequency();
	CSAmplitude = proto.getAmplitude();
	CSCommand = proto.getCommand();

	cout << "------------------------" << endl;

	cout << "Frequency : " << CSFrequency << endl;
	cout << "Amplitude : " << CSAmplitude << endl;
	proto.OnSendFreAmp(CSFrequency, CSAmplitude);
	proto.OnSendCommand(CSCommand);
	*/
	//		wprintf(L"Testing the InputBox static lib\n");
	LPWSTR result = GetString((LPCSTR)L"Signal Generator - by Xavier Durumain", (LPCSTR)L"Result", (LPCSTR)L"");
	wprintf(L"User entered '%s'\n", result);
	printf("contenu=  %s\n", result);

	std::cout << "avant sleep du main " << endl;
	Sleep(10);
	std::cout << "Fin du main " << endl;

	return 0;
}

///////////////////////////////////////////////////////////////////

LPWSTR GetString(LPCTSTR szCaption, LPCTSTR szPrompt, LPCTSTR szDefaultText = (LPCTSTR)L"")
{
	LOGFONT lfont;
	HINSTANCE m_hInst = NULL;
	RECT r;
	HWND hWnd = GetDesktopWindow();
	GetWindowRect(hWnd, &r);
	std::cout << "GetString" << std::endl;


	// Création de la fenêtre principale

	if (!GetClassInfoEx(hInst, (LPCSTR)CLASSNAME, &wcex))
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = NULL;//LoadIcon(hInst, (LPCTSTR)IDI_MYINPUTBOX);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = (LPCSTR)CLASSNAME;
		wcex.hIconSm = NULL;

		if (RegisterClassEx(&wcex) == 0)
			std::cout << "GetClassInfoEx " << GetLastError() << std::endl;
		//		REPORTERROR;
	}

	m_hWndParent = hWnd;
	std::cout << "before create " << hWnd << " hInst= " << hInst << std::endl;
	m_hWndInputBox = CreateWindowEx(WS_EX_DLGMODALFRAME,
		(LPCSTR)CLASSNAME,
		"Fenêtre principale",
		WS_POPUPWINDOW | WS_CAPTION | WS_TABSTOP,
		(r.right - INPUTBOX_WIDTH) / 2, (r.bottom - INPUTBOX_HEIGHT) / 2,
		INPUTBOX_WIDTH, INPUTBOX_HEIGHT,
		m_hWndParent,
		NULL,
		hInst,
		NULL);


	if (m_hWndInputBox == NULL)
	{
		//		REPORTERROR;
		std::cout << "after create" << GetLastError() << std::endl;
		return NULL;
	}
	std::cout << "after create m_hWndInputBox= " << m_hWndInputBox << std::endl;

	// Set test alignment
	setTextAlignment(m_hWndPrompt, SS_CENTER);
	char temp[50] = "";  //OK
	SetWindowText(m_hWndPrompt, (LPCSTR)temp);
	setTextAlignment(m_hWndEdit, SS_CENTER);
	SetForegroundWindow(m_hWndInputBox);

	// Set default button
	SendMessage((HWND)m_hWndOK, BM_SETSTYLE,
		(WPARAM)LOWORD(BS_DEFPUSHBUTTON), MAKELPARAM(TRUE, 0));
	SendMessage((HWND)m_hWndCancel, BM_SETSTYLE,
		(WPARAM)LOWORD(BS_PUSHBUTTON), MAKELPARAM(TRUE, 0));
	std::cout << "set default button " << GetLastError() << std::endl;
	std::cout << "set default button " << GetLastError() << std::endl;
	// Set default text
	SendMessage(m_hWndEdit, EM_SETSEL, 0, -1);
	SendMessage(m_hWndEdit, EM_REPLACESEL, 0, (LPARAM)szDefaultText);
	SendMessage(m_hWndEdit, EM_SETSEL, 0, -1);
	SetFocus(m_hWndEdit);

	std::cout << "set default text " << GetLastError() << std::endl;
	EnableWindow(m_hWndParent, FALSE);
	std::cout << "show window " << GetLastError() << std::endl;
	ShowWindow(m_hWndInputBox, SW_SHOW); //	ShowWindow(m_hWndInputBox, SW_NORMAL);
	UpdateWindow(m_hWndInputBox);

	BOOL ret = 0;

	MSG msg;

	HWND hWndFocused;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		hWndFocused = GetFocus();

		if (msg.message == WM_KEYDOWN)
		{
			if (msg.wParam == VK_ESCAPE)
			{
				SendMessage(m_hWndInputBox, WM_DESTROY, 0, 0);
				ret = 0;
			}
			if (msg.wParam == VK_RETURN)
			{
				if (hWndFocused == m_hWndConnect) {
					proto.OnConnect(USB_adress);
					cout << "USB_adress :" << USB_adress << endl;
					//char temp[50] = USB_adress;
					SetWindowText(m_hWndShowConnect, (LPCSTR)USB_adress);
				}

				else {
					int nCount = GetWindowTextLength(m_hWndEdit);
					nCount++;
					GetWindowText(m_hWndEdit, (LPSTR)&m_String, nCount);
					std::cout << "nCount = " << nCount << endl;
					std::cout << "@input = " << m_String << " val= " << *m_String << endl;
					printf("contenu=  %s\n", m_String);
					CString StringCommand = (LPSTR)m_String;
					proto.OnSendCommand(StringCommand, result);
					//SendMessage(m_hWndInputBox, WM_DESTROY, 0, 0);
					SetWindowText(m_hWndPrompt, result);

					ret = 1;
				}
			}
			if (msg.wParam == VK_TAB)
			{
				hWndFocused = GetFocus();
				if (hWndFocused == m_hWndEdit) SetFocus(m_hWndOK);
				if (hWndFocused == m_hWndOK) SetFocus(m_hWndCancel);
				if (hWndFocused == m_hWndCancel) SetFocus(m_hWndEdit);
			}



		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return m_String;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cpt++;
	// std::cout << "callback entry = " << cpt << " msg= " << message << " hWnd = " << hWnd << std::endl;
	LOGFONT lfont;
	HINSTANCE m_hInst = NULL;
	switch (message)
	{
	case WM_CTLCOLORSTATIC:
	{
		std::cout << "callback entry = " << cpt << " WM_CTLCOLORSTATIC= " << message << std::endl;
		HDC hdcStatic = (HDC)wParam;
		if (hbrBkgnd == NULL)
		{
			hbrBkgnd = CreateSolidBrush(SOFT_BLUE);
		}
		SetTextColor(hdcStatic, RGB(0, 0, 0));
		SetBkColor(hdcStatic, SOFT_BLUE);

		return (INT_PTR)hbrBkgnd;
	}
	break;
	case WM_CREATE:
		std::cout << "callback entry = " << cpt << " WM_CREATE= " << message << std::endl;

		// Define out font
		memset(&lfont, 0, sizeof(lfont));
		lstrcpy(lfont.lfFaceName, FONT_NAME);
		lfont.lfHeight = FONT_HEIGHT;
		lfont.lfWeight = FW_NORMAL;//FW_BOLD;
		lfont.lfItalic = FALSE;
		lfont.lfCharSet = DEFAULT_CHARSET;
		lfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfont.lfQuality = DEFAULT_QUALITY;
		lfont.lfPitchAndFamily = DEFAULT_PITCH;
		m_hFont = CreateFontIndirect(&lfont);
		// 
		m_hInst = GetModuleHandle(NULL);
		std::cout << "callback creation nelle fenetre" << endl;
		
		// The OnConnect confirmation
		m_hWndShowConnect = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("static"), (LPCSTR)L"",
			WS_VISIBLE | WS_CHILD,
			50, 50, INPUTBOX_WIDTH - BUTTON_WIDTH - 250, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);	

		if (m_hWndShowConnect == NULL)
		{
			std::cout << "callback CreateWindowEx static = " << GetLastError() << std::endl;
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndPrompt);
		SetFocus(m_hWndEdit);

		// The Connect button
		m_hWndConnect = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("button"), TEXT("Connect"),
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			INPUTBOX_WIDTH - BUTTON_WIDTH - 50, 50, BUTTON_WIDTH, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndConnect == NULL)
		{
			std::cout << "callback CreateWindowEx BUTTON = " << GetLastError() << std::endl;
			//	REPORTERROR;
			return NULL;
		}
		// setting font
		SetFontToControl(m_hWndConnect);


		// The TextEdit Control - For the text to be input
		m_hWndEdit = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("Edit"), (LPCSTR)L"",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
			50, 165, INPUTBOX_WIDTH - BUTTON_WIDTH - 250, TEXTEDIT_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);
		std::cout << "callback CreateWindowEx = " << "hwnd " << m_hWndEdit << "error" << GetLastError() << std::endl;


		if (m_hWndEdit == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		SetFontToControl(m_hWndEdit);


		
		// The Confirm button
		m_hWndOK = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("button"), TEXT("Send command"),
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			INPUTBOX_WIDTH - BUTTON_WIDTH - 50, 165, BUTTON_WIDTH, TEXTEDIT_HEIGHT,
			hWnd,NULL,m_hInst,NULL);

		if (m_hWndOK == NULL)
		{
			std::cout << "callback CreateWindowEx BUTTON = " << GetLastError() << std::endl;
			//	REPORTERROR;
			return NULL;
		}
		// setting font
		SetFontToControl(m_hWndOK);

		

		// The SG_InputBox Caption Static text
		m_hWndPrompt = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("static"), (LPCSTR)L"",
			WS_VISIBLE | WS_CHILD,
			50, 300, INPUTBOX_WIDTH - BUTTON_WIDTH - 250, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndPrompt == NULL)
		{
			std::cout << "callback CreateWindowEx static = " << GetLastError() << std::endl;
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndPrompt);
		SetFocus(m_hWndEdit);

		// The Cancel button
		m_hWndCancel = CreateWindowEx(WS_EX_STATICEDGE,
			TEXT("button"), TEXT("Cancel"),
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			INPUTBOX_WIDTH - BUTTON_WIDTH - 50, 300, BUTTON_WIDTH, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndCancel == NULL)
		{
			std::cout << "callback CreateWindowEx cancel BUTTON = " << GetLastError() << std::endl;
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndCancel);

		break;

	case WM_DESTROY:

		DeleteObject(m_hFont);


		EnableWindow(m_hWndParent, TRUE);
		SetForegroundWindow(m_hWndParent);
		DestroyWindow(hWnd);
		PostQuitMessage(0);

		break;
	case WM_COMMAND:
		std::cout << "callback entry = " << cpt << " WM_COMMAND= " << message << std::endl;
		switch (HIWORD(wParam))
		{

		case BN_CLICKED:
			if ((HWND)lParam == m_hWndConnect)
				PostMessage(m_hWndConnect, WM_KEYDOWN, VK_RETURN, 0);
			if ((HWND)lParam == m_hWndOK)
				PostMessage(m_hWndInputBox, WM_KEYDOWN, VK_RETURN, 0);
			if ((HWND)lParam == m_hWndCancel)
				PostMessage(m_hWndInputBox, WM_KEYDOWN, VK_ESCAPE, 0);
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void setTextAlignment(HWND hwnd, int intTextAlignment)
{
	LONG_PTR s;
	LONG_PTR textalignment = GetWindowLongPtr(hwnd, GWL_STYLE);
	if (textalignment != intTextAlignment)
	{
		//delete the last text alignment
		if (intTextAlignment == 0)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s & ~(SS_LEFT);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}
		else if (intTextAlignment == 1)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s & ~(SS_CENTER);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}
		else if (intTextAlignment == 2)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s & ~(SS_RIGHT);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}

		textalignment = intTextAlignment;

		//put the new text alignment
		if (textalignment == 0)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s | (SS_LEFT);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}
		else if (textalignment == 1)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s | (SS_CENTER);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}
		else if (textalignment == 2)
		{
			s = GetWindowLongPtr(hwnd, GWL_STYLE);
			s = s | (SS_RIGHT);
			SetWindowLongPtr(hwnd, GWL_STYLE, (LONG_PTR)s);
		}
		SetWindowPos(hwnd, 0, 0, 0, 0, 0,
			SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_DRAWFRAME);
	}
}
void ReportError(const char* CallingFunction)
{
	DWORD error = GetLastError();
	LPVOID lpMsgBuf;
	DWORD bufLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);
	wprintf(L"%S: Error '%s'\n", CallingFunction, (wchar_t*)lpMsgBuf);
}


/********************************************************************************************************
*
PyObject* py_args_tuple;
Py_Initialize();
// USB address recovery
CString cs_USB_address = "";
proto.OnConnect(&cs_USB_address);
std::cout << "OnConnect" << " USB_addr=" << cs_USB_address << endl;


//setup args for my_function
string s_USB_address((LPCTSTR)cs_USB_address);
char* paramval = new char[s_USB_address.length() + 1];
strcpy_s (paramval, s_USB_address.length()+1 , s_USB_address.c_str());

PyObject* USB_name = PyUnicode_FromString(paramval);
py_args_tuple = PyTuple_New(1);    // 1 argument
PyTuple_SetItem(py_args_tuple, 0, USB_name);

// call my_function in my_module
PyObject* my_module = PyImport_ImportModule("python_modules.my_module");
cout << "my_module" << my_module << endl;
//PyErr_Print();
PyObject* my_function = PyObject_GetAttrString(my_module, "my_function");
PyObject* my_result = PyObject_CallObject(my_function, NULL);

Py_Finalize();
*/
