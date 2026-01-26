// Graph.cpp : implementation file
//

#include "stdafx.h"

#include "Graph.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CLIP_PIXELS 5
/////////////////////////////////////////////////////////////////////////////
// CGraph

BEGIN_MESSAGE_MAP(CGraph, CWnd)
	//{{AFX_MSG_MAP(CGraph)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(WM_SAVE_BITMAP,SaveAsBitmap)
	ON_COMMAND(WM_CLIPBOARD,CopyToClipboard)
	ON_COMMAND(WM_PRINT_GRAPH,PrintGraph)
	ON_COMMAND(WM_UNZOOM,OnUnZoom)
	ON_COMMAND(WM_PRE_ZOOM,OnPreZoom)
	ON_COMMAND(WM_NEXT_ZOOM,OnNextZoom)
	ON_COMMAND(WM_PROPERITY,OnProperty)
	ON_COMMAND(WM_REMOVE_TOOLTIPS,OnClearTooltips)
	ON_MESSAGE(WM_CREATE_TABLE,OnCreateTable)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_CLEAR_TABLES,OnClearTextTables)
	ON_MESSAGE(WM_ENABLE_MOVING_LINE,OnEnableMovingLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGraph::CGraph()
{
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_fontLabelX),&m_fontLabelX);
	m_fontLabelX.lfHeight = -15; 
	m_fontLabelX.lfWeight = FW_NORMAL; 
	m_fontLabelX.lfClipPrecision = CLIP_LH_ANGLES; 
	m_fontLabelX.lfEscapement = 0; 
	m_fontLabelX.lfHeight = 14;
	m_fontLabelX.lfWeight = 300;
	strcpy(m_fontLabelX.lfFaceName,_T("Times New Roman"));


	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_fontLabelY),&m_fontLabelY);
	m_fontLabelY.lfHeight = -15; 
	m_fontLabelY.lfWeight = FW_NORMAL; 
	m_fontLabelY.lfClipPrecision = CLIP_LH_ANGLES; 
	m_fontLabelY.lfEscapement = 900;  
	m_fontLabelY.lfHeight = 14;
	m_fontLabelY.lfWeight = 300;
	strcpy(m_fontLabelY.lfFaceName,_T("Times New Roman"));


	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_fontTitle),&m_fontTitle);
	m_fontTitle.lfHeight = -15; 
	m_fontTitle.lfWeight = FW_NORMAL; 
	m_fontTitle.lfClipPrecision = CLIP_LH_ANGLES; 
	m_fontTitle.lfEscapement = 0;  

	memset(&m_fontTooltip,0,sizeof(LOGFONT));
	m_fontTooltip.lfHeight = 18;
	m_fontTooltip.lfWeight = 300;
	strcpy(m_fontTooltip.lfFaceName,_T("Times New Roman"));

	memset(&m_fontLegend,0,sizeof(LOGFONT));
	m_fontLegend.lfHeight = -14;
	m_fontLegend.lfWeight = 300;
	strcpy(m_fontLegend.lfFaceName,_T("Times New Roman"));
	
	//Background
//	m_clrBk	    = (RGB(255,255,255));
//	m_clrBkInner= (RGB(255,255,255));
 	m_clrBk	    = (RGB(253,253,253));
 	m_clrBkInner= (RGB(251,251,251));

	//Net
	SetVisibleNetX(TRUE);
	SetVisibleNetY(TRUE);
	m_clrNet    = COLOR_GRAY;
	
	//Division X Y
	SetDivX(5);
	SetDivY(5);
	m_bDivInner = TRUE;
	
	//Title
	m_bVisibleTitle   = TRUE;
	m_clrTitle  = COLOR_BLACK;
	SetTitleText(_T("Graph"));

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(m_fontTitle),&m_fontTitle);
	m_fontTitle.lfHeight = -18;
	m_fontTitle.lfWeight = FW_NORMAL; 
	m_fontTitle.lfClipPrecision = CLIP_LH_ANGLES; 
	m_fontTitle.lfEscapement = 0; 

	//Label X Y
	m_bVisibleLabelX  = TRUE;
	m_bVisibleLabelY  = TRUE;
	m_clrLabelX = COLOR_BLACK;
	m_clrLabelY = COLOR_BLACK;
	SetLabelX(_T("时间(min)"));
	SetLabelY(_T("Y 坐标轴"));
	
	//Coordinate
	m_clrCoord  = COLOR_BLUE;		
	m_nCoordWidth  = 1;

	//Zoom Range X Y
	SetRangeRestore(0,1000,0,1000,TRUE);

	//鼠标的点击
	m_bClipRect = FALSE;
	/////////////
	m_nPos   = 0;
	RecordCoordinate();

	m_nLineColor   = COLOR_RED;
	m_nLineWidth   = 1;
	m_bRButtonDown = FALSE;
	m_bRButtonMove = FALSE;
	m_bEnableMovingLine = FALSE;
	m_bMovingLine  = FALSE;

// 	m_pfX = NULL;
// 	m_pfY = NULL;
// 	m_nPointNums = 0;

	m_clrTooltip = RGB(176,224,230);//火药蓝 #B0E0E6 
	m_clrTooltip = RGB(0,0,180);//火药蓝 #B0E0E6 
	
	m_bVisibleTextTable = TRUE;
	m_bCreatingTable = FALSE;

	m_bVisibleLegend = TRUE;
	m_bMouseCross = FALSE;
	m_bMouseTooltip = TRUE;
	m_bVisibleTooltips = TRUE;
	m_bVisibleNetX = TRUE;
	m_bVisibleNetY = TRUE;

	m_bSelectTextTable = FALSE;
	m_nIndexSelectTextTable = -1;

	m_bSelectLegend = FALSE;
	m_bMouseTooltip = FALSE;
	m_bMovingTooltip= FALSE;
	m_nIndexMovingTooltip = -1;
}

CGraph::~CGraph()
{
	DeleteObject(m_hBitmap);
	m_dcBuffer.DeleteDC();
	m_pen.DeleteObject();
	m_rgn.DeleteObject();

}

/////////////////////////////////////////////////////////////////////////////
// CGraph message handlers

BOOL CGraph::Create(CWnd *pParentWnd,const CRect &rect, UINT nID)
{
	BOOL bCreate = CWnd::Create(AfxRegisterWndClass(
		CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, 
		//AfxGetApp()->LoadStandardCursor(IDC_CROSS), NULL, NULL),
		AfxGetApp()->LoadStandardCursor(IDC_ARROW), NULL, NULL),
		NULL,WS_CHILD |WS_VISIBLE ,rect,pParentWnd, nID);

	return bCreate;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Draw related
//

void CGraph::DrawBackground(CDC *pDC)
{
	if(pDC->IsPrinting()) return;

	pDC->FillSolidRect(&m_rcDraw,m_clrBk);
	CRect cLineRect = GetLineRect();
	pDC->FillSolidRect(&cLineRect,m_clrBkInner);
}

void CGraph::DrawCoord(CDC *pDC)
{
	CRect cLineRect = GetLineRect();
	int nOldMode    = pDC->SetBkMode(TRANSPARENT);
	CPen pen; pen.CreatePen(PS_SOLID ,m_nCoordWidth,m_clrCoord);

	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(cLineRect.left,cLineRect.top);
	pDC->LineTo(cLineRect.left,cLineRect.bottom);
	pDC->LineTo(cLineRect.right,cLineRect.bottom);

	pen.DeleteObject();
	pen.CreatePen(PS_SOLID ,1,m_clrCoord);
	pDC->SelectObject(&pen);

	pDC->LineTo(cLineRect.right,cLineRect.top);
	pDC->LineTo(cLineRect.left,cLineRect.top);

	pDC->SelectObject(pOldPen);	pen.DeleteObject();
	pDC->SetBkMode(nOldMode);
	
}

/*
void CGraph::DrawNet(CDC *pDC)
{
	CRect cLineRect = GetLineRect();
	int	   nOldMode = pDC->SetBkMode(TRANSPARENT);
	CPen pen; pen.CreatePen(PS_DOT ,1,m_clrNet);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);
	
	double dPerDivX = (double)cLineRect.Width() / (double)(m_nDivX);
	for( UINT i = 1 ; i < m_nDivX ; i++)
	{
		if(!m_bVisibleNetX) break;
		pDC->MoveTo((int)(cLineRect.left + dPerDivX * i),cLineRect.bottom );
		pDC->LineTo((int)(cLineRect.left + dPerDivX * i),cLineRect.top    );
	}

	float fPerDivY = (float)cLineRect.Height() / (float)(m_nDivY);
	for(     i = 1 ; i < m_nDivY ; i++)
	{
		if(!m_bVisibleNetY) break;
		pDC->MoveTo(cLineRect.left   ,(int)(cLineRect.bottom - fPerDivY * i));
		pDC->LineTo(cLineRect.right  ,(int)(cLineRect.bottom - fPerDivY * i));
	}

	pDC->SelectObject(pOldPen);	pen.DeleteObject();
	pDC->SetBkMode(nOldMode);
}
*/
/*
void CGraph::DrawLabelX(CDC *pDC)
{
	if(!m_bVisibleLabelX) return;

	CRect cLineRect = GetLineRect();

	int nOldMode    = pDC->SetBkMode(TRANSPARENT); 
	COLORREF clrOld = pDC->SetTextColor(m_clrLabelX); 

	CFont font; font.CreateFontIndirect(&m_fontLabelX);
	CFont *pOldFont = pDC->SelectObject(&font); 
	CPen pen; pen.CreatePen(PS_SOLID ,m_nCoordWidth,m_clrCoord);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);



	pDC->DrawText(m_strLabelX,GetLabelXRect(),DT_CENTER|DT_BOTTOM|DT_SINGLELINE);

	double dPerDivX = (double)cLineRect.Width() / (double)m_nDivX ;
	CString strDivX;
	for( UINT i = 0 ; i < m_nDivX + 1 ; i++)
	{
		double  dTimeSec  =PointToValueX((int)(cLineRect.left + dPerDivX*i));
		strDivX.Format("%.2f",dTimeSec);
		CSize sizeTextExt = pDC->GetTextExtent(strDivX);
		pDC->TextOut((int)(cLineRect.left + i * dPerDivX) - sizeTextExt.cx/2, 
					cLineRect.bottom + 7,
					strDivX);
		//DrawDivX
		pDC->MoveTo((int)(cLineRect.left + dPerDivX * i),cLineRect.bottom);
		pDC->LineTo((int)(cLineRect.left + dPerDivX * i),cLineRect.bottom+5); 
		if( i >= m_nDivX ) continue;
		for(int j = 0 ; j < 5 ; j++)//X小刻度 
		{
			pDC->MoveTo((int)(cLineRect.left + dPerDivX * i + dPerDivX*j/5),cLineRect.bottom);
			pDC->LineTo((int)(cLineRect.left + dPerDivX * i + dPerDivX*j/5),cLineRect.bottom + 3);
		}
	}

	pDC->SelectObject(pOldFont); 	font.DeleteObject(); 
	pDC->SetBkMode(nOldMode);   	pDC->SetTextColor(clrOld);
	pDC->SelectObject(pOldPen);	pen.DeleteObject();

}

void CGraph::DrawLabelY(CDC *pDC)
{
	if(!m_bVisibleLabelY) return;
	
	CRect cLineRect = GetLineRect();
	int nOldMode    = pDC->SetBkMode(TRANSPARENT); 
	COLORREF clrOld = pDC->SetTextColor(m_clrLabelY); 

	CFont font; 	font.CreateFontIndirect(&m_fontLabelY); 
	CFont *pOldFont = pDC->SelectObject(&font); 
	CPen pen; pen.CreatePen(PS_SOLID ,m_nCoordWidth,m_clrCoord);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);
	CString strLabelY(m_strLabelY);

	CSize sizeLabelY = pDC->GetTextExtent(m_strLabelY);
	pDC->TextOut(m_rcDraw.left ,cLineRect.top + cLineRect.Height() / 2 + sizeLabelY.cx /2,m_strLabelY);

	m_fontLabelY.lfEscapement = 0;
	font.DeleteObject();font.CreateFontIndirect(&m_fontLabelY);
	pDC->SelectObject(&font); 
	m_fontLabelY.lfEscapement = 900;
	
	double dPerDivY = (double)cLineRect.Height()/(double)m_nDivY;
	CString strDivY;
	for( UINT i = 0 ; i < m_nDivY + 1 ; i++)
	{
		strDivY.Format("%.1f",PointToValueY((long)(cLineRect.bottom - dPerDivY*i)));
		CSize sizeTextExt = pDC->GetTextExtent(strDivY);
		pDC->TextOut(cLineRect.left-sizeTextExt.cx - 7,
			(int)(cLineRect.bottom - i*dPerDivY - sizeTextExt.cy/2 ),strDivY);

		//DrawDivY Y大刻度
		pDC->MoveTo(cLineRect.left   ,(int)(cLineRect.bottom - dPerDivY * i));
		pDC->LineTo(cLineRect.left-5 ,(int)(cLineRect.bottom - dPerDivY * i));
		if( i >= m_nDivY ) continue;
		//Y小刻度 
		for(int j = 0 ; j < 5 ; j++)
		{
			pDC->MoveTo(cLineRect.left     ,(int)(cLineRect.bottom - dPerDivY * i - dPerDivY*j/5));
			pDC->LineTo(cLineRect.left - 3 ,(int)(cLineRect.bottom - dPerDivY * i - dPerDivY*j/5));
		}
	}
	
	pDC->SelectObject(pOldFont); 	font.DeleteObject(); 
	pDC->SetBkMode(nOldMode);	pDC->SetTextColor(clrOld);
	pDC->SelectObject(pOldPen);	pen.DeleteObject();
}
*/

void CGraph::DrawLabelX(CDC *pDC)
{
	if(!m_bVisibleLabelX) return;
	
	CRect cLineRect = GetLineRect();
	int nOldMode    = pDC->SetBkMode(TRANSPARENT); 
	COLORREF clrOld = pDC->SetTextColor(m_clrLabelX); 
	
	CFont font; 	font.CreateFontIndirect(&m_fontLabelX); 
	CFont *pOldFont = pDC->SelectObject(&font); 
	CPen pen; pen.CreatePen(PS_SOLID ,m_nCoordWidth,m_clrCoord);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);
	CString strLabelX(m_strLabelX);

	CSize sizeLabelX = pDC->GetTextExtent(m_strLabelX);
	pDC->DrawText(m_strLabelX,GetLabelXRect(),DT_CENTER|DT_BOTTOM|DT_SINGLELINE);

	CString strFormat  = "%.0f";
	double dIntervalX = (m_dMaxX - m_dMinX) / (double)m_nDivX;
	if( dIntervalX < 1) { strFormat = "%.2f";}
	if( dIntervalX > 1)  { dIntervalX = ((int)(dIntervalX/1)) * 1;}
	if( dIntervalX > 10)  { dIntervalX = ((int)(dIntervalX/10)) * 10;}
	if( dIntervalX > 100)  { dIntervalX = ((int)(dIntervalX/100)) * 100;}
	if( dIntervalX > 1000)  { dIntervalX = ((int)(dIntervalX/1000)) * 1000;}
	if( dIntervalX > 10000)  { dIntervalX = ((int)(dIntervalX/10000)) * 10000;}
	
	int nCurX = (int) floor((m_dMinX + dIntervalX) / dIntervalX);
	double dCurX = nCurX * dIntervalX;

	CString strDivX;
	int xDiv;
	int xMiniDiv;
	double dMiniInteval;
	int nDivOffset;
	CPen *pCoordPen;
	CPen netPen; netPen.CreatePen(PS_DOT,1,m_clrNet);
	for( UINT i = 0 ; ; i++)
	{
		xDiv = ValueToPointX(dCurX);
		strDivX.Format(strFormat,dCurX);
		CSize sizeTextExt = pDC->GetTextExtent(strDivX);
		pDC->TextOut(xDiv - sizeTextExt.cx/2, cLineRect.bottom + 7,strDivX);

		//X大刻度
		nDivOffset = m_bDivInner ? -6 : 6;
		pDC->MoveTo(xDiv,cLineRect.bottom);
		pDC->LineTo(xDiv,cLineRect.bottom + nDivOffset); 
	
		if( m_bVisibleNetX)
		{
			pCoordPen = pDC->SelectObject(&netPen);
			if( m_bDivInner )
				pDC->MoveTo(xDiv,cLineRect.bottom + nDivOffset);
			else
				pDC->MoveTo(xDiv,cLineRect.bottom);
			pDC->LineTo(xDiv,cLineRect.top);
			pDC->SelectObject(pCoordPen);
		}

		dCurX += dIntervalX;
		if( dCurX >= m_dMaxX) break;

		//X小刻度 
		nDivOffset = m_bDivInner ? -2 : 2;
		dMiniInteval = dIntervalX / 5.0;
		for(int j = 1 ; j < 5 ; j++)
		{
			xMiniDiv = ValueToPointX(dCurX-j*dMiniInteval);
			pDC->MoveTo(xMiniDiv,cLineRect.bottom);
			pDC->LineTo(xMiniDiv,cLineRect.bottom + nDivOffset);
		}
	
	}
	netPen.DeleteObject();
	pDC->SelectObject(pOldFont); 	font.DeleteObject(); 
	pDC->SetBkMode(nOldMode);	pDC->SetTextColor(clrOld);
	pDC->SelectObject(pOldPen);	pen.DeleteObject();
}

