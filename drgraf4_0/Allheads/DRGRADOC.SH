// drgradoc.h : interface of the CDrGrafDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _DRGRAFDOC_H
#define _DRGRAFDOC_H
 
////////////////////
#include <3dhrchy.h>
/////////////////////
#include "mousemgr.h"
///////////////////
#include "ObjMgr.h"
///////////////////////////////////
class CDrGrafDoc : public COleDocument 
{

protected: // create from serialization only
	CDrGrafDoc();
	DECLARE_DYNCREATE(CDrGrafDoc)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//virtual	void DeleteContents();

// Attributes
public:  

	///////////////////////////////////////////////////// OBJECT Manager
	CObjectMgr*		GetObjectMgr(){return &m_ObjectMgr;};
	///////////////////////////////////////////////////// Mouse Manager
	CMouseMgr*		GetMouseMgr(){return &m_MouseMgr;};
	///////////////////////////////////////////////////// NEW/OLD Doc File
	void			SetNewDocFile(BOOL bNewFile)
						{ m_bNewDocFile = bNewFile;};
	BOOL			IsNewDocFile(){return m_bNewDocFile;};			
	///////////////////////////////////////////////////// 

protected:

	virtual	BOOL	OnNewDocument();
	virtual BOOL 	OnOpenDocument(const char* pszPathName);
	virtual	void	OnCloseDocument();
	virtual	void 	DeleteContents();
			void 	Init();
			void 	ReadDefaults();

public:
	hCollection	hC;		// 3d object collection
	RendAttr	RA;		// rendering attributes storage

    virtual void AllocCollection(int nG);
	virtual void AllocGroup		(int ixG,int nP);
    virtual void SetRendAttr	(colorFactor r,colorFactor g,colorFactor b);

	
protected:
 
	///////////////////////////////////////////////////// NEW/OLD DOC File
	BOOL			m_bNewDocFile;
	////////////////////////////
	CMouseMgr		m_MouseMgr;
	////////////////////////////
	CObjectMgr		m_ObjectMgr;	
    //////////////////////////// 
    
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

// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafDoc)
	afx_msg void OnEditClearall();
	afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
	afx_msg void OnSpecAxis();
	afx_msg void OnUpdateSpecAxis(CCmdUI* pCmdUI);
	afx_msg void OnSpecLayer();
	afx_msg void OnUpdateSpecLayer(CCmdUI* pCmdUI);
	afx_msg void OnSpecPaper();
	afx_msg void OnUpdateSpecPaper(CCmdUI* pCmdUI);
	afx_msg void OnSpecPrecision();
	afx_msg void OnUpdateSpecPrecision(CCmdUI* pCmdUI);
	afx_msg void OnSpecScalefactor();
	afx_msg void OnUpdateSpecScalefactor(CCmdUI* pCmdUI);
	afx_msg void OnSpecUnits();
	afx_msg void OnUpdateSpecUnits(CCmdUI* pCmdUI);
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
/*///////////////////////////////////////// Temporarily taken out of AFX_MSG	
	afx_msg void OnDrawPrecision();
	afx_msg void OnDrawScalefactor();
	afx_msg void OnDrawLayer();
	afx_msg void OnEditClearall();
	afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
	afx_msg void OnOptionsPenchange();
*/	
};
/////////////////////////////////////////////////////////////////////////////
#endif
