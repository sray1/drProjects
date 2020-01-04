// Mouse.cpp : implementation file
//


#include "stdafx.h" 
#include <float.h>		// DBL_MIN 

#include "Def_Type.h"
#include "Def_Objs.h"
///////////////////// DrawOperationObjs
#include "3DMath.h"
#include "XForm.h"

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "HitNet.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "MMs1Mgr.h"  
///////////////////// elements
#include "Def_Elem.h"
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrMesh1D.h"
#include "DrProf_1.h"
#include "MatObj.h"
/////////////////////
#include "MI_1Spn.h" 

#include "MI_1Prof.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	NUM_LEN	12
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_DYNAMIC(CMI_1Prof,CDrObject)
/////////////////////////////////////
#define new	DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
CMI_1Prof::CMI_1Prof()
{
}

CMI_1Prof::~CMI_1Prof()
{
}	
 
int CMI_1Prof::RBUp_1Profile(CDrProf_1* pProfile) // NOT Using Dlg (Used for Now)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(MESH1D);
	//////////////////////////////////////////////////////////////////
	CString		ID;
	CString*	pID = &ID;
	////////////////////////////////////////////////////////////////
	m_pDrProf	= pProfile;                  	// 
	///////////////////////////////////////////////////////////////////// Go Generate
	////////////////////////////////////////////////////////// Save
	int nResult = InsertProfileInfo();
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1Prof::RBUp_1Profile\nInsertProfileInfo");
		return -1;
	}
	/////////
	return 0;		 
}
int CMI_1Prof::InsertProfileInfo()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
//	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CMsObjMgr* pMsObjMgr	= pDoc->GetMsObjMgr();
	///////////////////////////////////////////////////////// Create a Mesh1D
  	int nActiveIndex;
    m_pDrMesh1D 	= (CDrMesh1D*)(pMsObjMgr->AddToDataBase(nActiveIndex,MESH1D));
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrMesh1D which IS NOT  YET Massaged
	/////////////////////////////////////////////////////////
	m_pDrMesh1D->SetShow(FALSE);
	////////////////////////////////
	m_pDrProf->SetMesh1D(m_pDrMesh1D);          			// addto Profile 
	///////////////////////////////////////////////////////// New Mesh1D Info
	int nResult = Generate_Mesh1DDataInfo();
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1Prof::InsertProfileInfo()\nGenerate_Mesh1DDataInfo");
		return -1;
	}
	////////////////////////////////////// LOCAL 3DBounds
	m_pDrProf->Calc_3DBoundsLocal();
	////////////////
	return 0;
}	

int CMI_1Prof::Generate_Mesh1DDataInfo()
{
	int nResult;
	/////////////////////////////
	CMI_Gang0 Gang0;
	Gang0.SetElemInfoID(m_Mesh1DID,MESH1D);		
	////////////////////////////////////////
	nResult = MergeMesh1Ds();
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1Prof::Generate_Mesh1DDataInfo()\nMergeMesh1Ds!");
		return -1;
	}
	////////////////////
	return 0;
}
	
