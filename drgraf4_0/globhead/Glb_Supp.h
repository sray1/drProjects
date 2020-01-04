#ifndef _GLB_SUPP_H
#define _GLB_SUPP_H 

#include "Def_Supp.h" 
////////////////////////////////////////////////////////
typedef struct sutypes 
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
	}SUTYPES;
/////////////////////////////////////////////////////////////////	
SUTYPES	SuTypes[] =
	{ 
		"",							-1,				-2,		"",		 0,0,	0,	0,
        ///////////////////////////////////////////////////////
		"SUPPORT",					SUPPORT,			0,		"",		 0,0,	0,	0,
		"LIN_SUPPORT",				LIN_SUPPORT,		0,		"",		 0,0,	0,	0,
		"NON_SUPPORT",				NON_SUPPORT,		0,		"",		 0,0,	0,	0,
 		"SUPPORT_RIGID",			SUPPORT_RIGID,		0,		"",		 0,0,	0,	0,
 		"SUPPORT_LINSPRING",		SUPPORT_LINSPRING,	0,		"",		 0,0,	0,	0,
 		"SUPPORT_LINSNUBBER",		SUPPORT_LINSNUBBER,	0,		"",		 0,0,	0,	0,
 		"SUPPORT_NLSPRING",			SUPPORT_NLSPRING,	0,		"",		 0,0,	0,	0,
 		"SUPPORT_NLSNUBBER",		SUPPORT_NLSNUBBER,	0,		"",		 0,0,	0,	0,
		///////////////////////////////////////////////////////
		"Nodal Rigid Support",		NSUP_RIGID,		0,		"",		 0,0,	0,	0,			
		"Nodal Linear Spring",		NSUP_LINSPRING,	0,		"",		 0,0,	0,	0,			
		"Nodal Linear Snubber",		NSUP_LINSNUBBER,0,		"",		 0,0,	0,	0,			
		"Nodal NonLinear Spring",	NSUP_NLSPRING,	0,		"",		 0,0,	0,	0,			
		"Nodal NonLinear Snubber",	NSUP_NLSNUBBER,	0,		"",		 0,0,	0,	0,			
		///////////////////////////////////////////
		"Curve Rigid Support",		CSUP_RIGID,		0,		"",		 0,0,	0,	0,			
		"Curve Linear Spring",		CSUP_LINSPRING,	0,		"",		 0,0,	0,	0,			
		"Curve Linear Snubber",		CSUP_LINSNUBBER,0,		"",		 0,0,	0,	0,			
		"Curve NonLinear Spring",	CSUP_NLSPRING,	0,		"",		 0,0,	0,	0,			
		"Curve NonLinear Snubber",	CSUP_NLSNUBBER,	0,		"",		 0,0,	0,	0,			
		///////////////////////////////////////////
		"Patch Rigid Support",		PSUP_RIGID,		0,		"",		 0,0,	0,	0,			
		"Patch Linear Spring",		PSUP_LINSPRING,	0,		"",		 0,0,	0,	0,			
		"Patch Linear Snubber",		PSUP_LINSNUBBER,0,		"",		 0,0,	0,	0,			
		"Patch NonLinear Spring",	PSUP_NLSPRING,	0,		"",		 0,0,	0,	0,			
		"Patch NonLinear Snubber",	PSUP_NLSNUBBER,	0,		"",		 0,0,	0,	0,			
		///////////////////////////////////////////
		"Solid Rigid Support",		SSUP_RIGID,		0,		"",		 0,0,	0,	0,			
		"Solid Linear Spring",		SSUP_LINSPRING,	0,		"",		 0,0,	0,	0,			
		"Solid Linear Snubber",		SSUP_LINSNUBBER,0,		"",		 0,0,	0,	0,			
		"Solid NonLinear Spring",	SSUP_NLSPRING,	0,		"",		 0,0,	0,	0,			
		"Solid NonLinear Snubber",	SSUP_NLSNUBBER,	0,		"",		 0,0,	0,	0			
		///////////////////////////////////////////
};
	int	nMax_SuppTypes = (sizeof (SuTypes)/ sizeof(SuTypes[0]) );  		
///////////////////////////////////////////////
#endif
