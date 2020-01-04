// Supp.cpp : implementation file
//


#include "stdafx.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN

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
////////////////////// SuppObjs
#include "Ext_Supp.h"        
#include "Def_Supp.h"        

#include "DrLinSup.h"
////////////////////////////////////
#define	DEFAULT_STIFF	1.0e12
///////////////////////////// Spring
#define	LENGTH	.3	
#define	WIDTH	.15	
#define	TICK	WIDTH/4	
///////////////////////////// Snubber
#define	LEN1	7	
#define	BOXSIZE	LEN1	
#define	LEN2	LEN1	
//////////////////
#define	MAX_RIGID_PT	6
#define	MAX_TSPR_PT		7
#define	MAX_RSPR_PT		13
#define	MAX_TSNU_PT		13
#define	MAX_RSNU_PT		19
#define MAX_PT			19  // max(MAX_RIGID_PT,MAX_TSPR_PT etc..)
//////////////////////////////////////////////////////////////////////////// static
static WORLD	m_RigidDat[MAX_RIGID_PT]=
{
	{0.0,			0.0,		0.0},{0.0,			LENGTH/2,	0.0},		 
	{0.0,			-LENGTH/2,	0.0},{1.5*TICK,		LENGTH/2,	0.0},
	{1.5*TICK,			0.0,	0.0},{1.5*TICK,		-LENGTH/2,	0.0}
};		

static WORLD	m_TSprDat_X[MAX_TSPR_PT]=
{
	{0.0,			0.0,		0.0},
	{LENGTH,		0.0,		0.0},{LENGTH,		WIDTH/2,	0.0},	// Ticks
	{LENGTH,		-WIDTH/2,	0.0},{LENGTH+TICK,	WIDTH/2,	0.0},
	{LENGTH+TICK,	0.0,		0.0},{LENGTH+TICK,	-WIDTH/2,	0.0}	
	///////////////
};
	
static WORLD 	m_TSprDat_Y[MAX_TSPR_PT]=
{
	{0.0,		0.0,			0.0},
	{0.0,		-LENGTH,		0.0},{WIDTH/2,	-LENGTH,		0.0},	// Ticks
	{-WIDTH/2,	-LENGTH,		0.0},{WIDTH/2,	-LENGTH-TICK,	0.0},
	{0.0,		-LENGTH-TICK,	0.0},{-WIDTH/2,	-LENGTH-TICK,	0.0}
	///////////////
};	
	
static WORLD 	m_TSprDat_Z[MAX_TSPR_PT]=
{
	{0.0,		0.0,0.0			},
	{0.0,			0.0,LENGTH	},{WIDTH/2,	0.0,LENGTH		},			// Ticks
	{-WIDTH/2,	0.0,LENGTH		},{WIDTH/2,	0.0,LENGTH+TICK	},
	{0.0,		0.0,LENGTH+TICK	},{-WIDTH/2,0.0,LENGTH+TICK	}
	///////////////
};	

////////////////
static WORLD 	m_RSprDat_X[MAX_RSPR_PT]=
{
	{0.0,			0.0,		0.0},{-.5*LENGTH,	0.0,		0.0},		 
    {-.5*LENGTH,	-.2*WIDTH,	0.0},{-.4*LENGTH,	-.2*WIDTH,	0.0},		 
    {-.4*LENGTH,	.2*WIDTH,	0.0},{-.6*LENGTH,	.2*WIDTH,	0.0},		 
    {-.6*LENGTH,	0.0,		0.0},
	{-LENGTH,		0.0,		0.0},{-LENGTH,		.5*WIDTH,	0.0},	// Ticks
	{-LENGTH,		-.5*WIDTH,	0.0},{-LENGTH-TICK,	.5*WIDTH,	0.0},
	{-LENGTH-TICK,	0.0,		0.0},{-LENGTH-TICK,	-.5*WIDTH,	0.0}
	///////////////
};
	