void CGraph::DrawLabelY(CDC *pDC)
{
	if(!m_bVisibleLabelY) return;
	
	CRect cLineRect = GetLineRect();
	int nOldMode    = pDC->SetBkMode(TRANSPARENT); 
	COLORREF clrOld = pDC->SetTextColor(m_clrLabelY); 
	
	CFont font; 	font.CreateFontIndirect(&m_fontLabelY); 
	CFont *pOldFont = pDC->SelectObject(&font); 
	CPen pen; pen.CreatePen(PS_SOLID ,m_nCoordWidth,m_clrCoord);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen);
	CString strLabelY(m_strLabelY);
	
	CSize sizeLabelY = pDC->GetTextExtent(m_strLabelY);
	pDC->TextOut(m_rcDraw.left + 5 ,cLineRect.top + cLineRect.Height() / 2 + sizeLabelY.cx /2,m_strLabelY);
	
	m_fontLabelY.lfEscapement = 0;
	font.DeleteObject();font.CreateFontIndirect(&m_fontLabelY);
	pDC->SelectObject(&font); 
	m_fontLabelY.lfEscapement = 900;
	
	CString strFormat  = "%.0f";
	double dIntervalY = (m_dMaxY - m_dMinY) / (double)m_nDivY;
	if( dIntervalY < 1) { strFormat = "%.2f";}
	if( dIntervalY > 1)  { dIntervalY = ((int)(dIntervalY/1)) * 1;}
	if( dIntervalY > 10)  { dIntervalY = ((int)(dIntervalY/10)) * 10;}
	if( dIntervalY > 100)  { dIntervalY = ((int)(dIntervalY/100)) * 100;}
	if( dIntervalY > 1000)  { dIntervalY = ((int)(dIntervalY/1000)) * 1000;}
	if( dIntervalY > 10000)  { dIntervalY = ((int)(dIntervalY/10000)) * 10000;}
	
	double dCurY = (floor((m_dMinY + dIntervalY) / dIntervalY)) * dIntervalY;;
	CString strDivY;
	int yDivY;
	int nDivOffset;
	CPen *pCoordPen;
	CPen netPen; netPen.CreatePen(PS_DOT,1,m_clrNet);
	for( UINT i = 0 ; ; i++)
	{
		yDivY = ValueToPointY(dCurY);
		strDivY.Format(strFormat,dCurY);
		CSize sizeTextExt = pDC->GetTextExtent(strDivY);
		pDC->TextOut(cLineRect.left-sizeTextExt.cx - 7,yDivY - sizeTextExt.cy/2,strDivY);
		
		//DrawDivY Y大刻度
		nDivOffset = m_bDivInner ? 6 : -6;
		pDC->MoveTo(cLineRect.left   ,yDivY );
		pDC->LineTo(cLineRect.left + nDivOffset ,yDivY);

		if( m_bVisibleNetY)
		{
			pCoordPen = pDC->SelectObject(&netPen);
			if( m_bDivInner )
				pDC->MoveTo(cLineRect.left + nDivOffset,yDivY);
			else
				pDC->MoveTo(cLineRect.left ,yDivY);
			pDC->LineTo(cLineRect.right ,yDivY);
			pDC->SelectObject(pCoordPen);
		}
	
		//Y小刻度 
		dCurY += dIntervalY;
		if( dCurY >= m_dMaxY) break;
		double dMiniInteval = dIntervalY / 5.0;
		nDivOffset = m_bDivInner ? 2 : -2;
		for(int j = 1 ; j < 5 ; j++)
		{
			pDC->MoveTo(cLineRect.left     ,ValueToPointY(dCurY - j*dMiniInteval ));
		 	pDC->LineTo(cLineRect.left + nDivOffset ,ValueToPointY(dCurY - j*dMiniInteval ));
		}
	}

	netPen.DeleteObject();
	pDC->SelectObject(pOldFont); 	font.DeleteObject(); 
	pDC->SetBkMode(nOldMode);	pDC->SetTextColor(clrOld);
	pDC->SelectObject(pOldPen);	pen.DeleteObject();
}

