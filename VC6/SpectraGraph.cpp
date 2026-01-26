// DataGraph.cpp: implementation of the CDataGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpectrumDemo.h"
#include "math.h"
#include "SpectraGraph.h"
#include <wingdi.h> //头文件
#pragma comment (lib,"msimg32.lib") 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CSpectraGraph::CSpectraGraph()
{

	m_strLabelX = "时间 (分钟)";
	m_strLabelY = "电压 (mv)";
	m_strTitle  = "";

	m_nDivY = 12;
	m_nDivX = 12;
	m_clrCoord = RGB(0,100,0) ;
	m_bVisibleTooltips = TRUE;
	
	//m_strTooltipFormat = "x: %x , y: %y , Pixel Index:%p";
	m_strTooltipFormat = "%ux , %uy";
	m_ptLengend.x = 15;
	m_ptLengend.y = 15;

	m_bTransparentTooltips = TRUE;
// 	ToolTip tipDemo;
// 	tipDemo.bVisible = TRUE;
// 	tipDemo.dPosX	 = 600.0f;
// 	m_ToolTips.Add(tipDemo);
// 	SetActiveTooltip(0);

// 	m_strCaption = _T("");
// 	m_nRotateAngle = 0;
// 	memset(&m_font,0,sizeof(LOGFONT));
// 	m_font.lfHeight = 16;
// 	m_font.lfWeight = 300;
// 	strcpy(m_font.lfFaceName,_T("Times New Roman"));
// 	
// 	m_clrBk  = RGB(255,255,255);
// 	m_clrText= RGB(0,0,0); 

	m_bTooltipX = TRUE;
	m_bTooltipXUnit = TRUE;
	m_bTooltipY = TRUE;
	m_bTooltipYUnit = TRUE;
	m_bTooltipPixel = FALSE;

	m_strXName = "波长:";
	m_strYName = "";//m_strYName = "强度:";
	m_strPixelName = "像素值:";

	m_bVisibleWavelengthColor = FALSE;

	m_clrBk	 = ::GetSysColor(COLOR_BTNFACE);//

// 	m_fWavelength.SetSize(CCD_PIXELS);
//	m_fIntensity.SetSize(CCD_PIXELS);
// 
// 	for( int i = 0 ; i < CCD_PIXELS ; i++)
// 	{
// 		m_fWavelength[i] = i;
// 	}

	SetRangeX(0,1200);
	SetRangeY(-1000,70000);

	//波长定标

	
// #define  MAXS_STRING  400
// 	
// 	char chTemp[MAXS_STRING];
// 	::GetModuleFileName(NULL,chTemp,MAXS_STRING);
// 	for(i=strlen(chTemp);i>0;i--)
// 	{
// 		if(chTemp[i-1]=='\\') break;
// 	}
// 		
// 	chTemp[i]='\0';
// 		
// 	CString fname;
// 	fname.Format("%s%s",chTemp,"定标系数.ini");
// 	
// #define COEFFICENT_NUMS 6
// 
// 	//从定标文件.ini 读取定标系数
// 	double dCoeffRead[COEFFICENT_NUMS];
// 	if( TRUE )
// 	{
// 		char strKeyValue[50];
// 		CString strKeyName;
// 		char chDefaultCoeffs[][4]={"100","1","0","0","0","0"};
// 		for(int i=0;i<6;i++)
// 		{
// 			strKeyName.Format("Coefficient%d",i);
// 			GetPrivateProfileString("Calibration",strKeyName,chDefaultCoeffs[i],strKeyValue,50,fname);
// 			dCoeffRead[i]=(float)atof(strKeyValue);
// 		}
// 	}
// 	
// 	//波长定标
// 	for(  i = 0 ; i < CCD_PIXELS ; i++)
// 	{
// 		m_fWavelength[i] =(float)(
// 			dCoeffRead[0]
// 			+dCoeffRead[1]*pow(i,1)
// 			+dCoeffRead[2]*pow(i,2)
// 			+dCoeffRead[3]*pow(i,3)
// 			+dCoeffRead[4]*pow(i,4)
// 			+dCoeffRead[5]*pow(i,5));
// 	}
		
}

CSpectraGraph::~CSpectraGraph()
{
	
}

BEGIN_MESSAGE_MAP(CSpectraGraph, CGraph)
//{{AFX_MSG_MAP(CSpectraGraph)
	ON_COMMAND(WM_UNZOOM_X,OnUnZoomX)
	ON_COMMAND(WM_UNZOOM_Y,OnUnZoomY)
	ON_COMMAND(WM_UNZOOM,OnUnZoom)
	ON_WM_RBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