static WORLD 	m_RSprDat_Y[MAX_RSPR_PT]=
{
	{0.0,			0.0,		0.0},{0.0,			.5*LENGTH,	0.0},		 
    {.2*WIDTH,		.5*LENGTH,	0.0},{.2*WIDTH,		.4*LENGTH,	0.0},		 
    {-.2*WIDTH,		.4*LENGTH,	0.0},{-.2*WIDTH,	.6*LENGTH,	0.0},		 
    {0.0,			.6*LENGTH,	0.0},							
	{0.0,			LENGTH,		0.0},{.5*WIDTH,		LENGTH,		0.0},	// Ticks
	{-.5*WIDTH,		LENGTH,		0.0},{.5*WIDTH,		LENGTH+TICK,0.0},
	{0.0,			LENGTH+TICK,0.0},{-.5*WIDTH,	LENGTH+TICK,0.0}
	///////////////
};	
	
static WORLD 	m_RSprDat_Z[MAX_RSPR_PT]=
{
	{0.0,	0.0,				-0.0},{0.0,	0.0,		-.5*LENGTH	},		 
    {0.0,	.2*WIDTH,	-.5*LENGTH	},{0.0,	.2*WIDTH,	-.4*LENGTH	},		 
    {0.0,	-.2*WIDTH,	-.4*LENGTH	},{0.0,	-.2*WIDTH,	-.6*LENGTH	},		 
    {0.0,	0.0,		-.6*LENGTH	},								
	{0.0,	0.0,		-LENGTH		},{0.0,	.5*WIDTH,	-LENGTH		},	// Ticks
	{0.0,	-.5*WIDTH,	-LENGTH		},{0.0,	.5*WIDTH,	-LENGTH-TICK},
	{0.0,	0.0,		-LENGTH-TICK},{0.0,	-.5*WIDTH,	-LENGTH-TICK}
	///////////////
};	
////////////////////////////////////// Snubber    							
static WORLD 	m_TSnuDat_X[MAX_TSNU_PT]=
{
	{0.0,			0.0,		0.0},{.4*LENGTH,	0.0,		0.0},		 
    {.4*LENGTH,		-.2*WIDTH,	0.0},{.6*LENGTH,	-.2*WIDTH,	0.0},		 
    {.6*LENGTH,		0.0,		0.0},{.6*LENGTH,	.2*WIDTH,	0.0},		 
    {.4*LENGTH,		.2*WIDTH,	0.0},								
	{LENGTH,		0.0,		0.0},{LENGTH,		.5*WIDTH,	0.0},	// Ticks
	{LENGTH,		-.5*WIDTH,	0.0},{LENGTH+TICK,	.5*WIDTH,	0.0},
	{LENGTH+TICK,	0.0,		0.0},{LENGTH+TICK,	-.5*WIDTH,	0.0}
	///////////////
};
	
static WORLD 	m_TSnuDat_Y[MAX_TSNU_PT]=
{
	{0.0,			0.0,		0.0},{0.0,			.4*LENGTH,	0.0},		 
    {-.2*WIDTH,		.4*LENGTH,	0.0},{-.2*WIDTH,	.6*LENGTH,	0.0},		 
    {0.0,			.6*LENGTH,	0.0},{.2*WIDTH,		.6*LENGTH,	0.0},		 
    {.2*WIDTH,		.4*LENGTH,	0.0},
	{0.0,			LENGTH,		0.0},{.5*WIDTH,		LENGTH,		0.0},	// Ticks
	{-.5*WIDTH,		LENGTH,		0.0},{.5*WIDTH,		LENGTH+TICK,0.0},
	{0.0,			LENGTH+TICK,0.0},{-.5*WIDTH,	LENGTH+TICK,0.0}
	///////////////
};	
	
