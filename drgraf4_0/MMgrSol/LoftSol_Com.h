#ifndef	_LOFTSOL_COM_H_
#define	_LOFTSOL_COM_H_


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "Def_CuPS.h"
#include "DListMgr.h"
#include <afxtempl.h>	// CList
/////////////////////////////////////////////////////////////////////////////
// CLoftSol_Compat
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CLoftSol_Compat : public CObject
{
// Construction
public:  
	CLoftSol_Compat(){};
//////////////////////////////////////
	DECLARE_DYNAMIC(CLoftSol_Compat)
//////////////////////////////////////
public:


	BOOL		ArePatchesCompatible(CDListMgr* pPatchList,CList<PATCHLATCH,PATCHLATCH>* pLatchList);





	
protected:


	BOOL		IsCompat_Closed(CDListMgr* pPatchList,BOOL& bClosed);
	int			PreProcessPatchesControlInfo(CDListMgr* pPatchList,int& nDim_S,int& nTopDegree);
	BOOL		IsRational(CDListMgr* pPatchList);
	int			GetTopDegree(CDListMgr* pPatchList);
	BOOL		IsCompat_NumberOfCNodes(CDListMgr* pPatchList,int nTopDegree,
													int& nPatchSeg,int& nConBZ);
	BOOL		IsCompat_OutputInfo(CDListMgr* pPatchList,
						CList<PATCHLATCH,PATCHLATCH>* pLatchList);
	
public:
	virtual ~CLoftSol_Compat(){};
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// 
