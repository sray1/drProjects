#ifndef STR_DRAW_H
#define STR_DRAW_H 
/////////////////////////////////
typedef struct drtypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with object
		int			type;  		// 0 	= edit & move tool(for button management)
								// 1	= object that can be edited & moved
								// 2	= independent tool other than move/edit
								// 3	= 3dObject
		char*		otherName; 	// name,if needed
	}DRTYPES;
typedef struct
{
	unsigned short
		gridtype	:1, // 0= drawgrid; 1= datagrid for snap
		screenful	:1, // 1= yes
		alignment	:1, // 0= min pt.;  1= alignment pt reqd.	
		left		:1,
		right		:1,
		top			:1,
		bottom		:1,
		back		:1,
		front		:1,
		connectX	:1,
		connectY	:1,
		connectZ	:1,
		rotation	:1,	// 0= no rotation; 1= yes for snapping data
		filler		:3;
}	GR_INFO, *pGR_INFO;
/////////////////////////////////
#endif