static WORLD 	m_TSnuDat_Z[MAX_TSNU_PT]=
{
	{0.0,0.0,		0.0			},{0.0,0.0,			.4*LENGTH	},		 
    {0.0,-.2*WIDTH,	.4*LENGTH	},{0.0,-.2*WIDTH,	.6*LENGTH	},		 
    {0.0,0.0,		.6*LENGTH	},{0.0,.2*WIDTH,	.6*LENGTH	},		 
    {0.0,.2*WIDTH,	.4*LENGTH	},
	{0.0,0.0,		LENGTH		},{0.0,.5*WIDTH,	LENGTH		},		// Ticks
	{0.0,-.5*WIDTH,	LENGTH		},{0.0,.5*WIDTH,	LENGTH+TICK	},
	{0.0,0.0,		LENGTH+TICK	},{0.0,-.5*WIDTH,	LENGTH+TICK	}
	///////////////
};	
////////////////
static WORLD 	m_RSnuDat_X[MAX_RSNU_PT]=
{
	{0.0,			0.0,		0.0},{-.3*LENGTH,	0.0,		0.0},		 
    {-.3*LENGTH,	-.2*WIDTH,	0.0},{-.2*LENGTH,	-.2*WIDTH,	0.0},		 
    {-.2*LENGTH,	.2*WIDTH,	0.0},{-.4*LENGTH,	.2*WIDTH,	0.0},		 
    {-.4*LENGTH,	0.0,		0.0},		 
	{-.6*LENGTH,	0.0,		0.0},		 
    {-.6*LENGTH,	-.2*WIDTH,	0.0},{-.8*LENGTH,	-.2*WIDTH,	0.0},		 
    {-.8*LENGTH,	0.0,		0.0},{-.8*LENGTH,	.2*WIDTH,	0.0},		 
    {-.6*LENGTH,	.2*WIDTH,	0.0},
	{-LENGTH,		0.0,		0.0},{-LENGTH,		.5*WIDTH,	0.0},	// Ticks
	{-LENGTH,		-.5*WIDTH,	0.0},{-LENGTH-TICK,	.5*WIDTH,	0.0},
	{-LENGTH-TICK,	0.0,		0.0},{-LENGTH-TICK,	-.5*WIDTH,	0.0}
	///////////////
};
	
static WORLD 	m_RSnuDat_Y[MAX_RSNU_PT]=
{
	{0.0,			0.0,		0.0	},{0.0,			-.3*LENGTH,		0.0},		 
    {-.2*WIDTH,		-.3*LENGTH,	0.0	},{-.2*WIDTH,	-.2*LENGTH,		0.0},		 
    {.2*WIDTH,		-.2*LENGTH,	0.0	},{.2*WIDTH,	-.4*LENGTH,		0.0},		 
    {0.0,			-.4*LENGTH,	0.0	},		 
	{0.0,			-.6*LENGTH,	0.0	},		 
    {-.2*WIDTH,		-.6*LENGTH,	0.0	},{-.2*WIDTH,	-.8*LENGTH,		0.0},		 
    {0.0,			-.8*LENGTH,	0.0	},{.2*WIDTH,	-.8*LENGTH,		0.0},		 
    {.2*WIDTH,		-.6*LENGTH,	0.0	},
	{0.0,			-LENGTH,	0.0	},{.5*WIDTH,	-LENGTH,		0.0},	// Ticks
	{-.5*WIDTH,		-LENGTH,	0.0	},{.5*WIDTH,	-LENGTH-TICK,	0.0},
	{0.0,			-LENGTH-TICK,0.0},{-.5*WIDTH,	-LENGTH-TICK,	0.0}
	///////////////
};	
	