//
// Draw Related Functions
//
void CSpectraGraph::DrawLabelX(CDC *pDC)
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
	
	m_strLabelX = "波长nm";

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

void CSpectraGraph::DrawLabelY(CDC *pDC)
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
	
	m_strLabelY = "强度counts";

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

void CSpectraGraph::DrawLines(CDC *pDC)
{
	if( m_dWavelength.GetSize() < 2) return;
	
	m_rgn.DeleteObject(); 
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
	

	//Draw Spectra lines 画线
	CPen  *pOldPen;
	int    nSize = m_dWavelength.GetSize();

	int  nOldBkMode = pDC->SetBkMode(TRANSPARENT);

	//准备画笔
	m_pen.DeleteObject();
	m_pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	pOldPen = pDC->SelectObject(&m_pen);

	POINT posCurrent;
	posCurrent.x = (long)(dCalcX + m_dWavelength[0] * dRatioX);
	posCurrent.y = (long)(dCalcY - m_dIntensity[0] * dRatioY);
	int xLastPoint = posCurrent.x;
	pDC->MoveTo(posCurrent);
			
	for( register int i = 1 ; i < nSize ; i++)
	{
		posCurrent.x = (long)(dCalcX + m_dWavelength[i] * dRatioX );
		//if( posCurrent.x == xLastPoint) continue;
		xLastPoint  = posCurrent.x;
		posCurrent.y = (long)(dCalcY - m_dIntensity[i] * dRatioY);
		pDC->LineTo(posCurrent);
	}
	pDC->SelectObject(pOldPen);	 
	
	pDC->SetBkMode(nOldBkMode);  
	pDC->SelectClipRgn(NULL);
}


