 // ELMouse.h : header file
//
#ifndef _MI_1PROF_H 
#define _MI_1PROF_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrProf_1.h"
#include "DrNode.h"
#include "DrMesh1D.h"
#include "MI_Gang1.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMI_1Prof : public CMI_Cur_I
class CMI_1Prof : public CDrObject
{
public:

	CMI_1Prof();
//////////////////////////////////////
	DECLARE_DYNAMIC(CMI_1Prof)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
    virtual int 	RBUp_1Profile(CDrProf_1* pProfile);		// NOT Using Dlg (Used for Now)
    				
		
protected:

	int 			InsertProfileInfo();
	///////////////////////////////////////////////////////////////////// DataInfo
	int 			Generate_Mesh1DDataInfo();
	int				MergeMesh1Ds();
	int				Copy_Mesh1D(CDrMesh1D* pCopyFrom, CDrMesh1D* pCopyTo);
	int				AppendLists_Mesh1D(CDrMesh1D* pNew, CDrMesh1D* pAppTo);
	int				Compare_N_Change_Mesh1D(CDrMesh1D* pMesh_P,CDrMesh1D* pMesh_S,CDrMesh1D* pMesh_T);
	void			ReciprocateMESH1DNodes(CDListMgr* pList);


	
protected:
	
	CDrProf_1*	m_pDrProf;
	CDrMesh1D*	m_pDrMesh1D;
	//////////////////////
	CString		m_Mesh1DID;
	////////////////////
    
//Operations
public:

	~CMI_1Prof();
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_1Prof)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