static WORLD 	m_RSnuDat_Z[MAX_RSNU_PT]=
{
	{0.0,	0.0,		0.0			},{0.0,	0.0,		-.3*LENGTH	},		 
    {0.0,	-.2*WIDTH,	-.3*LENGTH	},{0.0,	-.2*WIDTH,	-.2*LENGTH	},		 
    {0.0,	.2*WIDTH,	-.2*LENGTH	},{0.0,.2*WIDTH,	-.4*LENGTH	},		 
    {0.0,	0.0,		-.4*LENGTH	},		 
	{0.0,	0.0,		-.6*LENGTH	},		 
    {0.0,	-.2*WIDTH,	-.6*LENGTH	},{0.0,	-.2*WIDTH,	-.8*LENGTH	},		 
    {0.0,	0.0,		-.8*LENGTH	},{0.0,	.2*WIDTH,	-.8*LENGTH	},		 
    {0.0,	.2*WIDTH,	-.6*LENGTH	},
	{0.0,	0.0,		-LENGTH		},{0.0,	.5*WIDTH,	-LENGTH		},	// Ticks
	{0.0,	-.5*WIDTH,	-LENGTH		},{0.0,	.5*WIDTH,	-LENGTH-TICK	},
	{0.0,	0.0,		-LENGTH-TICK},{0.0,	-.5*WIDTH,	-LENGTH-TICK	}
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
// CDrLinSup
IMPLEMENT_SERIAL(CDrLinSup, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrLinSup, CDrObject)
	//{{AFX_MSG_MAP(CDrLinSup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrLinSup::CDrLinSup()
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
    SetObjectType((int)LIN_SUPPORT);
    SetElemType((int)ELEM_OBJECT);          //
    //////////////////////////////  
	m_SuppCard.ElNum		= 0;                  
	m_SuppCard.IDNum		= 0;                  
	m_SuppCard.sup_id		= "";
	m_SuppCard.SuppProc		= SUP_RIGID;				
	///////////////////////////
	for(i=0;i<6;i++)
	{
		m_SuppCard.kode[i]		= 0;
		m_SuppCard.stiffness[i]	= DEFAULT_STIFF;
	}
	m_SuppCard.nid_a		= "";            
	m_SuppCard.bTanCur		= FALSE;            
	m_SuppCard.bTanPat		= FALSE;            
	m_SuppCard.bNorPat		= FALSE;            
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

CDrLinSup::~CDrLinSup()
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
	
void CDrLinSup::SetSuppCard(SUPPCARD sC)
{
	///////////////////
	m_SuppCard.sup_id		= sC.sup_id;
	m_SuppCard.SuppProc		= sC.SuppProc;
	m_SuppCard.kode[0]		= sC.kode[0];
	m_SuppCard.kode[1]		= sC.kode[1];
	m_SuppCard.kode[2]		= sC.kode[2];
	m_SuppCard.kode[3]		= sC.kode[3];
	m_SuppCard.kode[4]		= sC.kode[4];
	m_SuppCard.kode[5]		= sC.kode[5];

	m_SuppCard.stiffness[0]	= sC.stiffness[0];
	m_SuppCard.stiffness[1]	= sC.stiffness[1];
	m_SuppCard.stiffness[2]	= sC.stiffness[2];
	m_SuppCard.stiffness[3]	= sC.stiffness[3];
	m_SuppCard.stiffness[4]	= sC.stiffness[4];
	m_SuppCard.stiffness[5]	= sC.stiffness[5];

	m_SuppCard.pgap[0]		= sC.pgap[0];
	m_SuppCard.pgap[1]		= sC.pgap[1];
	m_SuppCard.pgap[2]		= sC.pgap[2];
	m_SuppCard.pgap[3]		= sC.pgap[3];
	m_SuppCard.pgap[4]		= sC.pgap[4];
	m_SuppCard.pgap[5]		= sC.pgap[5];
	/////////////////////
	m_SuppCard.nid_a		= sC.nid_a;
	m_SuppCard.bCN_a		= sC.bCN_a;		// nid_a is Control Node?		
	m_SuppCard.nid_b		= sC.nid_b;			
	m_SuppCard.bCN_b		= sC.bCN_b;		// nid_b is Control Node?		
	m_SuppCard.bTanCur		= sC.bTanCur;				
	m_SuppCard.bTanPat		= sC.bTanPat;				
	m_SuppCard.bNorPat		= sC.bNorPat;				
	m_SuppCard.ID_CP		= sC.ID_CP;		
	m_SuppCard.jcType		= sC.jcType;		//	JC_DEFAULT,
	m_SuppCard.GenKind		= sC.GenKind;
	m_SuppCard.SkewDir.x	= sC.SkewDir.x;
	m_SuppCard.SkewDir.y	= sC.SkewDir.y;
	m_SuppCard.SkewDir.z	= sC.SkewDir.z;
	///////////////////////////////////
	return;
}

void CDrLinSup::InitRawData(SUPPPROC SuppProc)
{
	m_SuppCard.SuppProc = SuppProc; 
	///////////////////////////////////////////////////////////////// PreProcess
	for(int i=0;i<6;i++)		// Over All Directions
	{
		/////////////////////////////////
		m_nPts[i] = GetApproDataLen(SuppProc,i);
		GetApproPts(m_SuppCard.SuppProc,m_pLoc[i],m_nPts[i],i);
		////////////////////////////////////////////////////
	}	 
} 

void CDrLinSup::ReadyToDelete()
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
			CDListMgr* pSuppList = pObject->GetSuppList();
			int index = pSuppList->GetObjectIndex(this);
			if(index>=0)
				pSuppList->RemoveObject(index); //elem
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
			CDListMgr* pSuppList = pObject->GetSuppList();
			int index = pSuppList->GetObjectIndex(this);
			if(index>=0)
				pSuppList->RemoveObject(index); //elem
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
			CDListMgr* pSuppList = pObject->GetSuppList();
			int index = pSuppList->GetObjectIndex(this);
			if(index>=0)
				pSuppList->RemoveObject(index); //elem
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
			CDListMgr* pSuppList = pObject->GetSuppList();
			int index = pSuppList->GetObjectIndex(this);
			if(index>=0)
				pSuppList->RemoveObject(index); //elem
		/////////////////////////
		}
	//////////
	}
	//////////////////////////////////////////////////////////////
}

