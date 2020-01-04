 // ELMouse.h : header file
//
#ifndef _SLD_OBJ_H 
#define _SLD_OBJ_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


/////////////////////
#include "DrStatic.h"
#include "DListMgr.h"
#include "Def_Type.h"                    
#include "Def_StaL.h"	// support                    
#include "Def_Mous.h"                    
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CSLDObj : public CObject
{
public:

	CSLDObj();
//////////////////////////////////////
	DECLARE_SERIAL(CSLDObj)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:
 
	virtual	void		GetObjectInfo(CSLDObj* pObject);
	virtual	void		SetObjectInfo(CSLDObj* pObject);
	////////////////////////////////////////////////////
			int			Get_Values(STALPROC StaLProc, CString& heading);
  				
		
protected:


	////////////////////////////////////////////////////////////////////////////////
	int			FillStLCard(STALCARD& StLCard,CString* pID);
	////////////////////////
	int			FillInfo_3(CString& Nid,STALCARD stLCard,char* buf, int jStart);
	int			FillInfo_6(CString& Nid,STALCARD stLCard,char* buf, int jStart);
	////////////////////////////////////////////////////////////////////////////////
	int			Get_Values_ManyDirections(CString& Nid,STALPROC StaLProc);
	int			Get_Values_Iso_WORLD(CString& wid,WORLD& NodeT,WORLD& NodeR, STALPROC StaLProc);


public:  
// Attributes


	int			m_nNodPos_S_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_S_End;		// index of Bezier Segment in s direction:End
									// now,useful for CProf internally
//todo									// later for UserInterface of BezSeg dependent input
	int			m_nNodPos_T_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_T_End;		// index of Bezier Segment in s direction:End
									// later,useful for PProf internally
	int			m_nNodPos_R_Beg;		// index of Bezier Segment in s direction:Begin
	int			m_nNodPos_R_End;		// index of Bezier Segment in s direction:End
									// later,useful for SProf internally
	int			m_nStartIndex;	// index in StaLList         
	int			m_nTotal;			// total generated in StaLList having
									// this StaLCard Properties         
	/////////////////////////////////////////// Static
	STALPROC	m_StaLProc;
	BOOL    	m_bTx;
	BOOL    	m_bTy;
	BOOL    	m_bTz;
	BOOL    	m_bRx;
	BOOL    	m_bRy;
	BOOL    	m_bRz;
	double    	m_dTx;			// also for Prs,Thr and LWt
	double    	m_dTy;			// also for Prs,Thr and LWt
	double    	m_dTz;			// also for             LWt
	double    	m_dRx;
	double    	m_dRy;
	double    	m_dRz;
	CString		m_aNid;		// Used for JC_X_FIXEDDIR
	BOOL		m_bCN_a;		// nid_a is Control Node?		
	CString		m_bNid;		// Used for JC_X_FIXEDDIR
	BOOL		m_bCN_b;		// nid_b is Control Node?		
	WORLD		m_SkewDir;
	UINT		m_GenKind;		//
	BOOL		m_bTanCur;		// for: 
	BOOL		m_bTanPat;		// for: 
	BOOL		m_bNorPat;		// for: 
								// Node:Tangent to Curve or Normal to Patch
								// Curve:Tangent
								// Patch:Normal
	CString		m_ID_CP;		// Used for NodeBased
							// if Tangent to Curve; it is CurveID
							// if Normal to Patch;	it is PatchID
	JOINTCOORD  m_jcType;		//	JC_DEFAULT,
							//	JC_X_FIXEDDIR,
							//	JC_X_TAN_CURVE,
							//	JC_I_TAN_PATCH
							//	JC_Z_NOR_PATCH
	BOOL		m_bUniform;	// Uniform distribution
	BOOL		m_bConOrDis;	// IsoParametric Concentrated or Distributed Input
	//
	BOOL		m_bIso;
	CString		m_cid_Iso;		// Iso  or NonIso to this Curve				
	CString		m_cid_ParentT;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	CString		m_cid_ParentR;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	/////////////////////// NonIso
	BOOL		m_bNonIso;
	CString		m_CID;
	BOOL		m_bIncrement;
	CString		m_Orient;
	double		m_dScale;
	double		m_dStep;
	double		m_dStart;
	//////////////////////////
	BOOL		m_bGravMul;



//Operations
public:

	~CSLDObj();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CSLDObj)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
