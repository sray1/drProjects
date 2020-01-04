#ifndef	_PO_QU_4_H_
#define	_PO_QU_4_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "Po_FE2D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Qu_4
/////////////////////////////////////////////////////////////////////////////
class CPo_Qu_4 : public CPo_FE2D
{
// Construction
public:  
	CPo_Qu_4();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Qu_4)
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

	/////////////////////////////////////////// Qu_4 Data


public:
	virtual ~CPo_Qu_4(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Qu_4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

