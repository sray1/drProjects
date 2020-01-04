// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"

#include "drgraf.h"
#include "drgradoc.h"
/////////////////////
#include "ObjMgr.h"
#include "dbObject.h"
///////////////////// SpecObjs
#include "spdefine.h"
#include "Layer.h"
////////////////////
#include "Dlg_Layr.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////
void CDrawLayer::OnDrawLayer()
{
	// TODO: Add your command handler code here
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)(((CDrGrafApp*)AfxGetApp())->m_pDoc ); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CLayer* pLayer	 		= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	/////////////////////////////////////		 
	CDrawLayer	dlg;
// save  old 
	UINT nLayer[MAX_LAYER][2];
	
	pLayer->GetLayerArray(nLayer);
	pLayer->SetLayerOldArray(nLayer);
	
	pLayer->SetCurrentLayerOld(pLayer->GetCurrentLayer() );
	///////////////////////////////////////////////////////		
	// call dialogbox
	if(dlg.DoModal() == IDOK)
	{
	 // Do Nothing here. All Done Thro' DlgLayer  
	}
	else
	{
		// restore data
		pLayer->GetLayerOldArray(nLayer);
		pLayer->SetLayerArray(nLayer);
	
		pLayer->SetCurrentLayer(pLayer->GetCurrentLayerOld() );
		
	}
	
} 
/////////////////// end of module ////////////////////////////