void CGraph::DrawTitle(CDC *pDC)
{
	if(!m_bVisibleTitle) return;

	CRect cLineRect = GetLineRect();
	int nOldMode    = pDC->SetBkMode(TRANSPARENT); 
	COLORREF clrOld = pDC->SetTextColor(m_clrTitle); 
	CFont font; font.CreateFontIndirect(&m_fontTitle);
	CFont *pOldFont = pDC->SelectObject(&font); 

	pDC->DrawText(m_strTitle,GetTitleRect(),DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	pDC->SelectObject(pOldFont); font.DeleteObject();
	pDC->SetBkMode(nOldMode);
	pDC->SetTextColor(clrOld);

}

void CGraph::DrawLegend(CDC *pDC)
{

}

void CGraph::DrawLines(CDC *pDC)
{

}

/*
void CGraph::DrawLines(CDC *pDC)
{
	
	if( m_nPointNums <= 1) return;
	if( m_pfX == NULL || m_pfY == NULL) return;

	m_rgn.DeleteObject(); 
	m_pen.DeleteObject();
	CRect rcLine = GetLineRect();
	
	if(pDC->IsPrinting())
	{
		CRect rcDeviceClipRect = rcLine;
		pDC->LPtoDP(&rcDeviceClipRect);
		m_rgn.CreateRectRgn(rcDeviceClipRect.left,rcDeviceClipRect.top,
			rcDeviceClipRect.right,rcDeviceClipRect.bottom); 
	}
	else
	{
		m_rgn.CreateRectRgn(rcLine.left,rcLine.top,rcLine.right,rcLine.bottom); 
		
	}
	
	pDC->SelectObject(&m_rgn);//pDC->SelectClipRgn(&m_rgn);
	
	double dRatioX = (double)rcLine.Width()   / (m_dMaxX - m_dMinX );
	double dCalcX  = (double)rcLine.left      - m_dMinX * dRatioX;
	double dRatioY = (double)rcLine.Height() / (m_dMaxY - m_dMinY );
	double dCalcY  = (double)rcLine.bottom + m_dMinY * dRatioY;

	m_pen.CreatePen(PS_SOLID ,m_nLineWidth,m_nLineColor);
	CPen * pOldPen; pOldPen =pDC->SelectObject(&m_pen);

	POINT posCurrent;
	posCurrent.x = (long)(dCalcX + m_pfX[0] * dRatioX );
	posCurrent.y = (long)(dCalcY - m_pfY[0] * dRatioY);
	int xLastPoint = posCurrent.x;
	pDC->MoveTo(posCurrent);
	
	for( register int i = 1 ; i < m_nPointNums ; i++)
	{
		posCurrent.x = (long)(dCalcX + m_pfX[i] * dRatioX );
		if( posCurrent.x == xLastPoint) continue;
		xLastPoint  = posCurrent.x;
		posCurrent.y = (long)(dCalcY - m_pfY[i] * dRatioY);
		pDC->LineTo(posCurrent);
	}
	
	pDC->SelectObject(pOldPen);	    // m_pen.DeleteObject();
	pDC->SelectClipRgn(NULL);
	
}
*/

BOOL CGraph::Draw(CDC *pDC,const CRect rcDraw)
{
	CalcRects(rcDraw);

	pDC->SetBkMode(TRANSPARENT);
	DrawBackground(pDC);

	CRect cLineRect = GetLineRect();
	if( cLineRect.IsRectEmpty() ) return FALSE;

	DrawCoord(pDC);
//	DrawNet(pDC);
	DrawTitle(pDC);
	DrawLabelX(pDC);
	DrawLabelY(pDC);
	DrawLines(pDC);
	DrawTooltips(pDC);
	DrawTextTable(pDC);
	DrawLegend(pDC);

	return TRUE;
}

void CGraph::OnSize(UINT nType, int cx, int cy)
{
	SetContentChanged();

	CWnd::OnSize(nType,cx,cy);
}

void CGraph::OnPaint() 
{
	CRect rcUpdate;
	GetUpdateRect(&rcUpdate);
	
	CPaintDC dc(this); // device context for painting
	
	//重绘所有区域
	if( m_bContentChanged )
	{
		CRect cDrawRect;	
		GetClientRect(&cDrawRect);
		if( m_hBitmap != NULL) DeleteObject(m_hBitmap);
		m_dcBuffer.DeleteDC();
		m_hBitmap = CreateCompatibleBitmap(dc.m_hDC,cDrawRect.Width(),cDrawRect.Height());
		m_dcBuffer.CreateCompatibleDC(&dc);
		m_dcBuffer.SelectObject(m_hBitmap);
		Draw(&m_dcBuffer,cDrawRect);
		dc.BitBlt(0,0,cDrawRect.Width(),cDrawRect.Height(),&m_dcBuffer,0,0,SRCCOPY);
		
	}
	//只绘更新区域
	else
	{
		dc.BitBlt(rcUpdate.left,rcUpdate.top,rcUpdate.Width(),rcUpdate.Height(),
			&m_dcBuffer,rcUpdate.left,rcUpdate.top,SRCCOPY);
	
	}
	
	//鼠标画线//左键拖动 || 画Tooltips
	if( m_bClipRect     ) DrawMouseClipRect(&dc);
	if( m_bMouseCross ) DrawMouseTooltips(&dc);

	m_bContentChanged = FALSE;
}


void CGraph::DrawTooltips(CDC *pDC)
{

}

void CGraph::DrawMouseTooltips(CDC *pDC)
{
	
}

void CGraph::CalcRectTextTable(CRect &rcOriginRect,float fRotateAngle,CDC *pDC)
{
	//Visual C++ 用的是弧度计算公式
	fRotateAngle *=  (float)(3.14159 / 180.0);
	CPoint ptCorner[4];
	float fOrgWidth  = (float)rcOriginRect.Width();
	float fOrgHeight = (float)rcOriginRect.Height();
	float fCrossLine = (float)(pow((pow(fOrgWidth,2.0) + pow(fOrgHeight,2.0)),0.5));
	float fOriginalAngle = (float)(asin(fOrgHeight / fCrossLine));
	ptCorner[0] = rcOriginRect.TopLeft();
	ptCorner[1].x = (long)(rcOriginRect.left + cos(fRotateAngle-1.5708) * fOrgHeight);
	ptCorner[1].y = (long)(rcOriginRect.top  - sin(fRotateAngle-1.5708) * fOrgHeight);
	ptCorner[2].x = (long)(rcOriginRect.left + cos(fRotateAngle-fOriginalAngle) * fCrossLine);
	ptCorner[2].y = (long)(rcOriginRect.top  - sin(fRotateAngle-fOriginalAngle) * fCrossLine);
	ptCorner[3].x = (long)(rcOriginRect.left + cos(fRotateAngle) * fOrgWidth);
	ptCorner[3].y = (long)(rcOriginRect.top  - sin(fRotateAngle) * fOrgWidth);
//	pDC->Polyline(ptCorner,4);
	rcOriginRect.left  = ptCorner[0].x;
	rcOriginRect.right = ptCorner[0].x;
	rcOriginRect.top   = ptCorner[0].y;
	rcOriginRect.bottom= ptCorner[0].y;
	for( int i = 1 ; i < 4; i++)
	{
		rcOriginRect.left  = min(ptCorner[i].x,rcOriginRect.left);
		rcOriginRect.right = max(ptCorner[i].x,rcOriginRect.right);
		rcOriginRect.top   = min(ptCorner[i].y,rcOriginRect.top);
		rcOriginRect.bottom= max(ptCorner[i].y,rcOriginRect.bottom);
	}
}

void CGraph::DrawTextTable(CDC *pDC)
{
	if( !m_bVisibleTextTable ) return;
	CRect rcLine = GetLineRect();
	int nSizeTextTable = m_TextTables.GetSize();
	int xPosText,yPosText;
	COLORREF clrOld;
	TextTable table;
	CFont *pOldFont;
	CSize TextSize;
	CPen pen;
	pen.CreatePen(PS_DOT,1,RGB(0,0,0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	for( int i = 0 ; i < nSizeTextTable ; i++)
	{
		table = m_TextTables.GetAt(i);
		xPosText = ValueToPointX(table.dPosX);
		yPosText = ValueToPointY(table.dPosY);
	//	if( !rcLine.PtInRect(CPoint(xPosText,yPosText))) continue;
		clrOld = pDC->SetTextColor(table.clrText);
		CFont font;
		font.CreateFontIndirect(&table.font);
		pOldFont = pDC->SelectObject(&font);
		pDC->TextOut(xPosText,yPosText,table.strCaption);
		TextSize = pDC->GetTextExtent(table.strCaption);
		table.rcRegion.left	= xPosText;
		table.rcRegion.right= xPosText + TextSize.cx;
		table.rcRegion.top	= yPosText;
		table.rcRegion.bottom = yPosText + TextSize.cy;
		CalcRectTextTable(table.rcRegion,(float)(table.font.lfEscapement / 10.0),pDC);
		//if( m_bSelectTextTable && m_nIndexSelectTextTable == i )
		if( m_nIndexSelectTextTable == i )
		{
			pDC->MoveTo(table.rcRegion.left-1,table.rcRegion.top-1);
			pDC->LineTo(table.rcRegion.right+1,table.rcRegion.top-1);
			pDC->LineTo(table.rcRegion.right+1,table.rcRegion.bottom+1);
			pDC->LineTo(table.rcRegion.left-1,table.rcRegion.bottom+1);
			pDC->LineTo(table.rcRegion.left-1,table.rcRegion.top-1);
		}
		m_TextTables.SetAt(i,table);
		pDC->SelectObject(pOldFont);font.DeleteObject();
		pDC->SetTextColor(clrOld);
	}
	pDC->SelectObject(pOldPen); pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Rect related
//

void CGraph::CalcRects(const CRect rcDraw)
{
	m_rcDraw = rcDraw;

	m_nDeflateLeft   = (m_bVisibleLabelY)? 80 : 10;
	m_nDeflateTop    = (m_bVisibleTitle) ? 40 : 20;
	m_nDeflateRight  = (m_bVisibleLabelX)? 20 : 10;
	m_nDeflateBottom = (m_bVisibleLabelX)? 50 : 10;
}

CRect CGraph::GetLineRect()
{
	CRect rcLine = m_rcDraw;
	rcLine.DeflateRect(0,m_nDeflateTop,0,0);
	rcLine.DeflateRect(0,0,0,m_nDeflateBottom);
	rcLine.DeflateRect(m_nDeflateLeft,0,0,0);
	rcLine.DeflateRect(0,0,m_nDeflateRight,0);
	return rcLine;
}

CRect CGraph::GetTitleRect()
{
	CRect rcTitle = m_rcDraw;
	rcTitle.DeflateRect(m_nDeflateLeft,0,m_nDeflateRight,m_rcDraw.Height() - m_nDeflateTop);
	return rcTitle;
}

CRect CGraph::GetLabelXRect()
{
	CRect rcLabelX = m_rcDraw;
	rcLabelX.DeflateRect(
		m_nDeflateLeft,
		m_rcDraw.Height() - m_nDeflateBottom,
		m_nDeflateRight,
		5);
	return rcLabelX;
}

CRect CGraph::GetLabelYRect()
{
	CRect rcLabelY = m_rcDraw;
	rcLabelY.DeflateRect(0,m_nDeflateTop,m_rcDraw.Width()-m_nDeflateLeft,m_nDeflateBottom);
	return rcLabelY;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// 
//
void CGraph::SetRangeX(double dMinX, double dMaxX)
{
	if( dMaxX <= dMinX) return;
	m_dMinX = max(-10000000.0,dMinX);
	m_dMaxX = min(10000000.0,dMaxX);
	SetContentChanged();
}

void CGraph::SetRangeY(double dMinY, double dMaxY)
{
	if( dMaxY <= dMinY) return;
	
	m_dMinY = max(-10000000.0,dMinY);
	m_dMaxY = min(10000000.0,dMaxY);
	SetContentChanged();
}

void CGraph::SetRange(double dMinX,double dMaxX,double dMinY,double dMaxY)
{
	SetRangeX(dMinX,dMaxX);
	SetRangeY(dMinY,dMaxY);
// 	if( dMaxX > dMinX)
// 	{
// 		m_dMaxX = dMaxX;
// 		m_dMinX = dMinX;
// 	}
// 	if( dMaxY > dMinY) 
// 	{
// 		m_dMaxY = dMaxY;
// 		m_dMinY = dMinY;
// 	}
// 	SetContentChanged();
}

void CGraph::SetDivX(int iDivX)
{
	m_nDivX = iDivX;
	SetContentChanged();
}

void CGraph::SetDivY(int iDivY)
{
	m_nDivY = iDivY;
	SetContentChanged();
}

void CGraph::SetVisibleNetX(BOOL bEnable)
{
	m_bVisibleNetX = bEnable;
	SetContentChanged();
}

void CGraph::SetVisibleNetY(BOOL bEnable)
{
	m_bVisibleNetY = bEnable;
	SetContentChanged();
}

void CGraph::SetLabelX(LPCTSTR strLabelX)
{
	m_strLabelX = strLabelX;
	SetContentChanged();
}

void CGraph::SetLabelY(LPCTSTR strLabelY)
{
	m_strLabelY = strLabelY;
	SetContentChanged();
}

void CGraph::SetTitleText(LPCTSTR strTitle)
{
	m_strTitle = strTitle;
	SetContentChanged();
}


void CGraph::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Legend  must before tooltips
	if( m_bVisibleLegend && m_rcLegend.PtInRect(point))
	{
		SendMessage(WM_COMMAND,WM_PROPERITY);
		return;
	}

	//TextTable must before tooltips

CRect rcLine = GetLineRect();
// 	//Tooltips
// 	
// 	if( m_bVisibleTooltips && rcLine.PtInRect(point))
// 	{
// 		ToolTip curTooptip;
// 		curTooptip.bVisible = TRUE;
// 		curTooptip.dPosX    = PointToValueX(point.x);
// 		curTooptip.dPosY    = PointToValueY(point.y);
// 		m_ToolTips.Add(curTooptip);
// 		SetActiveTooltip(m_ToolTips.GetSize()-1);
// 		SetContentChanged(TRUE);
// 		return;
// 	}

	//坐标Label X && Label Y Edit...
	CRect rcRegionY; rcRegionY.SetRect(0,rcLine.top,rcLine.left,rcLine.bottom);
	CRect rcRegionX; rcRegionX.SetRect(rcLine.left,rcLine.bottom,rcLine.right,m_rcDraw.bottom);
	if( rcRegionY.PtInRect(point) )
	{
		SendMessage(WM_COMMAND,WM_SET_COORD_Y);
		return;
	}
	else if( rcRegionX.PtInRect(point))
	{
		SendMessage(WM_COMMAND,WM_SET_COORD_X);
		return;
	}

	//Title Edit...
	CRect rcTitle; rcTitle.SetRect(rcLine.left,0,rcLine.right,rcLine.top);
	if( rcTitle.PtInRect(point))
	{
		SendMessage(WM_COMMAND,WM_PROPERITY);
		return;
	}

	CWnd::OnLButtonDblClk(nFlags,point);
}
void CGraph::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();//得到键盘，鼠标的输入焦点

	GetCursorPos  (&m_ptStart);
	ScreenToClient(&m_ptStart);
	m_ptEnd = m_ptStart;

	CRect cLineRect = GetLineRect();

	//
	
	if( m_bEnableMovingLine )
	{
		m_bMovingLine = TRUE;
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}

	//创建Text Table
	if( m_bCreatingTable )
	{
		TextTable table = m_TextTables.GetAt(m_TextTables.GetSize() - 1);
		table.dPosX = PointToValueX(point.x);
		table.dPosY = PointToValueY(point.y);
		m_TextTables.SetAt(m_TextTables.GetSize() - 1,table);
		m_bCreatingTable = FALSE;
		SetContentChanged(TRUE);
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}

	//移动Legend;
	if( m_bVisibleLegend )
	{
		if( m_rcLegend.PtInRect(point))
		{
			m_bSelectLegend = TRUE;
			SetContentChanged(TRUE);
			CWnd::OnLButtonDown(nFlags, point);
			return;
		}
	}

	//移动TextTable
	if( m_bVisibleTextTable )
	{
		int nSizeTextTable = m_TextTables.GetSize();
		m_bSelectTextTable = FALSE;
		for( int i = 0 ; i < nSizeTextTable; i++)
		{
			if( m_TextTables.GetAt(i).rcRegion.PtInRect(point))
			{
				m_bSelectTextTable = TRUE;
				m_nIndexSelectTextTable = i;
				SetContentChanged(TRUE);
				CWnd::OnLButtonDown(nFlags, point);
				return;
			}
		}
	}
	
	//移动Tooltip
// 	if(m_bVisibleTooltips)
// 	{
// 		int nSize = m_ToolTips.GetSize();
// 		m_bMovingTooltip = FALSE;
// 		for( int i = 0 ; i < nSize; i++)
// 		{
// 			int xPosTooltip = ValueToPointX(m_ToolTips.GetAt(i).dPosX);
// 			if( abs(xPosTooltip - point.x) < 10)
// 			{
// 				m_nIndexMovingTooltip = i;
// 				m_bMovingTooltip = TRUE; 
// 				SetActiveTooltip(i);
// 				SetContentChanged(TRUE);
// 				CWnd::OnLButtonDown(nFlags, point);
// 				return;
// 			}
// 		}
// 	}
	//移动Tooltip
	 	if(m_bVisibleTooltips)
	 	{
	 		int nSize = m_ToolTips.GetSize();
	 		m_bMovingTooltip = FALSE;
	 		for( int i = 0 ; i < min(1,nSize); i++)
	 		{
	 			int xPosTooltip = ValueToPointX(m_ToolTips.GetAt(i).dPosX);
	 			if( abs(xPosTooltip - point.x) < 10)
	 			{
	 				m_nIndexMovingTooltip = i;
	 				m_bMovingTooltip = TRUE; 
	 				SetActiveTooltip(i);
	 				SetContentChanged(TRUE);
	 				CWnd::OnLButtonDown(nFlags, point);
	 				return;
	 			}
	 		}
	 	}

	m_bClipRect      = cLineRect.PtInRect(m_ptStart);
	if(m_bClipRect)	{SetCapture();}
	CWnd::OnLButtonDown(nFlags, point);
	
}

BOOL CGraph::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	
	return	CWnd::OnSetCursor(pWnd,nHitTest,message);
}

void CGraph::OnMouseMove(UINT nFlags, CPoint point) 
{
	//移动 谱线
	if( m_bMovingLine )
	{
		CRect LineRect = GetLineRect();
		CPoint ptPre = m_ptEnd;
		GetCursorPos  (&m_ptEnd);
		ScreenToClient(&m_ptEnd);
		double dRateX = (m_dMaxX - m_dMinX) /(double) LineRect.Width();
		double dRateY = (m_dMaxY - m_dMinY) /(double) LineRect.Height();
		m_dMinX  -= dRateX * (m_ptEnd.x - ptPre.x);
		m_dMaxX  -= dRateX * (m_ptEnd.x - ptPre.x);
		m_dMinY  += dRateY * (m_ptEnd.y - ptPre.y);
		m_dMaxY  += dRateY * (m_ptEnd.y - ptPre.y);
		
		SetContentChanged(TRUE);
	}

	//移动Legend
	if( m_bSelectLegend )
	{
		CRect LineRect = GetLineRect();
		CPoint ptPre = m_ptEnd;
		GetCursorPos  (&m_ptEnd);
		ScreenToClient(&m_ptEnd);
		m_ptLengend.x  += m_ptEnd.x - ptPre.x;
		m_ptLengend.y  += m_ptEnd.y - ptPre.y;
		SetContentChanged(TRUE);
	}

	//移动textTable
	if( m_bSelectTextTable )
	{
		TextTable textTable = m_TextTables.GetAt(m_nIndexSelectTextTable);
		//if( textTable.)
		CRect LineRect = GetLineRect();
		CPoint ptPre = m_ptEnd;
		GetCursorPos  (&m_ptEnd);
		ScreenToClient(&m_ptEnd);
		double dRateX = (m_dMaxX - m_dMinX) /(double) LineRect.Width();
		double dRateY = (m_dMaxY - m_dMinY) /(double) LineRect.Height();
		textTable.dPosX  += dRateX * (m_ptEnd.x - ptPre.x);
		textTable.dPosY  -= dRateY * (m_ptEnd.y - ptPre.y);
		m_TextTables.SetAt(m_nIndexSelectTextTable,textTable);
		SetContentChanged(TRUE);
	}

	//右键拖动
	if( m_bRButtonDown )
	{
		m_bRButtonMove = TRUE;
		CRect LineRect = GetLineRect();
		CPoint ptPre = m_ptEnd;
		GetCursorPos  (&m_ptEnd);
		ScreenToClient(&m_ptEnd);
		double dRateX = (m_dMaxX - m_dMinX) /(double) LineRect.Width();
		double dRateY = (m_dMaxY - m_dMinY) /(double) LineRect.Height();
		m_dMinX  -= dRateX * (m_ptEnd.x - ptPre.x);
		m_dMaxX  -= dRateX * (m_ptEnd.x - ptPre.x);
		m_dMinY  += dRateY * (m_ptEnd.y - ptPre.y);
		m_dMaxY  += dRateY * (m_ptEnd.y - ptPre.y);

		SetContentChanged(TRUE);
	}

	//移动tooltip
	if( m_bMovingTooltip )
	{
		ASSERT(m_nIndexMovingTooltip >= 0);
		ToolTip tipMoving;
		tipMoving = m_ToolTips.GetAt(m_nIndexMovingTooltip);
		tipMoving.bVisible = TRUE;
		tipMoving.dPosX = PointToValueX(point.x);
		tipMoving.dPosY = PointToValueY(point.y);
		m_ToolTips.SetAt(m_nIndexMovingTooltip,tipMoving);
		SetContentChanged(TRUE);
	}

 	//左键拖动 || 画Tooltips
 	if( m_bClipRect || m_bMouseCross)
 	{
		Invalidate();
 	}

	CWnd::OnMouseMove(nFlags, point);
}

void CGraph::DrawMouseClipRect(CDC *pDC)
{
	if(!m_bClipRect) return;

	int nOldMode    = pDC->SetBkMode(TRANSPARENT);
	CPen pen; pen.CreatePen(PS_DOT ,1,COLOR_RED);
	CPen * pOldPen; pOldPen = pDC->SelectObject(&pen); 

	GetCursorPos  (&m_ptEnd);
	ScreenToClient(&m_ptEnd);
	CRect LineRect = GetLineRect();
	m_ptEnd.x = ( m_ptEnd.x < LineRect.left )  ?LineRect.left   : m_ptEnd.x;
	m_ptEnd.x = ( m_ptEnd.x > LineRect.right ) ?LineRect.right  : m_ptEnd.x;
	m_ptEnd.y = ( m_ptEnd.y < LineRect.top )   ?LineRect.top    : m_ptEnd.y;
	m_ptEnd.y = ( m_ptEnd.y > LineRect.bottom )?LineRect.bottom : m_ptEnd.y;

	//int nMode		= pDC->SetROP2(R2_NOTXORPEN);
	POINT LinePt[5];
	LinePt[0]=CPoint(m_ptStart.x,m_ptStart.y);
	LinePt[1]=CPoint(m_ptEnd.x,m_ptStart.y);
	LinePt[2]=CPoint(m_ptEnd.x,m_ptEnd.y);
	LinePt[3]=CPoint(m_ptStart.x,m_ptEnd.y);
	LinePt[4]=CPoint(m_ptStart.x,m_ptStart.y);
	pDC->Polyline(LinePt,5);

	pDC->SelectObject(pOldPen);	pen.DeleteObject();
	//pDC->SetBkMode(nOldMode);
}

void CGraph::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//m_bSelectTextTable      = FALSE;
	m_nIndexSelectTextTable = -1;
	//m_bSelectLegend			= FALSE;
	//m_bMovingTooltip		= FALSE;
	m_nIndexMovingTooltip   = -1;

	if( m_bMovingLine)
	{
		m_bMovingLine = FALSE; return;
	}

	if( m_bSelectTextTable)
	{
		m_bSelectTextTable = FALSE; return;
	}
	if( m_bCreatingTable)
	{
		m_bCreatingTable = FALSE; return;
	}
	if( m_bSelectLegend)
	{
		m_bSelectLegend = FALSE; return;
	}
	if( m_bMovingTooltip)
	{
		m_bMovingTooltip = FALSE; return;
	}

	//左键拖动
	if( m_bClipRect)
	{
		ReleaseCapture();
		m_bClipRect = FALSE;

		//恢复设置
		if( m_ptEnd.x < m_ptStart.x )
		{
			CWnd::OnLButtonUp(nFlags, point);
			SendMessage(WM_COMMAND,WM_UNZOOM); 
			GetParent()->SendMessage(WM_EQUAL_GRAPH_COORDINATE,(WPARAM)GetSafeHwnd());
			return;
		}

		//选中区域
		CRect rectpart(m_ptStart,m_ptEnd);
		rectpart.NormalizeRect();
		if( rectpart.Width() > 8 )
		{
			CRect LineRect = GetLineRect();
			double dRateX = (m_dMaxX - m_dMinX) /(double) LineRect.Width();
			double dRateY = (m_dMaxY - m_dMinY) /(double) LineRect.Height();
			if(  (m_dMaxX - m_dMinX) > 0.1 )
			{
				m_dMinX  += dRateX * (rectpart.left - LineRect.left);
				m_dMaxX  += dRateX * (rectpart.right - LineRect.right);
			}
			if( (m_dMaxY - m_dMinY) > 0.1 )
			{
				m_dMinY  -= dRateY * (rectpart.bottom - LineRect.bottom);
				m_dMaxY  -= dRateY * (rectpart.top - LineRect.top);
			}

			RecordCoordinate();
			// SetContentChanged(TRUE);
		}
		// GetParent()->SendMessage(WM_EQUAL_GRAPH_COORDINATE,(WPARAM)GetSafeHwnd());
	}

	if(m_bVisibleTooltips)
	{
		CRect rcClip(m_ptStart,m_ptEnd);
		if(rcClip.Width() <= CLIP_PIXELS && rcClip.Height() <= CLIP_PIXELS)
		{
		
			// ClientToScreen(&point);
			ToolTip tip;
			if(m_ToolTips.GetSize() <=0 ) m_ToolTips.Add(tip);
			tip = m_ToolTips.GetAt(0);
			tip.dPosX = PointToValueX(point.x);
			tip.bActive = TRUE;
			m_ToolTips.SetAt(0,tip);
	
		}
	}

	SetContentChanged(TRUE);
	CWnd::OnLButtonUp(nFlags, point);
}

void CGraph::OnRButtonDown(UINT nFlags, CPoint point) 
{
	GetCursorPos  (&m_ptStart);
	ScreenToClient(&m_ptStart);
	m_ptEnd = m_ptStart;
	m_bRButtonDown = TRUE;
	m_bRButtonMove = FALSE;

	if( m_bCreatingTable )
	{
		m_bCreatingTable = FALSE;
		m_TextTables.RemoveAt(m_TextTables.GetSize() - 1);
	}

	CWnd::OnRButtonDown(nFlags, point);
}

// BOOL CGraph::PopMenu(CPoint point)
// {
// 	CPoint pt;	GetCursorPos(&pt);
//    	CMenu *pPopMenu = new CMenu;
// 	pPopMenu->CreatePopupMenu();   
//   
// 	pPopMenu->AppendMenu(MF_STRING,WM_SET_COORD,"坐标设置(&S)...");
// 	pPopMenu->AppendMenu(MF_STRING,WM_CREATE_TABLE,"添加文字标注(&T)...");
// 	//pPopMenu->AppendMenu(MF_STRING,WM_MOUSE_TOOLTIP,"鼠标文字提示(&M)");
// 	pPopMenu->AppendMenu(MF_SEPARATOR,0,"");
// 
// 	CMenu menuSpectra;
// 	menuSpectra.CreatePopupMenu();
// //	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_OPEN,"打开光谱...");
// 	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_VIEW,"查看数据...");
// 	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_SAVE,"保存光谱...");
// 	menuSpectra.AppendMenu(MF_SEPARATOR);
// 	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_EXCEL,"导出Excel...");
// //	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_WORD, "导出Word...");
// 
// //	menuSpectra.AppendMenu(MF_STRING,WM_SPECTRA_DELETE,"清除数据");
// 
// 	CBitmap bitmap;
// 	bitmap.LoadBitmap(IDB_SPECTRA);
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuSpectra.m_hMenu,"谱图");
// 	pPopMenu->SetMenuItemBitmaps(3,MF_BYPOSITION,&bitmap,&bitmap);
// //	LONG nDimension = GetMenuCheckMarkDimensions();
// //	CString str;str.Format("%d",nDimension);MessageBox(str);
// 
// 	CMenu menuCoord;
// 	menuCoord.CreatePopupMenu();
// 	menuCoord.AppendMenu(MF_STRING,WM_SET_COORD,"坐标设置(&S)...");
// 	menuCoord.AppendMenu(MF_SEPARATOR,0,"");
// //	menuCoord.AppendMenu(MF_STRING,WM_SET_DEFAULT_COORD,"默认坐标(&D)...");
// 	menuCoord.AppendMenu(MF_STRING,WM_UNZOOM,"恢复默认坐标(&R)");
// 	menuCoord.AppendMenu(MF_STRING,WM_PRE_ZOOM,"前一个坐标(&P)");  
// 	menuCoord.AppendMenu(MF_STRING,WM_NEXT_ZOOM,"后一个坐标(&N)");  
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuCoord.m_hMenu,"坐标"); 
// 	if(  m_nPos <= 0 )
// 		menuCoord.EnableMenuItem(WM_PRE_ZOOM,MF_BYCOMMAND|MF_GRAYED);
// 	if(  m_nPos >= m_aCoord.GetSize() - 1 || m_aCoord.GetSize() == 0)
// 		menuCoord.EnableMenuItem(WM_NEXT_ZOOM,MF_BYCOMMAND|MF_GRAYED);
// 
// 	CMenu menuTextTable;
// 	menuTextTable.CreatePopupMenu();
// 	menuTextTable.AppendMenu(MF_STRING,WM_CREATE_TABLE,"添加文字标注(&T)...");
// 	menuTextTable.AppendMenu(MF_SEPARATOR,0,"");
// 	menuTextTable.AppendMenu(MF_STRING,WM_VISIBLE_TABLES,"显示文字标注");
// 	menuTextTable.AppendMenu(MF_STRING,WM_CLEAR_TABLES,"清除所有文字标注");
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuTextTable.m_hMenu,"文字标注");  
// 	if( m_TextTables.GetSize() <= 0)
// 		menuTextTable.EnableMenuItem(WM_CLEAR_TABLES,MF_BYCOMMAND|MF_GRAYED);
// 	if( m_bVisibleTextTable )
// 		menuTextTable.CheckMenuItem(WM_VISIBLE_TABLES,MF_BYCOMMAND|MF_CHECKED);
// 	
// 	CMenu menuMouse;
// 	menuMouse.CreatePopupMenu();
// 	menuMouse.AppendMenu(MF_STRING,WM_MOUSE_CROSS,"鼠标十字架(&C)");
// 	menuMouse.AppendMenu(MF_STRING,WM_MOUSE_TOOLTIP,"鼠标文字提示(&M)");
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuMouse.m_hMenu,"鼠标");  
// 	if( m_bMouseCross )
// 		menuMouse.CheckMenuItem(WM_MOUSE_CROSS,MF_BYCOMMAND|MF_CHECKED);
// 	else
// 		menuMouse.EnableMenuItem(WM_MOUSE_TOOLTIP,MF_BYCOMMAND|MF_GRAYED);
// 	if( m_bMouseTooltip )
//  		menuMouse.CheckMenuItem(WM_MOUSE_TOOLTIP,MF_BYCOMMAND|MF_CHECKED);
// 
// 
// 	CMenu menuTooltip;
// 	menuTooltip.CreatePopupMenu();
// // 	menuTooltip.AppendMenu(MF_STRING,WM_MOUSE_CROSS,"鼠标十字架(&C)");
// // 	menuTooltip.AppendMenu(MF_STRING,WM_MOUSE_TOOLTIP,"鼠标文字提示(&M)");
// // 	menuTooltip.AppendMenu(MF_SEPARATOR,0,"");
// 	menuTooltip.AppendMenu(MF_STRING,WM_VISIBLE_TOOLTIPS,"显示指示条");
// 	menuTooltip.AppendMenu(MF_STRING,WM_ADD_TOOLTIP,"添加指示条");
// 	menuTooltip.AppendMenu(MF_STRING,WM_REMOVE_TOOLTIPS,"清除所有指示条");
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuTooltip.m_hMenu,"指示条");  
// // 	if( m_bMouseCross )
// // 		menuTooltip.CheckMenuItem(WM_MOUSE_CROSS,MF_BYCOMMAND|MF_CHECKED);
// 	if( m_bVisibleTooltips )
// 		menuTooltip.CheckMenuItem(WM_VISIBLE_TOOLTIPS,MF_BYCOMMAND|MF_CHECKED);
// 	if( m_ToolTips.GetSize() <= 0)
// 		menuTooltip.EnableMenuItem(WM_REMOVE_TOOLTIPS,MF_BYCOMMAND|MF_GRAYED);
// 	if( !m_bVisibleTooltips )
// 		menuTooltip.EnableMenuItem(WM_ADD_TOOLTIP,MF_BYCOMMAND|MF_GRAYED);
// // 	if( m_bMouseTooltip )
// //  		menuTooltip.CheckMenuItem(WM_MOUSE_TOOLTIP,MF_BYCOMMAND|MF_CHECKED);
// 
//  	CMenu menuVisibleItems;
// 	menuVisibleItems.CreatePopupMenu();
// 	menuVisibleItems.AppendMenu(MF_STRING,WM_VISIBLE_TITLE,"显示标题");
// 	menuVisibleItems.AppendMenu(MF_STRING,WM_VISIBLE_LEGEND,"显示图示");
// 	menuVisibleItems.AppendMenu(MF_STRING,WM_VISIBLE_NET_X,"显示网格X");
// 	menuVisibleItems.AppendMenu(MF_STRING,WM_VISIBLE_NET_Y,"显示网格Y");
// 	pPopMenu->AppendMenu(MF_POPUP,(UINT)menuVisibleItems.m_hMenu,"显隐");
// 	if( m_bVisibleTitle )
// 		menuVisibleItems.CheckMenuItem(WM_VISIBLE_TITLE,MF_BYCOMMAND|MF_CHECKED);
// 	if( m_bVisibleLegend )
// 		menuVisibleItems.CheckMenuItem(WM_VISIBLE_LEGEND,MF_BYCOMMAND|MF_CHECKED);
// 	if( m_bVisibleNetX)
// 		menuVisibleItems.CheckMenuItem(WM_VISIBLE_NET_X,MF_BYCOMMAND|MF_CHECKED);
// 	if( m_bVisibleNetY )
// 		menuVisibleItems.CheckMenuItem(WM_VISIBLE_NET_Y,MF_BYCOMMAND|MF_CHECKED);
// 	
// 	pPopMenu->AppendMenu(MF_SEPARATOR,0,""); 
// //	pPopMenu->AppendMenu(MF_STRING,WM_PRINT_GRAPH,"打印曲线(&L)..."); 
// 	pPopMenu->AppendMenu(MF_STRING,WM_SAVE_BITMAP,"保存图片(&S)..."); 
// 	pPopMenu->AppendMenu(MF_STRING,WM_CLIPBOARD,"复制图像到剪贴板(&V)"); 
// 	pPopMenu->AppendMenu(MF_SEPARATOR,0,"");  
// 	pPopMenu->AppendMenu(MF_STRING,WM_PROPERITY,"属性(&O)..."); 
// 
// // 	if( m_bMouseTooltip )
// // 		pPopMenu->CheckMenuItem(WM_MOUSE_TOOLTIP,MF_BYCOMMAND|MF_CHECKED);
// 
// 	int nRet = 	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x,pt.y,this);
// 	
// 
// 	switch(nRet)
// 	{
// 		case WM_VISIBLE_TOOLTIPS: m_bVisibleTooltips = !m_bVisibleTooltips; SetContentChanged(TRUE); break;
// 		case WM_SAVE_BITMAP: SaveAsBitmap(); break;
// 		case WM_CLIPBOARD: CopyToClipboard();break;
// 		case WM_PRINT_GRAPH: PrintGraph(); break;
// // 		case WM_UNZOOM:    SendMessage(WM_COMMAND,WM_UNZOOM);break;
// // 		case WM_PRE_ZOOM:  SendMessage(WM_COMMAND,WM_PRE_ZOOM);break;
// // 		case WM_PROPERITY: SendMessage(WM_COMMAND,WM_PROPERITY);break;
// // 		case WM_NEXT_ZOOM: SendMessage(WM_COMMAND,WM_NEXT_ZOOM);break;
// 		case WM_REMOVE_TOOLTIPS: m_ToolTips.RemoveAll(); SetContentChanged(TRUE); break;
// 		case WM_MOUSE_CROSS: m_bMouseCross = !m_bMouseCross; SetContentChanged(TRUE);break;
// 		case WM_CREATE_TABLE: SendMessage(WM_CREATE_TABLE); break;
// 		case WM_CLEAR_TABLES: SendMessage(WM_CLEAR_TABLES); break;
// 		case WM_MOUSE_TOOLTIP: m_bMouseTooltip = !m_bMouseTooltip; SetContentChanged(TRUE);break;
// //		case WM_SET_COORD: SendMessage(WM_COMMAND,WM_SET_COORD); break;
// 		case WM_VISIBLE_TABLES: m_bVisibleTextTable = !m_bVisibleTextTable;SetContentChanged(TRUE);break;
// 		case WM_VISIBLE_TITLE: m_bVisibleTitle = !m_bVisibleTitle; SetContentChanged(TRUE);break;
// 		case WM_VISIBLE_NET_X: m_bVisibleNetX = !m_bVisibleNetX; SetContentChanged(TRUE);break;
// 		case WM_VISIBLE_NET_Y: m_bVisibleNetY = !m_bVisibleNetY; SetContentChanged(TRUE);break;
// 		case WM_VISIBLE_LEGEND: m_bVisibleLegend = !m_bVisibleLegend;SetContentChanged(TRUE);break;
// 		case WM_ADD_TOOLTIP: 
// 			{
// 				if( m_bVisibleTooltips)
// 				{
// 					ToolTip curTooptip;
// 					curTooptip.bVisible = TRUE;
// 					curTooptip.dPosX    = PointToValueX(point.x);
// 					curTooptip.dPosY    = PointToValueY(point.y);
// 					m_ToolTips.Add(curTooptip);
// 					SetContentChanged(TRUE);
// 				}
// 				break;
// 			}
// 		default: 
// 			{
// 				SendMessage(WM_COMMAND,nRet);break;
// 			}
// 	}
// 	delete pPopMenu; bitmap.DeleteObject();
// 	return TRUE;
// }
BOOL CGraph::PopMenu(CPoint point)
{
	CPoint pt;	GetCursorPos(&pt);
   	CMenu *pPopMenu = new CMenu;
	pPopMenu->CreatePopupMenu();   
	pPopMenu->AppendMenu(MF_STRING,WM_UNZOOM,"恢复默认坐标(&R)");
	pPopMenu->AppendMenu(MF_STRING,WM_SPECTRA_VIEW,"查看数据...");
	pPopMenu->AppendMenu(MF_SEPARATOR,0,"");
	pPopMenu->AppendMenu(MF_STRING,WM_CREATE_TABLE,"添加文字标注(&T)...");
	pPopMenu->AppendMenu(MF_STRING,WM_ADD_TOOLTIP,"添加指示条");
	pPopMenu->AppendMenu(MF_SEPARATOR,0,"");
	pPopMenu->AppendMenu(MF_STRING,WM_VISIBLE_TOOLTIPS,"指示条");
	pPopMenu->AppendMenu(MF_STRING,WM_VISIBLE_TABLES,"文字标注");
	pPopMenu->AppendMenu(MF_STRING,WM_VISIBLE_LEGEND,"图示");
	pPopMenu->AppendMenu(MF_SEPARATOR,0,""); 
	pPopMenu->AppendMenu(MF_STRING,WM_SAVE_BITMAP,"保存图片(&S)..."); 
	pPopMenu->AppendMenu(MF_STRING,WM_CLIPBOARD,"复制图像到剪贴板(&V)"); 
	pPopMenu->AppendMenu(MF_SEPARATOR,0,"");  
	pPopMenu->AppendMenu(MF_STRING,WM_PROPERITY,"属性(&O)..."); 

	if( m_bVisibleTextTable )
	{
		pPopMenu->CheckMenuItem(WM_VISIBLE_TABLES,MF_BYCOMMAND|MF_CHECKED);
	}
	else
	{
		pPopMenu->EnableMenuItem(WM_CREATE_TABLE,MF_BYCOMMAND|MF_GRAYED);
	}
	if( m_bVisibleTooltips )
	{
		pPopMenu->CheckMenuItem(WM_VISIBLE_TOOLTIPS,MF_BYCOMMAND|MF_CHECKED);
	}
	else
	{
		pPopMenu->EnableMenuItem(WM_ADD_TOOLTIP,MF_BYCOMMAND|MF_GRAYED);
	}
	if( m_bVisibleLegend )
		pPopMenu->CheckMenuItem(WM_VISIBLE_LEGEND,MF_BYCOMMAND|MF_CHECKED);
	int nRet = 	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x,pt.y,this);
	

	switch(nRet)
	{
		case WM_VISIBLE_TOOLTIPS: m_bVisibleTooltips = !m_bVisibleTooltips; SetContentChanged(TRUE); break;
		case WM_SAVE_BITMAP: SaveAsBitmap(); break;
		case WM_CLIPBOARD: CopyToClipboard();break;
		case WM_PRINT_GRAPH: PrintGraph(); break;
// 		case WM_UNZOOM:    SendMessage(WM_COMMAND,WM_UNZOOM);break;
// 		case WM_PRE_ZOOM:  SendMessage(WM_COMMAND,WM_PRE_ZOOM);break;
// 		case WM_PROPERITY: SendMessage(WM_COMMAND,WM_PROPERITY);break;
// 		case WM_NEXT_ZOOM: SendMessage(WM_COMMAND,WM_NEXT_ZOOM);break;
		case WM_REMOVE_TOOLTIPS: m_ToolTips.RemoveAll(); SetContentChanged(TRUE); break;
		case WM_MOUSE_CROSS: m_bMouseCross = !m_bMouseCross; SetContentChanged(TRUE);break;
		case WM_CREATE_TABLE: SendMessage(WM_CREATE_TABLE); break;
		case WM_CLEAR_TABLES: SendMessage(WM_CLEAR_TABLES); break;
		case WM_MOUSE_TOOLTIP: m_bMouseTooltip = !m_bMouseTooltip; SetContentChanged(TRUE);break;
//		case WM_SET_COORD: SendMessage(WM_COMMAND,WM_SET_COORD); break;
		case WM_VISIBLE_TABLES: m_bVisibleTextTable = !m_bVisibleTextTable;SetContentChanged(TRUE);break;
		case WM_VISIBLE_TITLE: m_bVisibleTitle = !m_bVisibleTitle; SetContentChanged(TRUE);break;
		case WM_VISIBLE_NET_X: m_bVisibleNetX = !m_bVisibleNetX; SetContentChanged(TRUE);break;
		case WM_VISIBLE_NET_Y: m_bVisibleNetY = !m_bVisibleNetY; SetContentChanged(TRUE);break;
		case WM_VISIBLE_LEGEND: m_bVisibleLegend = !m_bVisibleLegend;SetContentChanged(TRUE);break;
		case WM_ADD_TOOLTIP: 
			{
				if( m_bVisibleTooltips)
				{
					ToolTip curTooptip;
					curTooptip.bVisible = TRUE;
					curTooptip.dPosX    = PointToValueX(point.x);
					curTooptip.dPosY    = PointToValueY(point.y);
					m_ToolTips.Add(curTooptip);
					SetContentChanged(TRUE);
				}
				break;
			}
		default: 
			{
				SendMessage(WM_COMMAND,nRet);break;
			}
	}
	delete pPopMenu; 
	return TRUE;
}
void CGraph::OnClearTooltips()
{
	m_ToolTips.RemoveAll(); 
	SetContentChanged(TRUE);
}

