// Supp.cpp : implementation file
//


#include "stdafx.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN
#include <stdio.h>

/////////////////////
#include "Def_Type.h"
#include "Def_Objs.h"
#include "DListMgr.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"        
#include "3DMath.h"
#include "XForm.h"
////////////////////// ElemObjs
//#include "Ext_Elem.h"
//#include "Def_Elem.h"
#include "DrNode.h"
///////////////////// Static Loads
#include "Def_StaL.h"
#include "Ext_StaL.h"

#include "DrStatic.h"
///////////////////////////// FORCE
#define	LENGTH	.3	
#define	WIDTH	.15	
#define	TICK	WIDTH/4	
///////////////////////////// MOMENT
#define	LEN1	7	
#define	BOXSIZE	LEN1	
#define	LEN2	LEN1	
///////////////////////////// LumpWt
#define	RADIUS			6 // pixel
/////////////////////////////
#define	MAX_FORCE_PT	15
#define	MAX_MOMENT_PT	14
#define	MAX_THERMAL_PT	1
#define	MAX_LUMPWT_PT	2
#define MAX_PT			15  // max(MAX_FORCE_PT,MAX_MOMENT_PT etc..)
//////////////////////////////////////////////////////////////////////////// static
static WORLD 	m_ForceDat_X[MAX_FORCE_PT]=
{
	////////////////////////////////////////////////////////////////// xy-plane
	{-LENGTH,	.1*WIDTH,	0.0	},{-.3*LENGTH	,.1*WIDTH	,0.0},		 
    {-.3*LENGTH,.2*WIDTH,	0.0	},{0.0			,0.0		,0.0},		 
    {-.3*LENGTH,-.2*WIDTH,	0.0	},{-.3*LENGTH	,-.1*WIDTH	,0.0},		 
    {-LENGTH,	-.1*WIDTH,	0.0	},
	////////////////////////////////////////////////////////////////// xz-plane
	{-LENGTH	,0.0,.1*WIDTH	},{-.3*LENGTH	,0.0,	.1*WIDTH	},		 
    {-.3*LENGTH	,0.0,.2*WIDTH	},{0.0			,0.0,	0.0			},		 
    {-.3*LENGTH	,0.0,-.2*WIDTH	},{-.3*LENGTH	,0.0,	-.1*WIDTH	},		 
    {-LENGTH	,0.0,-.1*WIDTH	},
	{-1.2*LENGTH,0.0,	0.0		}									// for Value(Text)
	///////////////
};
static WORLD 	m_ForceDat_Y[MAX_FORCE_PT]=
{
	////////////////////////////////////////////////////////////////// yx-plane
	{.1*WIDTH,	-LENGTH,	0.0		},{.1*WIDTH	,-.3*LENGTH	,0.0	},		 
    {.2*WIDTH,	-.3*LENGTH,	0.0		},{0.0		,0.0		,0.0	},		 
    {-.2*WIDTH,	-.3*LENGTH,	0.0		},{-.1*WIDTH,-.3*LENGTH	,0.0	},		 
    {-.1*WIDTH,	-LENGTH,	0.0		},
	////////////////////////////////////////////////////////////////// yz-plane
	{0.0,	-LENGTH,	.1*WIDTH	},{0.0,-.3*LENGTH	,.1*WIDTH	},		 
    {0.0,	-.3*LENGTH,	.2*WIDTH	},{0.0,0.0			,0.0		},		 
    {0.0,	-.3*LENGTH,	-.2*WIDTH	},{0.0,-.3*LENGTH	,-.1*WIDTH	},		 
    {0.0,	-LENGTH,	-.1*WIDTH	},
	{0.0,	-1.2*LENGTH,0.0			}								// for Value(Text)
	///////////////
};
static WORLD 	m_ForceDat_Z[MAX_FORCE_PT]=
{
	////////////////////////////////////////////////////////////////// zx-plane
	{.1*WIDTH,	0.0,-LENGTH		},{.1*WIDTH,	0.0,-.3*LENGTH	},		 
    {.2*WIDTH,	0.0,-.3*LENGTH	},{0.0,			0.0,0.0			},		 
    {-.2*WIDTH,	0.0,-.3*LENGTH	},{-.1*WIDTH,	0.0,-.3*LENGTH	},		 
    {-.1*WIDTH,	0.0,-LENGTH		},
	////////////////////////////////////////////////////////////////// yz-plane
	{0.0,.1*WIDTH,	-LENGTH		},{0.0,.1*WIDTH,	-.3*LENGTH	},		 
    {0.0,.2*WIDTH,	-.3*LENGTH	},{0.0,0.0,			0.0			},		 
    {0.0,-.2*WIDTH,	-.3*LENGTH	},{0.0,-.1*WIDTH,	-.3*LENGTH	},		 
    {0.0,-.1*WIDTH,	LENGTH		},
	{0.0,0.0,		-1.2*LENGTH	}									// for Value(Text)
	///////////////
};
////////////////
static WORLD 	m_MomentDat_X[MAX_MOMENT_PT]=
{
	////////////////////////////////////////////////////////////////// xy-plane
	{0.0,		.1*WIDTH,	0.0	},{.3*LENGTH,	.1*WIDTH,	0.0	},		 
    {.3*LENGTH,.2*WIDTH,	0.0	},{.5*LENGTH,	.1*WIDTH,	0.0	},		 
    {.7*LENGTH,.1*WIDTH,	0.0	},{.7*LENGTH,	.2*WIDTH,	0.0	},		 
    {LENGTH,	0.0,		0.0	},
	{.7*LENGTH,	-.2*WIDTH,	0.0	},{.7*LENGTH,	-.1*WIDTH,	0.0	},	
	{.5*LENGTH,	-.1*WIDTH,	0.0	},{.3*LENGTH,	-.2*WIDTH,	0.0	},
	{.3*LENGTH,	-.1*WIDTH,	0.0	},{0.0,			-.1*WIDTH,	0.0	},
	{-.2*LENGTH,0.0,		0.0	}									// for Value(Text)
	///////////////
};
static WORLD 	m_MomentDat_Y[MAX_MOMENT_PT]=
{
	////////////////////////////////////////////////////////////////// yx-plane
	{.1*WIDTH,0.0,0.0			},{.1*WIDTH,.3*LENGTH,	0.0	},		 
    {.2*WIDTH,.3*LENGTH,0.0		},{.1*WIDTH,.5*LENGTH,	0.0	},		 
    {.1*WIDTH,.7*LENGTH,0.0		},{.2*WIDTH,.7*LENGTH,	0.0	},		 
    {0.0,LENGTH,	0.0			},
	{-.2*WIDTH,.7*LENGTH,0.0	},{-.1*WIDTH,.7*LENGTH,	0.0	},	
	{-.1*WIDTH,.5*LENGTH,0.0	},{-.2*WIDTH,.3*LENGTH,	0.0	},
	{-.1*WIDTH,.3*LENGTH,0.0	},{0.0,		-.1*WIDTH,	0.0	},
	{0.0,-.2*LENGTH,0.0			}									// for Value(Text)
	///////////////
};
static WORLD 	m_MomentDat_Z[MAX_MOMENT_PT]=
{
	{0.0,.1*WIDTH,	0.0			},{0.0,	.1*WIDTH,.3*LENGTH	},		 
    {0.0,.2*WIDTH,	.3*LENGTH	},{0.0,	.1*WIDTH,.5*LENGTH	},		 
    {0.0,.1*WIDTH,	.7*LENGTH	},{0.0,	.2*WIDTH,.7*LENGTH	},		 
    {0.0,0.0,		LENGTH		},
	{0.0,-.2*WIDTH,.7*LENGTH	},{0.0,	-.1*WIDTH,.7*LENGTH	},	
	{0.0,-.1*WIDTH,.5*LENGTH	},{0.0,	-.2*WIDTH,.3*LENGTH	},
	{0.0,-.1*WIDTH,.3*LENGTH	},{0.0,	-.1*WIDTH,0.0		},
	{0.0,0.0,		-.2*LENGTH	}									// for Value(Text)
	///////////////
};
static WORLD 	m_TemperDat[MAX_THERMAL_PT]=
{
	{0.0,		.1*WIDTH,	0.0	}									// for Value(Text)
	///////////////
};
static WORLD 	m_LumpWtDat[MAX_LUMPWT_PT]=
{
	{0.0,		0.0,		0.0	},								// center of Circle
	{0.0,		.1*WIDTH,	0.0	}								// for Value(Text)
	///////////////
};
////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////
#define GREEN	RGB(0,255,0)
#define RED		RGB(255,0,0)
/////////////////////////////////////////////////////////////////////////////
// CDrStatic
IMPLEMENT_SERIAL(CDrStatic, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrStatic, CDrObject)
	//{{AFX_MSG_MAP(CDrStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrStatic::CDrStatic()
{
	int i;
	/////////////
	m_bDoneXform	= FALSE;
	m_bDoneProject	= FALSE;
	//////////////////////////////
	for(i=0;i<6;i++)
	{
		m_pLoc[i]	= new WORLD[MAX_PT];
		m_pEye[i]	= new WORLD[MAX_PT];
		m_nPts[i]	= 0;
	}
	//////////////////////////////
	m_StaLCard.StaLProc		= STL_FORCE;				
    SetObjectType((int)FORCE);
    SetElemType((int)STAL_OBJECT);          //
    //////////////////////////////  
	m_StaLCard.ElNum		= 0;                  
	m_StaLCard.IDNum		= 0;                  
	m_StaLCard.load_id		= "";
	///////////////////////////
	for(i=0;i<6;i++)
	{
		m_StaLCard.kode[i]	= 0;
		m_StaLCard.value[i] = 0.0;
	}
	///////////////////////////
	m_StaLCard.nid_a		= "";            
	m_StaLCard.bTanCur		= FALSE;            
	m_StaLCard.bTanPat		= FALSE;            
	m_StaLCard.bNorPat		= FALSE;            
	m_StaLCard.cid_Iso		= "";	// this force IsoParametric to this Curve
	m_StaLCard.cid_ParentT	= "";	// this force part of this Curve of Category CA_FORCE
	m_StaLCard.cid_ParentR	= "";	// this force part of this Curve of Category CA_FORCE
	//////////////////////
	m_dMin.x = DBL_MAX; 
	m_dMin.y = DBL_MAX; 
	m_dMin.z = DBL_MAX;
	 
	m_dMax.x = -DBL_MIN; 
	m_dMax.y = -DBL_MIN; 
	m_dMax.z = -DBL_MIN;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
	///////////////////////////////////////////////////////////////////// Quick Search
	m_bTriangle = FALSE;		// if CreateBase = PATCH, Is It Triangle;
						// if CreateBase = Solid, Is It TetraHed
	m_bPentaHed = FALSE;		// if CreateBase = Solid, Is It PentaHed;
	////////////////////
}