/*
void CSpectraGraph::DrawTooltips(CDC *pDC)
{
	if(!m_bVisibleTooltips) return;
	
	CRect rcLine = GetLineRect();

	//画十字架
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	CPen pen,penActive;
	CPen *pOldPen;
	COLORREF clrPen = RGB( 255 - GetRValue(m_clrBkInner),
		255 - GetGValue(m_clrBkInner),
		255 - GetBValue(m_clrBkInner));
	pen.CreatePen(PS_SOLID,1,m_clrTooltip);
//	penActive.CreatePen(PS_SOLID,1,RGB(255,0,0));
	penActive.CreatePen(PS_SOLID,1,clrPen);
	pOldPen = pDC->SelectObject(&pen);
	int nToopTipSize = m_ToolTips.GetSize();
	int xPosTooltip;
	for( int i = 0 ; i < nToopTipSize ; i++)
	{
		xPosTooltip = ValueToPointX(m_ToolTips.GetAt(i).dPosX);
		// if( m_ToolTips.GetAt(i).bActive )
		if( i == 0 )
		{
			pDC->SelectObject(&penActive);
		}
		else
		{
			pDC->SelectObject(&pen);
		}
		if( xPosTooltip < rcLine.left || xPosTooltip > rcLine.right) continue;
		pDC->MoveTo(xPosTooltip,rcLine.bottom);
		pDC->LineTo(xPosTooltip,rcLine.top);
		int iInitX = xPosTooltip;
		COLORREF clrOuter = RGB(0,0,85);
		COLORREF clrInner = RGB(255,255,0);
		int iInitY = rcLine.top-1;
		pDC->SetPixel(iInitX,iInitY,clrOuter);
		for( int k = 1 ; k < 5 ; k++)
		{
			for( int u = -k ; u <= k ; u++)
			{
				pDC->SetPixel(iInitX+u,iInitY-k,clrInner);
			}
			pDC->SetPixel(iInitX+k,iInitY-k,clrOuter);
			pDC->SetPixel(iInitX-k,iInitY-k,clrOuter);
		}
		for( int u = -k ; u <= k ; u++)
		{
			pDC->SetPixel(iInitX+u,iInitY-k,clrOuter);
		}
		pDC->MoveTo(xPosTooltip,rcLine.bottom);
		pDC->LineTo(xPosTooltip,rcLine.top);
	}
	
	pDC->SelectObject(pOldPen);	
	pen.DeleteObject();
	penActive.DeleteObject();


	//画数据(x,y)
	int xData,yData;
	int nLineNums = m_pData->GetLineNums();
	CFont tipFont;
	tipFont.CreateFontIndirect(&m_fontTooltip);
	CFont *pOldFont   = pDC->SelectObject(&tipFont);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	double dCoordX;double dIntensity;
	CString strX,strY,strPixel;
	int nMaxTextExt;

	int cyFont  = pDC->GetTextExtent("a").cy;
	for( int j = 0 ; j < nToopTipSize ; j++)
	{
		int yDataOutput = rcLine.top + 3;
		for( i = 0 ; i < nLineNums ; i++)
		{
			if( !m_pData->IsValidLine(i))   continue;
			if( !m_pData->IsVisibleLine(i)) continue;
		
			dCoordX		= m_ToolTips.GetAt(j).dPosX;
			dIntensity  = m_pData->GetYAtX((float)dCoordX,i);
			yData = ValueToPointY(dIntensity);
			
			yDataOutput = yDataOutput + cyFont; 

			strPixel = "";
			strX = "";
			strY = "";
			nMaxTextExt = 0;
			if(m_bTooltipPixel)
			{
				strPixel.Format("%s %d",m_strPixelName,m_pData->XtoIndex((float)dCoordX,i));
				nMaxTextExt = max(nMaxTextExt,pDC->GetTextExtent(strPixel).cx);
			}
			
			if( m_bTooltipY)
			{
				CString strDecimalFormat;
				strDecimalFormat.Format(".%df",m_pData->GetDecimalY(i));
				//strY.Format("%d: %" + strDecimalFormat,i+1,dIntensity);
				strY.Format("%" + strDecimalFormat,dIntensity);
				//strY.Format("%s%.2f",m_strYName,dIntensity);
				if( m_bTooltipYUnit )
					strY  = strY + " " + m_pData->GetUnitY();
				nMaxTextExt = max(nMaxTextExt,pDC->GetTextExtent(strY).cx);
			}
			
			pDC->SetTextColor(m_pData->GetSpectraLineColor(i));
			xData = ValueToPointX(dCoordX);
			
			if( !rcLine.PtInRect(CPoint(xData,yData))) continue;
			
			int nOldMode;
			if( m_bTransparentTooltips)
				nOldMode = pDC->SetBkMode(TRANSPARENT);
			else 
				nOldMode = pDC->SetBkMode(OPAQUE);
			
			int yBottom = yDataOutput - cyFont + cyFont + 2;
			
			int xLeft = xData+4;
			if( xData + nMaxTextExt > rcLine.right )
				xLeft -= nMaxTextExt;
			
			
			if( m_bTooltipY)
			{
				pDC->TextOut(xLeft,yBottom,strY);
				//yBottom -= cyFont;
			}

			if(m_bTooltipPixel)
			{
				pDC->TextOut(xLeft + pDC->GetTextExtent(strY).cx + 5,yBottom,strPixel);
				//yBottom -= cyFont;
			}

			pDC->Ellipse(xData-4,yData-4,xData+4,yData+4);
			pDC->SetBkMode(nOldMode);
		}	
	}


	//画X坐标(单个)
	if(m_bTooltipX)
	{
		for( j = 0 ; j < nToopTipSize ; j++)
		{
			dCoordX	= m_ToolTips.GetAt(j).dPosX;
			
			strX.Format("%.1f",dCoordX);
			if( m_bTooltipXUnit )
				strX  = strX +  " " + m_pData->GetUnitX();
		
			xData = ValueToPointX(dCoordX);
			if( xData <= rcLine.left || xData >= rcLine.right ) continue;
			
			int nOldMode;
			if( m_bTransparentTooltips)
				nOldMode = pDC->SetBkMode(TRANSPARENT);
			else 
				nOldMode = pDC->SetBkMode(OPAQUE);

			COLORREF clrOld = pDC->SetTextColor(RGB(0,0,0));
			pDC->TextOut(xData + 4,rcLine.top,strX);
			pDC->SetTextColor(clrOld);
			pDC->SetBkMode(nOldMode);	
		}
	}
	
	//移动tooltip 指示
	if( m_bMovingTooltip && !m_bTooltipX)
	{
		POINT ptCursor;
		GetCursorPos(&ptCursor); ScreenToClient(&ptCursor);
		if( rcLine.PtInRect(ptCursor))
		{
			ASSERT(m_nIndexMovingTooltip >= 0);
			CString strMovingPosX;
			ToolTip tipMoving = m_ToolTips.GetAt(m_nIndexMovingTooltip);
			int xPos = ValueToPointX(tipMoving.dPosX);
			strMovingPosX.Format("%.2f%s",tipMoving.dPosX,m_pData->GetUnitX());
			pDC->SetTextColor(RGB(
				255 - GetRValue(m_clrBkInner),
				255 - GetGValue(m_clrBkInner),
				255 - GetBValue(m_clrBkInner)));
			pDC->TextOut(xPos + 2,ptCursor.y + 6,strMovingPosX);
		}
	}
	
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont); 
	tipFont.DeleteObject();
}
*/

