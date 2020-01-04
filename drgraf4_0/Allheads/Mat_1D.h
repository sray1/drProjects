#ifndef	_MAT_1D_H_
#define	_MAT_1D_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CMat_1D		// Also Used For ELBOW
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMat_1D : public CObject
{
// Construction
public:  
	CMat_1D();
//////////////////////////////////////
	DECLARE_DYNAMIC(CMat_1D)
//////////////////////////////////////
public:


	CString&	GetObjectID(){return m_MatID;};	
	void		SetObjectID(CString p){m_MatID = p;};	
	UINT		GetObjectNum(){return m_MatNum;};	
	void		SetObjectNum(UINT p){m_MatNum = p;};	
	////////////////////////////////////////////////
	double		GetE(){return m_E;};
	void 		SetE(double d){m_E = d;};
	double		GetNu(){return m_Nu;};
	void 		SetNu(double d){m_Nu = d;};
	double		GetAlfa(){return m_Alfa;};
	void 		SetAlfa(double d){m_Alfa = d;};
	double		GetRo_W(){return m_Ro_W;};
	void 		SetRo_W(double d){m_Ro_W = d;};
	double		GetRo_M(){return m_Ro_M;};
	void 		SetRo_M(double d){m_Ro_M = d;};
	double		GetRo_I(){return m_Ro_I;};
	void 		SetRo_I(double d){m_Ro_I = d;};
	/////

	
protected:


	CString		m_MatID;		// MaterialID
	UINT		m_MatNum;		// Material Number
	//////////////////////
	double		m_E;			// Modulus of Elasticity
	double		m_Nu;			// Poisson's Ratio
	double		m_Alfa;			// Thermal Expn. Coeff.
	double		m_Ro_W;			// Weight Density
	double		m_Ro_M;			// Mass Density
	double		m_Ro_I;			// Insulation Density
	//////////////////////////////////////
//	CString		m_ScheduleID;	// To get into Table below
//	CList		m_Table;		// Data Table 		

	
public:
	virtual ~CMat_1D(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Pro_PIPE_H_
