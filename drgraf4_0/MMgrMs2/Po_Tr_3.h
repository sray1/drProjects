#ifndef	_PO_TR_3_H_
#define	_PO_TR_3_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "Po_FE2D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Tr_3
/////////////////////////////////////////////////////////////////////////////
class CPo_Tr_3 : public CPo_FE2D
{
// Construction
public:  
	CPo_Tr_3();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Tr_3)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
//	int			Do_MeshObjs(CDrObject* pMesh,int nOut,UINT nGenType);				// 1D		
	int			Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);
	////////////////////////////////////////////////////////////////////////////
	
protected:

	int			Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Tr_3 Data


public:
	virtual ~CPo_Tr_3(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Tr_3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

