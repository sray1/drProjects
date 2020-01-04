#ifndef _MOEXTERN_H
#define _MOEXTERN_H 


typedef struct motypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// MO_TOOL 
								// MO_NONE
								// MO_OBJ_0D
								// MO_OBJ_1D
								// MO_OBJ_2D 
								// MO_OBJ_3D
	}MOTYPES;
	
extern MOTYPES FAR MoTypes[];
extern int nMax_MousTypes;
////////////////////////////
#endif