int CDrLinSup::DealObjectDialog()
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
	
void CDrLinSup::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrLinSup* pAdd = (CDrLinSup*) pObject;
	///////////////////////////////////////////////////// SuppINFO
	m_NodeList.AddTail(pAdd->GetNodeList() ); 
	////////////////////////////////////////////////////
	m_SuppCard.ElNum		= (pAdd->GetSuppCard())->ElNum;                  
	m_SuppCard.IDNum		= (pAdd->GetSuppCard())->IDNum;                  
	m_SuppCard.sup_id		= (pAdd->GetSuppCard())->sup_id;
	m_SuppCard.SuppProc		= (pAdd->GetSuppCard())->SuppProc;				
	///////////////////////////
	for(int i=0;i<6;i++)
	{
		m_SuppCard.kode[i]		=  (pAdd->GetSuppCard())->kode[i];
		m_SuppCard.stiffness[i]	=  (pAdd->GetSuppCard())->stiffness[i];
	}
	m_SuppCard.nid_a		=  (pAdd->GetSuppCard())->nid_a;            
	m_SuppCard.bCN_a		=  (pAdd->GetSuppCard())->bCN_a;            
	m_SuppCard.nid_b		=  (pAdd->GetSuppCard())->nid_b;            
	m_SuppCard.bCN_b		=  (pAdd->GetSuppCard())->bCN_b;            
	m_SuppCard.bTanCur		=  (pAdd->GetSuppCard())->bTanCur;            
	m_SuppCard.bTanPat		=  (pAdd->GetSuppCard())->bTanPat;            
	m_SuppCard.bNorPat		=  (pAdd->GetSuppCard())->bNorPat;            
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
	////////////////////
	return;
}		

void CDrLinSup::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrLinSup* pAdd = (CDrLinSup*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	pAdd->m_NodeList.AddTail(GetNodeList() ); 
	////////////////////////////////////////////////////////   
	(pAdd->GetSuppCard())->ElNum	= m_SuppCard.ElNum;
	(pAdd->GetSuppCard())->IDNum	= m_SuppCard.IDNum;
	(pAdd->GetSuppCard())->sup_id	= m_SuppCard.sup_id;
	(pAdd->GetSuppCard())->SuppProc	= m_SuppCard.SuppProc;
	///////////////////////////
	for(int i=0;i<6;i++)
	{
		(pAdd->GetSuppCard())->kode[i]		=  m_SuppCard.kode[i];
		(pAdd->GetSuppCard())->stiffness[i] = m_SuppCard.stiffness[i];
	}
	(pAdd->GetSuppCard())->bTanCur	= m_SuppCard.bTanCur;            
	(pAdd->GetSuppCard())->bTanPat	= m_SuppCard.bTanPat;            
	(pAdd->GetSuppCard())->bNorPat	= m_SuppCard.bNorPat;            
	(pAdd->GetSuppCard())->nid_a	= m_SuppCard.nid_a;            
	(pAdd->GetSuppCard())->bCN_a	= m_SuppCard.bCN_a;            
	(pAdd->GetSuppCard())->nid_b	= m_SuppCard.nid_b;            
	(pAdd->GetSuppCard())->bCN_b	= m_SuppCard.bCN_b;            
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

void CDrLinSup::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrLinSup::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_SuppTypes;i++)
   		if(SuTypes[i].num == LIN_SUPPORT) 
   		{
   			name = SuTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
	return;

} 
  
