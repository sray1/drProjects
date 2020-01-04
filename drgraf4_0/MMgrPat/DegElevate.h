 // ELMouse.h : header file
//
#ifndef _DEGELEVATE_H 
#define _DEGELEVATE_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CDegElevate : public CMI_Cur_I
class AFX_EXT_CLASS CDegElevate : public CObject
{
public:

	CDegElevate(BOOL bClosed);
//////////////////////////////////////
	DECLARE_DYNAMIC(CDegElevate)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	////////////////////////////////////////////
	int				Elevate_Curve
					(
						pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
						pWORLD pConNew, pDOUBLE pWtsNew,int nSeg_BZ, int nDim
					);
		
protected:

	///////////////////////////////////////////////////////////////////// ControlInfo
	int				Elevate_BezSeg
					(
						pWORLD pConOld, pDOUBLE pWtsOld,int nDegOld,int nElev,
						pWORLD pConNew, pDOUBLE pWtsNew, int nDim
					);
	int				DegreeElevate(pWORLD Con_BZ, pDOUBLE Wts_BZ, int nDegree, 
							 pWORLD NewCon_BZ, pDOUBLE NewWts_BZ, int nDim);
	//////////////////////////////////////////////////////////////////// Reparametrize
	
protected:
	
	BOOL			m_bClosed;   

//Operations
public:

	~CDegElevate();
/*
	// Generated message map functions

	//{{AFX_MSG(CDegElevate)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
