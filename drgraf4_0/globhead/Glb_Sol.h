#ifndef _GLB_SOL_H
#define _GLB_SOL_H 

#include "Def_IGen.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct sotypes 
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
	}SOTYPES;
/////////////////////////////////////////////////////////////////	
SOTYPES	SoTypes[] =
	{ 
		"",				-1,			-2,		"",				0,
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		"SOLID",			SOLID,		3,		"",			-5,
		"Gordons Solid",	S_GORDON,	3,		"",			-5,
		"Tensor Solid",		S_TENSOR,	3,		"",			-5,
		"Coons Solid",		S_COONS,	3,		"",			-5,
		"ROTATED Solid",	S_ROTATE,	3,		"",			-5,
		"LOFTED Solid",   	S_LOFT,   	3,		"",			-5,
		"EXTRUDED Solid",	S_EXTRUDE,	3,		"",			-5,
		"DUCTED Solid",   	S_DUCT,   	3,		"",			-5,
		"SWEPT Solid",  	S_SWEEP,  	3,		"",			-5,
		"FLAT Solid",		S_FLATPLATE,3,		"",			-5,
		"EDIT Solid",		S_EDIT,		-2,		"",			-4,
		"MOVE Solid",		S_MOVE,		-2,		"",			-4, 
		"POST Solid",		S_POST,		-2,		"",			-4, 
		"UNPOST Solid",		S_UNPOST,	-2,		"",			-4, 
  		"Delete Solid",		S_DELETE,	-2,		"",			-4, 
		"SPLICE Solid",		S_COP_STITCH,	-2,		"",			-4, 
		"SPAWN Solid",		S_COP_SPAWN,	-2,		"",			-4 
      ///////////////////////////////////////////////////////
    	
};
	int	nMax_SolidTypes = (sizeof (SoTypes)/ sizeof(SoTypes[0]) );  		
///////////////////////////////////////////////
#endif
