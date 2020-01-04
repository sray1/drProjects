#ifndef	_PRO_BEAM_H_
#define	_PRO_BEAM_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Property.h"
/////////////////////////////////////////////////////////////////////////////
// CPro_BEAM		// Also Used For TRUSS
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CPro_BEAM : public CProperty
{
// Construction
public:  
	CPro_BEAM();
//////////////////////////////////////
	DECLARE_DYNAMIC(CPro_BEAM)
//////////////////////////////////////
public:


	////////////////////////////////////////////////
	double		GetAx(){return m_Ax;};
	void 		SetAx(double d){m_Ax = d;};
	double		GetAy(){return m_Ay;};
	void 		SetAy(double d){m_Ay = d;};
	double		GetAz(){return m_Az;};
	void 		SetAz(double d){m_Az = d;};
	/////
	double		GetIxx(){return m_Ixx;};
	void 		SetIxx(double d){m_Ixx = d;};
	double		GetIyy(){return m_Iyy;};
	void 		SetIyy(double d){m_Iyy = d;};
	double		GetIzz(){return m_Izz;};
	void 		SetIzz(double d){m_Izz = d;};

	
protected:


	//////////////////////
	double		m_Ax;			// Axial Area_X dir
	double		m_Ay;			// Axial Area_Y dir
	double		m_Az;			// Axial Area_Z dir
	double		m_Ixx;			// Inertia_X dir
	double		m_Iyy;			// Inertia_Y dir
	double		m_Izz;			// Inertia_Z dir
	//////////////////////////////////////

	
public:
	virtual ~CPro_BEAM(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Pro_PIPE_H_
