#ifndef _OBJMAP_H
#define _OBJMAP_H

/////////////////////////////////////////////////////////
#include <afxtempl.h>
typedef CMap< CString,  LPCSTR, UINT, UINT > DrObjectMap;
/////////////////////////////////////////////////////////
enum DROBJECT
{
	NODE,
	CNODE,
	CURVE,
	PROFILE_C,
	PATCH,
	PROFILE_P,
	SOLID,
	OBJ3D,
	//////
	MNODE,
	MCNODE,
	MESH1D,
	MESH2D,
	MESH3D,
	MBJ3D
};	
//////////////////////////////////////
#endif
