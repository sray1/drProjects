 // ELMouse.h : header file
//
#ifndef _MI_2PROF_H 
#define _MI_2PROF_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrProf_2.h"
#include "DrNode.h"
#include "DrMesh2D.h"
#include "MI_Gang2.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMI_2Prof : public CMI_Cur_I
class CMI_2Prof : public CDrObject
{
public:

	CMI_2Prof();
//////////////////////////////////////
	DECLARE_DYNAMIC(CMI_2Prof)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
    virtual int 	RBUp_2Profile(CDrProf_2* pProfile);		// NOT Using Dlg (Used for Now)
    				
		
protected:

	int 			InsertProfileInfo();
	///////////////////////////////////////////////////////////////////// DataInfo
	int 			Generate_Mesh2DDataInfo();
	int				MergeMesh2Ds();
	int				Copy_Mesh2D(CDrMesh2D* pCopyFrom, CDrMesh2D* pCopyTo);
	int				AppendLists_Mesh2D(CDrMesh2D* pNew, CDrMesh2D* pAppTo);
	int				Compare_N_Change_Mesh2D(CDrMesh2D* pMesh_P,CDrMesh2D* pMesh_S,CDrMesh2D* pMesh_T);
	void			ReciprocateMESH2DNodes(CDListMgr* pList);


	
protected:
	
	CDrProf_2*	m_pDrProf;
	CDrMesh2D*	m_pDrMesh2D;
	//////////////////////
	CString		m_Mesh2DID;
	////////////////////
    
//Operations
public:

	~CMI_2Prof();
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_2Prof)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
