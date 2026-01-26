// SpectrumDemo.h : main header file for the SPECTRUMDEMO application
//

#if !defined(AFX_SPECTRUMDEMO_H__1ADA896E_00DD_4D6D_A5DF_7192238FEAA5__INCLUDED_)
#define AFX_SPECTRUMDEMO_H__1ADA896E_00DD_4D6D_A5DF_7192238FEAA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDemoApp:
// See SpectrumDemo.cpp for the implementation of this class
//

class CSpectrumDemoApp : public CWinApp
{
public:
	CSpectrumDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpectrumDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMDEMO_H__1ADA896E_00DD_4D6D_A5DF_7192238FEAA5__INCLUDED_)