int CDrLinSup::Calc_3DBoundsLocal(pWORLD pOut, int nPts)
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
void CDrLinSup::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrLinSup::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}
	
void CDrLinSup::TransformObjectToViewDirect
				(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes)
{
	/////////////////////////////
	TransformToEyePosDirect
				(pLM,pViewM,pComposedM,bYes);
	/////////////////////////////
}

BOOL CDrLinSup::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrLinSup::ProjectObject
				(pMATRIX pvv3DM,double dScale_U,double dScale_V)
{

	if(!m_bDoneProject)
	{
		m_bDoneProject = TRUE;
		//////////////////////
		ProjectToScreenPos(pvv3DM,dScale_U,dScale_V);
		///////////////////////
		Calc_ScreenRectFromCNodes();
		////////////////////////////
	}

}

int CDrLinSup::GetApproDataLen(SUPPPROC SuppProc, int direction)
{

	////////////
	switch(SuppProc)
	{
		case SUP_RIGID:return MAX_RIGID_PT;

		case SUP_LINSPR:
			switch(direction)
			{
				case 0:
				case 1:
				case 2:return MAX_TSPR_PT;
				case 3:
				case 4:
				case 5:return MAX_RSPR_PT;
			}
		case SUP_LINSNU:
			switch(direction)
			{
				case 0:
				case 1:
				case 2:return MAX_TSNU_PT;
				case 3:
				case 4:
				case 5:return MAX_RSNU_PT;
			}

		default:
			break;
		//////////////////////
	}
	/////////
	return 0;
}

