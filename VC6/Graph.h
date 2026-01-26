#if !defined(AFX_GRAPH_H__84442A8C_B6A5_46EE_AF06_5C65DD440DFC__INCLUDED_)
#define AFX_GRAPH_H__84442A8C_B6A5_46EE_AF06_5C65DD440DFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Graph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraph window
#define COLOR_WHITE			(RGB(255,255,255))
#define COLOR_BLACK			(RGB(0,0,0))
#define COLOR_YELLOW		(RGB(255,255,0))
#define COLOR_DARK_YELLOW   (RGB(255,255,134))
#define COLOR_PURPLE		(RGB(255,0,255))
#ifndef COLOR_BLUE
#define COLOR_BLUE			(RGB(0,0,255))
#endif
#define COLOR_RED			(RGB(255,0,0))
#define COLOR_GREEN			(RGB(0,255,0))
#define COLOR_CYAN			(RGB(0,255,255))
#define COLOR_BROWN			(RGB(255,153,57))
#define COLOR_DARK_RED		(RGB(255,133,134))
#define COLOR_GRAY          (RGB(220,220,220))
#define COLOR_BK			(RGB(255,255,255))
#define COLOR_BK_INNER		(RGB(23,23,23))

//Message Define
#define WM_PRE_ZOOM			(WM_USER + 1)
#define WM_NEXT_ZOOM		(WM_USER + 2)
#define WM_UNZOOM			(WM_USER + 3)
#define WM_RESTORE			(WM_USER + 3)
#define WM_PROPERITY		(WM_USER + 4)
#define WM_SAVE_BITMAP		(WM_USER + 5)
#define WM_CLIPBOARD		(WM_USER + 6)
#define WM_PRINT_GRAPH		(WM_USER + 7)
#define WM_VISIBLE_TOOLTIPS	(WM_USER + 8)
#define WM_REMOVE_TOOLTIPS	(WM_USER + 9)
#define WM_MOUSE_CROSS		(WM_USER + 10)
#define WM_CREATE_TABLE		(WM_USER + 11)
#define WM_CLEAR_TABLES		(WM_USER + 12)
#define WM_MOUSE_TOOLTIP	(WM_USER + 13)
#define WM_SET_COORD_Y		(WM_USER + 14)
#define WM_VISIBLE_TABLES	(WM_USER + 15)
#define WM_VISIBLE_TITLE	(WM_USER + 16)
#define WM_VISIBLE_LEGEND	(WM_USER + 17)
#define WM_VISIBLE_NET_X	(WM_USER + 18)
#define WM_VISIBLE_NET_Y	(WM_USER + 19)
#define WM_ADD_TOOLTIP		(WM_USER + 20)

#define WM_SPECTRA_OPEN		(WM_USER + 21)
#define WM_SPECTRA_SAVE		(WM_USER + 22)
#define WM_SPECTRA_EXCEL	(WM_USER + 23)
#define WM_SPECTRA_DELETE	(WM_USER + 24)
#define WM_SPECTRA_VIEW		(WM_USER + 25)
#define WM_SPECTRA_WORD		(WM_USER + 26)
#define WM_SET_DEFAULT_COORD (WM_USER + 27)
#define WM_ENABLE_MOVING_LINE (WM_USER + 28)

#define WM_UNZOOM_X			(WM_USER + 29)
#define WM_UNZOOM_Y			(WM_USER + 30)
#define WM_SET_COORD_X		(WM_USER + 31)

#define WM_EQUAL_GRAPH_COORDINATE (WM_USER + 1001)


