#ifndef _DEF_VIEW_H
#define _DEF_VIEW_H
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
#define VIEWMESH			9
#define VIEWMESHDATA		10
#define VIEWDECK			11
#define VIEWFORMDATA		12
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
		OP_OUTPUT,		// 3D View for Generator/Mesh
		OP_INPUT,		// 12View etc. for Generator/Mesh
		OP_STATIC_IN,
		OP_SPECTRA_IN,
		OP_HISTORY_IN
	};
enum IN_STATIC
	{
		IST_DISPLACE,
		IST_FORCE,
		IST_PRESSURE,
		IST_THERMAL,
		IST_WEIGHT,
	};
enum IN_SPECTRA
	{
		ISP_DISPLACE,
		ISP_VELOCITY,
		ISP_ACCELER,
		ISP_FORCE,
		ISP_PRESSURE,
		ISP_THERMAL
	};
enum IN_HISTORY
	{
		IHI_DISPLACE,
		IHI_VELOCITY,
		IHI_ACCELER,
		IHI_FORCE,
		IHI_PRESSURE,
		IHI_THERMAL
	};
////////////////////////////////////////////////
enum	RENDITION
{
		WF_PURE		= 101,
		WF_HIDDEN	= 102,
		FS_PAINTER	= 103,
		FS_ZBUFFER	= 104,
		ZB_GOURAUD	= 105,
		ZB_PHONG	= 106
};
////////////////////////////////////////////////		
enum	VIEWOPER
{
		VO_ROTATE	= 201,
		VO_ZOOM		= 202,
		VO_PAN		= 203,
		VO_ANIMATE	= 204
};
/////////////////////////////////////////////////////////////////////////////
#endif 

