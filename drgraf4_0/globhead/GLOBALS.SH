#ifndef _GLOBALS_H
#define _GLOBALS_H
///////////////////////////////////////////////////////////// GLOBALS
#define MAX_POLY_NODES		4 
////////////////////////////// Objects in DrObject->SetElemType()
#define ELEM_OBJECT			1	// Viewable/NOT Renderable: Structural Elements-Node,Pipe etc
#define DRAW_OBJECT			2   // Viewable/NOT Renderable: Drawing Objects- Freehand,Label etc
#define EL3D_OBJECT			3   // Viewable/3D  RENDERABLE: Structural Elements- Plate etc.
#define DR3D_OBJECT			4   // Viewable/3D  RENDERABLE: Drawing Objects- Sphere,Cone etc.
#define GENR_OBJECT			5   // Viewable/3D  RENDERABLE: Generator:CURVE & PATCH
#define TOOL_OBJECT			-1	// Not Viewable: Tools
#define SPEC_OBJECT			-2  // Not Viewable: Specials- Booleans, Font etc
#define OPER_OBJECT			-3  // Not Viewable: Operations- XForm etc 
///////////////////////////////////////////// applicable for All
#define INSERT				-1
#define POST				-2
#define EDIT				-3
#define MOVE				-4
#define UNPOST				-5
#define DELETE				-6
////////////////////////////// LEVEL
#define LEVEL_EUNUK			-1  // No Level
#define LEVEL_GRAPA			0	// Dr3DObjects/Individual Elements	
#define LEVEL_DADDY			1	// Patch/Curve
#define LEVEL_UNCLE     	2	// Curve
#define LEVEL_KIDDO     	3   // Generated Elements(in Patch/CurveLists)
////////////////////////////// ZOOM
#define ZOOM_USER			1
#define ZOOM_FIT			3
////////////////////////////// VIEW
#define	VIEW12				1 	             
#define	VIEW23				2 	             
#define	VIEW31				3 	             
#define	VIEWISO				4 
#define VIEWDAT				5
////////////////////////////// TOOLBOXES
#define ELEMENT_BOX			1
#define DRAW_BOX			2	             
//////////////////////////////
#define ID_CLOCK_TIMER    	1
//////////////////////////////
#define TOP_STATUSBAR		1
///////////////////////////
typedef unsigned long 		HUGESIZE;
typedef	char __huge 		*HUGEBLK;	
#define	HUGECOPY(s,d,sz)	while( (sz)-- ) *(d)++ = *(s)++ 
/////////////////////////////////////////////////////////// 
typedef int	__far			*pINT;
typedef double	__far		*pDOUBLE;
typedef unsigned int __far 	*pUINT;
typedef RECT __far			*pRECT;
/////////////////////////////////
typedef	struct 
	{
		long x;
		long y;
		long z;
	}LPOINT3, __far *pLPOINT3;
			
typedef	struct 
	{
		int x;
		int y;
		int z;
	}POINT3, __far *pPOINT3;
			
typedef	struct 
	{
		long x;
		long y;
	}LPOINT, __far *pLPOINT;	
		
typedef	struct 
	{
		float x;
		float y;
		float z;
	}WORLF, __far *pWORLF; 
	
typedef	struct 
	{
		double x;
		double y;
		double z;
	} WORLD, __far *pWORLD; 
	
typedef	struct 
	{
		long left;
		long top;
		long right;
		long bottom;
	}	LRECT, __far *pLRECT;
						
typedef struct {
	double v[4];
}	VECTOR, __far *pVECTOR;   // Homogenous Coords

typedef struct {
	double v[4][4];
}	MATRIX, __far *pMATRIX;   // Homogenous Coords

enum SOLIDTYPE
	{
		SO_BEZIER,
		SO_BSPLINE,
		SO_CATMULLROM,
		SO_HERMITE,
		SO_BETA,
		SO_LINEAR,
		SO_QUADRATIC,
		SO_EXTRUDE,
		SO_ROTATE,
		SO_LOFT,
		SO_SWEEP,
		SO_DUCT,
		SO_FLAT,
	};	

enum PATCHTYPE
	{
		PA_BEZIER,
		PA_BSPLINE,
		PA_CATMULLROM,
		PA_HERMITE,
		PA_BETA,
		PA_LINEAR,
		PA_QUADRATIC,
		PA_EXTRUDE,
		PA_ROTATE,
		PA_LOFT,
		PA_SWEEP,
		PA_DUCT,
		PA_FLAT,
	};	

enum CURVETYPE
	{
		CU_BEZIER, 	// Cubics:
		CU_BSPLINE,		// B-Spline UNIFORM
		CU_NUSPLINE,		// B-Spline NON-UNIFORM
		CU_NURB, 			// B-Spline NON-UNIFORM RATIONAL
		CU_CATMULLROM,	// Catmull-Rom
		CU_CARDISPLINE,	// Cardinal Spline (ALFA Catmull-Rom)
		CU_HERMITE,       // Hermite
		CU_BETA,			// Beta-Spline
		CU_QUADRATIC,	// Quadratics:
		CU_LAGQUAD, 		// Lagrange
		CU_NURBQUAD,		// B-Spline NON-UNIFORM RATIONAL (for conics)
		CU_CIRCLE,
		CU_ELLIPSE,
		CU_PARABOLA,
		CU_LINEAR,	// Linears
	};
		
enum CURVEOUTPUT
	{
		CO_HORNER,
		CO_FINITEDIF,
		CO_BLEND
	};	
		
enum XFMODE
	{
		XF_REPLACE,
		XF_PREMULT,
		XF_POSTMULT
	};	

enum VISIBILITY
	{
		VI_NOT_VISIBLE,
		VI_YES_VISIBLE
	};

enum MATRICES
	{ 
		MT_IDENTITY,
		MT_LOCAL,
		MT_VIEWER,
		MT_COMBINED,
		MT_VV3D
	};
enum OPMODE
	{
		OP_OUTPUT,
		OP_INPUT
	};
enum SUBDIV
	{
		SU_NOSUB,
		SU_ONCE,
		SU_TWICE,
		SU_AUTO
	};
enum ORIENT
	{
		OT_ANTICLOCK,
		OT_CLOCKWISE,
		OT_DUALSIDED
	};
enum LISTTYPE
	{
		LI_NODELIST,
		LI_CNODELIST,
		LI_ELEMLIST,
		LI_CURVELIST,
		LI_PATCHLIST,
		LI_SOLIDLIST
	};	
enum ORDER				// Order of Curve: 4,3,2
	{
		OR_CUBIC,
		OR_QUADRATIC,
		OR_LINEAR
	};	
enum BOUNDARY			// Boundary Condition
	{
		BC_AUTO,
		BC_CLAMPED,
		BC_FREE,
		BC_BESSEL,
		BC_QUADRATIC,
		BC_CLOSED,
		BC_TANGENT,
		BC_NOT_A_KNOT
	};	
enum KNOT				// Knot sequence
	{
		KN_AUTO,
		KN_UNIFORM,
		KN_CHORDLENGTH,
		KN_CENTRIPETAL,
		KN_FOLEY,
		KN_USER
	};	
enum WEIGHT				// Rational Weights
	{
		WT_AUTO,
		WT_UNIFORM,
		WT_USER
	};	
						 
enum ENDS				// (S)Curve/(S,T)Patch/(S,T,R)Solid Ends 
{
	END_S0,	// i = 0 end
	END_SL,	// i = L end
	END_T0,
	END_TL,
	END_R0,
	END_RL
};	
/////////////////////////////////////////////////////////////////////////////
#endif 

