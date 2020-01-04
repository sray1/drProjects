#ifndef _CRGLOBAL_H
#define _CRGLOBAL_H 

#include "crdefine.h"
////////////////////////////////
#define	MAXSTRINGLENGTH	20    // formatting string for Cards
#define CARD_SIZE		200
#define	ID_LEN	5             // Length of All IDs in Cards
#define NUM_LEN	10            // No. of All Numbers in Cards
//****************************************************************/ 
/////////////////////////////////
//******* Node variables / data structure *************/
typedef struct nodecard
	{
		CString		id;     		// Node Card
		CString		sup_id;         // pad 10 char field
		CString		nid_r;
		long		x;
		long		y;
		long		z;
		BOOL		bnid_c; 
	}NODECARD, FAR *pNODECARD;
//******** Pipe variables/ data structure **************/
typedef struct pipecard
	{
    CString line_id;
    CString nid_i,nid_j;
    CString rid_i,rid_j;   //* pad 2 nos 5 char fields */
    CString pid,mid;
    CString sid_i,sid_j;   //* pad 5 char field */
    int numseg;            //* pad 5 char field */
    BOOL bValve;
    }PIPECARD, FAR *pPIPECARD;
//******** Beam variables/ data structure **************/
typedef struct beamcard
	{
	CString line_id;
    CString nid_i,nid_j;
    CString rid_i,rid_j,nid_k;   //* pad 5 char field */
    CString pid,mid;             //* pad 3 nos 5 char fields */
    int numseg;                  //* pad 5 char field */
    }BEAMCARD, FAR *pBEAMCARD;
//****** Elbow variables/ data structure **************/
typedef struct elbowcard
	{
    CString line_id;
    CString nid_i,nid_j;
    CString nid_cc,nid_ti;
    CString nid_a,nid_b;
    CString pid,mid;
    CString sid_i,sid_j;   
    CString rid_i,rid_j;   
	}ELBOWCARD, FAR *pELBOWCARD;
/******** Support variables/ data structure **************/
typedef struct supportcard
	{
    CString sup_id;
    int kode;
    double stiffness;
    CString nid_a;            /* pad 3 nos 10 char fields */
    }SUPPORTCARD, FAR *pSUPPORTCARD;
//******** NonLin Support variables/ data structure **************/   TEMPORARY
typedef struct nonsupcard 
	{
    CString sup_id;
    int kode;
    double stiffness;
    CString nid_a;            /* pad 3 nos 10 char fields */
    }NONSUPCARD, FAR *pNONSUPCARD;
//******** PipeProp       variables/ data structure **************/
typedef struct pipeprop 
	{
    CString gid;            //* pad 1 no 10 char field */
    double od;
    double thk;
    double thki;
    double r;
    double pres;
    }PIPEPROPCARD, FAR *pPIPEPROP;
/******** Master         variables/ data structure **************/
typedef struct master {
    CString xstat;
    CString unit;
    CString g;
    double fac;
    CString lambda;
    CString damp;              /* pad 10 char field */
    }MASTERCARD, FAR *pMASTER;
/******** MetaCards ... unrecognised cards **********************/
typedef struct metacard
	{
		CString		WholeCard;
	}METACARD, FAR *pMETACARD;	
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
CRTYPES	CrTypes[] =
	{ 
		"",				-1,			-2,		"",				"",
		"CNODE",		CNODE,		1,		"CNODE",		"",

    	"RIGIDSUP",		RIGIDSUP,	2,		"RIGIDSUP",		"",
    	"TSPRING",		TSPRING,	2,		"TSPRING",		"",
    	"TSNUBBER",		TSNUBBER,	2,		"TSNUBBER",		"",
    	"RSPRING",		RSPRING,	2,		"RSPRING",		"",
    	"RSNUBBER",		RSNUBBER,	2,		"RSNUBBER",		"",
        ///////////////
		"META",			META,		-1,		"",				"",
		"C",			COMMENT,	1,		"C",			"",
		"FIXFORMAT",	FIX,		1,		"FIXFORMAT",	"",
		"FREEFORMAT",	FREE,		1,		"FREEFORMAT",	"",
		"END",			END,		1,		"END",			"",
    	"MASTER",		MASTER,		1,		"MASTER",		"",
    	"PIPEPROP",		PIPEPROP,	1,		"PIPEPROP",		""  
    	
};
	int	nMax_CardTypes = (sizeof (CrTypes)/ sizeof(CrTypes[0]) );
////////////////////////////////////////////////////////////////////	  		
#endif