CDrStatic::~CDrStatic()
{
	int i;
	///////////////////////////
	for(i=0;i<6;i++)
	{
		delete [] m_pLoc[i];
		delete [] m_pEye[i];
	}
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}
	
void CDrStatic::SetStaLCard(STALCARD sC)
{
	///////////////////
	m_StaLCard.load_id		= sC.load_id;
	m_StaLCard.StaLProc		= sC.StaLProc;
	m_StaLCard.kode[0]		= sC.kode[0];
	m_StaLCard.kode[1]		= sC.kode[1];
	m_StaLCard.kode[2]		= sC.kode[2];
	m_StaLCard.kode[3]		= sC.kode[3];
	m_StaLCard.kode[4]		= sC.kode[4];
	m_StaLCard.kode[5]		= sC.kode[5];

	m_StaLCard.value[0]		= sC.value[0];
	m_StaLCard.value[1]		= sC.value[1];
	m_StaLCard.value[2]		= sC.value[2];
	m_StaLCard.value[3]		= sC.value[3];
	m_StaLCard.value[4]		= sC.value[4];
	m_StaLCard.value[5]		= sC.value[5];
	/////////////////////
	m_StaLCard.GenKind		= sC.GenKind;
	m_StaLCard.nid_a		= sC.nid_a;
	m_StaLCard.bCN_a		= sC.bCN_a;		// nid_a is Control Node?		
	m_StaLCard.nid_b		= sC.nid_b;			
	m_StaLCard.bCN_b		= sC.bCN_b;		// nid_b is Control Node?		
	m_StaLCard.bTanCur		= sC.bTanCur;				
	m_StaLCard.bTanPat		= sC.bTanPat;				
	m_StaLCard.bNorPat		= sC.bNorPat;				
	m_StaLCard.ID_CP		= sC.ID_CP;		
	m_StaLCard.jcType		= sC.jcType;		//	JC_DEFAULT,
	m_StaLCard.bUniform		= sC.bUniform;	// Uniform distribution
	m_StaLCard.bConOrDis	= sC.bConOrDis;		// IsoParametric Concentrated or Distributed Input
	m_StaLCard.bIso			= sC.bIso;				
	m_StaLCard.cid_Iso		= sC.cid_Iso;				
	m_StaLCard.cid_ParentT	= sC.cid_ParentT;				
	m_StaLCard.cid_ParentR	= sC.cid_ParentR;				
	/////////////////////////////////// NonIso
	m_StaLCard.bNonIso		= sC.bNonIso;
	m_StaLCard.bIncrement	= sC.bIncrement;
	m_StaLCard.Orient		= sC.Orient;
	m_StaLCard.dScale		= sC.dScale;
	m_StaLCard.dStep		= sC.dStep;
	m_StaLCard.dStart		= sC.dStart;
	m_StaLCard.SkewDir.x	= sC.SkewDir.x;
	m_StaLCard.SkewDir.y	= sC.SkewDir.y;
	m_StaLCard.SkewDir.z	= sC.SkewDir.z;
	///////////////////////////////////
	return;
}

