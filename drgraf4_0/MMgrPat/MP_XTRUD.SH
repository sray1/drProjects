 // mp_Xtrude.h : header file
//
#ifndef _MP_XTRUD_H 
#define _MP_XTRUD_H 
                    
#include "MI_Pat_I.h"
#include "DrNode.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "glb_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CMP_Xtrud : public CMI_Pat_I
{
public:

	CMP_Xtrud();
	DECLARE_SERIAL(CMP_Xtrud)


// Attributes 

// Operations
public:

// Implementation
public:
 
    				
		
protected:

	////////////////////////////////////////////////////////////
	int 		Extrude(); 
	CDrPatch* 	Extrude_GetInfo();
	int 		Extrude_GenerateCNodes();
	/////////////////////////
		          

protected:  
// Attributes

	PATCHTYPE	m_PatchType;           	// P_MESH,P_EXTRUDE etc
	//////////////////////////////////// ControlNodes Draw
	int			m_nSegs_SCon;
	int			m_nSegs_TCon;
	int			m_nOut_SCon;
	int			m_nOut_TCon;
	long		m_nOutCon;
	/////////////////////////////////////////// Mesh
	BOOL		m_bDirtyPatch; //True: Indivual Elements NOT SAVED yet    
	CDrPatch* 	m_pDrPatch;
	CString 	m_CurrentPatchID;
	int			m_nMaxPatchCNodes;
	int			m_nMaxPatchCNodes_S;
	int			m_nMaxPatchCNodes_T;
	////////////////////////////////
	BOOL		m_bClosed_S;
	BOOL		m_bClosed_T;
	int			m_nSegs_S;
	int			m_nSegs_T;
	int			m_nOut_S;
	int			m_nOut_T;
	int 		m_nCubicPatches_S;
	int 		m_nCubicPatches_T;
	/////////////////////////////////////////// Extrude
	CString		m_FromID;
	CString		m_ToID;
	CString		m_CurveID;
	double		m_dLen;
	WORLD		m_vAxis;  
	//////////////////////////////// Memory Curve/Patch
	CDListMgr* 	m_pCNodeList;
	pWORLD		m_pIn_S[4];
	pWORLD		m_pOut;
	long		m_nOut;
	////////////////////////
//Operations
public:

	~CMP_Xtrud();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Xtrud)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

/////////////////////////////////////////////////////////////////////////////
#endif
