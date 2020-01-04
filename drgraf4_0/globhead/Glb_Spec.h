#ifndef _GLB_SPEC_H
#define _GLB_SPEC_H 

#include "Def_Spec.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct sptypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= tool
								// 1	= specs
								// 2	= operation
		char*		otherName; 	// name,if needed
	}SPTYPES;
/////////////////////////////////////////////////////////////////	
SPTYPES	SpTypes[] =
	{ 
		"",					-1,				-2,		"",
		"DataWindow",		DATAWINDOW,		2,		"",
		"Booleans",			BOOLEANS,		2,		"",
		"DrFont",			DRFONT,			1,		"",
		"DrPen",			DRPEN,			0,		"",
		"HitNet",			HITNET,			1,		"",
		"Layer",			LAYER,			1,		"",
		"Mapfactor",		MAPFACTOR,		1,		"",
		"Unit",				UNIT,			1,		"",
		"Precision",		PRECISION,		1,		"",
		"ScaleFactor",		SCALEFACTOR,	1,		"",
		"PatcMenu",			PATCHMNU,		1,		"",
		"Obj3DMenu",		OBJ3DMNU,		1,		""
        ///////////////
    	
};
	int	nMax_SpecTypes = (sizeof (SpTypes)/ sizeof(SpTypes[0]) );  		
/////////////////////////////////
#endif
