// Microsoft Visual C++ generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#include "winres.h"

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
// Russian (Russia) resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_RUS)
LANGUAGE LANG_RUSSIAN, SUBLANG_DEFAULT

#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE
BEGIN
"resource.h\0"
END

2 TEXTINCLUDE
BEGIN
"#include ""winres.h""\r\n"
"\0"
END

3 TEXTINCLUDE
BEGIN
"\r\n"
"\0"
END

#endif    // APSTUDIO_INVOKED

#endif    // Russian (Russia) resources
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// English (United States) resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_ENU)
LANGUAGE LANG_ENGLISH, SUBLANG_ENGLISH_US

/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_DIALOG1 DIALOGEX 0, 0, 309, 176
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | DS_CENTER | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Dialog"
FONT 8, "MS Shell Dlg", 400, 0, 0x1
BEGIN
DEFPUSHBUTTON   "OK", IDOK, 198, 155, 50, 14
PUSHBUTTON      "E&xit", IDCANCEL, 252, 155, 50, 14
LTEXT           "IP-�����:", IDC_STATIC_IP_ADDRESS, 7, 7, 182, 8
LTEXT           "�����:", IDC_STATIC_IP_MASK, 7, 42, 24, 8
LTEXT           "�������:", IDC_STATIC_IP_PREFIX, 117, 42, 33, 8
CONTROL         "", IDC_IPADDRESS, "SysIPAddress32", WS_TABSTOP, 7, 17, 100, 15
CONTROL         "", IDC_IPMASK, "SysIPAddress32", WS_TABSTOP, 7, 54, 100, 15
EDITTEXT        IDC_EDIT_PREFIX, 116, 54, 40, 14, ES_RIGHT | ES_AUTOHSCROLL | ES_NUMBER, WS_EX_RIGHT
CONTROL         "", IDC_SPIN_PREFIX, "msctls_updown32", UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, 145, 54, 10, 14
LTEXT           "Static", IDC_STATIC_INFO, 7, 77, 295, 76
END


/////////////////////////////////////////////////////////////////////////////
//
// DESIGNINFO
//

#ifdef APSTUDIO_INVOKED
GUIDELINES DESIGNINFO
BEGIN
IDD_DIALOG1, DIALOG
BEGIN
LEFTMARGIN, 7
RIGHTMARGIN, 302
TOPMARGIN, 7
BOTTOMMARGIN, 169
END
END
#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// AFX_DIALOG_LAYOUT
//

IDD_DIALOG1 AFX_DIALOG_LAYOUT
BEGIN
0
END

#endif    // English (United States) resources
/////////////////////////////////////////////////////////////////////////////



#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//


/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

