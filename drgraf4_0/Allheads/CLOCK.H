// CClock.h : header file
//
#ifndef _CLOCKOBJECT
#define _CLOCKOBJECT

/////////////////////////////////////////////////////////////////////////////
// CClock
/////////////////////////////////////////////////////////////////////////////
class CClock : public CObject
{
// Construction
public:  
	CClock();
	DECLARE_DYNAMIC(CClock);
	
	void 	SetInternational (void);
	void 	GetTimeDate(CString* pstrDate,CString* pstrTime);
 public:
	virtual ~CClock();
};
//////////////////////////////////////
#endif