BOOL CGraph::PopMenuTooltips(CPoint point)
{
	if( !m_bVisibleTooltips ) return FALSE;

	int nSize = m_ToolTips.GetSize();
	for( int i = 0 ; i < nSize; i++)
	{
		int xPosTooltip = ValueToPointX(m_ToolTips.GetAt(i).dPosX);
		if(  abs(xPosTooltip - point.x) < 10)
		{
			CPoint pt;	GetCursorPos(&pt);
			CMenu *pPopMenu = new CMenu;
			pPopMenu->CreatePopupMenu();
			pPopMenu->AppendMenu(MF_STRING,1,"删除指示条(&D)");  
			pPopMenu->AppendMenu(MF_STRING,11,"删除所有指示条(&A)");
			pPopMenu->AppendMenu(MF_STRING,12,"隐藏所有指示条(&V)");
			
			pPopMenu->AppendMenu(MF_SEPARATOR);
			pPopMenu->AppendMenu(MF_STRING,2,"左移(&L)");  
			pPopMenu->AppendMenu(MF_STRING,3,"右移(&R)");
			pPopMenu->AppendMenu(MF_SEPARATOR);
			pPopMenu->AppendMenu(MF_STRING,13,"设置...(&C)");
		//	pPopMenu->AppendMenu(MF_SEPARATOR);
		//	pPopMenu->AppendMenu(MF_STRING,4,"双击添加新指示条!");
		//	pPopMenu->EnableMenuItem(4,MF_BYCOMMAND | MF_GRAYED);
			if(i==0)
			{
				pPopMenu->EnableMenuItem( 1,MF_BYCOMMAND | MF_GRAYED);
				pPopMenu->EnableMenuItem(11,MF_BYCOMMAND | MF_GRAYED);
			}
			if( m_bVisibleTooltips )
				pPopMenu->CheckMenuItem(WM_VISIBLE_TOOLTIPS,MF_BYCOMMAND|MF_CHECKED);
			
			int nRet = 	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x,pt.y,this);
			switch(nRet)
			{
			case 1: 
				{
					if( GetActiveTooltip() == i) SetActiveTooltip(0);
					m_ToolTips.RemoveAt(i); 
					SetContentChanged(TRUE); 
				}break;
			case 2:
				{
					ToolTip tip = m_ToolTips.GetAt(i);
					tip.dPosX -= (m_dMaxX - m_dMinX) / GetLineRect().Width();
					m_ToolTips.SetAt(i,tip);
					SetContentChanged(TRUE);
				}break;
			case 3:
				{
					ToolTip tip = m_ToolTips.GetAt(i);
					tip.dPosX += (m_dMaxX - m_dMinX) / GetLineRect().Width();
					m_ToolTips.SetAt(i,tip);
					SetContentChanged(TRUE);
					break;
				}
			case 11:
				{
					m_ToolTips.RemoveAll(); SetContentChanged(TRUE); 
					break;
				}
			case 12:
				{
					m_bVisibleTooltips = !m_bVisibleTooltips; SetContentChanged(TRUE); 
					break;
				}
			case 13:
				{
					SendMessage(WM_COMMAND,WM_PROPERITY); SetContentChanged(TRUE); 
					break;
				}
			}
			delete pPopMenu;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGraph::PopMenuLegend(CPoint point)
{
	if( !m_rcLegend.PtInRect(point) || !m_bVisibleLegend) return FALSE;

	CPoint pt;	GetCursorPos(&pt);
	CMenu popMenu;
	popMenu.CreatePopupMenu();   
	popMenu.AppendMenu(MF_STRING,1,"隐藏图示(&H)");
	//popMenu.AppendMenu(MF_SEPARATOR,0,""); 
	int nRet = 	popMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x,pt.y,this);
	m_nIndexSelectTextTable = -1;
	switch(nRet)
	{
		case 1: m_bVisibleLegend = FALSE; SetContentChanged(TRUE); break;
		default: break;
	}

	return TRUE;
}

BOOL CGraph::PopMenuTextTable(CPoint point)
{
	if( !m_bVisibleTextTable ) return FALSE;
	
	int nSizeTextTable = m_TextTables.GetSize();
	m_bSelectTextTable = FALSE;
	for( int i = 0 ; i < nSizeTextTable; i++)
	{
		if( m_TextTables.GetAt(i).rcRegion.PtInRect(point))
		{
			m_nIndexSelectTextTable = i;
			SetContentChanged(TRUE);
			CPoint pt;	GetCursorPos(&pt);
			CMenu *pPopMenu = new CMenu;
			pPopMenu->CreatePopupMenu();   
			pPopMenu->AppendMenu(MF_STRING,1,"删除文字标注(&D)");
			pPopMenu->AppendMenu(MF_STRING,2,"创建副本(&C)");
			pPopMenu->AppendMenu(MF_STRING,3,"编辑(&E)...");
			pPopMenu->AppendMenu(MF_SEPARATOR,0,""); 
			pPopMenu->AppendMenu(MF_STRING,WM_CLEAR_TABLES,_T("清除所有文字标注"));
			int nRet = 	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, pt.x,pt.y,this);
			m_nIndexSelectTextTable = -1;
			switch(nRet)
			{
			case 1: m_TextTables.RemoveAt(i); SetContentChanged(TRUE); break;
			case 2: 
				{
					TextTable newTable = m_TextTables.GetAt(i);
					newTable.dPosX = PointToValueX(ValueToPointX(newTable.dPosX) + 20);
					newTable.dPosY = PointToValueY(ValueToPointY(newTable.dPosY) + 20);;
					m_TextTables.Add(newTable);
					SetContentChanged(TRUE);
					break;
				}
			case 3:
				{
					
					break;
				}
			case WM_CLEAR_TABLES:
				{
					SendMessage(WM_CLEAR_TABLES); break;
				}
			}
			delete pPopMenu; return TRUE;
		}
	}
	return FALSE;
}

