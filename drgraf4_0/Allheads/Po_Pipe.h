#ifndef	_PO_PIPE_H_
#define	_PO_PIPE_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DrPipe.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Pipe
/////////////////////////////////////////////////////////////////////////////
class CPo_Pipe : public CPo_FE1D
{
// Construction
public:  
	CPo_Pipe();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Pipe)
//////////////////////////////////////

protected: 
public:
// Implementation


	
	int			Post_FE1D_Elem(CDrObject* pMesh,UINT nGenType, CDrFE0D* pVert[],pWORLD LocalPos);
	////////////////////////////////////////////////////////////////////////////
	CString&	GetSIid(int i){return m_SIid[i];};
 	void		SetSIid(CString p,int i){m_SIid[i] = p;};
	BOOL 		IsValve(){return m_bValve;};
	void 		SetValve(BOOL b){m_bValve = b;};

	
protected:

	int		Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Pipe Data
	BOOL		m_bValve;
	CString		m_SIid[MAX_CORNERS_1D];


public:
	virtual ~CPo_Pipe(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Pipe)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