// 
// void CSpectraGraph::DrawLegend(CDC *pDC)
// {
// 	if( !m_bVisibleLegend) return;
// 
// 	ASSERT( m_pData != NULL);
// 	
// 	CRect rcLine = GetLineRect();
// 
// 	CFont fontLegend;
// 	fontLegend.CreateFontIndirect(&m_fontLegend);
// 	CFont *pOldFont  = pDC->SelectObject(&fontLegend);
// 	
// 	int xLegendLeft,yLegendTop,xLegendRight,yLegendBottom;
// 	
// 	int nLineNums		= m_pData->GetLineNums();
// 	int nValidLineNums	= 0;
// 	CSize nTextSize;
// 	int cxMaxText = 0;
// 	for(int j = 0; j < nLineNums; j++)
// 	{
// 		if( m_pData->IsValidLine(j) && m_pData->IsVisibleLine(j))
// 		{
// 			nValidLineNums++;
// 			nTextSize = pDC->GetTextExtent(m_pData->GetSpectraLineName(j));
// 			cxMaxText = max(nTextSize.cx,cxMaxText);
// 		}
// 	}
// 
// 	if( nValidLineNums <= 0) 
// 	{
// 		m_rcLegend.SetRect(0,0,0,0);
// 		pDC->SelectObject(*pOldFont); fontLegend.DeleteObject(); return;
// 	}
// 	
// 	nTextSize		= pDC->GetTextExtent("a");
// 	xLegendLeft		= m_ptLengend.x + rcLine.left;
// 	yLegendTop		= m_ptLengend.y + rcLine.top;
// 	xLegendRight	= xLegendLeft + cxMaxText + 50;
// 	yLegendBottom	= yLegendTop + (nTextSize.cy + 2)  * nValidLineNums + 10 - 2;
// 	
// 	m_rcLegend.SetRect(xLegendLeft,yLegendTop,xLegendRight,yLegendBottom);
// 
// 	pDC->Rectangle(xLegendLeft, yLegendTop, xLegendRight,yLegendBottom);
// 	
// 	CString strText;
// 	int yLineTop;
// 	CRect rcColor;
// 	
// 	yLineTop = yLegendTop + 5;
// 	for(int n = 0; n < nLineNums; n++)
// 	{
// 		if( !m_pData->IsValidLine(n))	continue;
// 		if( !m_pData->IsVisibleLine(n))	continue;
// 		
// 
// 		CPen pen;pen.CreatePen(m_pData->GetSpectraLineStyle(n),1,m_pData->GetSpectraLineColor(n));
// 		CPen *pOldPen = pDC->SelectObject(&pen);
// 		pDC->MoveTo(xLegendLeft+5,yLineTop+7);
// 		pDC->LineTo(xLegendLeft+35,yLineTop+7);
// 
// 		pDC->SetTextColor(RGB(50,50,50));
// 	
// 		strText = m_pData->GetSpectraLineName(n);
// 		pDC->TextOut(xLegendLeft + 40, yLineTop,strText);
// 
// 		yLineTop  += nTextSize.cy + 2;
// 		pDC->SelectObject(pOldPen); pen.DeleteObject();
// 	}
// 
// 	pDC->SelectObject(*pOldFont); fontLegend.DeleteObject();
// }

