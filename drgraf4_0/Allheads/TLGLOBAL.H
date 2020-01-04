#ifndef _TLGLOBAL_H
#define _TLGLOBAL_H 

#include "TLdefine.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct TLtypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with TLement
		int			type;  		// -1 	= metacard
								// -2   = NONE
								// 0	= TLement
								// 1	= cardtype
								// 2	= TLem+card both 
								// 3	= 3dObject
		char*		cardName;  	// dreamPipe	
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
	}TLTYPES;
/////////////////////////////////////////////////////////////////	
TLTYPES	TLTypes[] =
	{ 
		"",				-1,			-2,		"",				-1,
		"OBJ3D",		OBJ3D,		3,		"OBJ3D",		-1
        ///////////////
    	
};
	int	nMax_TLevelTypes = (sizeof (TLTypes)/ sizeof(TLTypes[0]) );  		
///////////////////////////////////////////////
#endif
