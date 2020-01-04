#ifndef	_PO_TR_9_H_
#define	_PO_TR_9_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "Po_FE2D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Tr_9
/////////////////////////////////////////////////////////////////////////////
class CPo_Tr_9 : public CPo_FE2D
{
// Construction
public:  
	CPo_Tr_9();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Tr_9)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
//	int			Do_MeshObjs(CDrObject* pMesh,int nOut,UINT nGenType);				// 1D		
	int			Post_FE2D(CDrObject* pMesh,UINT nGenType,CDrFE0D* pVert[],pWORLD LocalPos);
	////////////////////////////////////////////////////////////////////////////
	
protected:

	int			SetAddlNodeInfo(CDrFE2D* pFE2D,pWORLD LocalPos,CDrObject* pMesh,UINT nGenType);
	int			Fill_Data_MeshObjs(CDrFE2D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Tr_3 Data


public:
	virtual ~CPo_Tr_9(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Tr_9)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

