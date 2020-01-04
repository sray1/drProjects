 // ELMouse.h : header file
//
#ifndef _MI_CPROF_H 
#define _MI_CPROF_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrProf_C.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "MI_GangC.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMI_CProf : public CMI_Cur_I
class AFX_EXT_CLASS CMI_CProf : public CMI_GangC
{
public:

	CMI_CProf();
//////////////////////////////////////
	DECLARE_DYNAMIC(CMI_CProf)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
    virtual int 	RBUp_CProfile(CView* pView,UINT nView); // Using Dlg (Not Used for Now)
    virtual int 	RBUp_CProfile(CDrProf_C* pProfile);		// NOT Using Dlg (Used for Now)
	////////////////////////////////////////////
	int				GoDoIt(CDrProf_C* pDrProf);	// All New Control Node Ptrs
												//	(Circular Component Present)
	int				GoDoIt(CDrProf_C* pDrProf,pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
								int nDegree, BOOL bClosed, int nDim); //No New Control Node Ptrs 
												//	(Circular Component Absent)
	int				SaveCoordsWtsinOldFoggies(CDrProf_C* pDrProf,pWORLD pCon_BZ,
																pDOUBLE pWts_BZ,int nCon);
	///
	CDrProf_C*		GetDrProf(){return m_pDrProf;};
	void			SetDrProf(CDrProf_C* p){m_pDrProf = p;};			
	CDrCurve*		GetProfCurve(){return m_pDrCurve;};
	void			SetProfCurve(CDrCurve* p){m_pDrCurve = p;};			
		
protected:

	BOOL			IsAnyCurveClosed();
	CDrProf_C* 		PR_GetInfo();
	int 			InsertProfileInfo();
	///////////////////////////////////////////////////////////////////// DataInfo
	int 			Generate_CurveDataInfo();
	BOOL 			IsClosed();
	int 			FillProfileCurveINodes();
	int				SaveMeshAsNewINodes(pWORLD pMNodes, pDOUBLE pWts, int nMNodes, int nCur, 
						BOOL bLast);
	void 			SetInfoForProfileCurveBase(CDrCurve* pDrObject);
	///////////////////////////////////////////////////////////////////// ControlInfo
	int 			Generate_CurveControlInfo();
	int				GetNumberOfCNodes(CDrProf_C* pDrProf,int nDegree,BOOL bClosed);
	int				Prep_CurveControlInfo(CDrProf_C* pDrProf);
	int				Post_CurveControlInfo(CDrProf_C* pDrProf,pWORLD pCon_BZ,pDOUBLE pWts_BZ,
																			int nCon_BZ);
	BOOL			IsRational(CDrProf_C* pDrProf);
	int				GetTopDegree(CDrProf_C* pDrProf);
	BOOL			IsProfileClosed(CDrProf_C* pDrProf);
	int				Elevate_Profile(CDrProf_C* pDrProf,pWORLD pCon_BZ, pDOUBLE pWts_BZ, 
												int nDegree,BOOL bClosed, int nDim);
	int				GetCNodeCoords_N_Wts(CDrCurve* pCurve, pWORLD pConOld, pDOUBLE pWtsOld);
/*
	int				Elevate_Curve
					(
						pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
						pWORLD pConNew, pDOUBLE pWtsNew,int nSeg_BZ, int nDim
					);
	int				Elevate_BezSeg
					(
						pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
						pWORLD pConNew, pDOUBLE pWtsNew, int nDim
					);
	int				DegreeElevate(pWORLD Con_BZ, pDOUBLE Wts_BZ, int nDegree, 
							 pWORLD NewCon_BZ, pDOUBLE NewWts_BZ, int nDim);
*/
	int				PostNewCNodes(CDrProf_C* pDrProf,pWORLD pCon_BZ, int nCon);
	void			CollectOutputInfo_CONTROL(CList<int,int>& ElperSegList);
	void			Reciprocate_Curves();
	void 			SetInfoForProfileCurveBase_CONTROL(CDrCurve* pDrObject);
	int				MergeComponentCurveEnds(CDrCurve* pDrCurrentCurve,CDrNode* pPrevCurveEndNode);
	int				GenerateProfileINodes(CDrCurve* pProfCurve,CDrProf_C* pDrProf);
	int				GenerateProfileSupport(CDrCurve* pProfCurve,CDrProf_C* pDrProf);
	int				GenerateProfileStatic(CDrCurve* pProfCurve,CDrProf_C* pDrProf);
	//////////////////////////////////////////////////////////////////// Reparametrize
	
protected:
	
	CDrProf_C*	m_pDrProf;
	//////////////////////
	BOOL		m_bBack;
	CString		m_CurveID;
	CURVELATCH	m_CuLatch;
    //////////////////////
	BOOL		m_bUnifOT;
	//////////////////////
	pDOUBLE		m_pOVal;
	pINT		m_pOSeg;
	////////////////////

 	CString		m_CPro_ID;
	CString		m_Orient;
	///////////////////////////
	//	Transformation (NO TRANSFORMATION: kept for Compatibility with CDrProf class
	BOOL		m_bCur_Ist;
	/////////////////////////// Transformation
	double		m_RotX;
	double		m_RotY;
	double		m_RotZ;
	double		m_TranX;
	double		m_TranY;
	double		m_TranZ;
	BOOL		m_bLMat;
 	CDListMgr	m_LMList; 
	/////////////////////// These needed for editing later so save in MatObj
	CString		m_End_NID;	// Connectivity
	CString		m_TranPtID;	// Only for the Ist Curve
//	CString		m_RotPtID;
//	CString		m_FromID;
//	CString		m_ToID;
	CMatObj		m_MatObj;
	MATRIX		m_LocalM;
//	WORLD		m_savRot;
   



//Operations
public:

	~CMI_CProf();
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_CProf)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
