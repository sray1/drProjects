#ifndef _GLB_PAT_H
#define _GLB_PAT_H 

#include "Def_IGen.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct patypes 
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
	}PATYPES;
/////////////////////////////////////////////////////////////////	
PATYPES	PaTypes[] =
	{ 
		"",				-1,			-2,		"",				0,
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		"PATCH",			PATCH,		3,		"",			-5,
		"Tensor Patch",		P_TENSOR,	3,		"",			-5,
		"Gordons Patch",	P_GORDON,	3,		"",			-5,
		"Coons Patch",		P_COONS,	3,		"",			-5,
		"ROTATED Patch",	P_ROTATE,	3,		"",			-5,
		"LOFTED Patch",   	P_LOFT,   	3,		"",			-5,
		"EXTRUDED Patch",	P_EXTRUDE,	3,		"",			-5,
		"DUCTED Patch",   	P_DUCT,   	3,		"",			-5,
		"SWEPT Patch",  	P_SWEEP,  	3,		"",			-5,
		"FLAT Patch",		P_FLATPLATE,3,		"",			-5,
		"EDIT Patch",		P_EDIT,		-2,		"",			-4,
		"MOVE Patch",		P_MOVE,		-2,		"",			-4, 
		"Delete Patch",		P_DELETE,	-2,		"",			-4, 
		"UNPOST Patch",		P_UNPOST,	-2,		"",			-4, 
		"POST Patch",		P_POST,		-2,		"",			-4, 
		"SPLICE Patch",		P_COP_STITCH,	-2,		"",			-4, 
		"SPAWN Patch",		P_COP_SPAWN,	-2,		"",			-4 
        ///////////////////////////////////////////////////////
    	
};
	int	nMax_PatchTypes = (sizeof (PaTypes)/ sizeof(PaTypes[0]) );  		
///////////////////////////////////////////////
#endif
