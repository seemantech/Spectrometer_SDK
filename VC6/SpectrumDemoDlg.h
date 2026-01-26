// SpectrumDemoDlg.h : header file
//

#if !defined(AFX_SPECTRUMDEMODLG_H__C8E5C233_9E1E_4AC7_8186_023D874D803C__INCLUDED_)
#define AFX_SPECTRUMDEMODLG_H__C8E5C233_9E1E_4AC7_8186_023D874D803C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpectraGraph.h"
#include "serialMfc.h"
#define MAX_PACKET_SIZE_READ 4096
#define MAX_PACKET_SIZE_WRITE 512

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDemoDlg dialog

class CSpectrumDemoDlg : public CDialog
{
// Construction
public:
	CSpectrumDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpectrumDemoDlg)
	enum { IDD = IDD_SPECTRUMDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpectrumDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonConnect();
	afx_msg void OnCheckRun();
	afx_msg void OnButtonUnzoom();
	//}}AFX_MSG
	afx_msg LRESULT OnSerialMsg(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
protected:
	CSpectraGraph m_Graph;
protected:
	double m_dBuffer[8000];
	BOOL m_bConnect;
	BOOL ReadCCD();
	void Close();

protected:
	BOOL m_bRunning;
	unsigned char m_cCommand[100];
protected:
	CSerialMFC m_serial;
	int	 m_nBytesToReceive;
	int  m_nBytesReaded;

//#define PIXELS 3694
//#define PIXELS 2088
//#define DATA_BYTES (PIXELS * 2) //总共接收的数据字节数
//#define COMMAND_READ 			0x10
//#define COMMAND_INFO_READ		0x51
//#define FLASH_PAGE_COEFFICENT		30//是10进制的30

};

typedef union{
	unsigned char cData[4];
	float fData;
	unsigned int nData;
}U_4B;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMDEMODLG_H__C8E5C233_9E1E_4AC7_8186_023D874D803C__INCLUDED_)