void CDrStatic::InitRawData(STALPROC StaLProc)
{
	m_StaLCard.StaLProc = StaLProc; 
	///////////////////////////////////////////////////////////////// PreProcess
	for(int i=0;i<6;i++)		// Over All Directions
	{
		/////////////////////////////////
		m_nPts[i] = GetApproDataLen(StaLProc,i);
		GetApproPts(m_StaLCard.StaLProc,m_pLoc[i],m_nPts[i],i);
		////////////////////////////////////////////////////
	}	 
} 

void CDrStatic::ReadyToDelete()
{
	////////////////////////////////////// unload Nodes/No delete
	CDListMgr* pNodeList = GetNodeList();
    //////////////////////////////////////
	CDrObject* pObject,pElem;
	while(!pNodeList->IsEmpty())
	{
		pObject = (CDrObject*)pNodeList->RemoveHead();  //Node
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pStaLList = pObject->GetStaLList();
			int index = pStaLList->GetObjectIndex(this);
			if(index>=0)
				pStaLList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
	/////////////////////////////////////////////////////////////
	while(!(GetCurveList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetCurveList()->RemoveHead());
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pStaLList = pObject->GetStaLList();
			int index = pStaLList->GetObjectIndex(this);
			if(index>=0)
				pStaLList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}	
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pStaLList = pObject->GetStaLList();
			int index = pStaLList->GetObjectIndex(this);
			if(index>=0)
				pStaLList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}	
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		/////////////////////////////////////////////
		if(pObject)
		{
			CDListMgr* pStaLList = pObject->GetStaLList();
			int index = pStaLList->GetObjectIndex(this);
			if(index>=0)
				pStaLList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
	//////////////////////////////////////////////////////////////
}

int CDrStatic::DealObjectDialog()
{
/*
	CSuppProp	dlg;
	if(dlg.DoModal() == IDOK)
		return 0;
	else
		return -1;
*/
	return 0;			
}
	
void CDrStatic::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrStatic* pAdd = (CDrStatic*) pObject;
	///////////////////////////////////////////////////// SuppINFO
	m_NodeList.AddTail(pAdd->GetNodeList() ); 
	////////////////////////////////////////////////////
	m_StaLCard.ElNum		= (pAdd->GetStaLCard())->ElNum;                  
	m_StaLCard.IDNum		= (pAdd->GetStaLCard())->IDNum;                  
	m_StaLCard.load_id		= (pAdd->GetStaLCard())->load_id;
	m_StaLCard.StaLProc		= (pAdd->GetStaLCard())->StaLProc;				
	///////////////////////////
	for(int i=0;i<6;i++)
	{
		m_StaLCard.kode[i]	=  (pAdd->GetStaLCard())->kode[i];
		m_StaLCard.value[i] =  (pAdd->GetStaLCard())->value[i];
	}
	///////////////////////////
	m_StaLCard.cid_Iso		=  (pAdd->GetStaLCard())->cid_Iso;            
	m_StaLCard.cid_ParentT	=  (pAdd->GetStaLCard())->cid_ParentT;            
	m_StaLCard.cid_ParentR	=  (pAdd->GetStaLCard())->cid_ParentR;            
	m_StaLCard.nid_a		=  (pAdd->GetStaLCard())->nid_a;            
	m_StaLCard.bTanCur		=  (pAdd->GetStaLCard())->bTanCur;            
	m_StaLCard.bTanPat		=  (pAdd->GetStaLCard())->bTanPat;            
	m_StaLCard.bNorPat		=  (pAdd->GetStaLCard())->bNorPat;            
	////////////////////////////////////////////////////
	m_bSkewed				= pAdd->m_bSkewed;
	if( m_bSkewed )
	{	
		C3DMath	Math3D;
		Math3D.BlockCopy((HUGEBLK)(&(pAdd->m_SkewMat)),(HUGEBLK)(&m_SkewMat), sizeof(MATRIX) );
	}
	m_nCardNo				= pAdd->m_nCardNo;
	///////////////////////////////////////////////////////////////////// Quick Search
	m_CreateBase			= pAdd->m_CreateBase;		// NODE,CURVE,PATCH or SOLID
	m_bTriangle				= pAdd->m_bTriangle;		// if CreateBase = PATCH, Is It Triangle;
														// if CreateBase = Solid, Is It TetraHed
	m_bPentaHed				= pAdd->m_bPentaHed;		// if CreateBase = Solid, Is It PentaHed;
	m_Create_i				= pAdd->m_Create_i;			// index in the CreateBaseList or TriangleList, if bTriangle = TRUE
	m_Create_j				= pAdd->m_Create_j;
	m_Create_k				= pAdd->m_Create_k;
	m_NodPos				= pAdd->m_NodPos;		// Needed to avoid Duplicate in Triangle Situation
	///////////
	return;
}		

