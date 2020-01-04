#ifndef _STR_MESH_H
#define _STR_MESH_H 


/////////////////////////////////////////////////////////////////////////////	  		
#define MAX_CORNERS_1D		2
#define MAX_CORNERS_2D		4
#define MAX_CORNERS_3D		21
#define MAX_EDGENODE_MID	2	// inter Nodes o----M1----M2----o : 2= Cubic 
#define MAX_EDGES_1D		1
#define MAX_EDGES_2D		4
#define MAX_EDGES_3D		12
#define MAX_FACES_2D		1
#define MAX_FACENODE_MID	4	// inter Nodes o-----o-----o----o : 4= Cubic 
								// inter Nodes o----M4-<---M3----o : CounterClockwise 
								// inter Nodes o----M1-->-M2----o :	from Outside  
								// inter Nodes o-----o-----o----o :  
#define MAX_FACES_3D		6
#define MAX_SOLIDNODE_MID	4	// : 4= Cubic 
#define	MAX_LOADS			4
////////////////////////////////////////////////////// For IsoParametric Elems
#define	MAX_CORNERS_1D_ISO	4	// Cubic:IsoParametric
#define	MAX_CORNERS_2D_ISO	16	// Cubic:IsoParametric
#define	MAX_CORNERS_3D_ISO	64	// Cubic:IsoParametric
#define MAX_EDGES_1D_ISO	3	// Effectively(for Cubic) for geometerical/Mesh Manipulation
#define MAX_EDGES_2D_ISO	12	// Effectively(for Cubic OnEachSide)
#define MAX_EDGES_3D_ISO	36	// Effectively(for Cubic OnEachFace)
////////////////////////////////////////////////////////////////////	  		
#endif