int CMI_1Prof::MergeMesh1Ds()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////// 
	CDListMgr*	pMesh1DList		= m_pDrProf->GetMesh1DList();	// Mesh1Ds making up Profile
 	CDListMgr*	pFE0DListNew	= m_pDrMesh1D->GetFE0DList();	// New Mesh1D in Profile
	/////////////////////////////////////////////////////////
	CDrMesh1D*	pMesh_P = NULL;	// Primary
	CDrMesh1D*	pMesh_S = NULL;	// Secondary
	CDrMesh1D*	pMesh_T = NULL;	// Temporary
	///
	int i=0,j,nResult,nMesh1Ds,indexMesh1D=-1;
	//////////////////////////////////////////////////////////// Total Meshes
	nMesh1Ds = pMesh1DList->GetCount();
	if(nMesh1Ds <= 0)
	{
		AfxMessageBox("Internal Problem:\nCMI_1Prof::MergeMesh1Ds()\nnMesh1Ds <= 0");
		return -1;
	}
	////////////////////////////////////////////////////// Loop
	for (i = 0; i<nMesh1Ds-1;i++)
	{
		POSITION posP = pMesh1DList->FindIndex(i);
		pMesh_P = (CDrMesh1D*)pMesh1DList->GetAt(posP);	// Current Primary
		if(!pMesh_P)
		{
			AfxMessageBox("Internal Problem:\nCMI_1Prof::MergeMesh1Ds()\npMesh_P = NULL");
			return -1;
		}
		/////////////////////////////////// Ist One Store Immediately
		if(i == 0)
		{
			pMesh_T = new CDrMesh1D;  // Temporary
			//////////////////////////////////////
			Copy_Mesh1D(pMesh_P, pMesh_T);
			AppendLists_Mesh1D(pMesh_T, m_pDrMesh1D);
			//////
			if(pMesh_T)
			{
				delete pMesh_T;
				pMesh_T = NULL;
			}
		}
   	 	///////////////////////////////////////////// 
		for (j = i+1; j<nMesh1Ds;j++)
		{
			POSITION posS = pMesh1DList->FindIndex(i);
			pMesh_S = (CDrMesh1D*)pMesh1DList->GetAt(posS);	// Current Secondary
			if(!pMesh_S)
			{
				AfxMessageBox("Internal Problem:\nCMI_1Prof::MergeMesh1Ds()\npMesh_S = NULL");
				return -1;
			}
			//////////////////////////////////////
			pMesh_T = new CDrMesh1D;  // Temporary
			////////////////////////////////////// Copy Secondary to Temporary
			Copy_Mesh1D(pMesh_S, pMesh_T);
			////////////////////////////////////// ComPare Secondary w/ Primary and Change Temporary
			nResult = Compare_N_Change_Mesh1D(pMesh_P,pMesh_S,pMesh_T);
			if(nResult<0)
			{
				AfxMessageBox("Internal ERROR:\nCMI_1Prof::MergeMesh1Ds\nCompare_N_Change_Mesh1D!");
				return -1;
			}
			//////////////////////////////// Append
			AppendLists_Mesh1D(pMesh_T, m_pDrMesh1D);
			//////
			if(pMesh_T)
			{
				delete pMesh_T;
				pMesh_T = NULL;
			}
			////
		}
	
	}
   	//////////////////////
	return 0; 
}

int CMI_1Prof::Copy_Mesh1D(CDrMesh1D* pCopyFrom, CDrMesh1D* pCopyTo)
{
	// This Routine is FLAWED and NEEDS TO BE CHANGED 082898
	/////////////////////////////////////////////////
/*
	/////////////////////////////////////////////////////////////// Using CMI_1SPN
	CMI_1SPN MI_1SPN;
// ?????????	MI_1SPN.SetCopy(TRUE);	// Copy Only/No Xform
	//////////////////////
	int nResult;
	MATRIX Mat;
	C3DMath Math3D;
	Math3D.GetIdentityMATRIX(&Mat);
	////////////////////////////////
	CString	SpawnID	= "Temp";
	////
	nResult = MI_1SPN.SpawnMESH1DWithoutDlg(pCopyTo,pCopyFrom,&Mat,&SpawnID,
												pCopyFrom,MESH1D); 
	///
*/
	int nResult = -1; // 082898
	/////////////
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1Prof::Copy_Mesh1D\nMI_1SPN.SpawnMESH1DWithoutDlg!");
		return -1;
	}

	////////////////
	return 0;
}

