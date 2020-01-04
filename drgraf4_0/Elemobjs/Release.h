#ifndef	_RELEASE_H_
#define	_RELEASE_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CRelease		// Also Used For ELBOW
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CRelease : public CObject
{
// Construction
public:  
	CRelease();
//////////////////////////////////////
	DECLARE_DYNAMIC(CRelease)
//////////////////////////////////////
public:


	CString&	GetObjectID(){return m_MatID;};	
	void		SetObjectID(CString p){m_MatID = p;};	
	UINT		GetObjectNum(){return m_MatNum;};	
	void		SetObjectNum(UINT p){m_MatNum = p;};	
	////////////////////////////////////////////////
	double		GetRx(){return m_Rx;};
	void 		SetRx(double d){m_Rx = d;};
	double		GetRy(){return m_Ry;};
	void 		SetRy(double d){m_Ry = d;};
	double		GetRz(){return m_Rz;};
	void 		SetRz(double d){m_Rz = d;};
	/////
	double		GetRxx(){return m_Rxx;};
	void 		SetRxx(double d){m_Rxx = d;};
	double		GetRyy(){return m_Ryy;};
	void 		SetRyy(double d){m_Ryy = d;};
	double		GetRzz(){return m_Rzz;};
	void 		SetRzz(double d){m_Rzz = d;};
	/////

	
protected:


	CString		m_MatID;		// MaterialID
	UINT		m_MatNum;		// Material Number
	//////////////////////
	double		m_Rx;			// Release Tran_X
	double		m_Ry;			// Release Tran_Y
	double		m_Rz;			// Release Tran_Z
	double		m_Rxx;			// Release Rot_X
	double		m_Ryy;			// Release Rot_Y
	double		m_Rzz;			// Release Rot_Z
	//////////////////////////////////////
//	CString		m_ScheduleID;	// To get into Table below
//	CList		m_Table;		// Data Table 		

	
public:
	virtual ~CRelease(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Pro_PIPE_H_
