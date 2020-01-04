 // ELMouse.h : header file
//
#ifndef _MI_CURVE_H 
#define _MI_CURVE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMI_Curve : public CObject
{
public:

	CMI_Curve();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_Curve)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual int 	Post_Curve(CDrObject* pObject);
    ///////////////////////////////////////////////////// Curve
	virtual CString	GetCurrentCNodeID(){return m_CurrentCNodeID;};
    virtual void    SetCurrentCNodeID(CString CurrentNodeID)
    				{
    					m_CurrentCNodeID = CurrentNodeID;
    				};
/*?    				 
	virtual CString GetCurrentCurveID(){return m_CurrentCurveID;}; 
    virtual void    SetCurrentCurveID(CString CurrentID)
    				{
    					m_CurrentCurveID = CurrentID;
    				};
*/    				
    /////////////////////////////////////////////
    virtual int 	LBDownInit_CPost(){return 0;}; 
    virtual int 	LBUpCurvePost(){return 0;};
    
    virtual int 	LBDownInit_CEdit(){return 0;}; 
    virtual int 	LBUpCurveEdit(){return 0;}; 
    virtual int 	LBDownInit_CMove(){return 0;}; 
    virtual int 	LBUpCurveMove(){return 0;}; 
	///////////////////////////////////////////// 
    virtual int 	LBDownInit_CInsert(UINT nType); 
    virtual int 	LBUpInit_CInsert(enum CURVEPROC kind); 
    virtual int 	RBDown_CInsert(enum CURVEPROC kind,CView* pView,UINT nView); 
    virtual int 	LBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView); 
    virtual int 	RBUp_CInsert(enum CURVEPROC kind,CView* pView,UINT nView); 
    				
		
protected:

	//////////////////////////////////////////////////////////// Curve/Patch
	int 		PostNodes_FWD();
	int 		InsertAllInfo(enum CURVEPROC kind);
	void 		SaveCNode(CDListMgr* pList,CString* pID);
	CDrCurve* 	C_GetInfo(int nButton);
	/////////////////////////////////////////////////// Memory						
	pWORLD 		FixMem(long nOut)
				{
					pWORLD pOut;
					return ((pOut = new WORLD[nOut]) == NULL)? (pWORLD)NULL:pOut;
				};
	
	void 		FreeMem(pWORLD pOut){delete[] pOut;};
	/////////////////////////
 /*?
/	void 		FillCNodesCoords(CView* pView,int nMaxCNodes);
	void 		ConvertOutPtsToDP(CView* pView);
	/////////////////////////////////////////////// Memory
	int 		FixMemforOutPts()
					{return ((m_pOut = new WORLD[m_nOut]) == NULL)?-1:0;};
	void 		FreeMemforOutPts(){delete[] m_pOut;};
	int			FixMemforCNodes(int nMaxCNodes)
					{return ((m_pIn	 = new WORLD[nMaxCNodes]) == NULL)?-1:0;};
	void 		FreeMemforCNodes(){delete[] m_pIn;};
	int 		FixMemforOutPtsDP()
					{return ((m_pOutDP = new POINT[m_nOut]) == NULL)?-1:0;};
	void 		FreeMemforOutPtsDP(){delete[] m_pOutDP;};
*/	
	//////////////////////////////////////////////////////////// Curve
//?	int 		CurveGen(enum CURVETYPE kind,CView* pView); 

		          

protected:  
// Attributes
protected:


 	/////////////////////////////////////////// CNode     
	int		    m_nCNodeDone;		// for Curve & Patch
	CString 	m_CurrentCNodeID;
	/////////////////////////////////////////// Curve
//?	BOOL		m_bDirtyCurve; //True: Indivual Elements NOT SAVED yet    
	CDrCurve* 	m_pDrCurve;
//?	CString 	m_CurrentCurveID;
	int			m_nMaxCurveCNodes;
	BOOL		m_bClosed;
	int			m_nSegs;
//?	int 		m_nCubicCurves;
	CURVEPROC	m_CurveType; 
/*
	//////////////////////////////// Memory Curve/Patch
	CDListMgr* 	m_pCNodeList;
	pWORLD		m_pIn;
	pWORLD		m_pOut;
	POINT*		m_pOutDP;
	long		m_nOut;
*/	
    /////////////////////////////////////////// Next

//Operations
public:

	~CMI_Curve();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_Curve)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