void CGraph::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRButtonDown  = FALSE;

	//右键拖动情况
	if( m_bRButtonMove ) 
	{
		GetParent()->SendMessage(WM_EQUAL_GRAPH_COORDINATE,(WPARAM)GetSafeHwnd());
		CWnd::OnRButtonUp(nFlags,point);
		return;
	}

	//Legend
	if( PopMenuLegend(point))  {CWnd::OnRButtonUp(nFlags,point);return;}

	//TextTable
	if( PopMenuTextTable(point))  {CWnd::OnRButtonUp(nFlags,point);return;}

	//指示条
	if(	PopMenuTooltips(point)) {CWnd::OnRButtonUp(nFlags,point);return;}
		
	
	//右键菜单	
	PopMenu(point);	CWnd::OnRButtonUp(nFlags,point);
	
}

void CGraph::OnClearTextTables(WPARAM,LPARAM)
{
	m_TextTables.RemoveAll(); SetContentChanged(TRUE);
}

BOOL CGraph::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	double dRate = zDelta / 2000.0;
	MoveDown(dRate);

	SetContentChanged(TRUE);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CGraph::OnCreateTable(WPARAM,LPARAM)
{
	

}

////////////////////////////////////////////////////
//
//Move Coordinate
//

void CGraph::MoveLeft(double dRate)
{
	double dRange = m_dMaxX - m_dMinX;
	m_dMaxX += dRange * dRate;
	m_dMinX += dRange * dRate;
	SetContentChanged(TRUE);
}

void CGraph::MoveRight(double dRate)
{
	double dRange = m_dMaxX - m_dMinX;
	m_dMaxX -= dRange * dRate;
	m_dMinX -= dRange * dRate;
	SetContentChanged(TRUE);
}

void CGraph::MoveUp(double dRate)
{
	double dRange = m_dMaxY - m_dMinY;
	m_dMaxY -= dRange * dRate;
	m_dMinY -= dRange * dRate;
	SetContentChanged(TRUE);
}

void CGraph::MoveDown(double dRate)
{
	double dRange = m_dMaxY - m_dMinY;
	m_dMaxY += dRange * dRate;
	m_dMinY += dRange * dRate;
	SetContentChanged(TRUE);
}

void CGraph::ZoomX(double dZoom)
{
	double dHalfLen = (m_dMaxX - m_dMinX)/2.0;
	double dMid     = (m_dMaxX + m_dMinX)/2.0;
	m_dMinX = dMid - dHalfLen * dZoom; //以中心为基准进行放大
	m_dMaxX = dMid + dHalfLen * dZoom;
	if(m_dMinX > m_dMaxX)   {m_dMaxX = m_dMinX + 1;}
	SetContentChanged(TRUE);
}

void CGraph::ZoomY(double dZoom)
{
	double dHalfLen = (m_dMaxY - m_dMinY)/2.0;
	double dMid     = (m_dMaxY + m_dMinY)/2.0;
	m_dMinY = dMid - dHalfLen * dZoom; //以中心为基准进行放大
	m_dMaxY = dMid + dHalfLen * dZoom;
	if(m_dMinY > m_dMaxY)   {m_dMaxY = m_dMinY + 1;}
	SetContentChanged(TRUE);
}

void CGraph::SaveAsBitmap()
{
	CDC *pDC = GetDC();
	HBITMAP hBitmap=CreateCompatibleBitmap(pDC->m_hDC,m_rcDraw.Width(),m_rcDraw.Height());
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(hBitmap);
	
	Draw(&dc,m_rcDraw);
	CBitmap bitmap;
	bitmap.Attach(hBitmap);
	HANDLE handle=DDBToDIB(bitmap,BI_RGB,NULL);
			
	CFileDialog dlg(false,_T("*.bmp"),_T("位图文件"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("BMP 文件(*.bmp)|*.bmp||"),this);
	if( IDOK == dlg.DoModal())
	{	
		char name[400];
		strcpy(name,dlg.GetPathName());
		WriteDIB(name,handle);
	}
	dc.DeleteDC();
}

BOOL CGraph::SaveBMPFileTopToBottom(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight)
{
	CDC *pDC = GetDC();
	HBITMAP hBitmap=CreateCompatibleBitmap(pDC->m_hDC,m_rcDraw.Width(),m_rcDraw.Height());

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(hBitmap);
	
	Draw(&dc,m_rcDraw);

	CBitmap bitmap;
	bitmap.Attach(hBitmap);

	WriteBmp(&bitmap,strBMPFileName);

	dc.DeleteDC();

	*pnImageWidth  = m_rcDraw.Width();
	*pnImageHeight = m_rcDraw.Height();
	
	return TRUE;
}

void  CGraph::WriteBmp(CBitmap *PBitmap,CString strFileName)   
{   
    BITMAPINFO   *m_pBMI;   
    BYTE   *m_pDIBData;   
    BITMAPFILEHEADER   bfh;   
    BITMAPINFOHEADER   bi;   
    BITMAP   BM;   
    PBitmap->GetObject(sizeof(BM),&BM);   
    CClientDC   dc(this);   
    bi.biSize     =   sizeof(BITMAPINFOHEADER);   
    bi.biWidth     =   BM.bmWidth;   
    bi.biHeight       =   BM.bmHeight;   
    bi.biPlanes       =   1;   
    bi.biBitCount     =   24;   
    bi.biCompression   =   0;   
    bi.biSizeImage     =   0;   
    bi.biXPelsPerMeter   =   0;   
    bi.biYPelsPerMeter   =   0;   
    bi.biClrUsed     =   0;   
    bi.biClrImportant   =   0;   
	
    bfh.bfType=0x4d42;   
    bfh.bfOffBits=sizeof(bfh)+sizeof(BITMAPINFOHEADER);   
    bfh.bfSize=bfh.bfOffBits+BM.bmWidth*BM.bmHeight*3;   
    bfh.bfReserved1=0;   
    bfh.bfReserved2=0;   
	
    m_pBMI=(BITMAPINFO*)new   char[sizeof(BITMAPINFO)];   
	m_pDIBData=(BYTE*)new   char[bfh.bfSize-bfh.bfOffBits];   
	
    memcpy(m_pBMI,&bi,sizeof(BITMAPINFOHEADER));   
    GetDIBits(dc.GetSafeHdc(),   (HBITMAP)PBitmap->GetSafeHandle(),   0l,   (DWORD)bi.biHeight,   
		(LPVOID)m_pDIBData,(LPBITMAPINFO)m_pBMI,   (DWORD)DIB_RGB_COLORS);   
	CFile   file;   
    if(!file.Open(strFileName,CFile::modeCreate|CFile::modeWrite))   
    {   
		MessageBox("error!");   
		return;   
    }   
    file.Write(&bfh,sizeof(bfh));   
    file.Write(m_pBMI,sizeof(BITMAPINFOHEADER));   
    file.Write(m_pDIBData,BM.bmWidth*BM.bmHeight*3);   
    file.Close();   
 }

BOOL CGraph::SaveBMPFileBottomToTop(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight)
{
	CDC *pDC = GetDC();
	HBITMAP hBitmap=CreateCompatibleBitmap(pDC->m_hDC,m_rcDraw.Width(),m_rcDraw.Height());

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(hBitmap);
	
	Draw(&dc,m_rcDraw);

	CBitmap bitmap;
	bitmap.Attach(hBitmap);

	HANDLE handle=DDBToDIB(bitmap,BI_RGB,NULL);//BI_RGB
	WriteDIB(strBMPFileName,handle);
	
	dc.DeleteDC();

	*pnImageWidth  = m_rcDraw.Width();
	*pnImageHeight = m_rcDraw.Height();
	
	return TRUE;
}

HANDLE CGraph::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal ) 
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;

	ASSERT( bitmap.GetSafeHandle() );
	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )	return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount); if( nColors> 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC=::GetDC(this->m_hWnd);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(CDC::FromHandle(hDC));
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(CDC::FromHandle(hDC));
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(CDC::FromHandle(hDC));
		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE);
	ReleaseDC(CDC::FromHandle(hDC));
	return hDIB;
}

