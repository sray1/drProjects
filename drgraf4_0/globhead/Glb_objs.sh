#ifndef _GLOBOBJS_H
#define _GLOBOBJS_H
///////////////////////////////////////////////////////////// GLOBALS
#define MAX_POLY_NODES		4 
////////////////////////////// Objects in DrObject->SetElemType()
#define SPEL_OBJECT			1	// Viewable/NOT Renderable: Structural SpectralLoads-Pseudovel etc
#define DYNL_OBJECT			1	// Viewable/NOT Renderable: Structural DynamicLoads-Eq.,Timehis etc
#define STAL_OBJECT			1	// Viewable/NOT Renderable: Structural StaticLoads-Force,Disp etc
#define ELEM_OBJECT			1	// Viewable/NOT Renderable: Structural Elements-Node,Pipe etc
#define DRAW_OBJECT			2   // Viewable/NOT Renderable: Drawing Objects- Freehand,Label etc
#define EL3D_OBJECT			3   // Viewable/3D  RENDERABLE: Structural Elements- Plate etc.
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
/////////////////////////////////////////////////////////////////////////////
#endif 

