#ifndef _STR_CUPS_H
#define _STR_CUPS_H 

//////////////////////////////////////////////////////////////////////////
//******** Curve Creation variables/ data structure **************/
typedef struct curve 
	{
		CString			ID;	
		CURVEPROC		CurveType;
		CIRCLETYPE		CircType;
		BOOL			bFinal;
		BOOL			bAdvanceOn;
		///////////////////////
		CDListMgr*		pNodeList;	
		CList<int,int>*	pElSegList;	
		///////////////////////
 		CDrNode*		pFromNode;  //
 		CDrNode*		pToNode;  //
		BOOL			bAxis;
		int				nAxis;
		BOOL			bNegative;
		double			dAng;
		double			SegAngle;
		double			dRadius;
		BOOL			bArc;
		///////////////////////
    }CURVEDATA, FAR *pCURVEDATA;
//******** Patch Creation variables/ data structure **************/
typedef struct patch 
	{
		///////////////////////
		CString			ID;	
		///////////////////////
   }PATCHDATA, FAR *pPATCHDATA;
//******** Solid Creation variables/ data structure **************/
typedef struct Solid
	{
		///////////////////////
		CString		ID;	
		///////////////////////
    }SOLIDDATA, FAR *pSOLIDDATA;
////////////////////////////////////////////////////////////////////	  		
#endif
