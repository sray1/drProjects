#ifndef _DEF_MESH_H
#define _DEF_MESH_H
////////////////////////////////////////// Last Number already assigned
//#define MESH_LAST_NUMBER	500
////////////////////////////////////////// For Global Processing
#define GREF_VRTX			500        
#define GREF_EDGE			501        
#define GREF_FACE			502        
#define GREF_CUBE			503        
///////////////////////////////////////////////////////////// GLOBALS
enum REF_QUAD			// Refinement
	{
		RQ_SUBDIV,		// SubDivide Globally(needs div factor)
		RQ_AUTO,		// RQ_SHORTDIAG iff NonCoPlanar		1 Quad or 2 Tri
		RQ_NOREF,		// leave alone						1 Quad
		RQ_SHORTDIAG,	// shorter Diag						2 Tri
		RQ_INTERSECT,	// IntersectionDiag					4 Tri
		RQ_CENTROID,	// Centroid							4 Tri
		RQ_MIDCENSHORT	// MidPtCentroidShortDiag			8 Tri
	};

enum REF_TRI			// Refinement
	{
		RT_SUBDIV,		// SubDivide Globally(needs div factor)
		RT_AUTO,		// = No Split (RT_NOREF)			1 Tri
		RT_NOREF,		// leave alone						1 Tri
		RT_CENTROID,	// Centroid							3 Tri
		RT_MIDCEN		// MidPtCentroid					4 Tri
	};

enum ORIENT
	{
		OT_ANTICLOCK,
		OT_CLOCKWISE,
		OT_DUALSIDED	//  forViewNavigation thro' Interior
	};

enum ELEM_DEGREE
	{
		ED_LINEAR,
		ED_QUADRATIC,
		ED_CUBIC,
		ED_QUARTIC,
		ED_QUINTIC,
		ED_MIXED		// for Iso-parametric Elements
	};
/////////////////////////////////////////////////////////////////////////////
#endif 

