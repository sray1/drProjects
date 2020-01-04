#ifndef _STR_SUPP_H
#define _STR_SUPP_H 

#include "Def_SUPP.h"
///////////////////////////////////////////////////////////////// CARDS
/******** Support variables/ data structure **************/
typedef struct supportcard
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
		int			nStartIndex;	// index in SuppList         
		int			nTotal;			// total generated in SuppList having
									// this SuppCard Properties         
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		sup_id;
		SUPPPROC	SuppProc;				//* Rigid,LinSpr,LinSnu etc
		BYTE		kode[6];
		double		stiffness[6];
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
		BYTE		pgap[6];
		CString		ID_CP;		// Used for NodeBased
								// if Tangent to Curve; it is CurveID
								// if Normal to Patch;	it is PatchID
		JOINTCOORD  jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH
    }SUPPCARD, FAR *pSUPPCARD;
//******** NonLin Support variables/ data structure **************/   TEMPORARY
typedef struct nonsupcard 
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
		int			nStartIndex;	// index in SuppList         
		int			nTotal;			// total generated in SuppList having
									// this SuppCard Properties         
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		sup_id;
		SUPPPROC	SuppProc;				//* Rigid,LinSpr,LinSnu etc
		BYTE		kode[6];
		double		stiffness[6];
		CString		nid_a;		// Used for NodeInput
								// also forSkewDirCalc with nid_b !=""
		BOOL		bCN_a;		// nid_a is Control Node?		
		CString		nid_b;
		BOOL		bCN_b;		// nid_b is Control Node?		
		WORLD		SkewDir;	// Used if nid_b !="";	
		UINT		GenKind;	// NODE,CURVE,PATCH,SOLID
		BYTE		gap[6];
		BOOL		bTanCur;		// for: 
		BOOL		bTanPat;		// for: 
		BOOL		bNorPat;		// for: 
									// Node:Tangent to Curve or Normal to Patch
									// Curve:Tangent
									// Patch:Normal
		BYTE		pgap[6];
		CString		ID_CP;		// Used for NodeBased
								// if Tangent to Curve ; it is CurveID
								// if Normal to Patch ; it is PatchID
		JOINTCOORD  jcType;		//	JC_DEFAULT,
								//	JC_X_FIXEDDIR,
								//	JC_X_TAN_CURVE,
								//	JC_Z_NOR_PATCH
   }NONSUPCARD, FAR *pNONSUPCARD;
////////////////////////////////////////////////////////////////////	  		
#endif
