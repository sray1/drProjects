// CPa_Duct.cpp : implementation of the CPA_Duct class
//

#include "stdafx.h"
#include <math.h>
#include <Float.h>		//DBL_MIN in sweep/duct

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
///////////////////
#include "PA_Rotat.h"

#include "PA_Duct.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPA_Duct

IMPLEMENT_DYNAMIC(CPA_Duct,CObject)
/*
BEGIN_MESSAGE_MAP(CPA_Duct,CObject)
//BEGIN_MESSAGE_MAP
	//{{AFX_MSG_MAP(CPA_Duct)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
//////////////////////////////////////////////
int CPA_Duct::Duct
	(
		WORLD	Anchor,		//	cross section Anchor point	
		int		nXSec,		//	number of cross section points
		pWORLD	pXSec,		//	cross section curve points
		pDOUBLE	pXSecWt,	//	cross section curve Wts
		int		nPath,		//	number of path points
		pWORLD	pPath,		//	path curve points
		pWORLD	pPathTan,	//	path curve Tangents
		pDOUBLE	pTwist,		//	path Twist factors: 
		pWORLD	pOut,		//	Output Pts array
		pDOUBLE	pOutWt		//	Output Wts array
	)	  
{
	///////////////////////////////////////////////////// NOTE
	pWORLD	pRow,p,pP,pSec,pTan;//,pS;
	pDOUBLE pRowWt,pW,pSecWt;
	int		ii,jj;
	long	sizeRow,sizeRowWt;
	////////////////////////////////
	if(pOut)
	{
		CPA_Rotat 	Rotate;
		C3DMath		Math3D;
		CXForm	XForm(TRUE);	// Parallel
		///////////////////////////////////////
		sizeRow		= nXSec*sizeof(WORLD);
		sizeRowWt	= nXSec*sizeof(double);
		////////////////////////////////////////
		MATRIX Mat,MatR;
		pMATRIX pMat = &Mat,pMatR = &MatR;  
		Math3D.GetIdentityMATRIX(pMat);
		XForm.Translate(pMat,-Anchor.x,-Anchor.y,-Anchor.z,XF_REPLACE);
		///////////////////////////////////////////////////////////////
		for( pRow=pOut,pRowWt=pOutWt,ii=0;ii<nPath;ii++,pRow+=nXSec,pRowWt+=nXSec ) 
		{
			/////////////////////////////// Pt. & Tangent
			pP		= pPath + ii;
			pTan	= pPathTan + ii;
			/////////////////////////////// Twist
			double theta = *(pTwist + ii);
		    ///////////////////////////////////////////////// Create New Matrix
			///////////////////////////// Rotate to NewX
			XForm.RotateToNewXMATRIX(pTan, pMatR, XF_REPLACE);
			///////////////////////////// Translate to the Pt.
			XForm.Translate(pMatR,pP->x,pP->y,pP->z,XF_PREMULT);
			////////////////////// for Rotation
			WORLD CurCenter,ExDir;
			CurCenter.x = pP->x;
			CurCenter.y = pP->y;
			CurCenter.z = pP->z;
			/////////////////////////////// Axis of Twist
			Math3D.Normalize(pTan,&ExDir);
			///////////////////////////////////////////////// Go Over the XSection
			for( p=pRow,pW=pRowWt,pSec = pXSec,pSecWt = pXSecWt,jj=0;
															jj<nXSec;
										jj++,p++,pW++,pSec++,pSecWt++ )
			{
				///////////////////////////// Translate by Anchor
				XForm.Transform(pSec, p, pMat);
				///////////////////////////// Head to p and perpendicular to path
				XForm.Transform(p, p, pMatR);
				///////////////////////////// Rotate
				Rotate.GetAPtByRotation(p , CurCenter, ExDir, theta, p); // Use pP as Center of Rotation
				///////////////////////////// XSec Wt
				*pW = (*pSecWt);  
			}
		}
	}			
	////////////////////////	
	return	nXSec * nPath;
}

/*
int CPA_Duct::Duct
	(
		WORLD	Anchor,		//	cross section Anchor point	
		int		nXSec,		//	number of cross section points
		pWORLD	pXSec,		//	cross section curve points
		pDOUBLE	pXSecWt,	//	cross section curve points
		int		nPath,		//	number of path points
		pWORLD	pPath,		//	path curve points
		pWORLD	pTwist,		//	path Twist factors: ONLY Y-COMPONENT is USEFUL
		pWORLD	pOut,		//	Output Pts array
		pDOUBLE	pOutWt		//	Output Wts array
	)	  
{
	///////////////////////////////////////////////////// NOTE
	pWORLD	pRow,p,pP,pSec;//,pS;
	pDOUBLE pRowWt,pW,pSecWt;
	int		ii,jj;
	long	sizeRow,sizeRowWt;
	////////////////////////////////
	if(pOut)
	{
		CPA_Xtrud 	Xtrud;
		CPA_Rotat 	Rotate;
		C3DMath		Math3D;
		CXForm	XForm(TRUE);	// Parallel
		///////////////////////////////////////
		sizeRow		= nXSec*sizeof(WORLD);
		sizeRowWt	= nXSec*sizeof(double);
		////////////////////////////////////////
		MATRIX Mat,MatR;
		pMATRIX pMat = &Mat,pMatR = &MatR;  
		Math3D.GetIdentityMATRIX(pMat);
		XForm.Translate(pMat,-Anchor.x,-Anchor.y,-Anchor.z,XF_REPLACE);
		///////////////////////////////////////////////////////////////
		for( pRow=pOut,pRowWt=pOutWt,ii=0;ii<nPath;ii++,pRow+=nXSec,pRowWt+=nXSec ) 
		{
			////////////
			WORLD To;
			///////////////////////////////
			pP = pPath + ii;
			/////////////////
			double theta = (pTwist + ii)->y;
			//////////////////////////////////////////////////////
			if(ii == 0)
			{
				Math3D.Sub3DPts(pP+1, pP, &To);
				Math3D.Add3DPts(pP, &To, &To);
				XForm.HeadToNewZLocMATRIX(pP, &To, pMatR, XF_REPLACE);
			}
			else
			if(ii == nPath-1)
			{
				Math3D.Sub3DPts(pP, pP-1, &To);
				Math3D.Add3DPts(pP, &To, &To);
				XForm.HeadToNewZLocMATRIX(pP, &To, pMatR, XF_REPLACE);
			}
			else
			{
				WORLD a,b;
				Math3D.Avg3DPts(pP-1, pP, &a);
				Math3D.Avg3DPts(pP, pP+1, &b);
				Math3D.Sub3DPts(&b, &a, &To);
				Math3D.Normalize(&To,&To);
				Math3D.Add3DPts(pP, &To, &To);
				XForm.HeadToNewZLocMATRIX(pP, &To, pMatR, XF_REPLACE);
			}
			////////////////////// for Rotation
			WORLD CurCenter,ExDir;
			CurCenter.x = pP->x;
			CurCenter.y = pP->y;
			CurCenter.z = pP->z;
			////////////////////
			Math3D.Sub3DPts(&To, pP, &ExDir);
			Math3D.Normalize(&ExDir,&ExDir);
			///////////////////////////////////////////////// Go Over the XSection
			for( p=pRow,pW=pRowWt,pSec = pXSec,pSecWt = pXSecWt,jj=0;jj<nXSec;jj++,p++,pW++,pSec++,pSecWt++ )
			{
				///////////////////////////// Translate by Anchor
				XForm.Transform(pSec, p, pMat);
				///////////////////////////// Head to p and perpendicular to path
				XForm.Transform(p, p, pMatR);
				///////////////////////////// Rotate
				Rotate.GetAPtByRotation(p , CurCenter, ExDir, theta, p); // Use pP as Center of Rotation
				/////////////////////////////
				*pW = *pXSecWt;  
			}
		}
	}			
	////////////////////////	
	return	nXSec * nPath;
}
*/
////////////////////////////// end of module /////////////////////// 
