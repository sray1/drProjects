 // CMI_GangN.h : header file
//
#ifndef _MI_GANGN_H 
#define _MI_GANGN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
 
#include "drNode.h"
#include "DrLabel.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_GangN : public CObject
{
public:

	CMI_GangN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_GangN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:

//092798	int			CompareNodeCoords(CDListMgr* pDListMgr,WORLD Pt,BOOL bCNode,BOOL bGen,BOOL bMNode);
	int			CompareNodeCoords(CDListMgr* pDListMgr,WORLD Pt,BOOL bCNode,BOOL bGen);
	void		Setid(CString s){m_id = s;};
	////////////////////////////////////////
//	CDrNode* 	PostNode(CString& Nid,WORLD Pt,BOOL bCNode,BOOL bMNode);//
				// Internal Generation: bMNode = TRUE->LEVEL_KIDDO/FALSE->LEVEL_GRAPA
	CDrNode* 	PostNode(CString& Nid,UINT uLevelType,WORLD Pt,BOOL bCNode);//
 	CDrNode*	CreateNode(CString& Nid,CDrLabel* pLabel,WORLD Pt,BOOL bCNode,BOOL bGen,
//							    BOOL bMNode,int& nNodeIndex, int& nLabelIndex);	//Use for Input
							    int& nNodeIndex, int& nLabelIndex,UINT uLevelType);	//Use for Input
//	CDrLabel*	CreateNodeLabel(CDrNode* pNode,int& nActiveIndex);
	CDrLabel*	CreateNodeLabel(CDrNode* pNode,int& nActiveIndex,UINT uLevelType);
	/////////////////////////////////////////////////// Memory						
	pDOUBLE		FixMemD(long nOut)
				{
					pDOUBLE pOut;
					return ((pOut = new double[nOut]) == NULL)? (pDOUBLE)NULL:pOut;
				};
	
	void 		FreeMemD(pDOUBLE pOut){delete[] pOut;};
	/////////////////////////
	pWORLD 		FixMem(long nOut)
				{
					pWORLD pOut;
					return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
				};
	
	void 		FreeMem(pWORLD pOut)
				{
					if(pOut) 
					delete[] pOut;
				};
	////////////////////////////////////////////////// Posting Helper
//	void		SetInfoForNodeBase(CDrNode* pNode,BOOL bGen,BOOL bMNode);
	void		SetInfoForNodeBase(CDrNode* pNode,BOOL bGen,UINT uLevelType);
//	void		SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel);
	void		SetInfoForNodeLabel(CDrNode* pAddNode,CDrLabel* pLabel,UINT uLevelType);
	void 		SaveINode(CDListMgr* pList,CString* pID);
		          



	

protected:  
// Attributes


	CString		m_id;
	//////////////////////////////////// Posting Nodes
	CString		m_nid_r;
	CString		m_sup_id;
	CString		m_load_id;
//	CString		m_FromID;
//	CString		m_ToID;
	CDrNode*	m_RefNode;
	CDrNode*	m_FromNode;
	CDrNode*	m_ToNode;
	BOOL		m_bFromCN;
	BOOL		m_bToCN;
	double		m_dLength;
	double		m_xWorld;
	double		m_yWorld;
	double		m_zWorld;
	double		m_DxWorld;
	double		m_DyWorld;
	double		m_DzWorld;
	BOOL		m_bnid_c;
 	BOOL		m_bCoord;

//Operations
public:

	~CMI_GangN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_GangN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
