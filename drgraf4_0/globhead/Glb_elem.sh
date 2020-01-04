#ifndef _ELGLOBAL_H
#define _ELGLOBAL_H 

#include "eldefine.h"
////////////////////////////// LEVEL
#define LEVEL_EUNUK			-1  // No Level
#define LEVEL_GRAPA			0	// Dr3DObjects/Individual Elements	
#define LEVEL_DADDY			1	// Patch/Curve
#define LEVEL_UNCLE     	2	// Curve
#define LEVEL_KIDDO     	3   // Generated Elements(in Patch/CurveLists)
////////////////////////////////
#define COMBO_NIDJ_LOC 	9     // Location of NidJ in element ComboBox
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct eltypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// -2   = NONE
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
								// 3	= 3dObject
		char*		cardName;  	// dreamPipe	
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
		BYTE		nVert;		// vertices;// Mesh Generation purpose							
		BYTE		nEdge;		// Edges;	// Mesh Generation purpose							
		BYTE		nFace;		// Faces;	// Mesh Generation purpose							
	}ELTYPES;
/////////////////////////////////////////////////////////////////	
ELTYPES	ElTypes[] =
	{ 
		"",					-1,			-2,		"",			0,0,	0,	0,
		"NODE",				NODE,		2,		"NODE",		0,0,	0,	0,
		"Control NODE",		CNODE,		2,		"CNODE",	0,0,	0,	0,
        ///////////////
		"PIPE",				PIPE,		2,		"PIPE",		1,2,	1,	0,
		"ELBOW",			ELBOW,		2,		"ELBOW",	-1,0,	0,	0,
		"BEAM",				BEAM,		2,		"BEAM",		1,2,	1,	0,
		"TRUSS",			TRUSS,		2,		"TRUSS",	1,2,	1,	0,
		"PLATE",			PLATE,		2,		"",			2,0,	0,	0,
		/////////
		"2D-QUAD",			QUAD,		2,		"",			2,0,	0,	0,
		"4 Node-QUAD",		QU_4,		2,		"",			2,4,	4,	0,
		"8 Node-QUAD",		QU_8,		2,		"",			2,8,	4,	0,
		"9 Node-QUAD",		QU_9,		2,		"",			2,9,	4,	0,
		"12 Node-QUAD",		QU_12,		2,		"",			2,12,	4,	0,
		"16 Node-QUAD",		QU_16,		2,		"",			2,16,	4,	0,
		/////////
		"2D-TRIANGLE",		TRIANGLE,	2,		"",			2,0,	0,	0,
		"3 Node-TRIANGLE",	TR_3,		2,		"",			2,3,	3,	0,
		"6 Node-TRIANGLE",	TR_6,		2,		"",			2,6,	3,	0,
		"9 Node-TRIANGLE",	TR_9,		2,		"",			2,9,	3,	0,
		"10 Node-TRIANGLE",	TR_10,		2,		"",			2,10,	3,	0,
		"THIN SHELL",		SHELL,		2,		"",			2,0,	0,	0,
		"BRICK",			FE3D,	 	2,		"",			3,0,	0,	0,
		/////////
		"3D-PENTAHED",		PENTAHED, 	2,		"",			3,0,	0,	0,
		"6 Node-PENTAHED",	PE_6,		2,		"",			3,6,	9,	5,
		"15 Node-PENTAHED",	PE_15,		2,		"",			3,15,	9,	5,
		/////////
		"3D-TETRAHED",		TETRAHED,	2,		"",			3,0,	0,	0,
		"4 Node-TETRAHED",	TE_4,		2,		"",			3,4,	6,	4,
		"10 Node-TETRAHED",	TE_10,		2,		"",			3,10,	6,	4,
		/////////
		"3D-HEXAHED",		HEXAHED,	2,		"",			3,0,	0,	0,
		"8 Node-HEXAHED",	HE_8,		2,		"",			3,8,	12,	6,
		"20 Node-HEXAHED",	HE_20,		2,		"",			3,20,	12,	6,
		"21 Node-HEXAHED",	HE_21,		2,		"",			3,21,	12,	6,
		///////////////////////////////////////////////////////
		"CURVE",			CURVE,		3,		"",			-5,0,	0,	0,
		"CIRCULAR Curve",	C_CIRCLE,	3,		"",			-5,0,	0,	0,
		"ELLIPTIC Curve",	C_ELLIPSE,	3,		"",			-5,0,	0,	0,
		"PARABOLIC Curve", 	C_PARABOLA,	3,		"",			-5,0,	0,	0,
		"LINEAR Curve",		C_LINEAR,	3,		"",			-5,0,	0,	0,
		"QUADRATIC Curve",  C_QUADRATIC,3,		"",			-5,0,	0,	0,
		"CUBIC Curve",		C_CUBIC,	3,		"",			-5,0,	0,	0,
		"HERMITE Curve",  	C_HERMITE, 	3,		"",			-5,0,	0,	0,
		"BEZIER Curve",		C_BEZIER,	3,		"",			-5,0,	0,	0,
		"B-SPLINE Curve",	C_BSPLINE,	3,		"",			-5,0,	0,	0,
		"NURB Curve",		C_NURB,		3,		"",			-5,0,	0,	0,
		"OPERATION Curve",	C_OPER,		-2,		"",			-4,0,	0,	0,
		"EDIT Curve",		C_EDIT,		-2,		"",			-4,0,	0,	0,
		"MOVE Curve",		C_MOVE,		-2,		"",			-4,0,	0,	0, 
		"POST Curve",		C_POST,		-2,		"",			-4,0,	0,	0, 
		"UNPOST Curve",		C_UNPOST,	-2,		"",			-4,0,	0,	0, 
		"DELETE Curve",		C_DELETE,	-2,		"",			-4,0,	0,	0, 
		"STITCH Curves",	C_STITCH,	-2,		"",			-4,0,	0,	0, 
		"SPAWN Curve",		C_SPAWN,	-2,		"",			-4,0,	0,	0, 
		"ROTATE Curve",		C_ROTATE,	-2,		"",			-4,0,	0,	0, 
		"TRANSLATE Curve",	C_XLATE,	-2,		"",			-4,0,	0,	0, 
		"SCALE Curve",		C_SCALE,	-2,		"",			-4,0,	0,	0, 
		"SHEAR Curve",		C_SHEAR,	-2,		"",			-4,0,	0,	0, // actually no such thing
		"Curve PROFILE",	C_PROFILE,	-2,		"",			-4,0,	0,	0, 
		///////////////////////////////////////////////////////
		"PATCH",			PATCH,		3,		"",			-5,0,	0,	0,
		"TENSOR Patch",		P_TENSOR,	3,		"",			-5,0,	0,	0,
		"GORDONS Patch",	P_GORDONS,	3,		"",			-5,0,	0,	0,
		"COONS Patch",		P_COONS,	3,		"",			-5,0,	0,	0,
		"ROTATED Patch",	P_ROTATE,	3,		"",			-5,0,	0,	0,
		"LOFTED Patch",   	P_LOFT,   	3,		"",			-5,0,	0,	0,
		"EXTRUDED Patch",	P_EXTRUDE,	3,		"",			-5,0,	0,	0,
		"DUCTED Patch",   	P_DUCT,   	3,		"",			-5,0,	0,	0,
		"SWEPT Patch",  	P_SWEEP,  	3,		"",			-5,0,	0,	0,
		"FLAT Patch",		P_FLATPLATE,3,		"",			-5,0,	0,	0,
		"LINEAR Patch",		P_LINEAR,	3,		"",			-5,0,	0,	0,
		"QUADRATIC Patch",  P_QUADRATIC,3,		"",			-5,0,	0,	0,
		"CUBIC Patch",		P_CUBIC,	3,		"",			-5,0,	0,	0,
		"BEZIER Patch",		P_BEZIER,	3,		"",			-5,0,	0,	0,
		"B-SPLINE Patch",	P_BSPLINE,	3,		"",			-5,0,	0,	0,
		"NURB Patch",		P_NURB,		3,		"",			-5,0,	0,	0,
		"OPERATION Patch",	P_OPER,		-2,		"",			-4,0,	0,	0,
		"EDIT Patch",		P_EDIT,		-2,		"",			-4,0,	0,	0,
		"MOVE Patch",		P_MOVE,		-2,		"",			-4,0,	0,	0, 
		"POST Patch",		P_POST,		-2,		"",			-4,0,	0,	0, 
		"UNPOST Patch",		P_UNPOST,	-2,		"",			-4,0,	0,	0, 
		"DELETE Patch",		P_DELETE,	-2,		"",			-4,0,	0,	0, 
		"STITCH Patches",	P_STITCH,	-2,		"",			-4,0,	0,	0, 
		"SPAWN Patch",		P_SPAWN,	-2,		"",			-4,0,	0,	0, 
		"ROTATE Patch",		P_ROTATE_B,	-2,		"",			-4,0,	0,	0, 
		"TRANSLATE Patch",	P_XLATE,	-2,		"",			-4,0,	0,	0, 
		"SCALE Patch",		P_SCALE,	-2,		"",			-4,0,	0,	0, 
		"SHEAR Patch",		P_SHEAR,	-2,		"",			-4,0,	0,	0, 
		"Patch PROFILE",	C_PROFILE,	-2,		"",			-4,0,	0,	0, 
		/////////////////////////////////////////////////////// solids
		"SOLID",			SOLID,		3,		"",			-5,0,	0,	0,
		"TENSOR Solid",		S_TENSOR,	3,		"",			-5,0,	0,	0,
		"GORDONS Solid",	S_GORDONS,	3,		"",			-5,0,	0,	0,
		"COONS Solid",		S_COONS,	3,		"",			-5,0,	0,	0,
		"ROTATED Solid",	S_ROTATE,	3,		"",			-5,0,	0,	0,
		"LOFTED Solid",   	S_LOFT,   	3,		"",			-5,0,	0,	0,
		"EXTRUDED Solid",	S_EXTRUDE,	3,		"",			-5,0,	0,	0,
		"DUCTED Solid",   	S_DUCT,   	3,		"",			-5,0,	0,	0,
		"SWEPT Solid",  	S_SWEEP,  	3,		"",			-5,0,	0,	0,
		"FLAT Solid",		S_FLATPLATE,3,		"",			-5,0,	0,	0,
		"LINEAR Solid",		S_LINEAR,	3,		"",			-5,0,	0,	0,
		"QUADRATIC Solid",  S_QUADRATIC,3,		"",			-5,0,	0,	0,
		"CUBIC Solid",		S_CUBIC,	3,		"",			-5,0,	0,	0,
		"BEZIER Solid",		S_BEZIER,	3,		"",			-5,0,	0,	0,
		"B-SPLINE Solid",	S_BSPLINE,	3,		"",			-5,0,	0,	0,
		"NURB Solid",		S_NURB,		3,		"",			-5,0,	0,	0,
		"OPERATION Solid",	S_OPER,		-2,		"",			-4,0,	0,	0,
		"EDIT Solid",		S_EDIT,		-2,		"",			-4,0,	0,	0,
		"MOVE Solid",		S_MOVE,		-2,		"",			-4,0,	0,	0, 
		"POST Solid",		S_POST,		-2,		"",			-4,0,	0,	0, 
		"UNPOST Solid",		S_UNPOST,	-2,		"",			-4,0,	0,	0, 
		"DELETE Solid",		S_DELETE,	-2,		"",			-4,0,	0,	0, 
		"STITCH Solids",	S_STITCH,	-2,		"",			-4,0,	0,	0, 
		"SPAWN Solid",		S_SPAWN,	-2,		"",			-4,0,	0,	0, 
		"ROTATE Solid",		S_ROTATE_B,	-2,		"",			-4,0,	0,	0, 
		"TRANSLATE Solid",	S_XLATE,	-2,		"",			-4,0,	0,	0, 
		"SCALE Solid",		S_SCALE,	-2,		"",			-4,0,	0,	0, 
		"SHEAR Solid",		S_SHEAR,	-2,		"",			-4,0,	0,	0, 
        ///////////////////////////////////////////////////////
		"SUPPORT",			SUPPORT,	0,		"",			 0,0,	0,	0,
		"LIN_SUPPORT",		LIN_SUPPORT,0,		"",			 0,0,	0,	0,
        ///////////////////////////////////////////////////////
		"NON_SUPPORT",		NON_SUPPORT,0,		"",			 0,0,	0,	0,
        ///////////////////////////////////////////////////////
		"EDIT",				E_EDIT,		-2,		"",			-4,0,	0,	0,
		"MOVE",				E_MOVE,		-2,		"",			-4,0,	0,	0,
		"POST",				E_POST,		-2,		"",			-4,0,	0,	0,
		"UNPOST",			E_UNPOST,	-2,		"",			-4,0,	0,	0
    	///////////////////////////////////////////////////////
};
	int	nMax_ElemTypes = (sizeof (ElTypes)/ sizeof(ElTypes[0]) );  		
///////////////////////////////////////////////
#endif
