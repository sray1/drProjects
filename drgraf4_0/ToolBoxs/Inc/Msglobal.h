#ifndef _MSGLOBAL_H
#define _MSGLOBAL_H 

#include "eldefine.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct mstypes 
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
	}MSTYPES;
/////////////////////////////////////////////////////////////////	
MSTYPES	MsTypes[] =
	{ 
		"",				-1,			-2,		"",				0,
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
//		"PIPE",				PIPE,		2,		"PIPE",		1,
		"BEAM",				BEAM,		2,		"BEAM",		1,
		"TRUSS",			TRUSS,		2,		"TRUSS",	1,
		/////////
		"2D-QUAD",			QUAD,		2,		"",			2,
		"4 Node-QUAD",		QU_4,		2,		"",			2,
		"8 Node-QUAD",		QU_8,		2,		"",			2,
		"9 Node-QUAD",		QU_9,		2,		"",			2,
		"12 Node-QUAD",		QU_12,		2,		"",			2,
		"16 Node-QUAD",		QU_16,		2,		"",			2,
		/////////
		"2D-TRIANGLE",		TRIANGLE,	2,		"",			2,
		"3 Node-TRIANGLE",	TR_3,		2,		"",			2,
		"6 Node-TRIANGLE",	TR_6,		2,		"",			2,
		"9 Node-TRIANGLE",	TR_9,		2,		"",			2,
		"10 Node-TRIANGLE",	TR_10,		2,		"",			2,
		"THIN SHELL",		SHELL,		2,		"",			2,
		/////////
		"3D-PENTAHED",		PENTAHED, 	2,		"",			3,
		"6 Node-PENTAHED",	PE_6,		2,		"",			2,
		"15 Node-PENTAHED",	PE_15,		2,		"",			2,
		/////////
		"3D-TETRAHED",		TETRAHED,	2,		"",			3,
		"4 Node-TETRAHED",	TE_4,		2,		"",			2,
		"10 Node-TETRAHED",	TE_10,		2,		"",			2,
		/////////
		"3D-HEXAHED",		HEXAHED,	2,		"",			3,
		"8 Node-HEXAHED",	HE_8,		2,		"",			2,
		"20 Node-HEXAHED",	HE_20,		2,		"",			2,
		"21 Node-HEXAHED",	HE_21,		2,		"",			2,
    	///////////////////////////////////////////////////////
	};
	int	nMax_MeshTypes = (sizeof (MsTypes)/ sizeof(MsTypes[0]) );  		
///////////////////////////////////////////////
#endif