class CGraph : public CWnd
{
// Construction
public:
	CGraph();

protected: //Background
	COLORREF m_clrBk;
	COLORREF m_clrBkInner;
public:
	COLORREF GetBkColor(){return m_clrBk;}
	COLORREF GetBkInnerColor(){return m_clrBkInner;}
	void	 SetBkColor(COLORREF clrBk){ m_clrBk = clrBk;}
	void	 SetBkInnerColor(COLORREF clrBkInner){ m_clrBkInner = clrBkInner;}


protected: //Title
	BOOL     m_bVisibleTitle;
	CString  m_strTitle;
	COLORREF m_clrTitle;
	LOGFONT	 m_fontTitle;
public:
	BOOL	IsVisibleTitle(){return m_bVisibleTitle;}
	void	SetVisibleTitle(BOOL bVisible){m_bVisibleTitle = bVisible;}
	void	SetTitleText(LPCTSTR strTitle);
	CString GetTitleText(){return m_strTitle;}
	void	SetColorTitle(COLORREF clrTitle){ m_clrTitle = clrTitle;}
	COLORREF GetTitleColor(){return m_clrTitle;}
	LOGFONT GetTitleFont(){ return m_fontTitle;}
	void	SetTitleFont(LOGFONT font){ m_fontTitle = font;}

//画坐标 网格 和 Labels
protected:
	BOOL	 m_bDivInner;
protected: 
	COLORREF m_clrCoord;	//坐标颜色
	UINT	 m_nCoordWidth;
protected: 
	BOOL     m_bVisibleNetX;			   
	BOOL	 m_bVisibleNetY;
	COLORREF m_clrNet;
protected: 
	UINT     m_nDivX;
	UINT     m_nDivY;
protected: 
	BOOL     m_bVisibleLabelX;
	BOOL     m_bVisibleLabelY;	
	COLORREF m_clrLabelX;
	COLORREF m_clrLabelY;
	CString  m_strLabelX;
	CString  m_strLabelY;
	LOGFONT	 m_fontLabelX;
	LOGFONT	 m_fontLabelY;
public:
	void	SetLabelY(LPCTSTR strLabelY);
	void	SetLabelX(LPCTSTR strLabelX);
	CString GetLabelX(){return m_strLabelX;}
	CString GetLabelY(){return m_strLabelY;}
	void	SetVisibleNetY(BOOL bEnable = TRUE);
	void	SetVisibleNetX(BOOL bEnable = TRUE);
	BOOL	IsVisibleNetX(){return m_bVisibleNetX;}
	BOOL	IsVisibleNetY(){return m_bVisibleNetY;}
	void	SetDivY(int iDivY);
	void	SetDivX(int iDivX);
	int		GetDivX(){return m_nDivX;}
	int		GetDivY(){return m_nDivY;}
	LOGFONT GetFontLabelX(){ return m_fontLabelX;}
	LOGFONT GetFontLabelY(){ return m_fontLabelY;}
	void	SetFontLabelX(LOGFONT font){ m_fontLabelX = font;}
	void	SetFontLabelY(LOGFONT font){ m_fontLabelY = font;}
	COLORREF GetColorLabelX(){return m_clrLabelX;}
	COLORREF GetColorLabelY(){return m_clrLabelY;}
	void	SetColorLabelX(COLORREF clrLabel){m_clrLabelX = clrLabel;}
	void	SetColorLabelY(COLORREF clrLabel){m_clrLabelY = clrLabel;}
	BOOL	IsVisibleLabelX(){return m_bVisibleLabelX;}
	BOOL	IsVisibleLabelY(){return m_bVisibleLabelY;}
	void	SetVisibleLabelX(BOOL bVisible){ m_bVisibleLabelX = bVisible;}
	void	SetVisibleLabelY(BOOL bVisible){ m_bVisibleLabelY = bVisible;}
	COLORREF GetColorCoord(){return m_clrCoord;}
	void	SetColorCoord(COLORREF clrCoord){ m_clrCoord = clrCoord;}
	UINT	GetCoordWidth(){return m_nCoordWidth;}
	void	SetCoordWidth(UINT nWidth){ m_nCoordWidth = nWidth;}


//画线框大小 LineRect
protected:
	CRect	 m_rcDraw;
	int		 m_nDeflateLeft;
	int		 m_nDeflateRight;
	int		 m_nDeflateTop;
	int		 m_nDeflateBottom;

//坐标
protected:
	typedef struct coordinate
	{
		double dMinX;
		double dMaxX;
		double dMinY;
		double dMaxY;
	}COORDINATE;
	COORDINATE m_coordRestore;
	CArray<COORDINATE,COORDINATE> m_aCoord;
	int		 m_nPos;
protected: 
	double   m_dMinX;
	double   m_dMaxX;
	double   m_dMinY;
	double   m_dMaxY;
	double   m_dZoomRate;
	double   m_dMoveRate;
public:
	double	GetMaxY();
	double	GetMinY();
	double	GetMaxX();
	double	GetMinX();
public:
	void	SetRangeY(double dMinY,double dMaxY);
	void	SetRangeX(double dMinX,double dMaxX);
	void	SetRange(double dMinX,double dMaxX,double dMinY,double dMaxY);
virtual	void	SetRangeRestore (double dMinX,double dMaxX,double dMinY, double dMaxY,BOOL bApply = FALSE);
virtual	void	SetRangeRestoreY(double dMinY, double dMaxY,BOOL bApply = FALSE);
virtual	void	SetRangeRestoreX(double dMinX,double dMaxX,BOOL bApply = FALSE);
void	IncXRange(float fMaxX);
protected:
	void	ZoomY(double dZoom);
	void	ZoomX(double dZoom);
	void	MoveDown(double dRate);
	void	MoveUp(double dRate);
	void	MoveRight(double dRate);
	void	MoveLeft(double dRate);
	void	RecordCoordinate(); // 保存xy坐标最大小值纪录
protected:
	virtual void Serialize(CArchive& ar);
//画线数据
protected: 
// 	float*		m_pfX;
// 	float*		m_pfY;
// 	int			m_nPointNums;
	
protected:
	COLORREF	m_nLineColor;
	UINT	    m_nLineWidth;
	CPen		m_pen; 
	CRgn		m_rgn; 


//鼠标
protected: 
	CPoint  m_ptStart;
	CPoint	m_ptEnd;
protected:
	BOOL  m_bClipRect;
	BOOL  m_bRButtonDown;
	BOOL  m_bRButtonMove;
protected:
	BOOL m_bMouseCross;
	BOOL m_bMouseTooltip;

public:

