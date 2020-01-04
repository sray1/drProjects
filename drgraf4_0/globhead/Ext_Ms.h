#ifndef _MSEXTERN_H
#define _MSEXTERN_H 


typedef struct mstypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= edit & move tool(for button management)
								// 1	= object that can be edited & moved
								// 2	= independent tool other than move/edit
								// 3	= 3dObject
		char*		otherName; 	// name,if needed
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
	}MSTYPES;
	
extern MSTYPES FAR MsTypes[];
extern int nMax_MeshTypes;
////////////////////////////
#endif

