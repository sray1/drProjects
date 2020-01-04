#ifndef _GLOBALS_H
#define _GLOBALS_H
///////////////////////////////////////////////////////////// GLOBALS
//////////////////////////////// DRAWBOX ButtonSize
#define DB_BNSIZE_CX		40
#define	DB_BNSIZE_CY		40
#define	DB_IMAGE_CX			32 
#define	DB_IMAGE_CY			30
//#define	BNSIZE		18    
//////////////////////////////// ELEMBOX ButtonSize
#define EL_BNSIZE_CX		40
#define	EL_BNSIZE_CY		40
#define	EL_IMAGE_CX			32 
#define	EL_IMAGE_CY			30
////////////////////////////// 
#define	MAX_LAYER	 6
//////////////////////////// DrawBox Palette controls
#define LABEL_EDIT			0
#define FREEHAND_INSERT		1
#define	LABEL_MOVE			2
#define	RESERVED1			3
#define	DIMENSION			4
#define	FONT				5
#define	LABEL_INSERT		6
#define	GRID				7
#define ZOOM_SELECT			8
#define RECTANGLE			9
#define ROUND_RECT			10
#define ELLIPSE				11
#define ROUND_ELLIPSE		12
//////////////////////////
#define ZOOM		1
#define ZOOM_FIT	3
/////////////////////
#define	VIEW12	1 	             
#define	VIEW23	2 	             
#define	VIEW31	3 	             
#define	VIEWISO	4 
#define VIEWDAT	5
///////////////////////////
#define ELEMENT_BOX	1
#define DRAW_BOX	2	             
///////////////////////////
#define ID_CLOCK_TIMER    1
//////////////////////////
#define TOP_STATUSBAR	1
///////////////////////////
struct LPOINT3
	{
		long x;
		long y;
		long z;
	};		
struct POINT3
	{
		int x;
		int y;
		int z;
	};		
struct LPOINT
	{
		long x;
		long y;
	};		
struct WORLD
	{
		double x;
		double y;
		double z;
	};
struct LRECT
	{
		long left;
		long top;
		long right;
		long bottom;
	};					
/////////////////////////////////////////////////////////////////////////////
#endif 

