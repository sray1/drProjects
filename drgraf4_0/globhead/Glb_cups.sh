#ifndef _GLB_CUPS_H
#define _GLB_CUPS_H
///////////////////////////////////////////////////////////// GLOBALS
enum SOLIDPROC
	{
		SP_EXTRUDE,
		SP_ROTATE,
		SP_LOFT2,
		SP_LOFT3,
		SP_LOFT4,
		SP_LOFTMANY,
		SP_SWEEP,
		SP_DUCT,
		SP_SPAWN,	// Spawn
		SP_STITCH,	// Stitch
		SP_POST		// MeshGen

	};
	
enum SOLIDTYPE
	{
		SO_TENSOR,
		SO_COONS,
		SO_GORDON
	};	

enum SOLSUBTYPE
	{
		SS_TETRA,
		SS_PENTA,
		SS_HEXA
	};	
	
enum SOLIDOUTPUT
	{
		SO_HORNER,
		SO_FINITEDIF,
		SO_BLEND
	};

enum PATCHPROC
	{
		PP_EXTRUDE,
		PP_ROTATE,
		PP_LOFT2,
		PP_LOFT3,
		PP_LOFT4,
		PP_LOFTMANY,
		PP_SWEEP,
		PP_DUCT,
		PP_TENSOR,
		PP_COONS,
		PP_GORDON,
		PP_FLAT,
		PP_SPAWN,	// Spawn
		PP_STITCH,	// Stitch
		PP_POST		// MeshGen
	};	

enum PATCHTYPE
	{
		PA_TENSOR,
		PA_COONS,
		PA_GORDON
	};	

enum PATSUBTYPE
	{
		PS_TRIANGLE,
		PS_QUADRILAT
	};	

enum CURVEPROC
	{
		CP_BEZIER, 	// Cubics:
		CP_BSPLINE,		// B-Spline UNIFORM
		CP_NUSPLINE,		// B-Spline NON-UNIFORM
		CP_NURB, 			// B-Spline NON-UNIFORM RATIONAL
		CP_CATMULLROM,	// Catmull-Rom
		CP_CARDISPLINE,	// Cardinal Spline (ALFA Catmull-Rom)
		CP_HERMITE,       // Hermite
		CP_BETA,			// Beta-Spline
		CP_QUADRATIC,	// Quadratics:
		CP_LAGQUAD, 		// Lagrange
		CP_NURBQUAD,		// B-Spline NON-UNIFORM RATIONAL (for conics)
		CP_CIRCLE,
		CP_ELLIPSE,
		CP_PARABOLA,
		CP_LINEAR,	// Linears
		CP_SPAWN,	// Spawn
		CP_STITCH,	// Stitch
		CP_POST		// MeshGen
	};
		
enum CURVEOUTPUT
	{
		CO_HORNER,
		CO_FINITEDIF,
		CO_BLEND
	};
	
enum PATCHOUTPUT
	{
		PA_HORNER,
		PA_FINITEDIF,
		PA_BLEND,
		PA_DECAS,
		PA_MODIFIED,	// for Triangular:Schumaker(1986)
		PA_EXPLICIT		// for Triangular:Yamaguchi(1988)
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
	
enum CURVELATCH				// Latching Curve in Patch or Stitch
	{
		CL_BACKWARD,
		CL_FORWARD
	};	
	
enum XFORMTYPE				// Xformation Generation Type
	{
		XT_DIRECT,
		XT_XFORMS,
		XT_SYMMETRIC
	};

enum CIRCLETYPE
{
	CIRCLE_BY_ROT,
	CIRCLE_BY_NO3,
	CIRCLE_BY_2N_TI,
	CIRCLE_BY_2N_CC,
	CIRCLE_BY_2CN_TI_R
};

enum CATEGORY
{
	CA_ANCILLARY,		// Twist,Spine,Radial etc.
	CA_ELEMENT,
	CA_SUPPORT,
	CA_FORCE,
	CA_DISPLACE,
	CA_THERMAL,
	CA_PRESSURE,
	CA_LUMPWT,
	CA_MASS,
	CA_HISFORCE,
	CA_HISDISPL,
	CA_HISTHERM,
	CA_HISPRESS,
	CA_HISVELOC,
	CA_HISACCEL
};	
/////////////////////////////////////////////////////////////////////////////
#endif 