void CDrStatic::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrStatic* pAdd = (CDrStatic*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	pAdd->m_NodeList.AddTail(GetNodeList() ); 
	////////////////////////////////////////////////////////   
	(pAdd->GetStaLCard())->ElNum	= m_StaLCard.ElNum;
	(pAdd->GetStaLCard())->IDNum	= m_StaLCard.IDNum;
	(pAdd->GetStaLCard())->load_id	= m_StaLCard.load_id;
	(pAdd->GetStaLCard())->StaLProc	= m_StaLCard.StaLProc;
	///////////////////////////
	for(int i=0;i<6;i++)
	{
		(pAdd->GetStaLCard())->kode[i] =  m_StaLCard.kode[i];
		(pAdd->GetStaLCard())->value[i] =  m_StaLCard.value[i];
	}
	///////////////////////////
	(pAdd->GetStaLCard())->cid_Iso		= m_StaLCard.cid_Iso;            
	(pAdd->GetStaLCard())->cid_ParentT	= m_StaLCard.cid_ParentT;            
	(pAdd->GetStaLCard())->cid_ParentR	= m_StaLCard.cid_ParentR;            
	(pAdd->GetStaLCard())->bTanCur	= m_StaLCard.bTanCur;            
	(pAdd->GetStaLCard())->bTanPat	= m_StaLCard.bTanPat;            
	(pAdd->GetStaLCard())->bNorPat	= m_StaLCard.bNorPat;            
	(pAdd->GetStaLCard())->nid_a	= m_StaLCard.nid_a;            
	///////////////////////////////////////////////////		
	pAdd->m_bSkewed					= m_bSkewed;
	if( pAdd->m_bSkewed )
	{	
		C3DMath	Math3D;
		Math3D.BlockCopy((HUGEBLK)(&m_SkewMat),(HUGEBLK)(&(pAdd->m_SkewMat)), sizeof(MATRIX) );
	}
	pAdd->m_nCardNo					= m_nCardNo;
	///////////////////////////////////////////////////////////////////// Quick Search
	pAdd->m_CreateBase				= m_CreateBase;		// NODE,CURVE,PATCH or SOLID
	pAdd->m_bTriangle				= m_bTriangle;		// if CreateBase = PATCH, Is It Triangle;
														// if CreateBase = Solid, Is It TetraHed
	pAdd->m_bPentaHed				= m_bPentaHed;		// if CreateBase = Solid, Is It PentaHed;
	pAdd->m_Create_i				= m_Create_i;			// index in the CreateBaseList or TriangleList, if bTriangle = TRUE
	pAdd->m_Create_j				= m_Create_j;
	pAdd->m_Create_k				= m_Create_k;
	pAdd->m_NodPos					= m_NodPos;		// Needed to avoid Duplicate in Triangle Situation
	////////////////////
	return;
}		

