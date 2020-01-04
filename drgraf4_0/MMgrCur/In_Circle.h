 // In_Circle.h : header file
//
#ifndef _IN_CIRCLE_H 
#define _IN_CIRCLE_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "drcurve.h"
#include "In_Conics.h"
#include "Def_Type.h"
#include "Def_CuPS.h" 
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class CIn_Circle : public CIn_Conics
{
public:

	CIn_Circle();
//////////////////////////////////////
	DECLARE_SERIAL(CIn_Circle)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
			//////////////////////////////////////////////////////////
			int		Prepare();
			int		Interpolate();
			////////////////////////////////////////////////////////// Info
			WORLD	GetCenter(){return m_Center;};
			void	SetCenter(WORLD t)
					{
						m_Center.x = t.x;
						m_Center.y = t.y;
						m_Center.z = t.z;
					};
			double	GetRadius(){return m_Radius;};
			void	SetRadius(double t){m_Radius = t;};
			WORLD	GetNormal(){return m_Normal;};
			void	SetNormal(WORLD t)
					{
						m_Normal.x = t.x;
						m_Normal.y = t.y;
						m_Normal.z = t.z;
					};
			//////////////////////////////////////////////////////////
							
							
		
protected:

			int		Compute_InBetweens(pWORLD Data,WORLD Center,double Radius,
								   pWORLD Con,pDOUBLE Wts,int L,BOOL bClosed);
			int		Compute_b1_w1(WORLD Center,WORLD b0,WORLD b2,double Rad,
									pWORLD pb1,pDOUBLE pw1);
		          

protected:
  
// Attributes
protected:


	
	/////////////////////////////////////////////////////////////// Info
	WORLD		m_Center;
	double  	m_Radius;
	WORLD		m_Normal;
    
    
//Operations
public:

	~CIn_Circle();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CIn_Circle)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
