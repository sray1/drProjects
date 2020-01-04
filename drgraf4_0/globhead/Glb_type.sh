#ifndef _GLOBTYPE_H
#define _GLOBTYPE_H
///////////////////////////////////////////////////////////// GLOBALS
typedef unsigned long 		HUGESIZE;
//16: typedef	char __huge 		*HUGEBLK;	
typedef	char 	*HUGEBLK;	
#define	HUGECOPY(s,d,sz)	while( (sz)-- ) *(d)++ = *(s)++ 
/////////////////////////////////////////////////////////// 
typedef int	__far			*pINT;
typedef double	__far		*pDOUBLE;
typedef unsigned int __far 	*pUINT;
typedef RECT __far			*pRECT;
/////////////////////////////////
typedef	struct 
	{
		long x;
		long y;
		long z;
	}LPOINT3, __far *pLPOINT3;
			
typedef	struct 
	{
		int x;
		int y;
		int z;
	}POINT3, __far *pPOINT3;
			
typedef	struct 
	{
		long x;
		long y;
	}LPOINT, __far *pLPOINT;	
		
typedef	struct 
	{
		float x;
		float y;
		float z;
	}WORLF, __far *pWORLF; 
	
typedef	struct 
	{
		double x;
		double y;
		double z;
	} WORLD, __far *pWORLD; 
	
typedef	struct 
	{
		long left;
		long top;
		long right;
		long bottom;
	}	LRECT, __far *pLRECT;
						
typedef struct {
	double v[4];
}	VECTOR, __far *pVECTOR;   // Homogenous Coords

typedef struct {
	double v[4][4];
}	MATRIX, __far *pMATRIX;   // Homogenous Coords

////////////////////////////
typedef	double	DMA24[2][4];		// for Rational Linear
typedef	double	(*PDMA24)[4];
typedef	double	DMA22[2][2];		// for Basis Matrix
typedef	double	(*PDMA22)[2];
////////////////////////////
typedef	double	DMA34[3][4];		// for Rational Quadratic
typedef	double	(*PDMA34)[4];
typedef	double	DMA33[3][3];		// for Basis Matrix
typedef	double	(*PDMA33)[3];
////////////////////////////
typedef	double	DMA44[4][4];		// for Cubic
typedef	double	(*PDMA44)[4];
//////////////////////////////////////////////// Surface:Finite Difference
typedef	double	DMAT[4][4];
typedef	double	(*PDMAT)[4];
typedef WORLD	WMAT[4][4];		// cubic
typedef WORLD	(*PWMAT)[4];
typedef WORLD	WMAT3[3][3];	// quadratic
typedef WORLD	(*PWMAT3)[3];
typedef WORLD	WMAT2[2][2];	// linear
typedef WORLD	(*PWMAT2)[2];
////////////////////////////                   
typedef	double (*PDMA3)[4];		// inter_C3
//////////////////////////////////////////////// Horner: Surface	
typedef pWORLD	(*PW44)[4];		// surface
typedef pDOUBLE	(*PD44)[4];
typedef pWORLD	(*PW4);			// surface
typedef pDOUBLE	(*PD4);
//////////////////////////////////////////////// Horner: Solid	
typedef pWORLD	(*PW444)[4][4];	// solid
typedef pDOUBLE	(*PD444)[4][4];
/////////////////////////////////////////////////////////////////////////////
#endif 

