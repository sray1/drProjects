#ifndef _DEF_CUPS_H
#define _DEF_CUPS_H
///////////////////////////////////////////////////////////// GLOBALS
enum SOLIDPROC
	{
		SP_EXTRUDE,
		SP_ROTATE,
		SP_LOFT,
		SP_LOFT2,
		SP_LOFTX,
		SP_SWEEP,
		SP_DUCT,
		SP_TENSOR,
		SP_COONS,
		SP_COONSHEXA,
		SP_COONSPENTA,
		SP_COONSTETRA,
		SP_GORDON,
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
		SS_HEXA,
		SS_RANDOM
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
		PP_LOFT,
		PP_LOFT2,
		PP_LOFTX,
		PP_SWEEP,
		PP_DUCT,
		PP_TENSOR,
		PP_COONS,
		PP_COONSTRI,
		PP_COONSQUAD,
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
		PS_QUADRILAT,
		PS_RANDOM
	};	

enum CURVEPROC
	{
		CP_BEZIER, 	// Cubics:
		CP_BSPLINE,		// B-Spline UNIFORM (ASSUMED CUBIC)
		CP_NUSPLINE,		// B-Spline NON-UNIFORM
		CP_NURB, 			// B-Spline NON-UNIFORM RATIONAL (ASSUMED CUBIC)
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
		CP_HYPERBOLA,
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

enum ORDER				// Order of Curve: 4,3,2
	{
		OR_CUBIC,
		OR_QUADRATIC,
		OR_LINEAR
	};
	
enum TWIST			// TWist Condition
	{
		TW_AUTO,
		TW_ZERO,
		TW_BESSEL,	// avg. of bilinear Coons Patch assumption
					//		ie,bi-Quadratic Bndry Curves
		TW_ADINI,	// bilinear Coons Patch with
					//		Ferguson(Hermite) Bndry Curves
		TW_SPLINE,	// Twists form a biCubic Spline Surface
		TW_ENERGY,
		TW_USER
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
	
enum PATCHLATCH				// Latching Patch in Solid or Stitch
	{
		PL_FIRST_FORWARD,
		PL_SECOND_FORWARD,
		PL_THIRD_FORWARD,
		PL_FOURTH_FORWARD,
		PL_FIRST_BACKWARD,
		PL_SECOND_BACKWARD,
		PL_THIRD_BACKWARD,
		PL_FOURTH_BACKWARD
	};	
	
enum CURVELATCH				// Latching Curve in Patch or Stitch
	{
		CL_BACKWARD,
		CL_FORWARD
	};	

enum CIRCLETYPE
{
	CIRCLE_BY_ROT,
	CIRCLE_BY_NO3,
	CIRCLE_BY_2N_TI,
	CIRCLE_BY_2N_CC,
	CIRCLE_BY_2CN_TI_R
};

enum BEZIERTYPE
{
	BEZIER_BY_PTS,			// for Order 2:Pts=2 etc. INTERPOLATION
	BEZIER_BY_TAN,			// for Cubic(Order 4): End Tangents given
	BEZIER_BY_CON			// CONTROLS given
};

enum PARABOLATYPE
{
	PARABOLA_BY_NO3,		// 2nd pt. is considered Shoulder Pt.
	PARABOLA_BY_3N_TI
};

enum HYPERBOLATYPE
{
	HYPERBOLA_BY_NO3,		// 2nd pt. is considered Shoulder Pt
	HYPERBOLA_BY_3N_TI
};

enum ELLIPSETYPE
{
	ELLIPSE_BY_NO3,			// 2nd pt. is considered Shoulder Pt
	ELLIPSE_BY_3N_TI,
	ELLIPSE_BY_3N_AB,		// a = major Axis  / b = minor Axis
	ELLIPSE_BY_RECT
};

enum PROFILETYPE
{
	PRT_BLEND,				// BlendType
	PRT_STITCH				// StitchType
};
/////////////////////////////////////////////////////////////////////////////
#endif 

