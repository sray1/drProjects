#ifndef _SOEXTERN_H
#define _SOEXTERN_H 
//////////////////////
typedef struct sotypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
		char*		cardName;  	// dreamPipe	
		int			ObjDim;		// 0,1,2,3;	// Mesh Generation purpose							
	}SOTYPES;

extern SOTYPES FAR SoTypes[];
extern int nMax_SolidTypes;
///////////////////////////////////////////////////
#endif
 