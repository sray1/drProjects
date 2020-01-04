#ifndef _GLB_ELEM_H
#define _GLB_ELEM_H 

#include "Def_IGen.h"
#include "Def_Elem.h"
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
		"0D Element",		FE0D,		2,		"VERTX",	0,0,	0,	0,
		"Input NODE",		NODE,		2,		"NODE",		0,0,	0,	0,
		"Control NODE",		CNODE,		2,		"CNODE",	0,0,	0,	0,
		"Mesh NODE",		MNODE,		2,		"MNODE",	0,0,	0,	0,
        //////////////////////////////////////////////////////////////////
		"1D Element",		FE1D,		2,		"EDGE",		1,2,	1,	0,
		"PIPE",				PIPE,		2,		"PIPE",		1,2,	1,	0,
		"ELBOW",			ELBOW,		2,		"ELBOW",	-1,0,	0,	0,
		"BEAM",				BEAM,		2,		"BEAM",		1,2,	1,	0,
		"TRUSS",			TRUSS,		2,		"TRUSS",	1,2,	1,	0,
		//////////////////////////////////////////////////////////////////
		"2D Element",		FE2D,		2,		"FACE",		2,0,	0,	0,
//		"PLATE",			PLATE,		2,		"",			2,0,	0,	0,
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
		//////////////////////////////////////////////////////////////////
		"3D Element",		FE3D,	 	2,		"BRICK",	3,0,	0,	0,
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
		"21 Node-HEXAHED",	HE_21,		2,		"",			3,21,	12,	6
		///////////////////////////////////////////
};
	int	nMax_ElemTypes = (sizeof (ElTypes)/ sizeof(ElTypes[0]) );  		
///////////////////////////////////////////////
#endif