int CMI_1Prof::AppendLists_Mesh1D(CDrMesh1D* pNew, CDrMesh1D* pAppTo)
{	
	////////////////////
	if(!(pNew->GetFE0DList()->IsEmpty()) )
		pAppTo->GetFE0DList()->AddTail(pNew->GetFE0DList());
	if(!(pNew->GetFE1DList()->IsEmpty()) )
		pAppTo->GetFE1DList()->AddTail(pNew->GetFE1DList());
/*
	if(!(pNew->GetFE2DList()->IsEmpty()) )
		pAppTo->GetFE2DList()->AddTail(pNew->GetFE2DList);
	if(!(pNew->GetFE3DList()->IsEmpty()) )
		pAppTo->GetFE3DList()->AddTail(pNew->GetFE3DList);
	if(!(pNew->GetFE3DList()->IsEmpty()) )
		pAppTo->GetFE3DList()->AddTail(pNew->GetFE3DList);
	if(!(pNew->GetMBJ3DList()->IsEmpty()) )
		pAppTo->GetMBJ3DList()->AddTail(pNew->GetMBJ3DList);
*/
	///
	if(!(pNew->GetNodeList()->IsEmpty()) )
		pAppTo->GetNodeList()->AddTail(pNew->GetNodeList());		// EdgeNode / CNodes etc
	if(pNew->GetLabelList() && !(pNew->GetLabelList()->IsEmpty()) )
		pAppTo->GetLabelList()->AddTail(pNew->GetLabelList());
	///////////////
	return 0;	
}

int CMI_1Prof::Compare_N_Change_Mesh1D(CDrMesh1D* pMesh_P,CDrMesh1D* pMesh_S,CDrMesh1D* pMesh_T)
{
	C3DMath Math3D;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	int			i,j,nResult,n_P,n_S;
	POSITION	pos_P,pos_S;
	////////////////////
	CDListMgr*	pFE0DList_P = pMesh_P->GetFE0DList();
	CDListMgr*	pFE0DList_S = pMesh_S->GetFE0DList();
	CDListMgr*	pFE0DList_T = pMesh_T->GetFE0DList();
	//////
	pFE0DList_T->RemoveAll();
	/////////////////////////////////////////////////////////// FE0D/MNode
	n_P = pFE0DList_P->GetCount(); 
	n_S = pFE0DList_S->GetCount(); 
	if((n_P <=0) || (n_S <=0) )
	{
		AfxMessageBox("Internal Problem:\nCMI_1Prof::Compare_N_Change_Mesh1D\nn_P<=0 OR n_S<=0");
		return -1;
	}
	for(i=0;i<n_P;i++)
	{
		pos_P				= pFE0DList_P->FindIndex(i);
		CDrFE0D* pFE0D_P	= (CDrFE0D*)pFE0DList_P->GetAt(pos_P);
		WORLD LocalPos_P	= *(pFE0D_P->GetLocalPos()); 
		/////////////////
		for(j=0;j<n_S;j++)
		{
			pos_S				= pFE0DList_S->FindIndex(j);
			CDrFE0D* pFE0D_S	= (CDrFE0D*)pFE0DList_S->GetAt(pos_S);
			WORLD LocalPos_S	= *(pFE0D_S->GetLocalPos());
			////////////////////////////////////////////////////////// Compare
			if(Math3D.AreSame_WORLD(&LocalPos_P,&LocalPos_S,pHitNet->GetDblRatio()))
				pFE0DList_T->InsertObject(pFE0D_P);			// save Primary
			else
				pFE0DList_T->InsertObject(pFE0D_S);			// save Secondary
		}
	}
	/////////////////////////////////////////////////////////// FE1D
	CMI_Gang1 Gang1;
	nResult = Gang1.Regen_MESH1D_Elements((CDrObject*)pMesh_T,(CDrObject*)pMesh_S);
	if(nResult<0)
	{
		AfxMessageBox("Internal ERROR:\nCMI_1Prof::Compare_N_Change_Mesh1D\nFE1DList Regen Problem!");
		return -1;
	}
	////////////
	return 0;
}	
	 		
void CMI_1Prof::ReciprocateMESH1DNodes(CDListMgr* pList)
{
	if(!pList || pList->IsEmpty())
		return;
	///////////////////////////////////
	int s,nMaxNodes;
	nMaxNodes = pList->GetCount();
	/////////////////////////////
	for (s = 0; s<nMaxNodes; s++)
	{
		CDrFE0D* pNewNode	= (CDrFE0D*)(pList->GetObject(s));
		//////////////////////////////////////// Reciprocate
		pNewNode->GetMs1List()->InsertObject(m_pDrMesh1D);
		////////
	}
}
///////////////////////////////////// end of Module //////////////////////		


