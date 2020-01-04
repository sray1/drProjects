#ifndef	_PO_BEAM_H_
#define	_PO_BEAM_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DrBeam.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Beam
/////////////////////////////////////////////////////////////////////////////
class CPo_Beam : public CPo_FE1D
{
// Construction
public:  
	CPo_Beam();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Beam)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
	int			Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType, CDrFE0D* pVert[],pWORLD LocalPos);
	////////////////////////////////////////////////////////////////////////////
	CString&	GetKNodeID(){return m_KNodeID;};
	void		SetKNodeID(CString& k){m_KNodeID = k;};
	
protected:

	int			Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Beam Data
	CString		m_KNodeID;


public:
	virtual ~CPo_Beam(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Beam)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

