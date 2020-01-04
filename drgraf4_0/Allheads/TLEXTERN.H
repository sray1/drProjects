#ifndef _TLEXTERN_H
#define _TLEXTERN_H 
//////////////////////
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
extern TLTYPES FAR TLTypes[];
extern	int	nMax_TLevelTypes;  		
///////////////////////////////////////////////
#endif
