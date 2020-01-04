#ifndef	_SINDEX_H_
#define	_SINDEX_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CSIndex		// Also Used For ELBOW
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSIndex : public CObject
{
// Construction
public:  
	CSIndex();
//////////////////////////////////////
	DECLARE_DYNAMIC(CSIndex)
//////////////////////////////////////
public:


	CString&	GetObjectID(){return m_MatID;};	
	void		SetObjectID(CString p){m_MatID = p;};	
	UINT		GetObjectNum(){return m_MatNum;};	
	void		SetObjectNum(UINT p){m_MatNum = p;};	
	////////////////////////////////////////////////
	CString&	GetCodeID(){return m_CodeID;};	
	void		SetCodeID(CString p){m_CodeID = p;};	
	double		GetC2(){return m_C2;};
	void 		SetC2(double d){m_C2 = d;};
	double		GetK2(){return m_K2;};
	void 		SetK2(double d){m_K2 = d;};
	/////

	
protected:


	CString		m_MatID;		// MaterialID
	UINT		m_MatNum;		// Material Number
	//////////////////////
	CString		m_CodeID;			// Code Component ID
	double		m_C2;				// Moment Loading Stress Indices
	double		m_K2;				// Moment Loading Stress Indices
	//////////////////////////////////////
//	CString		m_ScheduleID;	// To get into Table below
//	CList		m_Table;		// Data Table 		

	
public:
	virtual ~CSIndex(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Pro_PIPE_H_
