#ifndef _3DGLOBAL_H
#define _3DGLOBAL_H 

#include "3Ddefine.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct D3types 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= tool
								// 1	= specs
								// 2	= operation
		char*		otherName; 	// name,if needed
	}D3TYPES;
/////////////////////////////////////////////////////////////////	
D3TYPES	D3Types[] =
	{ 
		"",					-1,				-2,		"",
		"XFORM",			XFORM,			2,		""
        ///////////////
    	
};
	int	nMax_Dr3DTypes = (sizeof (D3Types)/ sizeof(D3Types[0]) );  		
/////////////////////////////////
#endif
