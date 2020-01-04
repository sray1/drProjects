#ifndef _GLB_VIEW_H
#define _GLB_VIEW_H
///////////////////////////////////////////////////////////// GLOBALS
////////////////////////////// ZOOM
#define ZOOM_USER			1
#define ZOOM_FIT			3
////////////////////////////// VIEW
#define	VIEW12				1 	             
#define	VIEW23				2 	             
#define	VIEW31				3 	             
#define	VIEWISO				4 
#define VIEWDAT				5
#define VIEWSTATIC_IN		6
#define VIEWSPECTRA_IN		7
#define VIEWHISTORY_IN		8
#define VIEWDECK			9
//////////////////////////////
enum XFMODE
	{
		XF_REPLACE,
		XF_PREMULT,
		XF_POSTMULT
	};	
enum VISIBILITY
	{
		VI_NOT_VISIBLE,
		VI_YES_VISIBLE
	};

enum MATRICES
	{ 
		MT_IDENTITY,
		MT_LOCAL,
		MT_VIEWER,
		MT_COMBINED,	// upto Win3D
		MT_VV3D,
		MT_PENULTI,		// upto Viewport3D
		MT_ULTIMATE		// projected to Viewport2D
	};
enum OPMODE
	{
		OP_OUTPUT,
		OP_INPUT,
		OP_STATIC_IN,
		OP_SPECTRA_IN,
		OP_DYNAMIC_IN
	};
////////////////////////////////////////////////
enum	RENDITION
{
		WF_PURE,
		WF_HIDDEN,
		FS_PAINTER,
		FS_ZBUFFER,
		ZB_GOURAUD,
		ZB_PHONG
};		
/////////////////////////////////////////////////////////////////////////////
#endif 

