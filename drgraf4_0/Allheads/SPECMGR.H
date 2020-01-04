// SpecMgr.h : interface of the CSpecial class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _SPECMGR_H
#define _SPECMGR_H 
///////////////////
#include "booleans.h"
#include "zoom.h"
#include "hitnet.h"
#include "drpen.h"
#include "datawind.h"
#include "layer.h" 
#include "precison.h" 
#include "scalefac.h"  
#include "mapfacto.h"
#include "unit.h"
///////////////////////////////////
class CSpecMgr : public CDrGrafDoc 
{

protected: // create from serialization only
	CSpecMgr();
	DECLARE_DYNCREATE(CSpecMgr)

// Attributes
public:  

	///////////////////////////////////////////////////// TOOLS
	CUnit*			GetUnit(){return &m_Unit;};			 
	CPrecision*		GetPrecision(){return &m_Precision;};			 
	CScaleFactor*	GetScaleFactor(){return &m_ScaleFactor;};			 
	CMapFactor*		GetMapFactor(){return &m_MapFactor;};			 
	CLayer*			GetLayer(){return &m_Layer;};			 
	CDataWindow*	GetDataWindow(){return &m_DataWin;};
	CDrPen*			GetDrPen(){return &m_DrPen;};			 
	CHitNet*		GetHitNet(){return &m_HitNet;};	
	CZoom*			GetZoom(){return &m_Zoom;};	   
	CBooleans*		GetBooleans(){return &m_Booleans;};
	
protected:
 
	/////////////////////////////////////////// OBJECTS
	CUnit			m_Unit; 
	CPrecision		m_Precision;
	CScaleFactor	m_ScaleFactor;
	CMapFactor		m_MapFactor;
	CLayer			m_Layer;
	CDataWindow		m_DataWin;
	CDrPen			m_DrPen; 
	CHitNet			m_HitNet;
	CZoom			m_Zoom;  
	CBooleans		m_Booleans;
    ///////////////////////////
// Operations
public:
// Implementation
public:
	virtual ~CSpecMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

protected: 

// Generated message map functions
protected:
	//{{AFX_MSG(CSpecMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
