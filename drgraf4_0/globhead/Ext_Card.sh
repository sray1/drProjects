#ifndef _EXT_CARD_H
#define _EXT_CARD_H 

#include "Glb_SUPP.h"
//*******************************************************/
#define MAX_CORNERS_2D	4
#define MAX_CORNERS_3D	21
#define MAX_FACES		6
#define	MAX_LOADS		4
//****************************************************************/ 
/////////////////////////////////
typedef struct crtypes 
	{
		char*   	ObjName;  	// internal name
		int			num;   		// number associated with element
		int			type;  		// -1 	= metacard
								// 0	= element
								// 1	= cardtype
								// 2	= elem+card both 
		char*		cardName;  	// dreamPipe	
		char*		otherName; 	// if different card name
	}CRTYPES;
/////////////////////////////////////////////////////////////////	
extern CRTYPES	CrTypes[];
extern	int	FAR nMax_CardTypes;
///////////////////////////////////////////////////////////////// CARDS
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
//******** Pipe variables/ data structure **************/
typedef struct pipecard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		line_id;
		CString		nid_i,nid_j;
		CString		rid_i,rid_j;   //* pad 2 nos 5 char fields */
		CString		lid[MAX_LOADS];		//Loadcase A,B,C,D
		CString		pid,mid;
		CString		sid_i,sid_j;   //* pad 5 char field */
		int			numseg;            //* pad 5 char field */
		BOOL		bValve;
    }PIPECARD, FAR *pPIPECARD;
//******** Beam variables/ data structure **************/
typedef struct beamcard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		line_id;
		CString		nid_i,nid_j;
		CString		rid_i,rid_j,nid_k;   //* pad 5 char field */
		CString		lid[MAX_LOADS];		//Loadcase A,B,C,D
		CString		pid,mid;             //* pad 3 nos 5 char fields */
		int			numseg;                  //* pad 5 char field */
    }BEAMCARD, FAR *pBEAMCARD;
//****** Elbow variables/ data structure **************/
typedef struct elbowcard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		line_id;
		CString		nid_i,nid_j;
		CString		nid_cc,nid_ti;
		CString		nid_a,nid_b;
		CString		pid,mid;
		CString		sid_i,sid_j;   
		CString		rid_i,rid_j;   
	}ELBOWCARD, FAR *pELBOWCARD;
/******** Support variables/ data structure **************/
typedef struct supportcard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		sup_id;
		SUPPPROC	SuppProc;				//* Rigid,LinSpr,LinSnu etc
		BYTE		kode[6];
		double		stiffness;
		CString		nid_a;            /* pad 3 nos 10 char fields */
    }SUPPCARD, FAR *pSUPPCARD;
//******** NonLin Support variables/ data structure **************/   TEMPORARY
typedef struct nonsupcard 
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		CString		sup_id;
		SUPPPROC	SuppProc;				//* Rigid,LinSpr,LinSnu etc
		BYTE		kode[6];
		double		stiffness;
		CString		nid_a;            /* pad 3 nos 10 char fields */
    }NONSUPCARD, FAR *pNONSUPCARD;
//******** PipeProp       variables/ data structure **************/
typedef struct pipeprop 
	{
		int			PropNum;                  //* pad 5 char field */
		CString		gid;            //* pad 1 no 10 char field */
		double		od;
		double		thk;
		double		thki;
		double		r;
		double		pres;
    }PIPEPROPCARD, FAR *pPIPEPROP;
/******** Master         variables/ data structure **************/
typedef struct master
	{
		CString		xstat;
		CString		unit;
		CString		g;
		double		fac;
		CString		lambda;
		CString		damp;              /* pad 10 char field */
    }MASTERCARD, FAR *pMASTER;
/******** MetaCards ... unrecognised cards **********************/
typedef struct metacard
	{
		CString		WholeCard;
	}METACARD, FAR *pMETACARD;	
//******** Plate (2D FEMs) variables/ data structure **************/
typedef struct platcard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		short		nNodes;				// intermediate + corner Nodes = ALL
		short		nCorners;			//3=triangular; 4=quadrilateral
		short		nPlateType;			//1=AxiSym;2=Pl.Strain;3=Pl.Stress(2D FEM)
		CString		nid[MAX_CORNERS_2D];
		CString		rid[MAX_CORNERS_2D];   //* pad 2 nos 5 char fields */
		CString		lid[MAX_LOADS];		//Loadcase A,B,C,D
		CString		pid,mid;
		double		refTemp,Thkness;	//RefrenceTemperature & Thickness
		CString		sprid;				//stress print CodeID */
    }PLATCARD, FAR *pPLATCARD;
//******** Solid (3D FEMs) variables/ data structure **************/
typedef struct fe3dcard
	{
		int			ElNum;                  //* pad 5 char field */
		int			IDNum;                  //* pad 5 char field */
		short		nNodes;				// intermediate + corner Nodes = ALL
		short		nCorners;			// Corner Nodes
		short		nEdges;				// Bounding Edges
		short		nFaces;				//4=tetra; 5=Penta; 6=Hexa
		CString		platid[MAX_FACES];
		CString		rid[MAX_CORNERS_3D];   //* pad 2 nos 5 char fields */
		CString		lid[MAX_LOADS];		//Loadcase A,B,C,D
		CString		pid,mid;
		double		refTemp,Thkness;	//RefrenceTemperature & Thickness
		CString		sprid;				//stress print CodeID */
    }FE3DCARD, FAR *pFE3DCARD;
////////////////////////////////////////////////////////////////////	  		
#endif
