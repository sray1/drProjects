#ifndef _PAEXTERN_H
#define _PAEXTERN_H 
//////////////////////
typedef struct patypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
		char*		cardName;  	// dreamPipe	
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
	}PATYPES;

extern PATYPES FAR PaTypes[];
extern int nMax_PatchTypes;
///////////////////////////////////////////////////
#endif
 