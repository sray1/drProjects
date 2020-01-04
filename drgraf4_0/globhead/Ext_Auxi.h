#ifndef _AUXITERN_H
#define _AUXITERN_H 


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
	
extern AXTYPES FAR AxTypes[];
extern int nMax_AuxiTypes;
////////////////////////////
#endif

