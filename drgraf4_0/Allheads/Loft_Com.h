#ifndef	_LOFT_COM_H_
#define	_LOFT_COM_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "DListMgr.h"
#include <afxtempl.h>	// CList
/////////////////////////////////////////////////////////////////////////////
// CLoft_Compat
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CLoft_Compat : public CObject
{
// Construction
public:  
	CLoft_Compat(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CLoft_Compat)
//////////////////////////////////////
public:


	BOOL		AreCurvesCompatible(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList);





	
protected:


	BOOL		IsCompat_Closed(CDListMgr* pCurveList,BOOL& bClosed);
	int			PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim_S,int& nTopDegree);
	BOOL		IsRational(CDListMgr* pCurveList);
	int			GetTopDegree(CDListMgr* pCurveList);
	BOOL		IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
													int& nCurveSeg,int& nConBZ);
	BOOL		IsCompat_OutputInfo(CDListMgr* pCurveList,
						CList<CURVELATCH,CURVELATCH>* pLatchList);
	
public:
	virtual ~CLoft_Compat(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// 