void CDrStatic::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrStatic::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_StaLTypes;i++)
   		if(StaLTypes[i].num == STATICLOAD) 
   		{
   			name = StaLTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
	return;

} 
  
int CDrStatic::Calc_3DBoundsLocal(pWORLD pOut, int nPts)
{
	// HAS TO BE UNION OF ALL THE SPRINGS OR SNUBBER
	//////////////////////	
	WORLD	Coords;
	int i;
	///////////////////////////
	for (i=0;i<nPts;i++)
	{
		///////////////////////
		Coords.x = pOut[i].x; 				
		Coords.y = pOut[i].y; 				
		Coords.z = pOut[i].z; 				
		///////////////////////////////////// compare and adjust
		if(Coords.x<m_dMin.x) m_dMin.x = Coords.x; 				
		if(Coords.y<m_dMin.y) m_dMin.y = Coords.y; 				
		if(Coords.z<m_dMin.z) m_dMin.z = Coords.z;
		 				
			if(Coords.x>m_dMax.x) m_dMax.x = Coords.x; 				
			if(Coords.y>m_dMax.y) m_dMax.y = Coords.y; 				
			if(Coords.z>m_dMax.z) m_dMax.z = Coords.z;
			//////////////////////////////////// 				
	}
	////////////////////////
	SetLocalCorner(&m_dMin,0);
	SetLocalCorner(&m_dMax,1);
	////////////////////////
	return	0;
}
//////////////////////////////////////////////////////////
void CDrStatic::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrStatic::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}
	
void CDrStatic::TransformObjectToViewDirect
				(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes)
{
	/////////////////////////////
	TransformToEyePosDirect
				(pLM,pViewM,pComposedM,bYes);
	/////////////////////////////
}

BOOL CDrStatic::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrStatic::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

//	if(!m_bDoneProject)
//	{
		m_bDoneProject = TRUE;
		//////////////////////
		ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		Calc_ScreenRectFromCNodes();
		////////////////////////////
//	}

}

int CDrStatic::GetApproDataLen(STALPROC StaLProc, int direction)
{
	////////////
	switch(StaLProc)
	{
//		case STL_THERMAL:return MAX_THERMAL_PT;
		case STL_LUMPWT:return MAX_LUMPWT_PT;

		case STL_FORCE:			// fall thro'
		case STL_DISPLACE:
		case STL_PRESSURE:
		case STL_THERMAL:	// temporarily
			switch(direction)
			{
				case 0:
				case 1:
				case 2:return MAX_FORCE_PT;
				case 3:
				case 4:
				case 5:return MAX_MOMENT_PT;
			}

		default:
			break;
		//////////////////////
	}
	/////////
	return 0;
}

void CDrStatic::GetApproPts(STALPROC StaLProc,WORLD pOut[],int nPts,
														int direction)
{
	int i;
	////////////
	switch(StaLProc)
	{
		/////////////////////////////////////////////////////// THERMAL
/*
		case STL_THERMAL:
		{
			for(i=0;i<nPts;i++)
			{
				pOut[i].x = m_TemperDat[i].x;
				pOut[i].y = m_TemperDat[i].y;
				pOut[i].z = m_TemperDat[i].z;
			}
			return;
		}
*/
		/////////////////////////////////////////////////////// LUMPWT
		case STL_LUMPWT:
		{
			for(i=0;i<nPts;i++)
			{
				pOut[i].x = m_LumpWtDat[i].x;
				pOut[i].y = m_LumpWtDat[i].y;
				pOut[i].z = m_LumpWtDat[i].z;
			}
			return;
		}

		/////////////////////////////////////////////////////// FORCE & PRESSURE & DISPLACE
		case STL_DISPLACE:		// fall thro'
		case STL_PRESSURE:
		case STL_THERMAL:
		case STL_FORCE:
		{
			switch(direction)
			{
				case 0:							// TX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_ForceDat_X[i].x;
						pOut[i].y = m_ForceDat_X[i].y;
						pOut[i].z = m_ForceDat_X[i].z;
					}
					return;

				case 1:							// TY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_ForceDat_Y[i].x;
						pOut[i].y = m_ForceDat_Y[i].y;
						pOut[i].z = m_ForceDat_Y[i].z;
					}
					return;

				case 2:							// TZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_ForceDat_Z[i].x;
						pOut[i].y = m_ForceDat_Z[i].y;
						pOut[i].z = m_ForceDat_Z[i].z;
					}
					return;

				case 3:							// RX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_MomentDat_X[i].x;
						pOut[i].y = m_MomentDat_X[i].y;
						pOut[i].z = m_MomentDat_X[i].z;
					}
					return;

				case 4:							// RY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_MomentDat_Y[i].x;
						pOut[i].y = m_MomentDat_Y[i].y;
						pOut[i].z = m_MomentDat_Y[i].z;
					}
					return;

				case 5:							// RZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_MomentDat_Z[i].x;
						pOut[i].y = m_MomentDat_Z[i].y;
						pOut[i].z = m_MomentDat_Z[i].z;
					}
					return;
			}
		}

		default:
			break;
		//////////////////////
	}
	/////////
	return;
}


