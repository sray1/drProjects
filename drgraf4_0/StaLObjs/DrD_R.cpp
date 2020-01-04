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
///////////////////// Static Loads
#include "Def_StaL.h"
#include "Ext_StaL.h"
#include "DrD_R.h"
///////////////////////////// FORCE
#define	LENGTH	.3	
#define	WIDTH	.15	
#define	TICK	WIDTH/4	
///////////////////////////// MOMENT
#define	LEN1	7	
#define	BOXSIZE	LEN1	
#define	LEN2	LEN1	
//////////////////
#define	MAX_FORCE_PT	8
#define	MAX_MOMENT_PT	14
#define MAX_PT			14  // max(MAX_FORCE_PT,MAX_MOMENT_PT etc..)
//////////////////////////////////////////////////////////////////////////// static
static WORLD 	m_ForceDat[MAX_FORCE_PT]=
{
	{0.0,			.1*WIDTH,	0.0},{.7*LENGTH,	.1*WIDTH,	0.0},		 
    {.7*LENGTH,		.2*WIDTH,	0.0},{LENGTH,		0.0,		0.0},		 
    {.7*LENGTH,		-.2*WIDTH,	0.0},{.7*LENGTH,	-.1*WIDTH,	0.0},		 
    {0.0,			-.1*WIDTH,	0.0},
	{-.2*LENGTH,	0.0,		0.0}									// for Value(Text)
	///////////////
};
////////////////
static WORLD 	m_MomentDat[MAX_MOMENT_PT]=
{
	{0.0,			.1*WIDTH,	0.0},{.3*LENGTH,	.1*WIDTH,	0.0},		 
    {.3*LENGTH,		.2*WIDTH,	0.0},{.5*LENGTH,	.1*WIDTH,	0.0},		 
    {.7*LENGTH,		.1*WIDTH,	0.0},{.7*LENGTH,	.2*WIDTH,	0.0},		 
    {LENGTH,		0.0,		0.0},
	{.7*LENGTH,		-.2*WIDTH,	0.0},{.7*LENGTH,	-.1*WIDTH,	0.0},	
	{.5*LENGTH,		-.1*WIDTH,	0.0},{.3*LENGTH,	-.2*WIDTH,	0.0},
	{.3*LENGTH,		-.1*WIDTH,	0.0},{0.0,			-.1*WIDTH,	0.0},
	{-.2*LENGTH,	0.0,		0.0}									// for Value(Text)
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
// CDrD_R
IMPLEMENT_SERIAL(CDrD_R, CDrObject,1)
/*
BEGIN_MESSAGE_MAP(CDrD_R, CDrObject)
	//{{AFX_MSG_MAP(CDrD_R)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/  
/////////////////////////////////////////////////////////////////////////////
CDrD_R::CDrD_R()
{
	int i;
	/////////////
	m_bDoneXform	= FALSE;
	m_bDoneProject	= FALSE;
	//////////////////////////////
	for(i=0;i<2;i++)
	{
		m_pLoc[i]	= new WORLD[MAX_PT];
		m_pEye[i]	= new WORLD[MAX_PT];
		m_nPts[i]	= 0;
	}
	//////////////////////////////
    SetObjectType((int)FORCE);
    SetElemType((int)STAL_OBJECT);          //
    //////////////////////////////  
	m_LoadID  = "";
	///////////////////////////
	m_kode[0] = 0;
	m_kode[1] = 0;
	///////////////////////////
	m_dMin.x = DBL_MAX; 
	m_dMin.y = DBL_MAX; 
	m_dMin.z = DBL_MAX;
	 
	m_dMax.x = -DBL_MIN; 
	m_dMax.y = -DBL_MIN; 
	m_dMax.z = -DBL_MIN;
	//////////////////////////////
    m_rectBounding.SetRectEmpty();
	//////////////
}

CDrD_R::~CDrD_R()
{
	int i;
	///////////////////////////
	for(i=0;i<2;i++)
	{
		delete [] m_pLoc[i];
		delete [] m_pEye[i];
	}
	/////////////////////////// empty all the lists
	ReadyToDelete();
	///////////////////////////
}	

void CDrD_R::InitRawData()
{
	///////////////////////////////////////////////////////////////// PreProcess
	for(int i=0;i<2;i++)		// Over 2 Directions
	{
		/////////////////////////////////
		m_nPts[i] = GetApproDataLen(i);
		GetApproPts(m_pLoc[i],m_nPts[i],i);
		////////////////////////////////////////////////////
	}	 
} 

void CDrD_R::ReadyToDelete()
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
			CDListMgr* pStaLList = pObject->GetSuppList();
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
		pObject->ReadyToDelete();
	}	
	while(!(GetPatchList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetPatchList()->RemoveHead());
		pObject->ReadyToDelete();
	}	
	while(!(GetSolidList()->IsEmpty()))// unload/no delete:public
	{
		pObject = (CDrObject*)(GetSolidList()->RemoveHead());
		pObject->ReadyToDelete();
	}
	//////////////////////////////////////////////////////////////
}

int CDrD_R::DealObjectDialog()
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
	
void CDrD_R::SetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::SetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrD_R* pAdd = (CDrD_R*) pObject;
	///////////////////////////////////////////////////// SuppINFO
	m_NodeList.AddTail(pAdd->GetNodeList() ); 
	////////////////////////////////////////////////////
	m_IDNum			= pAdd->m_IDNum;                  
	m_LoadID		= pAdd->m_LoadID;
	///////////////////////////
	for(int i=0;i<2;i++)
		m_kode[i] =  pAdd->m_kode[i];
	////////////////////////////////////////////////////
	m_nCardNo				= pAdd->m_nCardNo;
	////////////////////
	return;
}		

void CDrD_R::GetObjectInfo(CDrObject* pObject)
{
	
	CDrObject::GetObjectInfo(pObject);	
	////////////////////////////////////////////////////////   
	CDrD_R* pAdd = (CDrD_R*) pObject;
	///////////////////////////////////////////////////// FE1DINFO
	pAdd->m_NodeList.AddTail(GetNodeList() ); 
	////////////////////////////////////////////////////////   
	pAdd->m_IDNum	= m_IDNum;
	pAdd->m_LoadID	= m_LoadID;
	///////////////////////////
	for(int i=0;i<2;i++)
		pAdd->m_kode[i] =  m_kode[i];
	///////////////////////////
	pAdd->m_nCardNo					= m_nCardNo;
	////////////////////
	return;
}		

void CDrD_R::DoDataView(CDC* PtrDC, int y)
{

	CString strCard;
	//////////////////////
	Pack_drPipe(&strCard);
	//////////////////////////// 
	PtrDC->TextOut(0,y,strCard);
	////////////////////////////
	return;
} 

void CDrD_R::Pack_drPipe(CString* pstrCard)
{

   	static CString name;
   	/////////////////////////
   	for (int i = 0;i<nMax_StaLTypes;i++)
   		if(StaLTypes[i].num == FORCE) 
   		{
   			name = StaLTypes[i].ObjName;
   			break;
   		}	
   /////////////////////////
   CString pad = " "; 
   ////////////////////////
	return;

} 
  
int CDrD_R::Calc_3DBoundsLocal(pWORLD pOut, int nPts)
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
void CDrD_R::TransformObjectToWorld(pMATRIX pLM,BOOL bYes)
{
	////////////////////////
	TransformToWorldPos(pLM,bYes);
	//////////////////
}
	
void CDrD_R::TransformObjectToView(pMATRIX pViewM)
{

	//////////////////////
	TransformToEyePos(pViewM);
	//////////////////////
}
	
void CDrD_R::TransformObjectToViewDirect
				(pMATRIX pLM,pMATRIX pViewM,pMATRIX pComposedM,BOOL bYes)
{
	/////////////////////////////
	TransformToEyePosDirect
				(pLM,pViewM,pComposedM,bYes);
	/////////////////////////////
}

BOOL CDrD_R::RemoveHiddenObject(pMATRIX pViewM,WORLD VDir,int nType)
{
		return FALSE;	// do nothing
}			 
				
void CDrD_R::ProjectObject
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

int CDrD_R::GetApproDataLen(int direction)
{

	switch(direction)
	{
		case 0:return MAX_FORCE_PT;
		case 1:return MAX_MOMENT_PT;

		default:
			break;
		//////////////////////
	}
	/////////
	return 0;
}

void CDrD_R::GetApproPts(WORLD pOut[],int nPts,int direction)
{
	int i;
	////////////
	switch(direction)
	{
		case 0:							// FORCE
			for(i=0;i<nPts;i++)
			{
				pOut[i].x = m_ForceDat[i].x;
				pOut[i].y = m_ForceDat[i].y;
				pOut[i].z = m_ForceDat[i].z;
			}
			return;

		case 1:							// MOMENT
			for(i=0;i<nPts;i++)
			{
				pOut[i].x = m_MomentDat[i].x;
				pOut[i].y = m_MomentDat[i].y;
				pOut[i].z = m_MomentDat[i].z;
			}
			return;


		default:
			break;
		//////////////////////
	}
	/////////
	return;
}


void CDrD_R::TransformToWorldPos(pMATRIX pLM,BOOL bYes)
{
	AfxMessageBox("CDrD_R::TransformToWorldPos\nSHOULD NOT BE CALLED");
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

void CDrD_R::TransformToEyePos(pMATRIX pViewM)
{
	AfxMessageBox("CDrD_R::TransformToEyePos\nSHOULD NOT BE CALLED");
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

void CDrD_R::TransformToEyePosDirect
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

void CDrD_R::ProjectToScreenPos
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

void CDrD_R::Calc_ScreenRectFromCNodes()
{
	/////////////////////
	Rearrange2DCorners();
	FinishObject();
	///////////////
}

void CDrD_R::Rearrange2DCorners()
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
	
void CDrD_R::FinishObject()
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
void CDrD_R::InitDraw(CDC* PtrDC,BOOL bParallel,int nView,
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
	for(i=0;i<2;i++)		// Over 2 Directions
	{
		if(m_kode[i] == 0)
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
	for(i=0;i<2;i++)		// Over All Directions
	{
		if(m_kode[i] == 0)
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
void CDrD_R::DoDrawView(CDC* PtrDC,BOOL bPenChange)
{

   	CPen    Pen;
   	CPen*   PtrOldPen;                        
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen
	if(bPenChange)
	{
   		Pen.CreatePen (m_nPenStyle,m_nPenWidthHi,m_crPenColor);
		///////////////
	}
	else
	{
   		Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);
		////////////////
	}
	//////////////////////////////////////
  	PtrOldPen = PtrDC->SelectObject(&Pen);
	///////////////////////////////////////////////////////////////// Doit
	for(int i=0;i<2;i++)		// Over 2 Directions
	{
		/////////////////////////// No Force or Moment
		if(m_kode[i] == 0)
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

void CDrD_R::GoDoIt(CDC* PtrDC, int direction)
{ 

	//////////////////////////////////
	if(direction == 0)		// Force
		GoConnect_Force(PtrDC);
	else
	if(direction==1)		// Moment
		GoConnect_Moment(PtrDC);
	//////////////
	return;

}   

void CDrD_R::GoConnect_Force(CDC* PtrDC)
{ 

	pWORLD pOut = m_pEye[0];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<MAX_FORCE_PT-1;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	///////////////////////////////////// close it
	DrawLine3D(PtrDC,pOut+MAX_FORCE_PT-2,pOut,TRUE);	 
	///////////////////////////////////// Value Text Out LastPt 
//////////////////////////////////////////////////////////////////////////
//				TODO:	SHOULD BE DONE BY DRLABEL						// 
//		WE WILL STORE LASTPT COORDS AND VALUE IN DRLABEL				//
//				AT CREATION TIME.i.e., MI_F_M.cpp						//
//////////////////////////////////////////////////////////////////////////	
	WORLD EyePos, Scr3DPos;
	POINT pt;
	CXForm XForm(m_bParallel);
	/////////
	EyePos = *(pOut+MAX_FORCE_PT-1);
	//////////////
	XForm.Project(&m_vv3DM,&EyePos, &Scr3DPos);
	//////////////////////////////////////////////////////
	// 	3DScreenPos belongs to [0,-1] because of CVV	//
	//	So before we Change into Integer Logical		//
	//	Coordinates, we Must Use Screen Client Data		//
	//////////////////////////////////////////////////////
	pt.x = (int)(Scr3DPos.x * m_dScale_U);
	pt.y = (int)(Scr3DPos.y * m_dScale_V);
	////////////////////////////////////////////////////// Value
	C3DMath Math3D;
	double dVal = Math3D.Len3DPts(&m_Moment);
    ////////////////////////////////////////////////////// Label Out
	CString text;
	char* pBuf = text.GetBuffer(20);
	sprintf(pBuf,"%d",dVal);
 	PtrDC->TextOut(pt.x,pt.y,text);
	text.ReleaseBuffer();
	////////////
  	
} 

void CDrD_R::GoConnect_Moment(CDC* PtrDC)
{ 
	pWORLD pOut = m_pEye[1];
	///////////////////////////////////////// Connect
	int i,iOld = 0;
	/////////////
	for(i=1;i<MAX_MOMENT_PT-1;i++)
	{
		DrawLine3D(PtrDC,pOut+iOld,pOut+i,TRUE);  //TRUE = XFormed; FALSE= NOT XFormed
		iOld = i;
	}
	///////////////////////////////////// close it
	DrawLine3D(PtrDC,pOut+MAX_MOMENT_PT-2,pOut,TRUE);	 
	///////////////////////////////////// Value Text Out LastPt
//////////////////////////////////////////////////////////////////////////
//				TODO:	SHOULD BE DONE BY DRLABEL						// 
//		WE WILL STORE LASTPT COORDS AND VALUE IN DRLABEL				//
//				AT CREATION TIME.i.e., MI_F_M.cpp						//
//////////////////////////////////////////////////////////////////////////	
   	WORLD EyePos, Scr3DPos;
	POINT pt;
	CXForm XForm(m_bParallel);
	/////////
	EyePos = *(pOut+MAX_MOMENT_PT-1);
	//////////////
	XForm.Project(&m_vv3DM,&EyePos, &Scr3DPos);
	//////////////////////////////////////////////////////
	// 	3DScreenPos belongs to [0,-1] because of CVV	//
	//	So before we Change into Integer Logical		//
	//	Coordinates, we Must Use Screen Client Data		//
	//////////////////////////////////////////////////////
	pt.x = (int)(Scr3DPos.x * m_dScale_U);
	pt.y = (int)(Scr3DPos.y * m_dScale_V);
	////////////////////////////////////////////////////// Value
	C3DMath Math3D;
	double dVal = Math3D.Len3DPts(&m_Moment);
    ////////////////////////////////////////////////////// Label Out
	CString text;
	char* pBuf = text.GetBuffer(20);
	sprintf(pBuf,"%d",dVal);
 	PtrDC->TextOut(pt.x,pt.y,text);
	text.ReleaseBuffer();
	////////////
  	
} 

//////////////////////////////////////////////////////////////////
BOOL CDrD_R::IsKeyMatch(CDrObject* pObject, CString KeyID,UINT KeyNo)
{

				
	CDrD_R* pStaL = (CDrD_R*)(pObject);
	///////////////////////////////////////////// SupID
	CString LoadID = pStaL->m_LoadID;
	//////////////////////////////////////////////	 
	switch(KeyNo)
	{ 
	  case 1:         // PipeID = Nid_I + Nid_J  

		if(pStaL->m_LoadID ==KeyID)
			return TRUE;
		break;  

	  case 2:         
		break;

	  default:
	  		return FALSE;					
	}
	return FALSE;
}

void CDrD_R::Serialize(CArchive& ar)
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
	
BOOL CDrD_R::IsObjectHit(int nNet,POINT point)
{
	/////////////// TODO
	return FALSE;
	///////////////
}
////////////////////// END OF MODULE ///////////////////////

