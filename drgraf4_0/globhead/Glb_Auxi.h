#ifndef _GLB_AUXI_H
#define _GLB_AUXI_H 

#include "Def_Auxi.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct axtypes 
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
	}AXTYPES;
/////////////////////////////////////////////////////////////////	
AXTYPES	AxTypes[] =
	{ 
		"",						-1,			-2,		"",		0,0,	0,	0,
		"Aux. NODE",			AUXNODE,	2,		"AUXNODE",	0,0,	0,	0,
		"Aux. Input NODE",		AUXINOD,	2,		"AUXINODE",	0,0,	0,	0,
		"Aux. Control NODE",	AUXCNOD,	2,		"AUXCNODE",	0,0,	0,	0,
		"Aux. Final NODE",		AUXFNOD,	2,		"AUXFNODE",	0,0,	0,	0,
        //////////////////////////////////////////////////////////////////
		"Aux. Curve",			AUXCUR,		2,		"AUXCURVE",	1,2,	1,	0
		//////////////////////////////////////////////////////////////////
};
	int	nMax_AuxiTypes = (sizeof (AxTypes)/ sizeof(AxTypes[0]) );  		
///////////////////////////////////////////////
#endif