	BOOL IsVisibleMouseCross(){return m_bMouseCross;}
	void SetVisibleMouseCross(BOOL bEnable = TRUE)  { m_bMouseCross   = bEnable;}

	
	BOOL IsVisibleMouseTooltip(){return m_bMouseTooltip;}
	void SetVisibleMouseTooltip(BOOL bEnable = TRUE){ m_bMouseTooltip = bEnable;}

	

//指示条
typedef struct{
	BOOL	bActive;
	BOOL	bVisible;
	double	dPosX;
	double	dPosY;
}ToolTip;
protected:
	BOOL	m_bMovingTooltip;
	int		m_nIndexMovingTooltip;
	BOOL	m_bVisibleTooltips; 
	CArray<ToolTip,ToolTip> m_ToolTips; 
	COLORREF m_clrTooltip;
	CString m_strTooltipFormat;
	LOGFONT m_fontTooltip;
protected:
	void SetActiveTooltip(int nIndexTooltip);
	int	 GetActiveTooltip();

public:
	LOGFONT GetFontTooltip(){return m_fontTooltip;}
	void	SetFontTooltip(LOGFONT fontTooltip){ m_fontTooltip = fontTooltip;}

	CString GetTooptipFormat(){return m_strTooltipFormat;}
	void    SetTooltipFormat(CString strTooltipFormat){ m_strTooltipFormat = strTooltipFormat;}
public:
	BOOL IsVisibleTooltip(){return m_bVisibleTooltips;}
	void SetVisibleTooltip(BOOL bEnable = TRUE){ m_bVisibleTooltips = bEnable;}
	COLORREF GetColorTooltip(){return m_clrTooltip;}
	void SetColorTooltip(COLORREF clrTooltip){ m_clrTooltip = clrTooltip;}

// 文本框       Text Tables
	typedef struct{
		BOOL	bBkTransparent;
		double	dPosX;
		double	dPosY;
		LOGFONT  font;
		COLORREF clrText;
		CString strCaption;
		CRect rcRegion;
	}TextTable;
	BOOL m_bSelectTextTable;
	int	 m_nIndexSelectTextTable;
	CArray<TextTable,TextTable> m_TextTables;
	BOOL m_bVisibleTextTable;
	BOOL m_bCreatingTable;
public:
	BOOL IsVisibleTextTable(){return m_bVisibleTextTable;}
	void SetTextTableVisible(BOOL bVisible){ m_bVisibleTextTable = bVisible;}
	int  GetSizeTextTables(){return m_TextTables.GetSize();}
protected:
	void CalcRectTextTable(CRect &rcOriginRect,float fRotateAngle,CDC *pDC);
//Legend
protected:
	POINT m_ptLengend;
	BOOL  m_bVisibleLegend;
	LOGFONT m_fontLegend;
	BOOL m_bSelectLegend;
	CRect m_rcLegend;
public:
	BOOL IsVisibleLegend(){return m_bVisibleLegend;}
	void SetVisibleLegend(BOOL bVisible = TRUE){ m_bVisibleLegend = bVisible;}
	LOGFONT GetFontLegend(){return m_fontLegend;}
	void	SetFontLegend(LOGFONT fontLegend){ m_fontLegend = fontLegend;}

//缓存位图提高速度
protected:
	HBITMAP	m_hBitmap;
	CDC		m_dcBuffer;
	BOOL	m_bContentChanged;

public:
	virtual	BOOL Draw(CDC *pDC,const CRect rcDraw);
protected:
	virtual void DrawBackground(CDC *pDC);
	virtual void DrawCoord(CDC *pDC);
//	virtual void DrawNet(CDC *pDC);
	virtual void DrawTitle(CDC *pDC);
	virtual	void DrawLabelY(CDC *pDC);
	virtual	void DrawLabelX(CDC *pDC);
	virtual void DrawLines(CDC *pDC);
	virtual void DrawLegend(CDC *pDC);
	virtual void DrawTooltips(CDC *pDC);
	virtual void DrawTextTable(CDC *pDC);
	virtual void DrawMouseTooltips(CDC *pDC);
	virtual void DrawMouseClipRect(CDC *pDC);

public:
	virtual void OpenSettingsReg(CString strSection);
	virtual void SaveSettingsReg(CString strSection);
	BOOL SaveSettings(CString strSettingsFileName);
	BOOL LoadSettings(CString strSettingsFileName);
public:
	CRect GetLineRect();
	CRect GetTitleRect();
	CRect GetLabelXRect();
	CRect GetLabelYRect();

public:
	virtual BOOL Create(CWnd *pParentWnd,const CRect &rect=CRect(0,0,200,200), UINT nID  = 1);

protected:
	long	ValueToPointX(double dValueX);// inline
	long	ValueToPointY(double dValueY);// inline	
	double	PointToValueX(long nPosX);//inline	
	double	PointToValueY(long nPosY);//inline

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraph)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsNextZoom();
	BOOL IsPreZoom();
	virtual ~CGraph();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraph)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCreateTable(WPARAM,LPARAM);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	afx_msg void SaveAsBitmap();
	afx_msg void CopyToClipboard();
	afx_msg void PrintGraph();
	afx_msg void OnUnZoom();
	afx_msg void OnPreZoom();
	afx_msg void OnNextZoom();
	afx_msg void OnProperty();
	afx_msg void OnClearTooltips();
	afx_msg void OnClearTextTables(WPARAM,LPARAM);
	afx_msg void OnEnableMovingLine(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	void CalcRects(const CRect rcDrawRect);
private:
	void   WriteBmp(CBitmap   *PBitmap,CString strFileName); 
	BOOL   WriteDIB( LPCTSTR szFile, HANDLE hDIB);
	HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );
