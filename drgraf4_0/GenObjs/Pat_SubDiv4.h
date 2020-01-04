#ifndef	_PAT_SUBDIV4_H_
#define	_PAT_SUBDIV4_H_


/////////////////////////////////////////////////////////////////////////////
// CDrSurfaces
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CPat_SubDiv4 : public CObject
class AFX_EXT_CLASS CPat_SubDiv4 : public CObject
{
// Construction
public:  
	CPat_SubDiv4();
	DECLARE_DYNAMIC(CPat_SubDiv4)

public:
// Implementation

	int			SubDivide_U(pWORLD Cons, double u, 
						pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV);
	int			SubDivide_V(pWORLD Cons, double v,  
						pWORLD NewC, BOOL bLeft, int nOrderU, int nOrderV);
	int			SubDivide_UV(pWORLD Cons, double u, double v, 
								pWORLD NewC, BOOL bLeftU, BOOL bLeftV, 
								int nDegreeU, int nDegreeV);
	int			Rat_SubDivide_U(pWORLD Cons, pDOUBLE Wts, double u, 
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV);
	int			Rat_SubDivide_V(pWORLD Cons, pDOUBLE Wts, double v,  
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV);
	int			Rat_SubDivide_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, 
							pWORLD NewC, pDOUBLE NewW, BOOL bLeftU, BOOL bLeftV, 
							int nOrderU, int nOrderV);





protected:


	
public:

	
protected:



public:
	virtual ~CPat_SubDiv4(){};
/*
	// Generated message map functions
	//{{AFX_MSG(CPat_SubDiv4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif	// _SURFACE_H_