void CDrStatic::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{
	AfxMessageBox("CDrStatic::TransformToWorldPos\nSHOULD NOT BE CALLED");
	return;
	/////////////////////
	pMATRIX		pLMP;	
	int i;
	///////////////////////// 
	if(bYes)
		pLMP 	= pLM;
	/////////////////////////////////////// All Data Pts
	CXForm XForm;
	WORLD LocalPos,WorldPos;
	///////////////////////////////
	pWORLD pLoc = m_pLoc[m_CurDir];
	pWORLD pWor = m_pEye[m_CurDir];
	int nPts	= m_nPts[m_CurDir];
	///////////////
	for (i = 0; i<nPts; i++)
	{
		LocalPos.x = pLoc[i].x;
		LocalPos.y = pLoc[i].y;
		LocalPos.z = pLoc[i].z;
		//////////////
		if(bYes)
			XForm.Transform(&LocalPos, &WorldPos, pLMP);
		/////////////////////////////	
		pWor[i].x = WorldPos.x;
		pWor[i].y = WorldPos.y;
		pWor[i].z = WorldPos.z;
		/////////////////////////////
	}	
	/////////////////////////////////////// Bounding Corners
	for (i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetLocalCorner(&LocalPos, i);
		//////////////
		if(bYes)
			XForm.Transform(&LocalPos, &WorldPos, pLMP);
		/////////////////////////////	
		SetWorldCorner(&WorldPos, i);
		/////////////////////////////
	}	
}

void CDrStatic::TransformToEyePos(pMATRIX pViewM)
{
	AfxMessageBox("CDrStatic::TransformToEyePos\nSHOULD NOT BE CALLED");
	return;
	/////////////////////
	int i;
	CXForm XForm;
	WORLD WorldPos,EyePos;
	///////////////////////////////
	pWORLD pWor = m_pEye[m_CurDir];
	int nPts	= m_nPts[m_CurDir];
	//////////////////////////////////////////// View Transform
	for (i = 0; i<nPts; i++)
	{
		WorldPos.x = pWor[i].x;
		WorldPos.y = pWor[i].y;
		WorldPos.z = pWor[i].z;
		/////////////////////////
		XForm.Transform(&WorldPos, &EyePos,pViewM); // Eye at PRP
		/////////////////////////	
		pWor[i].x = EyePos.x;
		pWor[i].y = EyePos.y;
		pWor[i].z = EyePos.z;
		/////////////////////////
	}	
	/////////////////////////////////////// Bounding Corners
	for (i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetWorldCorner(&WorldPos, i);
		//////////////
		XForm.Transform(&WorldPos, &EyePos,pViewM);
		/////////////////////////// 
		SetEyeCorner(&EyePos, i);	
		///////////////////////////
	}
}

void CDrStatic::TransformToEyePosDirect
				(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes)
{
	WORLD LocalPos,EyePos;
	CXForm XForm(m_bParallel);
	//////////////////////
	if(bYes)
	{
		//////////////////////////
		XForm.ComposeCombineMATRIX
				(pLM,pViewM,pComposedM);		// Penultimate
		//////////////////////////
	}
	//////////////////////////////////////////// View Transform(Current Direction)
	pWORLD pLoc = m_pLoc[m_CurDir];
	pWORLD pEye = m_pEye[m_CurDir];
	int nPts	= m_nPts[m_CurDir];
	///////////////////////////////
	for (int i = 0; i<nPts; i++)
	{
		LocalPos.x = pLoc[i].x;
		LocalPos.y = pLoc[i].y;
		LocalPos.z = pLoc[i].z;
		/////////////////////////
		XForm.Transform(&LocalPos, &EyePos,pComposedM); // Eye at PRP
		/////////////////////////	
		pEye[i].x = EyePos.x;
		pEye[i].y = EyePos.y;
		pEye[i].z = EyePos.z;
		/////////////////////////
	}	
	/////////////////////////////////////// Bounding Corners
	// (ONLY ONCE) because it contains
	// UNION of all directions Data
	///////////////////////////////////////
	if(!m_bDoneXform)
	{
		m_bDoneXform = TRUE;
		///////////////
		for (int i = 0; i<MAX_NODES_CORNER; i++)
		{
			GetLocalCorner(&LocalPos, i);
			//////////////
			XForm.Transform(&LocalPos, &EyePos,pComposedM);
			/////////////////////////// 
			SetEyeCorner(&EyePos, i);	
			///////////////////////////
		}
	}
}

