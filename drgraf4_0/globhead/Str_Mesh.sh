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
/////////////////////////////////////////////////////////////////////////////
typedef struct edge
	{
		CObList		m_NodeList;
	}EDGE, FAR *pEDGE;
///////////////////
typedef struct face
	{
		CObList		m_NodeList;
	}FACE, FAR *pFACE;
typedef struct cube
	{
		CObList		m_NodeList;
	}CUBE, FAR *pCUBE;
//////////////////////////////////////////////////////////////////// 0D
//******* Node variables / data structure *************/
typedef struct nodecard
	{
		short		ElNum;			//* pad 5 char field */
		CString		id;     		// Node Card
		CString		sup_id;         // pad 10 char field
		CString		nid_r;
		long		x;
		long		y;
		long		z;
		BOOL		bnid_c;			// control Node
		BOOL		bnid_m;			// mesh node
		CString		load_id;
		CString		disp_id;
		int			num_min;		// band-minimized
	}NODECARD, FAR *pNODECARD;
//////////////////////////////////////////////////////////////////// 1D
typedef struct fem1D
	{

		short		nNodes;			// intermediate + corner Nodes = ALL
		short		nEdgeDegree;	// 1 = Linear/ 2 = Quadratic etc
		CList<EDGE,EDGE>	m_EdgeList;				//
		//////////////////////////////////
		CString		ElNumID;	
		CString		ElTypeID;			// TRUSS,BEAM,PIPE etc
		CString		line_id;
		CString		rid[MAX_CORNERS_1D];  //
		CString		lid[MAX_LOADS];		// Loadcase A,B,C,D
		CString		pid,mid;  
		//////////////////////////////////
		int			ElNum;              // Element Number
		int			ElTypeNum;        // id Number: Element Type
		UINT		line_no;
		UINT		rel[MAX_CORNERS_1D]; 
		UINT		load[MAX_LOADS];	// Loadcase A,B,C,D
		UINT		prop,mat;           //
		int			numseg;             //
		//////////////////////////////////
    }FEM1D, FAR *pFEM1D;
//////////////////////////////////////////////////////////////////////////
//******** 2D FEMs variables/ data structure **************/
typedef struct fem2D
	{
		short		nCorners;		// 3 = Triangle/ 4 = Quadrilateral
		short		nNodes;			// intermediate + corner Nodes = ALL
		short		nEdges;			// Bounding Edges
		short		nEdgeDegree;	// 1 = Linear/ 2 = Quadratic etc
		CList<EDGE,EDGE>	m_EdgeList;				//
		//////////////////////////////////
		CString		ElNumID;	
		CString		ElTypeID;	
		CString		Group_id;
		CString		rid[MAX_CORNERS_2D]; 
		CString		lid[MAX_LOADS];		// Loadcase A,B,C,D
		CString		pid,mid;  
		//////////////////////////////////
		UINT		ElNum;                 
		UINT		ElType;               
		UINT		GroupNum; 
		UINT		rel[MAX_CORNERS_2D]; 
		UINT		load[MAX_LOADS];		// Loadcase A,B,C,D
		UINT		prop,mat;  
		//////////////////////////////////
		double		refTemp,Thkness;	//RefrenceTemperature & Thickness
		CString		sprid;				//stress print CodeID */
    }FEM2D, FAR *pFEM2D;
//////////////////////////////////////////////////////////////////////////
//******** 3D FEMs variables/ data structure **************/
typedef struct fem3D
	{
		short		nCorners;		// 4 = Tetra/ 5 = Penta/ 6 = Hexa
		short		nNodes;			// intermediate + corner Nodes = ALL
		short		nEdges;			// Bounding Edges
		short		nFaces;			//4=tetra; 5=Penta; 6=Hexa
		short		nEdgeDegree;	// 1 = Linear/ 2 = Quadratic etc
		CList<EDGE,EDGE>	m_EdgeList;				//
		CList<FACE,FACE>	m_FaceList;				//
		CList<CUBE,CUBE>	m_CubeList;				//
		//////////////////////////////////
		CString		ElNumID;	
		CString		ElTypeID;	
		CString		Group_id;
		CString		rid[MAX_CORNERS_3D]; 
		CString		lid[MAX_LOADS];		// Loadcase A,B,C,D
		CString		pid,mid;  
		//////////////////////////////////
		UINT		ElNum;                 
		UINT		ElType;               
		UINT		GroupNum; 
		UINT		nod[MAX_EDGENODE_MID]; 
		UINT		rel[MAX_CORNERS_3D]; 
		UINT		load[MAX_LOADS];		// Loadcase A,B,C,D
		UINT		prop,mat;  
		//////////////////////////////////
		double		refTemp,Thkness;	//RefrenceTemperature & Thickness
		CString		sprid;				//stress print CodeID */
	
		CString		platid[MAX_FACES];
    }FE3DCARD, FAR *pFE3DCARD;
////////////////////////////////////////////////////////////////////	  		
#endif