/*
void CSpectraGraph::DrawLegend(CDC *pDC)
{
	if( !m_bVisibleLegend) return;
	

	CRect rcLine = GetLineRect();
	
	CFont fontLegend;
	fontLegend.CreateFontIndirect(&m_fontLegend);
	CFont *pOldFont  = pDC->SelectObject(&fontLegend);
	
	int xLegendLeft,yLegendTop,xLegendRight,yLegendBottom;
	
	int nLineNums		= m_pData->GetLineNums();
	int nValidLineNums	= 0;
	CSize nTextSize;
	int cxMaxText = 0;
	for(int j = 0; j < nLineNums; j++)
	{
		if( m_pData->IsValidLine(j) && m_pData->IsVisibleLine(j))
		{
			nValidLineNums++;
			nTextSize = pDC->GetTextExtent(m_pData->GetSpectraLineName(j));
			cxMaxText = max(nTextSize.cx,cxMaxText);
		}
	}
	
	if( nValidLineNums <= 0) 
	{
		m_rcLegend.SetRect(0,0,0,0);
		pDC->SelectObject(*pOldFont); fontLegend.DeleteObject(); return;
	}
	
	nTextSize		= pDC->GetTextExtent("a");
	xLegendLeft		= m_ptLengend.x + rcLine.left;
	yLegendTop		= m_ptLengend.y + rcLine.top;
	xLegendRight	= xLegendLeft + cxMaxText + 40 + 18  ;
	yLegendBottom	= yLegendTop + (nTextSize.cy + 2)  * nValidLineNums + 10 - 2;
	
	m_rcLegend.SetRect(xLegendLeft,yLegendTop,xLegendRight,yLegendBottom);
	

	//

	//////////////
	HBITMAP hBendBMP = CreateBitmap(m_rcLegend.Width(),m_rcLegend.Height(),8,4,NULL); //创建单色掩码位图
	HDC hAlphaBendDC = CreateCompatibleDC(pDC->m_hDC); //创建设备句柄
	HBITMAP hBendOldBMP=(HBITMAP)SelectObject(hAlphaBendDC, hBendBMP);
	CDC *pBlendDC = CDC::FromHandle(hAlphaBendDC);

	CString strText;
	CRect rcColor;

	CFont *pOldFontBlend  = pBlendDC->SelectObject(&fontLegend);
	pBlendDC->Rectangle(0, 0, m_rcLegend.Width(),m_rcLegend.Height());
	
	int yLineTop = 5;
	int nLineWidth;
	for(int n = 0; n < nLineNums; n++)
	{
		if( !m_pData->IsValidLine(n))	continue;
		if( !m_pData->IsVisibleLine(n))	continue;
		
		nLineWidth = m_pData->GetSpectraLineWidth(n);
		CPen pen;pen.CreatePen(m_pData->GetSpectraLineStyle(n),
			nLineWidth,//1,
			m_pData->GetSpectraLineColor(n));
		CPen *pOldPen = pBlendDC->SelectObject(&pen);
		pBlendDC->MoveTo( 5,yLineTop+7+nLineWidth/2);
		pBlendDC->LineTo(35,yLineTop+7+nLineWidth/2);
		
		//pBlendDC->SetTextColor(RGB(50,50,50));
		pBlendDC->SetTextColor(RGB(0,0,0));
		
		strText = m_pData->GetSpectraLineName(n);
		pBlendDC->TextOut(40, yLineTop,strText);
		
		yLineTop  += nTextSize.cy + 2;
		pBlendDC->SelectObject(pOldPen); pen.DeleteObject();
	}
	pBlendDC->SelectObject(*pOldFontBlend); 


	BLENDFUNCTION  blend;
	memset( &blend, 0, sizeof( blend) );
	blend.BlendOp= AC_SRC_OVER;
	blend.SourceConstantAlpha= 135; //透明值
	
	AlphaBlend(pDC->m_hDC,m_rcLegend.left,m_rcLegend.top,m_rcLegend.Width(),m_rcLegend.Height()
			,hAlphaBendDC,0,0,m_rcLegend.Width(),m_rcLegend.Height(),blend);

	DeleteObject(hBendOldBMP);
	DeleteObject(hBendBMP);
	DeleteObject(hAlphaBendDC);

	pDC->SelectObject(*pOldFont);
	fontLegend.DeleteObject();
	
}

*/

void CSpectraGraph::OpenSettingsReg(CString strSection)
{

}	

void CSpectraGraph::SaveSettingsReg(CString strSection)
{

}


void CSpectraGraph::Serialize(CArchive& ar)
{
	CGraph::Serialize(ar);

	if( ar.IsLoading())
	{
		ar>>m_bTooltipX>>m_bTooltipXUnit;
		ar>>m_bTooltipY>>m_bTooltipYUnit;
		ar>>m_bTooltipPixel;
	}
	else
	{
		ar<<m_bTooltipX<<m_bTooltipXUnit;
		ar<<m_bTooltipY<<m_bTooltipYUnit;
		ar<<m_bTooltipPixel;
	}
}



void CSpectraGraph::OnUnZoom()
{
	UnZoomX();
	UnZoomY();
	
	m_aCoord.RemoveAll();
	RecordCoordinate();
	
	SetContentChanged(TRUE);
}

void CSpectraGraph::OnUnZoomX()
{
	UnZoomX();
	
	SetContentChanged(TRUE);
}

