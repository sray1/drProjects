#ifndef _DEF_OBJS_H
#define _DEF_OBJS_H
///////////////////////////////////////////////////////////// GLOBALS
#define MAX_POLY_NODES		4 
////////////////////////////// Objects in DrObject->SetElemType()
#define AUXI_OBJECT			1	// Viewable/Renderable: Auxilliary Objects etc
#define SPEL_OBJECT			1	// Viewable/NOT Renderable: Structural SpectralLoads-Pseudovel etc
#define DYNL_OBJECT			1	// Viewable/NOT Renderable: Structural DynamicLoads-Eq.,Timehis etc
#define STAL_OBJECT			1	// Viewable/NOT Renderable: Structural StaticLoads-Force,Disp etc
#define ELEM_OBJECT			1	// Viewable/NOT Renderable: Structural Elements-Node etc
#define MESH_OBJECT			1	// Viewable/NOT Renderable: Structural Elements-Node etc
#define DRAW_OBJECT			2   // Viewable/NOT Renderable: Drawing Objects- Freehand,Label etc
#define EL1D_OBJECT			3   // Viewable/3D  RENDERABLE: Structural Elements- Pipe etc.
#define EL2D_OBJECT			3   // Viewable/3D  RENDERABLE: Structural Elements- Plate etc.
#define EL3D_OBJECT			3   // Viewable/3D  RENDERABLE: Structural Elements- Hexa etc.
#define DR3D_OBJECT			4   // Viewable/3D  RENDERABLE: Drawing Objects- Sphere,Cone etc.
#define GENR_OBJECT			5   // Viewable/3D  RENDERABLE: Generator:CURVE & PATCH
#define TOOL_OBJECT			-1	// Not Viewable: Tools
#define SPEC_OBJECT			-2  // Not Viewable: Specials- Booleans, Font etc
#define OPER_OBJECT			-3  // Not Viewable: Operations- XForm etc 
////////////////////////////// LEVEL
#define LEVEL_EUNUK			-1  // No Level
#define LEVEL_GRAPA			0	// Dr3DObjects/Individual Elements	
#define LEVEL_DADDY			1	// Patch/Curve
#define LEVEL_UNCLE     	2	// Curve
#define LEVEL_KIDDO     	3   // Generated Elements(in Patch/CurveLists)
//////////////////////////////
enum LISTTYPE
	{
		LI_NODELIST,
		LI_CNODELIST,
		LI_ELEMLIST,
		LI_CURVELIST,
		LI_PATCHLIST,
		LI_SOLIDLIST
	};	
enum PROBDIMLIM
	{
		PDL_ZERO,
		PDL_ONE,
		PDL_TWO,
		PDL_THREE,
	};	
enum ELEMDIMLIM
	{
		EDL_ZERO,
		EDL_ONE,
		EDL_TWO,
		EDL_THREE,
	};	
enum CATEGORY
{
	CA_AUXILLIARY,		// Spectral,TimeHistory Nodes & Curves.
	CA_ANCILLARY,		// Twist,Spine,Radial etc.
	CA_ELEMENT,			// Node,Curve,Patch,Solid
	CA_RIGID,
	CA_LINSPR,
	CA_LINSNU,
	CA_NONSPR,
	CA_NONSNU,
	CA_FORCE,			// Boundary Conditions
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
	CA_HISACCEL,
	CA_HISINITIAL		// Initial Condition
};	
enum SUBCAT
{
	SC_TWIST,		// Twist,Spine,Radial etc.
	SC_SPINE,
	SC_RADIAL,
	SC_TRAN,
	SC_ROT,
	SC_AUXINODE,	// Auxilliary Input Nodes
	SC_AUXCNODE,	// Auxilliary Control Nodes
	SC_AUXFNODE,	// Auxilliary Final Nodes
	SC_AUXCURVE		// Distribution Input Curve
};	
/////////////////////////////////////////////////////////////////////////////
#endif 

