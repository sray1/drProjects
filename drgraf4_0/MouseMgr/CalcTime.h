#ifndef	_CALCTIME_H_
#define	_CALCTIME_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////////////////////////////////////////////////////////////
// CCalcTime
/////////////////////////////////////////////////////////////////////////////
class CCalcTime : public CObject
{
// Construction
public:  
	CCalcTime();
//////////////////////////////////////
	DECLARE_DYNAMIC(CCalcTime)
//////////////////////////////////////
public:


		void	StartClock();
		void	StopClock();
		void	OutDuration(CString& str);
		void	OutComment(CString& str);






	
protected:


	clock_t		m_Start;
	double		m_Duration;
	//////////////////////////////////////
	
public:
	virtual ~CCalcTime(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _TRIANGLE_H_