void CSpectraGraph::OnUnZoomY()
{
	UnZoomY();
	SetContentChanged(TRUE);
}

void CSpectraGraph::UnZoomX()
{
// 	float fMaxWave = -0;
// 	float fMinWave = 100000;
// 	float fTempMin,fTempMax;
// 	for( int i = 0; i < MAX_LINES ; i++)
// 	{
// 		if( m_pData->IsValidLine(i)&& m_pData->IsVisibleLine(i))
// 		{
// 			fTempMin = m_pData->GetWavelengthAt(0,i);
// 			fTempMax = m_pData->GetWavelengthAt(m_pData->GetLineSize(i)-1,i);
// 
// 			fMaxWave = max(fMaxWave,max(fTempMax,fTempMin));
// 			fMinWave = min(fMinWave,min(fTempMin,fTempMax));
// 		}
// 	}
// 	
// 	float fMinX;
// 	float fMaxX;
// 	switch(m_pData->GetTypeX())
// 	{
// 	case Wavelength_nm:
// 		{
// 			fMinX = fMinWave; fMaxX = fMaxWave;
// 			break;
// 		}
// 	case THz:
// 		{
// 			fMinX = m_pData->WavelengthToX(fMaxWave);
// 			fMaxX = m_pData->WavelengthToX(fMinWave);
// 			break;
// 		}
// 	case cm_1:
// 		{
// 			fMinX = m_pData->WavelengthToX(fMaxWave);
// 			fMaxX = m_pData->WavelengthToX(fMinWave);
// 			break;
// 		} 
// 	}
// 	//SetRangeX(fMinWave,fMaxWave);
// 	SetRangeX(fMinX-(fMaxX-fMinX)*0.1,fMaxX+(fMaxX-fMinX)*0.1);

	//SetRangeX(m_coordRestore.dMinX,m_coordRestore.dMaxX);
	SetRangeX(0,max(1200,1.1*m_dWavelength[m_dWavelength.GetSize()-1]));
}

void CSpectraGraph::UnZoomY()
{
	SetRangeY(-1000,70000);
// 	float fMaxY = 0;
// 	float fMinY = 100000;
// 	for( int i = 0; i < MAX_LINES ; i++)
// 	{
// 		if( m_pData->IsValidLine(i)&& m_pData->IsVisibleLine(i))
// 		{
// 			fMaxY = max(fMaxY,m_pData->GetMaxValueY(i));
// 			fMinY = min(fMinY,m_pData->GetMinValueY(i));
// 		}
// 	}
// 
// 	//SetRangeY(fMinY,fMaxY+ 0.2 *(fMaxY-fMinY));
// 	//SetRangeY(fMinY - 0.05 *(fMaxY-fMinY),fMaxY + 0.2 *(fMaxY-fMinY));
// 	//SetRangeY(0,fMaxY*1.2);
// 	SetRangeY(-0.05 * fMaxY,fMaxY*1.2);
	
	//SetRangeY(m_coordRestore.dMinY,m_coordRestore.dMaxY);
}

void CSpectraGraph::Boxcar(int nPixelSpan)
{
	int nSize = m_dWavelength.GetSize();
	
	if( nSize < 100)	return;
	
	//Special Deal;
	//nPixelSpan += BOXCAR_DEAL;
	if( nPixelSpan==0 )		return;
	
	// Boxcar(float *content,int num)             //加权相加
	
	int   i,j,n,pixel=7;
	CArray<float,float> temp;	temp.SetSize(nSize);
	float *temp_content = temp.GetData();
	float temp_use;
	float all=0;
	float radio[7];
	
	radio[2]=radio[4]=(float)(6+nPixelSpan/2);
	radio[1]=radio[5]=(float)(3+nPixelSpan/2);
	radio[0]=radio[6]=(float)(1+nPixelSpan/2);
	radio[3]=10;
	
	for( n=0 ; n < nPixelSpan; n++)
	{
		for( i = 0; i < nSize ; i++)
		{
			temp_content[i]=m_dIntensity.GetAt(i);
		}
		for( i = 0; i<nSize-pixel; i++)
		{
			temp_use=0;
			all=0;
			for(j=0;j<pixel;j++)
				if(i+j-pixel/2>=0)
				{
					temp_use += (float)(1.0*radio[j]*temp_content[i+j-pixel/2]);
					all+=radio[j];
				}
				m_dIntensity.SetAt(i,(float)(1.0*temp_use/all));
				//	content[i]=(float)(1.0*temp_use/all);
		}
	}
}