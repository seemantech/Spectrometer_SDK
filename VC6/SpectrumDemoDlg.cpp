// SpectrumDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpectrumDemo.h"
#include "SpectrumDemoDlg.h"

#include "math.h"
#include "Spectrometer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDemoDlg dialog

CSpectrumDemoDlg::CSpectrumDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpectrumDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrumDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bConnect = FALSE;
	m_bRunning = FALSE;

	SpectrometerInit(&g_tSP);
}

void CSpectrumDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpectrumDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSpectrumDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_CHECK_RUN, OnCheckRun)
	ON_BN_CLICKED(IDC_BUTTON_UNZOOM, OnButtonUnzoom)
	//}}AFX_MSG_MAP
	ON_WM_SERIAL(OnSerialMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumDemoDlg message handlers

BOOL CSpectrumDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	SetDlgItemText(IDC_EDIT_EXP_TIME,"60");
	SetDlgItemText(IDC_EDIT_BOXCAR,"1");

	CheckDlgButton(IDC_CHECK_RUN,TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpectrumDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpectrumDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpectrumDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CSpectrumDemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_Graph.Create(this);
	m_Graph.ShowWindow(SW_SHOW);
	return 0;
}

HBRUSH CSpectrumDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_IS_CONNECT: 
		pDC->SetTextColor(m_bConnect?RGB(0,0,255):RGB(255,0,0));
		break;
	default:break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSpectrumDemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CSpectrumDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rcClient,rcGraph;
	GetClientRect(&rcClient);
	rcGraph = rcClient;
	rcGraph.DeflateRect(0,100,0,0);
	m_Graph.MoveWindow(rcGraph);
}

//打开光谱仪设备
void CSpectrumDemoDlg::OnButtonConnect() 
{
	//如果打开，那么先关闭
	CString strComPort;
	GetDlgItemText(IDC_COMBO1,strComPort);

//	MessageBox(strComPort);

	if( m_serial.IsOpen()) m_serial.Close();

	m_serial.Open(strComPort,this);
	m_serial.Setup(CSerial::EBaud115200);
	
	if( m_serial.IsOpen()) 
	{
		SetDlgItemText(IDC_STATIC_IS_CONNECT,"connected");
		
		//初始化波长和强度数据
		m_Graph.m_dWavelength.SetSize(PIXELS); 
		m_Graph.m_dIntensity.SetSize(PIXELS);

		ReadPixelNumReady(&g_tSP);
		m_serial.Write(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend);
	
	}
	else
	{
		SetDlgItemText(IDC_STATIC_IS_CONNECT,"unconnect");
		
	}	
}

void CSpectrumDemoDlg::OnTimer(UINT nIDEvent) 
{
	m_bRunning = IsDlgButtonChecked(IDC_CHECK_RUN);
	if( m_bRunning )
	{
		CString strExpTime;
		GetDlgItemText(IDC_EDIT_EXP_TIME,strExpTime);
		//发送数据命令

		if( m_serial.IsOpen())
		{
			g_tSP.fExposureTimeMS = (float)atof(strExpTime);
			ReadIntensityReady(&g_tSP);
			//ReadIntensitySectionReady(&g_tSP,200,400);
			m_serial.Write(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend);
		}

		KillTimer(1);
	}
	
	CDialog::OnTimer(nIDEvent);
}



void CSpectrumDemoDlg::OnCheckRun() 
{
	// TODO: Add your control notification handler code here

}

void CSpectrumDemoDlg::OnButtonUnzoom() 
{
	// TODO: Add your control notification handler code here
	m_Graph.SendMessage(WM_COMMAND,WM_UNZOOM);
}


unsigned char g_cBuffer[PIXELS * 8];

LRESULT CSpectrumDemoDlg::OnSerialMsg (WPARAM wParam, LPARAM /*lParam*/)
{
	CSerial::EEvent eEvent = CSerial::EEvent(LOWORD(wParam));
	if (!(eEvent & CSerial::EEventRecv)) return 0;
	
	//收到数据就马上返回一个信号给电路板，让电路板知道上位机还在工作
	//WriteCOMM(0);
	
	//读取串口进来的数据
	T_SPECTROMETER_COMMAND *tBuffer = &(g_tSP.cmd);
	if( tBuffer->nBytesReaded < tBuffer->nBytesToReceive && tBuffer->nBytesToReceive > 0)
	{
		DWORD cbBytes;
		m_serial.Read(tBuffer->nBuffer + tBuffer->nBytesReaded,tBuffer->nBytesToReceive - tBuffer->nBytesReaded,&cbBytes);
		if (cbBytes <= 0) return 0;

		tBuffer->nBytesReaded += cbBytes;

		//数据读取完成
		if( tBuffer->nBytesReaded >= tBuffer->nBytesToReceive)
		{
			
			if( tBuffer->nCMDMode == READ_MODE_WAVELENGTH )  //if( m_nBytesToReceive == 64)
			{
				ReadWavelengthParse(&g_tSP);
				for( int i = 0 ; i < g_tSP.nPixelNum ; i++)
				{
					m_Graph.m_dWavelength.SetAt(i,g_tSP.fWavelength[i]);
				}
				//读完波长读取强度
				SetTimer(1,100,NULL);
			}
			else if( tBuffer->nCMDMode == READ_MODE_INTENSITY )  //if( m_nBytesToReceive == DATA_BYTES)
			{
				ReadIntensityParse(&g_tSP);

				for( int i = 0 ; i < g_tSP.nPixelNum ; i++)
				{
					m_Graph.m_dIntensity.SetAt(i,g_tSP.nIntensity[i]);
				}
				m_Graph.SetContentChanged(TRUE);
				//m_Graph.Boxcar(1);
				
				//Invalidate();
				CString strStatus;
				CTime time = CTime::GetCurrentTime();
				strStatus.Format("Read OK:  %s",time.Format("%y-%m-%d %H:%M:%S"));
				SetDlgItemText(IDC_STATUS,strStatus);

				SetTimer(1,100,NULL);
			}
			else if( tBuffer->nCMDMode == READ_MODE_INTENSITY_SECTION ) 
			{
				ReadIntensitySectionParse(&g_tSP);
				
				for( int i = 0 ; i < g_tSP.nPixelNum ; i++)
				{
					m_Graph.m_dIntensity.SetAt(i,g_tSP.nIntensity[i]);
				}
				m_Graph.SetContentChanged(TRUE);
				//m_Graph.Boxcar(1);
				
				//Invalidate();
				CString strStatus;
				CTime time = CTime::GetCurrentTime();
				strStatus.Format("Read OK:  %s",time.Format("%y-%m-%d %H:%M:%S"));
				SetDlgItemText(IDC_STATUS,strStatus);
				
				SetTimer(1,100,NULL);
			}
			else if( tBuffer->nCMDMode == READ_MODE_PIXEL_NUM )  
			{
				ReadPixelNumParse(&g_tSP);
				
				m_Graph.m_dWavelength.SetSize(g_tSP.nPixelNum); 
				m_Graph.m_dIntensity.SetSize(g_tSP.nPixelNum);

				//读完像素个数读取波长
				ReadWavelengthReady(&g_tSP);
				m_serial.Write(g_tSP.cmd.nCommand,g_tSP.cmd.nBytesToSend);
				//SetTimer(1,100,NULL);
			}
		}
	}
	else
	{
		DWORD dwBytesReaded;
		m_serial.Read(g_cBuffer,100,&dwBytesReaded);
		if (dwBytesReaded <= 0) return 0;
	}
	

	return 0;
}