void CDrStatic::ProjectToScreenPos
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{
	// NEEDED ONLY FOR SMART PAINT: BOUNDING RECTANGLE
	///////////////////////////////////////////////////

	WORLD 	EyePos,Scr3DPos;
	CXForm XForm;
	/////////////////////////////////////// Bounding Corners
	POINT pt;
	// (ONLY ONCE) because it contains
	// UNION of all directions Data
	///////////////////////////////////////
	for (int i = 0; i<MAX_NODES_CORNER; i++)
	{
		GetEyeCorner(&EyePos, i);
		//////////////
		XForm.Project(pvv3DM,&EyePos, &Scr3DPos);
		SetScreen3DCorner(&Scr3DPos, i);
		//////////////////////////////////////////////////////
		// 	3DScreenPos belongs to [0,-1] because of CVV	//
		//	So before we Change into Integer Logical		//
		//	Coordinates, we Must Use Screen Client Data		//
		//////////////////////////////////////////////////////
		pt.x = (int)(Scr3DPos.x * dScale_U);
		pt.y = (int)(Scr3DPos.y * dScale_V);
		////
		SetScreen2DCorner(pt, i);
		/////////////////////////
	}
	//////////////
}

void CDrStatic::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	Rearrange2DCorners();
	FinishObject();
	///////////////
}

void CDrStatic::Rearrange2DCorners()
{ 

	//We want to reaarange as TopLeft(m_pt[0]) & RightBottom(m_pt[1]):Logical
	////////////////////	
	int	temp;
	///////////////////
	if(m_pt[0].x > m_pt[1].x)     // left > right: switch
	{
		temp 		= m_pt[0].x;
		m_pt[0].x 	= m_pt[1].x;
		m_pt[1].x 	= temp;
	}			 
	if(m_pt[0].y < m_pt[1].y)     // top < bottom: switch
	{
		temp 		= m_pt[0].y;
		m_pt[0].y 	= m_pt[1].y;
		m_pt[1].y 	= temp;
	}			 
	////////////
	return;
}
	
