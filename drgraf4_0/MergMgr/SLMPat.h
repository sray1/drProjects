 // ELMouse.h : header file
//
#ifndef _SLE_PAT_H 
#define _SLE_PAT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


                    
#include "SLECur.h"
/////////////////////
#include "DrPatch.h" 	
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CSLEPat : public CSLECur
{
public:

	CSLEPat();
//////////////////////////////////////
	DECLARE_SERIAL(CSLEPat)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 

 	virtual	void		GetObjectInfo(CSLEObj* pObject);
	virtual	void		SetObjectInfo(CSLEObj* pObject);
	/////////////////////////////////////////////////////////////////////////////// PatchStatic
			int			Get_Values_NonIso_Pat(STALPROC StaLProc);
			int			ShowInfo_PatchStaticLoad(CDrPatch* pDrPatch, char* buf, int jStart
																	,CString& CurrentStLID);
			int			ShowPatchStaticLoad(CDrPatch* pCurrentPatch,CString* pID,int nHowMany);
			int			Generate_IsoPatchControls(CDrPatch* pPatchIsoTo,CString* pID,BOOL bTran);
			int			Get_Values_Iso_Pat(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																		CString& CurrentStPID);
				
		
protected:

	int			Get_Values_IsoNod_AnyProc(CString& NodeID,
									STALPROC StaLProc,CString& CurrentStPID,CString& strProc); 
	int			Get_Values_IsoCur_AnyProc(CString& CurveID,int iT,int iR,int IndexSkipNode,
					STALPROC StaLProc,CString& CurrentStPID,CString& strProc,BOOL bLastCurve);
	/////////////////////////////////////////////////////////////////////////////// PatchStatic
	void		RemoveMostListsFromPatch(CDrPatch* pAdd);
	int			Get_Values_Iso_Pat_Curve(CDrCurve* pCurveIsoTo,int indexCT,int indexCR,
					int IndexSkipNode,STALPROC StaLProc,CString& CurrentStPID,BOOL bLastCurve);
	///////////////////////
	int			Get_Values_Iso_EXTRUDE_Type1(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_EXTRUDE_Type2(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_ROTATE(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_LOFT2(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_DUCT(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_SWEEP(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	int			Get_Values_Iso_COONS(CDrPatch* pPatchIsoTo, STALPROC StaLProc,
																	CString& CurrentStPID);
	///////////////////////
	int			SetUp_IsoPatchControls(CDrPatch* pPatchIsoTo,int indexP,CString* pID,BOOL bTran);
	int			Generate_IsoControls_EXTRUDE(CDrPatch* pCurrentSPatch,CString* pID);
	int			Generate_IsoControls_ROTATE(CDrPatch* pCurrentSPatch,CString* pID);
	int			Generate_IsoControls_LOFT2(CDrPatch* pCurrentSPatch,CString* pID);
	int			Generate_IsoControls_DUCT(CDrPatch* pCurrentSPatch,CString* pID);
	int			Generate_IsoControls_SWEEP(CDrPatch* pCurrentSPatch,CString* pID);
	int			Generate_IsoControls_COONS(CDrPatch* pCurrentSPatch,CString* pID);


protected:  
// Attributes


	CView*							m_pView;
	////////////////////////////////////////
	CDListMgr						m_CurveList;		// 
	CList<CURVELATCH,CURVELATCH>	m_LatchList;	
	/////////////////////////////////////////////////////////////////// Patch
	CString		m_CurrentStPID;
	CDrPatch	*m_pCurrentSPatchT[6];	// Iso or NonIso Patch
	CDrPatch	*m_pCurrentSPatchR[6];	// Iso or NonIso Patch
	CDListMgr	m_CurveListT;
	CDListMgr	m_CurveListR;
	WORLD		m_Len_T;
	WORLD		m_Len_R;
	CString		m_FromID_T; 
	CString		m_FromID_R; 
	CString		m_ToID_T; 
	CString		m_ToID_R; 
	//////////////////////////



//Operations
public:

	~CSLEPat();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLEPat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