BOOL CGraph::WriteDIB( LPCTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B'); // is always "BM" 
	hdr.bfSize=GlobalSize(hDIB) + sizeof( hdr ); 
	hdr.bfReserved1=0;
	hdr.bfReserved2=0;
	hdr.bfOffBits=(DWORD)(sizeof( hdr ) + lpbi->biSize+nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, GlobalSize(hDIB) );

	return TRUE;
}

void CGraph::CopyToClipboard()
{
	CDC *pDC = GetDC();
	OpenClipboard();
	EmptyClipboard();  
//	HGLOBAL hbit=GetClipboardData(CF_BITMAP);

	HBITMAP hBitmap = CreateCompatibleBitmap(pDC->m_hDC,m_rcDraw.Width(),m_rcDraw.Height());

	CDC dc;	dc.CreateCompatibleDC(pDC);	dc.SelectObject(hBitmap);
	Draw(&dc,m_rcDraw);
	
	SetClipboardData(CF_BITMAP,hBitmap);
	CloseClipboard();
	dc.DeleteDC();

	MessageBox("成功复制到剪切板!","剪切板",MB_OK|MB_ICONINFORMATION);
}

void CGraph::PrintGraph()
{
	CDC printDC;	CRect rect;
	CPrintDialog printDlg(FALSE,PD_ALLPAGES|PD_USEDEVMODECOPIES|PD_NOPAGENUMS|PD_HIDEPRINTTOFILE|PD_NOSELECTION,this);
	DOCINFO docInfo;	

	if(printDlg.DoModal() == IDOK)
	{
		HDC hDC = printDlg.GetPrinterDC();
		if(!printDC.Attach(hDC))  return;
	}
	else
	{
		printDC.Detach(); 	return;
	}
	printDC.m_bPrinting = TRUE;

	memset(&docInfo,0,sizeof(docInfo));
	docInfo.cbSize=sizeof(DOCINFO);
	docInfo.lpszDocName="Graph";

	if(printDC.StartDoc(&docInfo)<=0)
	{
		printDC.Detach();  return;
	}

	printDC.StartPage();

    printDC.SetMapMode(MM_ANISOTROPIC);
	printDC.SetWindowExt(96,96);
	printDC.SetViewportExt(printDC.GetDeviceCaps(LOGPIXELSX),printDC.GetDeviceCaps(LOGPIXELSY));

	//Center the print graph
	int nWidth  = printDC.GetDeviceCaps(HORZRES)*96 / printDC.GetDeviceCaps(LOGPIXELSX);
	int nHeigth = printDC.GetDeviceCaps(VERTRES)*96 / printDC.GetDeviceCaps(LOGPIXELSY);
	int nStartX = ( nWidth  - m_rcDraw.Width()  ) / 2;
	int nStartY = ( nHeigth - m_rcDraw.Height() ) / 2;
	CRect rcPrint(nStartX,nStartY,m_rcDraw.Width(),m_rcDraw.Height());

	Draw(&printDC,m_rcDraw);
	
	printDC.EndPage();
	printDC.EndDoc();
	printDC.Detach();
}

void CGraph::RecordCoordinate()
{
	COORDINATE cord ;
	cord.dMaxX = m_dMaxX;
	cord.dMinX = m_dMinX;
	cord.dMinY = m_dMinY;
	cord.dMaxY = m_dMaxY;
	m_aCoord.Add(cord);
	m_nPos = m_aCoord.GetSize() - 1;
}

BOOL CGraph::IsPreZoom()
{
	return ( m_nPos == 0) ? FALSE : TRUE;
}

void CGraph::OnPreZoom()
{
	if( !IsPreZoom()) return;

	m_nPos--;

	COORDINATE cord = m_aCoord.GetAt(m_nPos);
	SetRangeX(cord.dMinX,cord.dMaxX);
	SetRangeY(cord.dMinY,cord.dMaxY);

	SetContentChanged();
	Invalidate();
}


BOOL CGraph::IsNextZoom()
{
	int nSize = m_aCoord.GetSize();
	return ( m_nPos >=  nSize -1 ) ?FALSE : TRUE;
}

void CGraph::OnNextZoom()
{
	if(! IsNextZoom()) return;

	m_nPos++;
	COORDINATE cord = m_aCoord.GetAt(m_nPos);
	SetRangeX(cord.dMinX,cord.dMaxX);
	SetRangeY(cord.dMinY,cord.dMaxY);

	SetContentChanged();
	Invalidate();

}


void CGraph::OnUnZoom()
{
	SetRangeX(m_coordRestore.dMinX,m_coordRestore.dMaxX);
	SetRangeY(m_coordRestore.dMinY,m_coordRestore.dMaxY);

	m_aCoord.RemoveAll();
	RecordCoordinate();

	SetContentChanged();
	Invalidate();
}

void CGraph::SetRangeRestore(double dMinX,double dMaxX,double dMinY, double dMaxY,BOOL bApply)
{
	m_coordRestore.dMinX = dMinX;
	m_coordRestore.dMaxX = dMaxX;
	m_coordRestore.dMinY = dMinY;
	m_coordRestore.dMaxY = dMaxY;
	
	if( bApply)
	{
		m_dMinX = dMinX;
		m_dMaxX = dMaxX;
		m_dMinY = dMinY;
		m_dMaxY = dMaxY;
	}

	SetContentChanged();
}

void CGraph::SetRangeRestoreX(double dMinX,double dMaxX,BOOL bApply)
{
	m_coordRestore.dMinX = dMinX;
	m_coordRestore.dMaxX = dMaxX;

	if( bApply)
	{
		m_dMinX = dMinX;
		m_dMaxX = dMaxX;
	}
	SetContentChanged();
}


void CGraph::SetRangeRestoreY(double dMinY, double dMaxY,BOOL bApply)
{
	m_coordRestore.dMinY = dMinY;
	m_coordRestore.dMaxY = dMaxY;
	
	if( bApply)
	{
		m_dMinY = dMinY;
		m_dMaxY = dMaxY;
	}
	SetContentChanged();
}

double CGraph::GetMaxX()
{
	return m_dMaxX;
}
double CGraph::GetMinX()
{
	return m_dMinX;
}
double CGraph::GetMinY()
{
	return m_dMinY;
}
double CGraph::GetMaxY()
{
	return m_dMaxY;
}

void CGraph::IncXRange(float fMaxX)
{
	m_dMaxX = fMaxX;
}



void CGraph::OnProperty()
{
}



////////////////////////////////////////////////////////////////////
//
//Private Functions
//
long CGraph::ValueToPointX(double dValueX)
{
	CRect  cLineRect = GetLineRect();
	return (long)(cLineRect.left + (dValueX - m_dMinX) * ((double)cLineRect.Width()  / (m_dMaxX - m_dMinX )));
}

long CGraph::ValueToPointY(double dValueY)
{
	CRect cLineRect = GetLineRect();
	return (long)(cLineRect.bottom - (dValueY - m_dMinY) * ((double)cLineRect.Height() / (m_dMaxY - m_dMinY )));
}

double CGraph::PointToValueX(long nPosX)
{
	double dRange = m_dMaxX - m_dMinX;
	double dLen   = GetLineRect().Width();
	double dScale = nPosX - GetLineRect().left;
	return m_dMinX + dRange * dScale / dLen; 
}


double CGraph::PointToValueY(long nPosY)
{
	double dRange = m_dMaxY - m_dMinY;
	double dLen   = GetLineRect().Height();
	double dScale = GetLineRect().bottom - nPosY;
	return m_dMinY + dRange * dScale / dLen; 
}

void CGraph::OpenSettingsReg(CString strSection)
{
	m_nLineColor = AfxGetApp()->GetProfileInt(strSection,"LineColor",COLOR_BLUE);
	m_nLineWidth = AfxGetApp()->GetProfileInt(strSection,"LineWidth",1);
	m_clrBk   = AfxGetApp()->GetProfileInt(strSection,"BkColor",RGB(56,137,248));
	m_clrBkInner = AfxGetApp()->GetProfileInt(strSection,"BkInnerColor",(RGB(56,213,191)));
	m_bVisibleNetX = AfxGetApp()->GetProfileInt(strSection,"DrawNetX",1);		   
	m_bVisibleNetY = AfxGetApp()->GetProfileInt(strSection,"DrawNetY",1);
	m_clrNet = AfxGetApp()->GetProfileInt(strSection,"NetColor",COLOR_GRAY);
	m_nDivX     = AfxGetApp()->GetProfileInt(strSection,"DivX",5);
	m_nDivY		= AfxGetApp()->GetProfileInt(strSection,"DivY",5);
	m_bVisibleTitle = AfxGetApp()->GetProfileInt(strSection,"DrawTitle",1);
	m_clrTitle= AfxGetApp()->GetProfileInt(strSection,"TitleColor",COLOR_BLACK);
	m_bVisibleLabelX = AfxGetApp()->GetProfileInt(strSection,"DrawLabelX",1);
	m_bVisibleLabelY = AfxGetApp()->GetProfileInt(strSection,"DrawLabelY",1);
	m_clrLabelX= AfxGetApp()->GetProfileInt(strSection,"LabelColorX",COLOR_BLACK);
	m_clrLabelY= AfxGetApp()->GetProfileInt(strSection,"LabelColorY",COLOR_BLACK);
	m_clrCoord = AfxGetApp()->GetProfileInt(strSection,"CoordColor",COLOR_RED);
	m_nCoordWidth = AfxGetApp()->GetProfileInt(strSection,"CoordWidth",1);
}

void CGraph::SaveSettingsReg(CString strSection)
{
	AfxGetApp()->WriteProfileInt(strSection,"LineColor",m_nLineColor);
	AfxGetApp()->WriteProfileInt(strSection,"LineWidth",m_nLineWidth);
	AfxGetApp()->WriteProfileInt(strSection,"BkColor",m_clrBk);
	AfxGetApp()->WriteProfileInt(strSection,"BkInnerColor",m_clrBkInner);
	AfxGetApp()->WriteProfileInt(strSection,"DrawNetX",m_bVisibleNetX);		   
	AfxGetApp()->WriteProfileInt(strSection,"DrawNetY",m_bVisibleNetY);
	AfxGetApp()->WriteProfileInt(strSection,"NetColor",m_clrNet);
	AfxGetApp()->WriteProfileInt(strSection,"DivX",m_nDivX);
	AfxGetApp()->WriteProfileInt(strSection,"DivY",m_nDivY);
	AfxGetApp()->WriteProfileInt(strSection,"DrawTitle",m_bVisibleTitle);
	AfxGetApp()->WriteProfileInt(strSection,"TitleColor",m_clrTitle);
	AfxGetApp()->WriteProfileInt(strSection,"DrawLabelX",m_bVisibleLabelX);
	AfxGetApp()->WriteProfileInt(strSection,"DrawLabelY",m_bVisibleLabelY);
	AfxGetApp()->WriteProfileInt(strSection,"LabelColorX",m_clrLabelX);
	AfxGetApp()->WriteProfileInt(strSection,"LabelColorY",m_clrLabelY);
	AfxGetApp()->WriteProfileInt(strSection,"CoordColor",m_clrCoord);
	AfxGetApp()->WriteProfileInt(strSection,"CoordWidth",m_nCoordWidth);
}


