// drgradoc.h : interface of the CDrGrafDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _DRGRAFDOC_H
#define _DRGRAFDOC_H
 
////////////////////
#include <afxole.h>		// OLE
///////////////////
#include "ObjMgr.h"
#include "MsObjMgr.h"
#include "DbObjMgr.h"
#include "AxObjMgr.h"
///////////////////////////////////

class CDrGrafSrvrItem;

class CDrGrafDoc : public COleServerDoc
//class CDrGrafDoc : public COleDocument 
{

protected: // create from serialization only
	CDrGrafDoc();
	DECLARE_DYNCREATE(CDrGrafDoc)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//virtual	void DeleteContents();

// Attributes
public:  

	virtual HMENU	GetDefaultMenu();	
	/////////////////////////////////////////
	CDrGrafSrvrItem* GetEmbeddedItem()
		{ return (CDrGrafSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

	///////////////////////////////////////////////////// OBJECT Manager
	CObjectMgr*		GetObjectMgr(){return &m_ObjectMgr;};
	///////////////////////////////////////////////////// MESH Manager
	CMsObjMgr*		GetMsObjMgr(){return &m_MsObjMgr;};
	///////////////////////////////////////////////////// DataBase Manager
	CDbObjMgr*		GetDbObjMgr(){return &m_DbObjMgr;};
	///////////////////////////////////////////////////// AUXI Manager
	CAxObjMgr*		GetAxObjMgr(){return &m_AxObjMgr;};
	///////////////////////////////////////////////////// NEW/OLD Doc File
	void			SetNewDocFile(BOOL bNewFile)
						{ m_bNewDocFile = bNewFile;};
	BOOL			IsNewDocFile(){return m_bNewDocFile;};			


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrGrafDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	virtual BOOL 	OnOpenDocument(const char* pszPathName);
	virtual	void	OnCloseDocument();

	protected:

	virtual	void 	DeleteContents();
			void 	Init();
			void 	ReadDefaults();

public:
	
protected:
 

	///////////////////////////////////////////////////// NEW/OLD DOC File
	BOOL			m_bNewDocFile;
	////////////////////////////
	CObjectMgr		m_ObjectMgr;	
	CMsObjMgr		m_MsObjMgr;	
	CDbObjMgr		m_DbObjMgr;	
	CAxObjMgr		m_AxObjMgr;	
    //////////////////////////// 
    
// Operations
public:
// Implementation
public:
	virtual ~CDrGrafDoc();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnSpecLayer();
	afx_msg void OnSpecObj3d();
	afx_msg void OnUpdateSpecObj3d(CCmdUI* pCmdUI);
	afx_msg void OnSpecPatch();
	afx_msg void OnUpdateSpecPatch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMeshOff(CCmdUI* pCmdUI);
	afx_msg void OnMeshOff();
	afx_msg void OnMeshQuad();
	afx_msg void OnUpdateMeshQuad(CCmdUI* pCmdUI);
	afx_msg void OnMeshLinr();
	afx_msg void OnUpdateMeshLinr(CCmdUI* pCmdUI);
	afx_msg void OnMeshHerm();
	afx_msg void OnUpdateMeshHerm(CCmdUI* pCmdUI);
	afx_msg void OnMeshBspl();
	afx_msg void OnUpdateMeshBspl(CCmdUI* pCmdUI);
	afx_msg void OnMeshBezi();
	afx_msg void OnUpdateMeshBezi(CCmdUI* pCmdUI);
	afx_msg void OnViewDatabaseSheetform();
	afx_msg void OnUpdateViewDatabaseSheetform(CCmdUI* pCmdUI);
	afx_msg void OnSpecDoubleratio();
	afx_msg void OnSpecColinear();
	afx_msg void OnSpecCoplanar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDrGrafDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