void CDrLinSup::GetApproPts(SUPPPROC SuppProc,WORLD pOut[],int nPts,
														int direction)
{
	int i;
	////////////
	switch(SuppProc)
	{
		/////////////////////////////////////////////////////// RIGID
		case SUP_RIGID:
		{
			for(i=0;i<nPts;i++)
			{
				pOut[i].x = m_RigidDat[i].x;
				pOut[i].y = m_RigidDat[i].y;
				pOut[i].z = m_RigidDat[i].z;
			}
			return;
		}

		/////////////////////////////////////////////////////// SPRING
		case SUP_LINSPR:
		{
			switch(direction)
			{
				case 0:							// TX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSprDat_X[i].x;
						pOut[i].y = m_TSprDat_X[i].y;
						pOut[i].z = m_TSprDat_X[i].z;
					}
					return;

				case 1:							// TY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSprDat_Y[i].x;
						pOut[i].y = m_TSprDat_Y[i].y;
						pOut[i].z = m_TSprDat_Y[i].z;
					}
					return;

				case 2:							// TZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSprDat_Z[i].x;
						pOut[i].y = m_TSprDat_Z[i].y;
						pOut[i].z = m_TSprDat_Z[i].z;
					}
					return;

				case 3:							// RX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSprDat_X[i].x;
						pOut[i].y = m_RSprDat_X[i].y;
						pOut[i].z = m_RSprDat_X[i].z;
					}
					return;

				case 4:							// RY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSprDat_Y[i].x;
						pOut[i].y = m_RSprDat_Y[i].y;
						pOut[i].z = m_RSprDat_Y[i].z;
					}
					return;

				case 5:							// RZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSprDat_Z[i].x;
						pOut[i].y = m_RSprDat_Z[i].y;
						pOut[i].z = m_RSprDat_Z[i].z;
					}
					return;
			}
		}
		/////////////////////////////////////////////////////// SNUBBER
		case SUP_LINSNU:
		{
			switch(direction)
			{
				case 0:							// TX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSnuDat_X[i].x;
						pOut[i].y = m_TSnuDat_X[i].y;
						pOut[i].z = m_TSnuDat_X[i].z;
					}
					return;

				case 1:							// TY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSnuDat_Y[i].x;
						pOut[i].y = m_TSnuDat_Y[i].y;
						pOut[i].z = m_TSnuDat_Y[i].z;
					}
					return;

				case 2:							// TZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_TSnuDat_Z[i].x;
						pOut[i].y = m_TSnuDat_Z[i].y;
						pOut[i].z = m_TSnuDat_Z[i].z;
					}
					return;

				case 3:							// RX
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSnuDat_X[i].x;
						pOut[i].y = m_RSnuDat_X[i].y;
						pOut[i].z = m_RSnuDat_X[i].z;
					}
					return;

				case 4:							// RY
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSnuDat_Y[i].x;
						pOut[i].y = m_RSnuDat_Y[i].y;
						pOut[i].z = m_RSnuDat_Y[i].z;
					}
					return;

				case 5:							// RZ
					for(i=0;i<nPts;i++)
					{
						pOut[i].x = m_RSnuDat_Z[i].x;
						pOut[i].y = m_RSnuDat_Z[i].y;
						pOut[i].z = m_RSnuDat_Z[i].z;
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


void CDrLinSup::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{
	AfxMessageBox("CDrLinSup::TransformToWorldPos\nSHOULD NOT BE CALLED");
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

void CDrLinSup::TransformToEyePos(pMATRIX pViewM)
{
	AfxMessageBox("CDrLinSup::TransformToEyePos\nSHOULD NOT BE CALLED");
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

void CDrLinSup::TransformToEyePosDirect
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

void CDrLinSup::ProjectToScreenPos
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

void CDrLinSup::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	Rearrange2DCorners();
	FinishObject();
	///////////////
}

void CDrLinSup::Rearrange2DCorners()
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
	
void CDrLinSup::FinishObject()
{ 

	//////////////////////////////////////////////////////
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.
	
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
void CDrLinSup::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
					 	pMATRIX pViewM,pMATRIX pvv3DM,
						double dzMin,double dScale_U,double dScale_V)
{
	m_bStepXform	= FALSE;
	m_bDoneXform	= FALSE;
	m_bDoneProject	= FALSE;
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
			(m_SuppCard.kode[i] == 0) ||
			(i>0 && m_SuppCard.SuppProc == SUP_RIGID)
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
		if
		(
			(m_SuppCard.kode[i] == 0) ||
			(i>0 && m_SuppCard.SuppProc == SUP_RIGID)	// Once Only for Rigid
		)
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
void CDrLinSup::DoDrawView(CDC* PtrDC,BOOL bPenChange)
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
		if(i>0 && m_SuppCard.SuppProc == SUP_RIGID)	// Once Only for Rigid
			continue;
		/////////////////////////// No Support
		if(m_SuppCard.kode[i] == 0)
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

void CDrLinSup::GoDoIt(CDC* PtrDC, int direction)
{ 

	//////////////////////////////////
	switch(m_SuppCard.SuppProc)
	{
		////////////////////////////////////////////// Rigid
		case SUP_RIGID:

			GoConnect_RIGID(PtrDC,direction);
			///////////////
			return;
				
		////////////////////////////////////////////// Linear Springs
		case SUP_LINSPR:

			if(direction<3)		// Translation
			{
				GoConnect_SprT(PtrDC,direction);
				//////////////
				return;
			}
			else
			if(direction>=3)		// Rotation
			{
				GoConnect_SprR(PtrDC,direction);
				//////////////
				return;
			}
			/////////
			break;

		///////////////////////////////////////////// Linear Snubbers
		case SUP_LINSNU:

			if(direction<3)		// Translation
			{
				GoConnect_SnuT(PtrDC,direction);
				//////////////
				return;
			}
			else
			if(direction>=3)		// Rotation
			{
				GoConnect_SnuR(PtrDC,direction);
				//////////////
				return;
			}
			/////////
			break;

		default:
			break;
		//////////////////////
		
	}
	/////////
	return;

}   

void CDrLinSup::GoConnect_RIGID(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];	//direction should be = 0
	///////////////////////////////////////////////////////////////////// Connect
	DrawLine3D(PtrDC,pOut+0,pOut+1,TRUE);	 
	DrawLine3D(PtrDC,pOut+1,pOut+3,TRUE);	 
	DrawLine3D(PtrDC,pOut+0,pOut+4,TRUE);	 
	DrawLine3D(PtrDC,pOut+0,pOut+2,TRUE);	 
	DrawLine3D(PtrDC,pOut+2,pOut+5,TRUE);
	///////////////////////////////////////// Free Memory
   	
} 

void CDrLinSup::GoConnect_SprT(CDC* PtrDC, int direction)
{ 

	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<=2;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	DrawLine3D(PtrDC,pOut+1,pOut+3,TRUE);	 
	DrawLine3D(PtrDC,pOut+1,pOut+5,TRUE);	 
	DrawLine3D(PtrDC,pOut+2,pOut+4,TRUE);	 
	DrawLine3D(PtrDC,pOut+3,pOut+6,TRUE);	 
	//////////   	
} 

void CDrLinSup::GoConnect_SprR(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<=8;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	DrawLine3D(PtrDC,pOut+7,pOut+9,TRUE);  
	DrawLine3D(PtrDC,pOut+7,pOut+11,TRUE);  
	DrawLine3D(PtrDC,pOut+8,pOut+10,TRUE);   
	DrawLine3D(PtrDC,pOut+9,pOut+12,TRUE);  
	////////// 
   	
} 

void CDrLinSup::GoConnect_SnuT(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<=6;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	DrawLine3D(PtrDC,pOut+6,pOut+1,TRUE);  
	DrawLine3D(PtrDC,pOut+4,pOut+7,TRUE);  
	DrawLine3D(PtrDC,pOut+7,pOut+11,TRUE);   
	DrawLine3D(PtrDC,pOut+8,pOut+10,TRUE);  
	DrawLine3D(PtrDC,pOut+9,pOut+12,TRUE);  
	DrawLine3D(PtrDC,pOut+9,pOut+7,TRUE);  
	DrawLine3D(PtrDC,pOut+7,pOut+8,TRUE);  
	//////////
   	
} 

void CDrLinSup::GoConnect_SnuR(CDC* PtrDC, int direction)
{ 
	pWORLD pOut = m_pEye[direction];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<=12;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	DrawLine3D(PtrDC,pOut+12,pOut+7,TRUE);  
	DrawLine3D(PtrDC,pOut+10,pOut+13,TRUE);  
	DrawLine3D(PtrDC,pOut+13,pOut+17,TRUE);   
	DrawLine3D(PtrDC,pOut+14,pOut+16,TRUE);  
	DrawLine3D(PtrDC,pOut+15,pOut+18,TRUE);  
	DrawLine3D(PtrDC,pOut+13,pOut+14,TRUE);  
	DrawLine3D(PtrDC,pOut+13,pOut+15,TRUE);  
	//////////
   	
} 
//////////////////////////////////////////////////////////////////
BOOL CDrLinSup::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrLinSup* pSupp = (CDrLinSup*)(pObject);
	///////////////////////////////////////////// SupID
	CString SupID = (pSupp->GetSuppCard())->sup_id;
	//////////////////////////////////////////////	 
	switch(KeyNo)
	{ 
	  case 1:         // PipeID = Nid_I + Nid_J  

		if((pSupp->GetSuppCard())->sup_id ==KeyID)
			return TRUE;
		break;  

	  case 2:         
		break;

	  default:
	  		return FALSE;					
	}
	return FALSE;
}

void CDrLinSup::Serialize(CArchive& ar)
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
	
BOOL CDrLinSup::IsObjectHit(int nNet,POINT point)
{
	/////////////// TODO
	return FALSE;
	///////////////
}
////////////////////// END OF MODULE ///////////////////////

