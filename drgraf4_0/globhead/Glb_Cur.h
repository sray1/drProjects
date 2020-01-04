#ifndef _GLB_CUR_H
#define _GLB_CUR_H 

#include "Def_IGen.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct cutypes 
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
	}CUTYPES;
/////////////////////////////////////////////////////////////////	
CUTYPES	CuTypes[] =
	{ 
		"",				-1,			-2,		"",				0,
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		"CURVE",			CURVE,		3,		"",			-5,
		"CIRCULAR Curve",	C_CIRCLE,	3,		"",			-5,
		"ELLIPTIC Curve",	C_ELLIPSE,	3,		"",			-5,
		"PARABOLA Curve",  	C_PARABOLA,	3,		"",			-5,
		"LINEAR Curve",		C_LINEAR,	3,		"",			-5,
		"QUADRATIC Curve",  C_QUADRATIC,3,		"",			-5,
		"HERMITE Curve",  	C_HERMITE, 	3,		"",			-5,
		"BEZIER Curve",		C_BEZIER,	3,		"",			-5,
		"B-SPLINE Curve",	C_BSPLINE,	3,		"",			-5,
		"NURB Curve",		C_NURB,		3,		"",			-5,
		"OPERATION Curve",	C_OPER,		-2,		"",			-4,
		"EDIT Curve",		C_EDIT,		-2,		"",			-4,
		"MOVE Curve",		C_MOVE,		-2,		"",			-4, 
		"POST Curve",		C_POST,		-2,		"",			-4, 
		"UNPOST Curve",		C_UNPOST,	-2,		"",			-4, 
		"DELETE Curve",		C_DELETE,	-2,		"",			-4, 
		"SPLICE Curve",		C_COP_STITCH,	-2,		"",			-4, 
		"SPAWN Curve",		C_COP_SPAWN,	-2,		"",			-4 
        ///////////////////////////////////////////////////////
    	
};
	int	nMax_CurveTypes = (sizeof (CuTypes)/ sizeof(CuTypes[0]) );  		
///////////////////////////////////////////////
#endif
