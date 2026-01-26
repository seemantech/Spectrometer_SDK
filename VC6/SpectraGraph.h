// DataGraph.h: interface for the CDataGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAGRAPH_H__7449485A_BF98_425F_A5DE_4141B6CD0E83__INCLUDED_)
#define AFX_DATAGRAPH_H__7449485A_BF98_425F_A5DE_4141B6CD0E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Graph.h"

class CSpectraGraph : public CGraph  
{
public:
	CSpectraGraph();
	virtual ~CSpectraGraph();

protected:
	virtual	void DrawLabelX(CDC *pDC);
	virtual	void DrawLabelY(CDC *pDC);

public:
	virtual void OpenSettingsReg(CString strSection);
	virtual void SaveSettingsReg(CString strSection);
	virtual void DrawLines(CDC *pDC);
/*	virtual void DrawLegend(CDC *pDC);*/
// 	virtual void DrawTooltips(CDC *pDC);
// 	virtual void DrawMouseTooltips(CDC *pDC);
protected:
	//{{AFX_MSG(CSpectraGraph)
	//}}AFX_MSG
	afx_msg void OnUnZoomX();
	afx_msg void OnUnZoomY();
	afx_msg void OnUnZoom();
//	void OnRButtonUp(UINT nFlags, CPoint point);
 	DECLARE_MESSAGE_MAP()
protected:
public:
	CArray<double,double> m_dWavelength;
	CArray<double,double> m_dIntensity;
	void Boxcar(int nPixelSpan);
public:
//	virtual	void	SetRangeRestore (double dMinX,double dMaxX,double dMinY, double dMaxY,BOOL bApply = FALSE);
//	virtual	void	SetRangeRestoreY(double dMinY, double dMaxY,BOOL bApply = FALSE);
//	virtual	void	SetRangeRestoreX(double dMinX,double dMaxX,BOOL bApply = FALSE);
//	void			UseSpectraDataRestore(BOOL bApply = FALSE);
public:
	BOOL m_bTooltipX;
	BOOL m_bTooltipXUnit;
	BOOL m_bTooltipY;
	BOOL m_bTooltipYUnit;
	BOOL m_bTooltipPixel;
	CString m_strXName;
	CString m_strYName;
	CString m_strPixelName;
protected:
	virtual void Serialize(CArchive& ar);
protected:
	BOOL m_bVisibleWavelengthColor;
public:
	BOOL IsVisibleWavelengthColor(){return m_bVisibleWavelengthColor;}
	void SetVisibleWavelengthColor(BOOL bVisible){m_bVisibleWavelengthColor = bVisible;}
protected:
	void UnZoomX();
	void UnZoomY();
};

#endif // !defined(AFX_DATAGRAPH_H__7449485A_BF98_425F_A5DE_4141B6CD0E83__INCLUDED_)