public:
	BOOL	SaveBMPFileTopToBottom(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight);
	BOOL	SaveBMPFileBottomToTop(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight);

public:
	void SetLine(float *pfX,float *pfY,int nPointNums);
public:
	void SetContentChanged(BOOL bRedraw = FALSE);
protected:
	BOOL PopMenu(CPoint point);
	BOOL PopMenuTooltips(CPoint point);
	BOOL PopMenuTextTable(CPoint point);
	BOOL PopMenuLegend(CPoint point);
public:
	double GetRestoreMinX(){return m_coordRestore.dMinX;}
	double GetRestoreMaxX(){return m_coordRestore.dMaxX;}
	double GetRestoreMinY(){return m_coordRestore.dMinY;}
	double GetRestoreMaxY(){return m_coordRestore.dMaxY;}
protected:
	BOOL m_bEnableMovingLine;
	BOOL m_bMovingLine;
public:
	BOOL IsEnableMovingLine(){return m_bEnableMovingLine;}

protected:
	BOOL m_bTransparentTooltips;
public:
	void SetTransparentTooltips(BOOL bTrans = TRUE){ m_bTransparentTooltips = bTrans;}
	BOOL IsTransparentTooltips() {return m_bTransparentTooltips;}
	BOOL SavePrintBMPFile(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight,BOOL bPrint = FALSE);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPH_H__84442A8C_B6A5_46EE_AF06_5C65DD440DFC__INCLUDED_)