void  CGraph::Serialize(CArchive& ar)
{
	if( ar.IsLoading() )
	{
		ar>>m_nCoordWidth;
		ar>>m_nDivX;
		ar>>m_nDivY;
		ar>>m_nLineWidth;
		
		ar>>m_bVisibleLabelX;
		ar>>m_bVisibleLabelY;
		ar>>m_bVisibleNetX;
		ar>>m_bVisibleNetY;
		ar>>m_bVisibleTitle;
		ar>>m_bVisibleLegend;
		ar>>m_bMouseCross;
		ar>>m_bMouseTooltip;
		ar>>m_bVisibleTooltips;
		ar>>m_bVisibleTextTable;
		
		ar>>m_clrBk;
		ar>>m_clrBkInner;
		ar>>m_clrCoord;
		ar>>m_clrLabelX;
		ar>>m_clrLabelY;
		ar>>m_clrNet;
		ar>>m_clrTitle;
		ar>>m_clrTooltip;
		
		ar>>m_strLabelX;
		ar>>m_strLabelY;
		ar>>m_strTitle;
		ar>>m_strTooltipFormat;

		ar>>m_ptLengend;
		
		int nTipSize;
		ar>>nTipSize;
		ASSERT(nTipSize >= 0);
		m_ToolTips.SetSize(nTipSize);
		ar.Read(m_ToolTips.GetData(),nTipSize * sizeof(ToolTip));
		
		int nLabelSize;
		ar>>nLabelSize;
		ASSERT(nLabelSize >= 0);
		m_TextTables.SetSize(nLabelSize);
		TextTable label;
		for(int i = 0 ; i < nLabelSize ; i++)
		{
			ar>>label.bBkTransparent;
			ar>>label.clrText;
			ar>>label.dPosX;
			ar>>label.dPosY;
			ar.Read(&label.font,sizeof(LOGFONT));
			ar>>label.rcRegion;
			ar>>label.strCaption;
			m_TextTables.SetAt(i,label);
		}
		
		//起始默认坐标
		ar.Read(&m_coordRestore,sizeof(COORDINATE));
		m_dMinX = m_coordRestore.dMinX;
		m_dMaxX = m_coordRestore.dMaxX;
		m_dMinY = m_coordRestore.dMinY;
		m_dMaxY = m_coordRestore.dMaxY;
		ar>>m_bTransparentTooltips;
		ar.Read(&m_fontTooltip,sizeof(LOGFONT));
		ar.Read(&m_fontTitle,sizeof(LOGFONT));
		ar.Read(&m_fontLabelX,sizeof(LOGFONT));
		ar.Read(&m_fontLabelY,sizeof(LOGFONT));
		ar.Read(&m_fontLegend,sizeof(LOGFONT));
	}
	else
	{
		ar<<m_nCoordWidth;
		ar<<m_nDivX;
		ar<<m_nDivY;
		ar<<m_nLineWidth;
		
		ar<<m_bVisibleLabelX;
		ar<<m_bVisibleLabelY;
		ar<<m_bVisibleNetX;
		ar<<m_bVisibleNetY;
		ar<<m_bVisibleTitle;
		ar<<m_bVisibleLegend;
		ar<<m_bMouseCross;
		ar<<m_bMouseTooltip;
		ar<<m_bVisibleTooltips;
		ar<<m_bVisibleTextTable;
		
		ar<<m_clrBk;
		ar<<m_clrBkInner;
		ar<<m_clrCoord;
		ar<<m_clrLabelX;
		ar<<m_clrLabelY;
		ar<<m_clrNet;
		ar<<m_clrTitle;
		ar<<m_clrTooltip;
		
		ar<<m_strLabelX;
		ar<<m_strLabelY;
		ar<<m_strTitle;
		ar<<m_strTooltipFormat;
		ar<<m_ptLengend;
		int nTipSize = m_ToolTips.GetSize();
		ar<<nTipSize;
		ar.Write(m_ToolTips.GetData(),nTipSize * sizeof(ToolTip));
		
		int nLabelSize = m_TextTables.GetSize();
		ar<<nLabelSize;
		for(int i = 0 ; i < nLabelSize ; i++)
		{
			ar<<m_TextTables.GetAt(i).bBkTransparent;
			ar<<m_TextTables.GetAt(i).clrText;
			ar<<m_TextTables.GetAt(i).dPosX;
			ar<<m_TextTables.GetAt(i).dPosY;
			ar.Write(&m_TextTables.GetAt(i).font,sizeof(LOGFONT));
			ar<<m_TextTables.GetAt(i).rcRegion;
			ar<<m_TextTables.GetAt(i).strCaption;
		}
		
		ar.Write(&m_coordRestore,sizeof(COORDINATE));
		ar<<m_bTransparentTooltips;
		ar.Write(&m_fontTooltip,sizeof(LOGFONT));
		ar.Write(&m_fontTitle,sizeof(LOGFONT));
		ar.Write(&m_fontLabelX,sizeof(LOGFONT));
		ar.Write(&m_fontLabelY,sizeof(LOGFONT));
		ar.Write(&m_fontLegend,sizeof(LOGFONT));
	}
}

BOOL CGraph::LoadSettings(CString strSettingsFileName)
{
	CFile file;
	BOOL bOpen = file.Open(strSettingsFileName,CFile::modeRead);
	if(!bOpen) {return FALSE;}
	
	try
	{
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
	}
	catch(...)
	{
		file.Close(); return FALSE;
	}
	
	file.Close();	return TRUE;
}


BOOL CGraph::SaveSettings(CString strSettingsFileName)
{
	CFile file;
	BOOL bOpen = file.Open(strSettingsFileName,CFile::modeCreate|CFile::modeReadWrite);
	if(!bOpen){ return FALSE;}
	
	try
	{
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
	}
	catch(...)
	{
		file.Close(); return FALSE;
	}
	file.Close();	return TRUE;
}


/*
BOOL CGraph::LoadSettings(CString strSettingsFileName)
{
	CFile file;
	BOOL bOpen = file.Open(strSettingsFileName,CFile::modeRead);
	if(!bOpen) {return FALSE;}
	
	try
	{
		CArchive ar(&file,CArchive::load);
		
		ar>>m_nCoordWidth;
		ar>>m_nDivX;
		ar>>m_nDivY;
		ar>>m_nLineWidth;
		
		ar>>m_bVisibleLabelX;
		ar>>m_bVisibleLabelY;
		ar>>m_bVisibleNetX;
		ar>>m_bVisibleNetY;
		ar>>m_bVisibleTitle;
		ar>>m_bVisibleLegend;
		ar>>m_bMouseCross;
		ar>>m_bMouseTooltip;
		ar>>m_bVisibleTooltips;
		ar>>m_bVisibleTextTable;
		
		ar>>m_clrBk;
		ar>>m_clrBkInner;
		ar>>m_clrCoord;
		ar>>m_clrLabelX;
		ar>>m_clrLabelY;
		ar>>m_clrNet;
		ar>>m_clrTitle;
		ar>>m_clrTooltip;
		
		ar>>m_strLabelX;
		ar>>m_strLabelY;
		ar>>m_strTitle;
		ar>>m_strTooltipFormat;
		
		int nTipSize;
		ar>>nTipSize;
		ASSERT(nTipSize >= 0);
		m_ToolTips.SetSize(nTipSize);
		ar.Read(m_ToolTips.GetData(),nTipSize * sizeof(ToolTip));
		
		int nLabelSize;
		ar>>nLabelSize;
		ASSERT(nLabelSize >= 0);
		m_TextTables.SetSize(nLabelSize);
		TextTable label;
		for(int i = 0 ; i < nLabelSize ; i++)
		{
			ar>>label.bBkTransparent;
			ar>>label.clrText;
			ar>>label.dPosX;
			ar>>label.dPosY;
			ar.Read(&label.font,sizeof(LOGFONT));
			ar>>label.rcRegion;
			ar>>label.strCaption;
			m_TextTables.SetAt(i,label);
		}
		
		//起始默认坐标
		ar.Read(&m_coordRestore,sizeof(COORDINATE));
		m_dMinX = m_coordRestore.dMinX;
		m_dMaxX = m_coordRestore.dMaxX;
		m_dMinY = m_coordRestore.dMinY;
		m_dMaxY = m_coordRestore.dMaxY;
	}
	catch(...)
	{
		file.Close(); return FALSE;
	}
	
	file.Close();	return TRUE;
}


BOOL CGraph::SaveSettings(CString strSettingsFileName)
{
	CFile file;
	BOOL bOpen = file.Open(strSettingsFileName,CFile::modeCreate|CFile::modeReadWrite);
	if(!bOpen){ return FALSE;}
	
	try
	{
		CArchive ar(&file,CArchive::store);
		
		ar<<m_nCoordWidth;
		ar<<m_nDivX;
		ar<<m_nDivY;
		ar<<m_nLineWidth;
		
		ar<<m_bVisibleLabelX;
		ar<<m_bVisibleLabelY;
		ar<<m_bVisibleNetX;
		ar<<m_bVisibleNetY;
		ar<<m_bVisibleTitle;
		ar<<m_bVisibleLegend;
		ar<<m_bMouseCross;
		ar<<m_bMouseTooltip;
		ar<<m_bVisibleTooltips;
		ar<<m_bVisibleTextTable;
		
		ar<<m_clrBk;
		ar<<m_clrBkInner;
		ar<<m_clrCoord;
		ar<<m_clrLabelX;
		ar<<m_clrLabelY;
		ar<<m_clrNet;
		ar<<m_clrTitle;
		ar<<m_clrTooltip;
		
		ar<<m_strLabelX;
		ar<<m_strLabelY;
		ar<<m_strTitle;
		ar<<m_strTooltipFormat;
		
		int nTipSize = m_ToolTips.GetSize();
		ar<<nTipSize;
		ar.Write(m_ToolTips.GetData(),nTipSize * sizeof(ToolTip));

		int nLabelSize = m_TextTables.GetSize();
		ar<<nLabelSize;
		for(int i = 0 ; i < nLabelSize ; i++)
		{
			ar<<m_TextTables.GetAt(i).bBkTransparent;
			ar<<m_TextTables.GetAt(i).clrText;
			ar<<m_TextTables.GetAt(i).dPosX;
			ar<<m_TextTables.GetAt(i).dPosY;
			ar.Write(&m_TextTables.GetAt(i).font,sizeof(LOGFONT));
			ar<<m_TextTables.GetAt(i).rcRegion;
			ar<<m_TextTables.GetAt(i).strCaption;
		}

		ar.Write(&m_coordRestore,sizeof(COORDINATE));
	}
	catch(...)
	{
		file.Close(); return FALSE;
	}
	file.Close();	return TRUE;
}
*/


BOOL CGraph::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CWnd::OnEraseBkgnd(pDC);
}

void CGraph::SetLine(float *pfX,float *pfY,int nPointNums)
{
// 	m_pfX = pfX;
// 	m_pfY = pfY;
// 	m_nPointNums = nPointNums;
// 	SetContentChanged();
}

void CGraph::SetContentChanged(BOOL bRedraw)
{
	m_bContentChanged = TRUE;
	if( bRedraw ) Invalidate();
}

BOOL CGraph::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{
			if( m_ToolTips.GetSize() <= 0) break;
			int nActiveTip = GetActiveTooltip();
			if( nActiveTip < 0) break;

			if( pMsg->wParam == VK_LEFT)
			{
				ToolTip tip = m_ToolTips.GetAt(nActiveTip);
				tip.dPosX -= (m_dMaxX - m_dMinX) / GetLineRect().Width();
				m_ToolTips.SetAt(nActiveTip,tip);
				SetContentChanged(TRUE);
				return TRUE;
			}

			if( pMsg->wParam == VK_RIGHT)
			{
				ToolTip tip = m_ToolTips.GetAt(nActiveTip);
				tip.dPosX += (m_dMaxX - m_dMinX) / GetLineRect().Width();
				m_ToolTips.SetAt(nActiveTip,tip);
				SetContentChanged(TRUE);
				return TRUE;
			}
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}


void CGraph::SetActiveTooltip(int nIndexTooltip)
{
	int nSizeTip = m_ToolTips.GetSize();
	if( nIndexTooltip < 0 || nIndexTooltip >= nSizeTip ) return;
	ToolTip tip;
	for( int i = 0 ; i < nSizeTip ; i++)
	{
		tip = m_ToolTips.GetAt(i);
		tip.bActive = (i == nIndexTooltip)?TRUE:FALSE;
		m_ToolTips.SetAt(i,tip);
	}
}

int  CGraph::GetActiveTooltip()
{
	int nSizeTip = m_ToolTips.GetSize();
	for( int i = 0 ; i < nSizeTip ; i++)
	{
		if( m_ToolTips.GetAt(i).bActive) return i;
	}
	return -1;
}

void CGraph::OnEnableMovingLine(WPARAM bEnable,LPARAM)
{
	m_bEnableMovingLine = bEnable;
}

BOOL CGraph::SavePrintBMPFile(CString strBMPFileName,int *pnImageWidth,int *pnImageHeight,BOOL bPrint)
{
	COLORREF clrBk,clrInner;
	clrBk    = m_clrBk;
	clrInner = m_clrBkInner;
	if( bPrint)
	{
		m_clrBkInner = RGB(255,255,255);
		m_clrBk      = RGB(255,255,255);
	}
	//	m_rcDraw.SetRect(0,0,684,489);
	if( *pnImageHeight > 100 && *pnImageWidth > 100 )
	{
		m_rcDraw.SetRect(0,0,*pnImageWidth,*pnImageHeight);
	}
	
	CDC *pDC = GetDC();
	HBITMAP hBitmap=CreateCompatibleBitmap(pDC->m_hDC,m_rcDraw.Width(),m_rcDraw.Height());
	
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(hBitmap);
	
	//	Draw(&dc,m_rcDraw);
	{
		CalcRects(m_rcDraw);
		
		pDC->SetBkMode(TRANSPARENT);
		CGraph::DrawBackground(&dc);
		
		CRect cLineRect = GetLineRect();
		if( !cLineRect.IsRectEmpty() )
		{
			DrawCoord(&dc);
			DrawTitle(&dc);
			DrawLabelX(&dc);
			DrawLabelY(&dc);
			DrawLines(&dc);
			DrawTooltips(&dc);
//			DrawActiveTooltip(&dc);
			DrawTextTable(&dc);
			DrawLegend(&dc);
		}
	}
	
	CBitmap bitmap;
	bitmap.Attach(hBitmap);
	
	HANDLE handle=DDBToDIB(bitmap,BI_RGB,NULL);//BI_RGB
	WriteDIB(strBMPFileName,handle);
	
	dc.DeleteDC();
	
	*pnImageWidth  = m_rcDraw.Width();
	*pnImageHeight = m_rcDraw.Height();
	
	m_clrBk      = clrBk;
	m_clrBkInner = clrInner;
	
	return TRUE;
}