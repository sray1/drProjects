#ifndef	_PROPERTY_H_
#define	_PROPERTY_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CProperty		// Also Used For ELBOW
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CProperty : public CObject
{
// Construction
public:  
	CProperty();
//////////////////////////////////////
	DECLARE_DYNAMIC(CProperty)
//////////////////////////////////////
public:


	UINT		GetPropType(){return m_PropType;};	
	void		SetPropType(UINT p){m_PropType = p;};
	///
	CString&	GetObjectID(){return m_PropID;};	
	void		SetObjectID(CString p){m_PropID = p;};	
	UINT		GetObjectNum(){return m_PropNum;};	
	void		SetObjectNum(UINT p){m_PropNum = p;};	
	////////////////////////////////////////////////

	
protected:


	UINT		m_PropType;		//  = PIPE
	///
	CString		m_PropID;		// PropertyID
	UINT		m_PropNum;		// Preoperty Number
	//////////////////////////////////////
//	CString		m_ScheduleID;	// To get into Table below
//	CList		m_Table;		// Data Table 		

	
public:
	virtual ~CProperty(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _Property_H_
