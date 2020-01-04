#ifndef	_PO_TRUSS_H_
#define	_PO_TRUSS_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DrTruss.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Truss
/////////////////////////////////////////////////////////////////////////////
class CPo_Truss : public CPo_FE1D
{
// Construction
public:  
	CPo_Truss();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Truss)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
	int		Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType, CDrFE0D* pVert[],pWORLD LocalPos);
	////////////////////////////////////////////////////////////////////////////
	
protected:

	int		Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Truss Data


public:
	virtual ~CPo_Truss(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Truss)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

