#ifndef	_PO_FE0D_H_
#define	_PO_FE0D_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "DrObject.h"
#include "DrFE0D.h"
/////////////////////////////////////////////////////////////////////////////
// CPo_FE0D
/////////////////////////////////////////////////////////////////////////////
class CPo_FE0D : public CObject
{
// Construction
public:  
	CPo_FE0D(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CPo_FE0D)
//////////////////////////////////////

protected: 
public:
// Implementation

				  
	int		FillData_0D(CDrFE0D* pNewObj,CDrObject* pMesh,UINT nGenType);
	int		SetElemInfoID(CString& ElemID,UINT nElemType);		



public:

	////////////////////////////////////////////////////////////////////// Members
 	CString&			GetElNumID(){return m_ElNumID;};
 	void				SetElNumID(CString p){m_ElNumID = p;};
 	CString&			GetElTypeID(){return m_ElTypeID;};
 	void				SetElTypeID(CString p){m_ElTypeID = p;};
 	CString&			Getrid(){return m_rid_0;};
 	void				Setrid(CString p){m_rid_0 = p;};
 	CString&			Getpid(){return m_pid;};
 	void				Setpid(CString p){m_pid = p;};
 	CString&			Getmid(){return m_mid;};
 	void				Setmid(CString p){m_mid = p;};
	//////////////////////////////////
	UINT				GetElNum(){return m_ElNum;};				
	void				SetElNum(UINT u){m_ElNum = u;};			
	UINT				GetElTypeNum(){return m_ElTypeNum;};	
	void				SetElTypeNum(UINT u){m_ElTypeNum = u;};	
	UINT				Getrel(){return m_rel_0;};				
	void				Setrel(UINT u){m_rel_0 = u;};			
	UINT				Getprop(){return m_prop;};		
	void				Setprop(UINT u){m_prop = u;};		
	UINT				Getmat(){return m_mat;};		
	void				Setmat(UINT u){m_mat = u;};
	//
	double				GetRefTemp(){return m_refTemp;};				
	void				SetRefTemp(double u){m_refTemp = u;};
	//
	UINT				GetCardNo(){return m_nCardNo;};		
	void				SetCardNo(UINT u){m_nCardNo = u;};
	////////////////////////////////////////////////////////////////////////////////



	
protected:

	
	//////////////////////////////////
	CString		m_ElNumID;	
	CString		m_ElTypeID;			// TRUSS,BEAM,PIPE etc
	CString		m_rid_0;//
	CString		m_pid;  
	CString		m_mid;  
	//////////////////////////////////
	UINT		m_ElNum;				// Element Number
	UINT		m_ElTypeNum;			// id Number: Element Type
	UINT		m_rel_0; 
	UINT		m_prop;           //
	UINT		m_mat;           //
	/////////////////////////
	double		m_refTemp;				//RefrenceTemperature
	////////////////////////////// 
	int			m_nCardNo;
	/////////////////////// Genetics
	UINT		m_GenObjType;	// Mesh0D,Mesh1D,Mesh2D or Mesh3D
	CDrObject*	m_pGenObj;
	////////////////////////

public:
	virtual ~CPo_FE0D(){};
/*
	// Generatioed message map functions
	//{{AFX_MSG(CPo_FE0D)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

