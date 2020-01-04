#ifndef _DEF_ELEM_H
#define _DEF_ELEM_H 

////////////////////////////// LEVEL
#define LEVEL_EUNUK			-1  // No Level
#define LEVEL_GRAPA			0	// Dr3DObjects/Individual Elements	
#define LEVEL_DADDY			1	// Patch/Curve
#define LEVEL_UNCLE     	2	// Curve
#define LEVEL_KIDDO     	3   // Generated Elements(in Patch/CurveLists)
////////////////////////////////
#define COMBO_NIDJ_LOC 		9     // Location of NidJ in element ComboBox
#define	DEFAULT_STIFF		1.0e12
//////////////////////////////////////////
#define	NONE				-1
////////////////////////////////////////// Last Number already assigned
#define ELEM_LAST_NUMBER	1160
////////////////////////////////////////// Meshes
#define MESH3D				11591        
#define MESH2D				11592        
#define MESH1D				11593        
#define MESH0D				11594        
#define MBJ3D				11595 // combo of Meshes       
#define M1_PROFILE			11596        
#define M2_PROFILE			11597        
#define M3_PROFILE			11598
//#define SUPERMESH			11599        
#define MM_PROFILE			11599        
////////////////////////////////////////// Objects
#define ELEMENT				1159        
//////////////////////////////// 
#define FE0D				1124 
#define	BALLJOINT			11241		// BALL JOINT Library (FE0D)
#define	MCNODE				11242		// Mesh Control Node (FE0D)
//////////////////////////////// 
#define FE1D				1002 
#define	TRUSS 				1008		// TRUSS Library
/////////////////////////////////////////////////////////////////// Beam Library
#define	BEAM				1004
/////////////////////////////////////////////////////////////////// Pipe Library
#define PIPE				1125 
#define	ELBOW				1003
/////////////////////////////////////////////////////////////////// 2D FEMs Library
//#define	PLATE				1105		// PLATE Library 
#define	FE2D				1105		// PLATE Library 
////////////////////////////////////////////////////////
#define	TRIANGLE			1010		// Triangle Library
#define	TR_3				1107		// Triangle 3 Nodes
#define	TR_6				1108		// Triangle 6 Nodes
#define	TR_9				1109		// Triangle 9 Nodes
#define	TR_10				1110		// Triangle 10 Nodes
////////////////////////////////////////////////////////
#define	QUAD 				1009		// Quad Library
#define	QU_4				1111		// Quad 4 Nodes
#define	QU_8				1112		// Quad 8 Nodes
#define	QU_9				1113		// Quad 9 Nodes
#define	QU_12				1114		// Quad 12 Nodes
#define	QU_16				1115		// Quad 16 Nodes
///////////////////////////////////////////////////////////////////
//#define	PLANE 				1009		// PLANE Library (Membrane)
///////////////////////////////////////////////////////////////////
#define	SHELL 				1011		// SHELL Library
//////////////////////////////////////////////////////////////////// 3D FEMs Library
#define	FE3D				1106		// Brick
////////////////////////////////////////////////
#define	HEXAHED				1059		// HEXA Library
#define	HE_8				1116		// HEXA 8 Nodes
#define	HE_20				1117		// HEXA 20 Nodes
#define	HE_21				1118		// HEXA 21 Nodes
////////////////////////////////////////////////
#define	PENTAHED			1058		// PENTA Library
#define	PE_6				1119		// PENTA 6 Nodes
#define	PE_15				1120		// PENTA 15 Nodes
////////////////////////////////////////////////
#define	TETRAHED 			1057		// TETRA Library
#define	TE_4				1121		// TETRA 4 Nodes
#define	TE_10				1122		// TETRA 10 Nodes
//////////////////////////////////////////////////////////////////// ElemINFO
#define	ELEMINFO			1160		// ElemInfo List etc Holder
////////////////////////////////////////////////
#endif

