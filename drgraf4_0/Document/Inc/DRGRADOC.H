// drgradoc.h : interface of the CDrGrafDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef DR_GRAF_DOC
#define DR_GRAF_DOC 

 
#include "axisDlg.h"
#include "eyepzDLg.h"
#include "layerDlg.h"
#include "preciDlg.h"
#include "scaleDlg.h"
#include "unitDlg.h"
/////////////////////
#include "mousemgr.h"
///////////////////
#include "globals.h" 
#include "grafobj.h"
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
class CDrGrafDoc : public CDocument 
{

protected: // create from serialization only
	CDrGrafDoc();
	DECLARE_DYNCREATE(CDrGrafDoc)
virtual	void DeleteContents();

// Attributes
public:  

	///////////////////////////////////////////////////// NEW/OLD Doc File
	void			SetNewDocFile(BOOL bNewFile)
						{ m_bNewDocFile = bNewFile;};
	BOOL			IsNewDocFile(){return m_bNewDocFile;};			
	///////////////////////////////////////////////////// Serialize
	void 			SerialDocument(CArchive& ar);
	///////////////////////////////////////////////////// OBJECT Manager
	CGrafObject*	GetObjectMgr(){return &m_ObjectMgr;};
	///////////////////////////////////////////////////// Mouse Manager
	CMouseMgr*		GetMouseMgr(){return &m_MouseMgr;};
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
 
	///////////////////////////////////////////////////// NEW/OLD DOC File
	BOOL			m_bNewDocFile;
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
	////////////////////////////
	CMouseMgr		m_MouseMgr;
	////////////////////////////
	CGrafObject		m_ObjectMgr;	
    ///////////////////////////
// Operations
public:
// Implementation
public:
	virtual ~CDrGrafDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();
	virtual BOOL 	OnOpenDocument(const char* pszPathName);
	virtual	void	OnCloseDocument();
			void 	InitDocument();
			void 	ReadDefaults();
			void 	Initialize();
// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafDoc)
	afx_msg void OnDrawPrecision();
	afx_msg void OnDrawScalefactor();
	afx_msg void OnDrawLayer();
	afx_msg void OnEditClearall();
	afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
	afx_msg void OnOptionsPenchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
