#ifndef	_PO_ELBOW_H_
#define	_PO_ELBOW_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DrElbow.h"
#include "Po_FE1D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_Elbow
/////////////////////////////////////////////////////////////////////////////
class CPo_Elbow : public CPo_FE1D
{
// Construction
public:  
	CPo_Elbow();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_Elbow)
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
	CString&	GetCCID(int i){return m_CCID;};
 	void		SetCCID(CString p){m_CCID = p;};
	CString&	GetTIID(int i){return m_TIID;};
 	void		SetTIID(CString p){m_TIID = p;};
	CString&	GetCAID(int i){return m_CAID;};
 	void		SetCAID(CString p){m_CAID = p;};
	CString&	GetCBID(int i){return m_CBID;};
 	void		SetCBID(CString p){m_CBID = p;};

	
protected:

	int			Fill_Data_MeshObjs(CDrFE1D* pNewObj,CDrObject* pMesh,UINT nGenType);		

	

protected:

	/////////////////////////////////////////// Elbow Data
	BOOL		m_bValve;
	CString		m_SIid[MAX_CORNERS_1D];
	CString		m_CCID;
	CString		m_TIID;
	CString		m_CAID;
	CString		m_CBID;


public:
	virtual ~CPo_Elbow(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_Elbow)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif

