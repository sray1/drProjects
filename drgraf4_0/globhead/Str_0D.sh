#ifndef _STR_0D_H
#define _STR_0D_H 
//*******************************************************/
//#define	MAX_CORNERS_2D	4
//#define	MAX_CORNERS_3D	21
//#define	MAX_FACES		6
//#define	MAX_LOADS		4
//****************************************************************/ 
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
////////////////////////////////////////////////////////////////////	  		
#endif
