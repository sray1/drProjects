#ifndef _GLB_OBJ_H
#define _GLB_OBJ_H 

#include "Def_IGen.h"
#include "Def_Elem.h"
#include "Def_Supp.h"
#include "Def_StaL.h"
////////////////////////////////
//****************************************************************/ 
////////////////////////////////////////////////////////
typedef struct objtypes 
	{
		LPCTSTR   	Name;  		// internal name
		UINT		ID;   		// ID number associated with element
	}OBJTYPES;
/////////////////////////////////////////////////////////////////	
OBJTYPES	ObjTypes[] =
	{ 
		"INPUT NODE",				NODE,
		"CONTROL NODE",				CNODE,
		"CURVE",					CURVE,
		"PROFILE_CURVE",			C_PROFILE,
		"PATCH",					PATCH,				
		"PROFILE_PATCH",			P_PROFILE,			
		"SOLID",					SOLID,				
		"PROFILE_SOLID",			S_PROFILE,			
		"OBJECT ASSEMBLY",			OBJ3D,				
		////////////////////////////////////////////////
		"MESH NODE",				MNODE,				
		"MESH CONTROL NODE",		MCNODE,				
		"1D MESH",					MESH1D,				
		"PROFILE_1D MESH",			M1_PROFILE,			
		"2D MESH",					MESH2D,				
		"PROFILE_2D MESH",			M2_PROFILE,			
		"3D MESH",					MESH3D,				
		"PROFILE_3D MESH",			M3_PROFILE,			
		"MESH ASSEMBLY",			MBJ3D,				
		////////////////////////////////////////////////
		"ELEMENT",					ELEMENT,			
		"0D FINITE ELEMENT",		FE0D,				
		"BALL JOINT",				BALLJOINT,			
		//////////////////////////////// 
		"1D FINITE ELEMENT",		FE1D,					
		"TRUSS",					TRUSS,					
		"BEAM",						BEAM,				
		"PIPE",						PIPE,					
		"ELBOW",					ELBOW,					
		//////////////////////////////// 
		"2D FINITE ELEMENT",		FE2D,				
		"TRIANGULAR ELEMENT",		TRIANGLE,				
		"3 NODE TRIANGLE",			TR_3,					
		"6 NODE TRIANGLE",			TR_6,					
		"9 NODE TRIANGLE",			TR_9,					
		"10 NODE TRIANGLE",			TR_10,					
		//
//		"QUADRILATERAL ELEMENT",	QUAD,					
		"4 NODE QUAD.",				QU_4,					
		"8 NODE QUAD.",				QU_8,					
		"9 NODE QUAD.",				QU_9,				
		"12 NODE QUAD.",			QU_12,					
		"16 NODE QUAD.",			QU_16,					
		//////////////////////////////// 
		"SHELL",					SHELL,					
		//////////////////////////////// 
//		"3D FINITE ELEMENT",		FE3D,				
//		"HEXAHEDRAL ELEMENT",		HEXAHED,				
		"8 NODE HEXAHEDRAL",		HE_8,					
		"20 NODE HEXAHEDRAL",		HE_20,					
		"21 NODE HEXAHEDRAL",		HE_21,				
		//
//		"PENTAHEDRAL ELEMENT",		PENTAHED,				
		"6 NODE PENTAHEDRAL",		PE_6,					
		"15 NODE PENTAHEDRAL",		PE_15,					
		//
//		"TETRAHEDRAL ELEMENT",		TETRAHED,				
		"4 NODE TETRAHEDRAL",		TE_4,					
		"10 NODE TETRAHEDRAL",		TE_10,					
		////////////////////////////////////////////////
//		"SUPPORT",					SUPPORT,			
		"LINEAR SUPPORT",			LIN_SUPPORT,			
		"NONLINEAR SUPPORT",		NON_SUPPORT,			
// 		"SUPPORT_RIGID",			SUPPORT_RIGID,			
// 		"SUPPORT_LINSPRING",		SUPPORT_LINSPRING,		
// 		"SUPPORT_LINSNUBBER",		SUPPORT_LINSNUBBER,		
// 		"SUPPORT_NLSPRING",			SUPPORT_NLSPRING,		
// 		"SUPPORT_NLSNUBBER",		SUPPORT_NLSNUBBER,	
		////////////////////////////////////////////////
		"STATIC LOAD",				STATICLOAD,
//		"FORCE",					FORCE,					
//		"DISPLACEMENT",				DISPLACE,				
//		"PRESUURE",					PRESSURE,				
//		"THERMAL",					THERMAL,				
//		"LUMP WTS.",				LUMPWT					
};
	int	nMax_ObjectTypes = (sizeof (ObjTypes)/ sizeof(ObjTypes[0]) );  		
///////////////////////////////////////////////
#endif
