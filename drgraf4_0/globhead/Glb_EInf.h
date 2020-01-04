#ifndef _GLB_EINF_H
#define _GLB_EINF_H 

#include "Def_Elem.h"
#include "Def_EInf.h"
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct eitypes 
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
	}EITYPES;
/////////////////////////////////////////////////////////////////	
EITYPES	EiTypes[] =
	{ 
		"",					-1,			-2,		"",			0,0,	0,	0,
		"Elem_Info",	ELEMINFO,		1,		"",			0,0,	0,	0,	
		"Prop_Ball",	PROP_BALL,		1,		"",			0,0,	0,	0,	
		/// 1D
		"Prop_PIPE",	PROP_PIPE,		1,		"",			0,0,	0,	0,	
		"Prop_ELBOW",	PROP_ELBOW,		1,		"",			0,0,	0,	0,	
		"Prop_BEAM",	PROP_BEAM,		1,		"",			0,0,	0,	0,	
		"Prop_TRUSS",	PROP_TRUSS,		1,		"",			0,0,	0,	0,	
		/// 2D
		"Prop_2D",		PROP_2D,		1,		"",			0,0,	0,	0,	
		/// 3D
		"Prop_3D",		PROP_3D,		1,		"",			0,0,	0,	0,	
		//////////////////////////////////////////////// Mat
		"Mat_Ball",		MAT_BALL,		1,		"",			0,0,	0,	0,	
		/// 1D
		"Mat_PIPE",		MAT_PIPE,		1,		"",			0,0,	0,	0,	
		"Mat_ELBOW",	MAT_ELBOW,		1,		"",			0,0,	0,	0,	
		"Mat_BEAM",		MAT_BEAM,		1,		"",			0,0,	0,	0,	
		"Mat_TRUSS",	MAT_TRUSS,		1,		"",			0,0,	0,	0,	
		/// 2D
		"Mat_2D",		MAT_2D,		1,		"",			0,0,	0,	0,	
		/// 3D
		"Mat_3D",		MAT_3D,		1,		"",			0,0,	0,	0,	
//////////////////////////////////////////////// Release
		"Release",		RELEASE,		1,		"",			0,0,	0,	0,	
//////////////////////////////////////////////// STRESSINDEX
		"SIndex",		SINDEX,		1,		"",			0,0,	0,	0,	
		///////////////////////////////////////////
};
	int	nMax_EInfTypes = (sizeof (EiTypes)/ sizeof(EiTypes[0]) );  		
///////////////////////////////////////////////
#endif
