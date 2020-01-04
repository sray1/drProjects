#ifndef _STR_STAL_H
#define _STR_STAL_H 

#include "Def_Supp.h"	// for Joint Coords
#include "Def_StaL.h"
///////////////////////////////////////////////////////////////// CARDS
/******** StaticLoad variables/ data structure **************/
typedef struct staLcard
	{
		int			nNodPos_S_Beg;		// index of Node in s direction:Begin
		int			nNodPos_S_End;		// index of Node in s direction:End
									// now,useful for CProf internally
//todo									// later for UserInterface of BezSeg dependent input
		int			nNodPos_T_Beg;		// index of Node in t direction:Begin
		int			nNodPos_T_End;		// index of Node in t direction:End
									// later,useful for PProf internally
		int			nNodPos_R_Beg;		// index of Node in t direction:Begin
		int			nNodPos_R_End;		// index of Node in t direction:End
		int			nStartIndex;	// index in StaLList         
		int			nTotal;			// total generated in StaLList having
									// this StaLCard Properties         
		int			ElNum;         
		int			IDNum;     
		CString		load_id;
		STALPROC	StaLProc;	// Force,Displace,Pressure etc
		BYTE		kode[6];
		double		value[6];	// Actual Input
		CString		nid_a;		// Used for JC_X_FIXEDDIR
		BOOL		bCN_a;		// nid_a is Control Node?		
		CString		nid_b;		// Used for JC_X_FIXEDDIR
		BOOL		bCN_b;		// nid_b is Control Node?		
		WORLD		SkewDir;	// Used if nid_b !="";	
		UINT		GenKind;	// NODE,CURVE,PATCH,SOLID
		BOOL		bTanCur;		// for: 
		BOOL		bTanPat;		// for: 
		BOOL		bNorPat;		// for: 
									// Node:Tangent to Curve or Normal to Patch
									// Curve:Tangent
									// Patch:Normal
		CString		ID_CP;		// Used for NodeBased
								// if Tangent to Curve; it is CurveID
								// if Normal to Patch;	it is PatchID
		JOINTCOORD  jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH
		BOOL		bUniform;	// Uniform distribution
		BOOL		bConOrDis;	// TRUE = Concentrated / FALSE = Distributed	
									// IsoParametric Concentrated or Distributed Input
		///////
		BOOL		bIso;		// IsoParametric Input
		CString		cid_Iso;	// this staLcard IsoParametric(Non-Iso) to this Curve/Patch
		CString		cid_ParentT;	// this staLcard part of this Curve of Category CA_FORCE: Tran
									// this is m_CID in Iso-Generated Curve
									// this is m_CID in NonIso Input
		CString		cid_ParentR;	// this staLcard part of this Curve of Category CA_FORCE: Rot
									// this is m_CID in Iso-Generated Curve
									// this is m_CID in NonIso Input
	/////////////////////// NonIso
		BOOL		bNonIso;	// Non-IsoParametric Input
//		CString		cid_Parent;	// this staLcard part of this Curve of Category CA_FORCE
		BOOL		bIncrement;
		CString		Orient;
		double		dScale;
		double		dStep;
		double		dStart;

    }STALCARD, FAR *pSTALCARD;
//******** NonLin StaticLoad variables/ data structure **************/   TEMPORARY
typedef struct nonstaLcard
	{
		int			nNodPos_S_Beg;		// index of Bezier Segment in s direction:Begin
		int			nNodPos_S_End;		// index of Bezier Segment in s direction:End
									// now,useful for CProf internally
//todo									// later for UserInterface of BezSeg dependent input
		int			nNodPos_T_Beg;		// index of Bezier Segment in s direction:Begin
		int			nNodPos_T_End;		// index of Bezier Segment in s direction:End
									// later,useful for PProf internally
		int			nNodPos_R_Beg;		// index of Bezier Segment in s direction:Begin
		int			nNodPos_R_End;		// index of Bezier Segment in s direction:End
		int			nStartIndex;	// index in StaLList         
		int			nTotal;			// total generated in StaLList having
									// this StaLCard Properties         
		int			ElNum;         
		int			IDNum;     
		CString		load_id;
		STALPROC	StaLProc;	// Force,Displace,Pressure etc
		BYTE		kode[6];
		double		value[6];	// Actual Input
		CString		nid_a;		// Used for JC_X_FIXEDDIR
		BOOL		bCN_a;		// nid_a is Control Node?		
		CString		nid_b;		// Used for JC_X_FIXEDDIR
		BOOL		bCN_b;		// nid_b is Control Node?		
		WORLD		SkewDir;	// Used if nid_b !="";	
		UINT		GenKind;	// NODE,CURVE,PATCH,SOLID
		BOOL		bTanCur;		// for: 
		BOOL		bTanPat;		// for: 
		BOOL		bNorPat;		// for: 
									// Node:Tangent to Curve or Normal to Patch
									// Curve:Tangent
									// Patch:Normal
		CString		ID_CP;		// Used for NodeBased
								// if Tangent to Curve; it is CurveID
								// if Normal to Patch;	it is PatchID
		JOINTCOORD  jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH
		BOOL		bUniform;	// Uniform distribution
		BOOL		bConOrDis;	// TRUE = Concentrated / FALSE = Distributed	
									// IsoParametric Concentrated or Distributed Input
		///////
		BOOL		bIso;		// IsoParametric Input
		CString		cid_Iso;	// this staLcard IsoParametric(Non-Iso) to this Curve/Patch
		CString		cid_ParentT;	// this staLcard part of this Curve of Category CA_FORCE: Tran
									// this is m_CID in Iso-Generated Curve
									// this is m_CID in NonIso Input
		CString		cid_ParentR;	// this staLcard part of this Curve of Category CA_FORCE: Rot
									// this is m_CID in Iso-Generated Curve
									// this is m_CID in NonIso Input
	/////////////////////// NonIso
		BOOL		bNonIso;	// Non-IsoParametric Input
//		CString		cid_Parent;	// this staLcard part of this Curve of Category CA_FORCE
		BOOL		bIncrement;
		CString		Orient;
		double		dScale;
		double		dStep;
		double		dStart;
    }NONSTLCARD, FAR *pNONSTLCARD;
////////////////////////////////////////////////////////////////////	  		
#endif
