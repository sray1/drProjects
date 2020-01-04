 // ELMouse.h : header file
//
#ifndef _SLD_CUR_H 
#define _SLD_CUR_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SLDNod.h"
/////////////////////
#include "DrCurve.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CSLDCur : public CSLDNod
{
public:

	CSLDCur();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDCur)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual	void		GetObjectInfo(CSLDObj* pObject);
	virtual	void		SetObjectInfo(CSLDObj* pObject);
	/////////////////////////////////////////////////////////////////////////////// CurveStatic
			int			Get_Values_Iso_Node(CDrNode* pNodeIsoTo,STALPROC StaLProc,CString& CurrentID);
			int			Get_Values_NonIso_Cur(STALPROC StaLProc);
			int			Get_Values_Iso_Cur(CDrCurve* pCurveIsoTo, STALPROC StaLProc, int IndexSkipNode,
																	BOOL bLastCurve);
			int			ShowCurveStaticLoad(CDrCurve* pCurrentCurve,CString* pID);
			int			ShowInfo_CurveStaticLoad(CDrCurve* pDrCurve, char* buf, int jStart,
																			CString& CurrentStLID);
			int			Generate_IsoCurveControls(CDrCurve* pCurveIsoTo,int indexC,CString* pID,
																						BOOL bTran);

		
protected:


	void		RemoveMostListsFromCurve(CDrCurve* pAdd);


protected:  
// Attributes


	BOOL		m_bAdvanceOn;		
	CDListMgr	m_NodeList;
	CList<int,int>	m_ElSegList;
	////////////////////////////
	CDrNode*	m_pSNodeT;
	CDrNode*	m_pSNodeR;
	////////////////////////////////////////////////////////////////// Curve
	CDListMgr	m_NodeListT;
	CDListMgr	m_NodeListR;
	/////////////////////////////////////////// Static
	CDrCurve*	m_pCurrentSCurveT[4];	// Iso or NonIso curve
	CDrCurve*	m_pCurrentSCurveR[4];	// Iso or NonIso curve
	/////////////////////////////////////////// Circle
	CIRCLETYPE	m_CircType;
	int			m_nMesh;
	double		m_SegAngle;
	BOOL		m_bAutoSeg;
	double		m_dAngSpec;
	BOOL		m_bArc;
	double		m_dAng;	
	CString		m_FromID;
	CString		m_ToID;	
	CString		m_TIID;
	CString		m_CCID;	
	CString		m_CAID;
	CString		m_CBID;	
	UINT		m_NodeType;	// NODE or CNODE
	double		m_dRadius;



//Operations
public:

	~CSLDCur();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDCur)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif