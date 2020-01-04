#ifndef	_PRO_PIPE_H_
#define	_PRO_PIPE_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "Property.h"
/////////////////////////////////////////////////////////////////////////////
// CPro_PIPE		// Also Used For ELBOW
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPro_PIPE : public CProperty
{
// Construction
public:  
	CPro_PIPE();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPro_PIPE)
//////////////////////////////////////
public:


	////////////////////////////////////////////////
	double		GetOutD(){return m_OutD;};
	void 		SetOutD(double d){m_OutD = d;};
	double		GetThk(){return m_Thk;};
	void 		SetThk(double d){m_Thk = d;};
	double		GetThk_I(){return m_Thk_I;};
	void 		SetThk_I(double d){m_Thk_I = d;};
	double		GetBendR(){return m_BendR;};
	void 		SetBendR(double d){m_BendR = d;};
	/////

	
protected:


	//////////////////////
	double		m_OutD;			// Outside Diameter
	double		m_Thk;			// Thickness
	double		m_Thk_I;		// Insulation Thickness
	//
	double		m_BendR;			// Bend Radius
	double		m_Pres;			// Internal Pres.for Elbow Flexibility
	//////////////////////////////////////

	
public:
	virtual ~CPro_PIPE(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Pro_PIPE_H_
