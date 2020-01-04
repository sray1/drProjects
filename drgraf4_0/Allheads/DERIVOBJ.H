#ifndef	_DERIVOBJ_H_
#define	_DERIVOBJ_H_


#include "glb_Type.h"
/////////////////////////////////////////////////////////////////////////////
// CDerivObj
/////////////////////////////////////////////////////////////////////////////
class CDerivObj : public CObject
{
// Construction
public:  
	CDerivObj();
	DECLARE_DYNAMIC(CDerivObj)
public:

	virtual double	GetParam(){return m_Param;};
	virtual void	SetParam(double dd){m_Param = dd;};
	virtual WORLD	GetTangent(){return m_Tangent;};
	virtual void	SetTangent(WORLD dd)
						{
							m_Tangent.x = dd.x;
							m_Tangent.y = dd.y;
							m_Tangent.z = dd.z;
						};
	virtual double	GetCurvature(){return m_Curvature;};
	virtual void	SetCurvature(double dd){m_Curvature = dd;};


	
protected:

	////////////////////////
	
	
	
	 
protected:

	////////////////////////
	double	m_Param;		// t value 
	WORLD	m_Tangent;		// tangent vector
	double	m_Curvature;	// curvature
	
public:
	virtual ~CDerivObj(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CDerivObj)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};
//////////////////////////////////////
#endif	// _XFLIST_H_