void CDrStatic::FinishObject()
{ 

	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	if(m_StaLCard.StaLProc == STL_LUMPWT)
	{
		m_rectBounding.left   = m_pt->x - 2*RADIUS;
		m_rectBounding.right  = m_pt->x + 2*RADIUS;
		m_rectBounding.top    = m_pt->y + 2*RADIUS;
		m_rectBounding.bottom = m_pt->y - 2*RADIUS;
	}
	else
		m_rectBounding = CRect(m_pt[0].x, m_pt[0].y, m_pt[0].x, m_pt[0].y);

	for ( int i=1; i < MAX_NODES_CORNER; i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		m_rectBounding.left     = min(m_rectBounding.left, m_pt[i].x);
		m_rectBounding.right    = max(m_rectBounding.right, m_pt[i].x);
		m_rectBounding.top      = max(m_rectBounding.top, m_pt[i].y);
		m_rectBounding.bottom   = min(m_rectBounding.bottom, m_pt[i].y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the Curve when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	///////
	return; 
	
} 
//////////////////////////////////////////////////////////////
void CDrStatic::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{
	m_bStepXform	= FALSE;
	////////////////////////////
	m_bParallel		= bParallel;
    m_nView			= nView;
    m_dzMin			= dzMin;
	m_dScale_U		= dScale_U;		// vv3DToLP:U-direction  
	m_dScale_V		= dScale_V;		// vv3DToLP:V-direction
	m_ViewM			= *pViewM;		// viewers transform MATRIX
	m_vv3DM			= *pvv3DM;		// Window to 3D Viewport MATRIX
	m_ComposedM		= *pViewM;
	//////////////////////////
	int i;
	///////////////////////////////////////////////////////////////// PreProcess
	for(i=0;i<6;i++)		// Over All Directions
	{
		if
		(
			(m_StaLCard.kode[i] == 0) ||
			(	i>0 && 
				(
					(m_StaLCard.StaLProc == STL_THERMAL) ||
					(m_StaLCard.StaLProc == STL_LUMPWT)
				)	
			)
		)
		continue;
		/////////////
		m_CurDir = i;
		////////////////////////////////////////////////////
		Calc_3DBoundsLocal(m_pLoc[i],m_nPts[i]);
		//////////////////
	}
	///////////////////////////////////////////////////////////////// Doit
	MATRIX LM;
	BOOL bXForm = FALSE;
	////////////////////
	for(i=0;i<6;i++)		// Over All Directions
	{
		if(m_StaLCard.kode[i] == 0)
			continue;
		/////////////
		m_CurDir = i;
		/////////////////////////////////
		if(!m_bStepXform)
			TransformObjectToViewDirect
					(&LM,&m_ViewM,&m_ComposedM,bXForm);
		else
		{
			////////////////////////////////////////////// Coordinates XForm
												// Local->World	  
			TransformObjectToWorld(&LM,bXForm);
			///////////////////////////////////////////
			TransformObjectToView(&m_ViewM);
		}	
		///////////////////////////////////////////
		ProjectObject(&m_vv3DM,m_dScale_U,m_dScale_V);///	calc Bounding Rect 
		///////////////////////////////////
//		FinishObject();//	calc Bounding Rect  
		/////////////
	}
}
						
//////////////////////////////////////////////////////////////
void CDrStatic::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	if(bPenChange)
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
	else
   		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
  	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////////////////// Doit
	for(int i=0;i<6;i++)		// Over All Directions
	{

		if(m_StaLCard.kode[i] == 0)
			continue;
		/////////////
		m_CurDir = i;
	    ///////////////////////////////////////////// Draw 
		GoDoIt(PtrDC,m_CurDir);
		///////////////////////
	}
	///////////////////////////////   	
   	PtrDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
   	//////////////////////////////////////////
    
}                            

void CDrStatic::GoDoIt(CDC* PtrDC, int direction)
{ 

	//////////////////////////////////
	switch(m_StaLCard.StaLProc)
	{
		////////////////////////////////////////////// Force, Displace & Pressure
		case STL_DISPLACE:		// fall thro'
		case STL_PRESSURE:
		case STL_THERMAL:
		case STL_FORCE:

			if(direction<3)		// Translation
			{
				GoConnect_TRANSLATION(PtrDC,direction);
				//////////////
				return;
			}
			else
			if(direction>=3)		// Rotation
			{
				GoConnect_ROTATION(PtrDC,direction);
				//////////////
				return;
			}
			/////////
			break;

		///////////////////////////////////////////// LUMPWT
		case STL_LUMPWT:

			GoConnect_LUMPWT(PtrDC,direction);
			//////////////
			return;
/*
		///////////////////////////////////////////// THERMAL
		case STL_THERMAL:

			GoConnect_THERMAL(PtrDC,direction);
			//////////////
			return;
*/
		default:
			break;
		//////////////////////
		
	}
	/////////
	return;

}   


void CDrStatic::GoConnect_TRANSLATION(CDC* PtrDC, int direction)
{ 

	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
//	for(i=1;i<MAX_FORCE_PT-1;i++)
	for(i=1;i<MAX_FORCE_PT-1;i++)		// last one for text, so omit
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	///////////////////////////////////// close it
	DrawLine3D(PtrDC,pOut+MAX_FORCE_PT-2,pOut,TRUE);	 
	///////////////////////////////////// Value Text Out LastPt 
  	
} 

void CDrStatic::GoConnect_ROTATION(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<MAX_MOMENT_PT;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	///////////////////////////////////// close it
	DrawLine3D(PtrDC,pOut+MAX_MOMENT_PT-1,pOut,TRUE);	 
	///////////////////////////////////// Value Text Out LastPt
  	
} 

void CDrStatic::GoConnect_THERMAL(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<MAX_THERMAL_PT-1;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	///////////////////////////////////// close it
	DrawLine3D(PtrDC,pOut+MAX_THERMAL_PT-2,pOut,TRUE);	 
	///////////////////////////////////// Value Text Out LastPt
  	
} 

void CDrStatic::GoConnect_LUMPWT(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	////////////////////////////////////// ellipse
   	CPen    Pen;
   	CPen*   PtrOldPen;
	CBrush	Br;
	CBrush* pBrOld;
	/////////////////////////////////////////////////// Pen 
	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
   	PtrOldPen = PtrDC->SelectObject(&Pen);
	//////////////////////////////////////
	Br.CreateSolidBrush(m_crPenColor);
	pBrOld = PtrDC->SelectObject(&Br);
	////////////////////////////////////////////////////////
   	CRect Rect;
	Rect.left   = m_pt->x - RADIUS;
	Rect.right  = m_pt->x + RADIUS;
	Rect.top    = m_pt->y - RADIUS;
	Rect.bottom = m_pt->y + RADIUS;
	/////////////////////	
	PtrDC->Ellipse(&Rect);
	/////////////////////////////// Delete 
	PtrDC->SelectObject(PtrOldPen);   
	Pen.DeleteObject(); 
	PtrDC->SelectObject(pBrOld);   
	Br.DeleteObject(); 
	//////////	
  	
} 
//////////////////////////////////////////////////////////////////
BOOL CDrStatic::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrStatic* pSupp = (CDrStatic*)(pObject);
	///////////////////////////////////////////// SupID
	CString SupID = (pSupp->GetStaLCard())->load_id;
	//////////////////////////////////////////////	 
	switch(KeyNo)
	{ 
	  case 1:         // PipeID = Nid_I + Nid_J  

		if((pSupp->GetStaLCard())->load_id ==KeyID)
			return TRUE;
		break;  

	  case 2:         
		break;

	  default:
	  		return FALSE;					
	}
	return FALSE;
}

void CDrStatic::Serialize(CArchive& ar)
{

	CDrObject::Serialize( ar);              // must call base class Serializer
	//////////////////////////////////////     
	
	if (ar.IsStoring())
	{
		TRACE( " Supp   :Storing\n");	// TODO: add loading code here

		//////////////////////////////////////////////////////

 	}
	else
	{
	
		TRACE( " Supp   :Loading\n");	// TODO: add loading code here

		//////////////////////////////////////////////////////

	}        
	//////////////////////////////////////////////////////
	m_NodeList.Serialize(ar);
	////////////////////////

}
	
BOOL CDrStatic::IsObjectHit(int nNet,POINT point)
{
	/////////////// TODO
	return FALSE;
	///////////////
}
////////////////////// END OF MODULE ///////////////////////

