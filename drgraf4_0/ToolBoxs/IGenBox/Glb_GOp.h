#ifndef _GLB_EOP_H
#define _GLB_EOP_H 

#include "Def_IGen.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct optypes 
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
	}OPTYPES;
/////////////////////////////////////////////////////////////////	
OPTYPES	OpTypes[] =
	{ 
		"",				-1,			-2,		"",				0,
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		"OPERATION Node",	N_OPER,		-2,		"",			-4,
		"EDIT Node",		N_EDIT,		-2,		"",			-4,
		"MOVE Node",		N_MOVE,		-2,		"",			-4, 
		"POST Node",		N_POST,		-2,		"",			-4, 
		"UNPOST Node",		N_UNPOST,	-2,		"",			-4, 
		"DELETE Node",		N_DELETE,	-2,		"",			-4, 
		///////////////////////////////////////////////////////
		"OPERATION Curve",	C_OPER,		-2,		"",			-4,
		"EDIT Curve",		C_EDIT,		-2,		"",			-4,
		"MOVE Curve",		C_MOVE,		-2,		"",			-4, 
		"POST Curve",		C_POST,		-2,		"",			-4, 
		"UNPOST Curve",		C_UNPOST,	-2,		"",			-4, 
		"DELETE Curve",		C_DELETE,	-2,		"",			-4, 
        ///////////////////////////////////////////////////////
 		"EDIT Patch",		P_EDIT,		-2,		"",			-4,
		"MOVE Patch",		P_MOVE,		-2,		"",			-4, 
		"POST Patch",		P_POST,		-2,		"",			-4, 
		"UNPOST Patch",		P_UNPOST,	-2,		"",			-4, 
		"DELETE Patch",		P_DELETE,	-2,		"",			-4, 
        ///////////////////////////////////////////////////////
 		"EDIT Solid",		S_EDIT,		-2,		"",			-4,
		"MOVE Solid",		S_MOVE,		-2,		"",			-4, 
		"POST Solid",		S_POST,		-2,		"",			-4, 
		"UNPOST Solid",		S_UNPOST,	-2,		"",			-4, 
		"DELETE Solid",		S_DELETE,	-2,		"",			-4, 
  	
};
	int	nMax_OperTypes = (sizeof (OpTypes)/ sizeof(OpTypes[0]) );  		
///////////////////////////////////////////////
#endif
