#ifndef _CUEXTERN_H
#define _CUEXTERN_H 
//////////////////////
typedef struct cutypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
		char*		cardName;  	// dreamPipe	
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
	}CUTYPES;

extern CUTYPES FAR CuTypes[];
extern int nMax_CurveTypes;
///////////////////////////////////////////////////
#endif
 