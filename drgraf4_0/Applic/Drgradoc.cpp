// drgradoc.cpp : implementation of the CDrGrafDoc class
//

#include "stdafx.h"
#include "resource.h"       // main symbols

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////
#include "cntritem.h"
#include "SrvrItem.h"
///////////////////// SpecObjs
#include "Def_Spec.h" 
#include "SDlgMgr.h"
///////////////////// Mesh
#include "Def_Ms.h"
/////////////////////
#include "drgradoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
///////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc

IMPLEMENT_DYNCREATE(CDrGrafDoc, COleDocument)

BEGIN_MESSAGE_MAP(CDrGrafDoc, COleDocument)
	//{{AFX_MSG_MAP(CDrGrafDoc)
	ON_COMMAND(IDM_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_COMMAND(IDM_SPEC_LAYER, OnSpecLayer)
	ON_COMMAND(IDM_SPEC_OBJ3D, OnSpecObj3d)
	ON_UPDATE_COMMAND_UI(IDM_SPEC_OBJ3D, OnUpdateSpecObj3d)
	ON_COMMAND(IDM_SPEC_PATCH, OnSpecPatch)
	ON_UPDATE_COMMAND_UI(IDM_SPEC_PATCH, OnUpdateSpecPatch)
	ON_UPDATE_COMMAND_UI(IDM_MESH_OFF, OnUpdateMeshOff)
	ON_COMMAND(IDM_MESH_OFF, OnMeshOff)
	ON_COMMAND(IDM_MESH_QUAD, OnMeshQuad)
	ON_UPDATE_COMMAND_UI(IDM_MESH_QUAD, OnUpdateMeshQuad)
	ON_COMMAND(IDM_MESH_LINR, OnMeshLinr)
	ON_UPDATE_COMMAND_UI(IDM_MESH_LINR, OnUpdateMeshLinr)
	ON_COMMAND(IDM_MESH_HERM, OnMeshHerm)
	ON_UPDATE_COMMAND_UI(IDM_MESH_HERM, OnUpdateMeshHerm)
	ON_COMMAND(IDM_MESH_BSPL, OnMeshBspl)
	ON_UPDATE_COMMAND_UI(IDM_MESH_BSPL, OnUpdateMeshBspl)
	ON_COMMAND(IDM_MESH_BEZI, OnMeshBezi)
	ON_UPDATE_COMMAND_UI(IDM_MESH_BEZI, OnUpdateMeshBezi)
	ON_COMMAND(ID_VIEW_DATABASE_SHEETFORM, OnViewDatabaseSheetform)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DATABASE_SHEETFORM, OnUpdateViewDatabaseSheetform)
	ON_COMMAND(IDM_SPEC_DOUBLERATIO, OnSpecDoubleratio)
	ON_COMMAND(IDM_SPEC_COLINEAR, OnSpecColinear)
	ON_COMMAND(IDM_SPEC_COPLANAR, OnSpecCoplanar)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleServerDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrGrafDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CDrGrafDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDrGraf to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0FDA4262-5F9D-11CF-9A11-88537EDAE885}
static const IID IID_IDrGraf =
{ 0xfda4262, 0x5f9d, 0x11cf, { 0x9a, 0x11, 0x88, 0x53, 0x7e, 0xda, 0xe8, 0x85 } };

BEGIN_INTERFACE_MAP(CDrGrafDoc, COleServerDoc)
	INTERFACE_PART(CDrGrafDoc, IID_IDrGraf, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc construction/destruction
//////////////////////////////////////////////////////////////////////////////////////
CDrGrafDoc::CDrGrafDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CDrGrafDoc::~CDrGrafDoc()
{
	AfxOleUnlockApp();
//	m_bVisibleLock = FALSE;		// Otherwise giving ERROR ( FOR NOW)    DOESNOT WORK!!!
	////////////////////////////////////////////////////////// 
/*																DONE in OBJECTMGR	
	CObjectMgr* pObjectMgr = GetObjectMgr();
	//////////////////////////////////////
	for(int iList=0;iList<MAX_LIST_ARRAY;iList++)
	{
		CDListMgr* pList = pObjectMgr->GetObjectListFromIndex(iList);	// 
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		///////////////////////////////////////////////////////////
		while(!pList->IsEmpty())
			delete pList->RemoveHead(); 	// Non-Viewable Specials
	}
*/
}

BOOL CDrGrafDoc::OnNewDocument()
{
	///////////////////////
	if (!COleServerDoc::OnNewDocument())
		return FALSE;
    /////////////////////////////////// Init All Data 
    SetModifiedFlag(FALSE); // clean start
    Init();
    /////////////////////////////////// ReadDefaults
    ReadDefaults();
    ///////////////
	// (SDI documents will reuse this document)

	return TRUE;
}

BOOL CDrGrafDoc::OnOpenDocument(const char* pszPathName)
{
	if (!CDocument::OnOpenDocument(pszPathName))
		return FALSE;
	//////////////////////////////////////////// Initialize All Data
	Init();	
	//////////////////// Set NewFile marker
//	SetNewDocFile(FALSE);
	// (SDI documents will reuse this document)
//	InitDocument();
	//////////////////////////////////////////// ReadDefaults
	ReadDefaults();   // Just defaults   NO INITIALIZATION when OLD
	//////////////////// 
	return TRUE;
}   

void CDrGrafDoc::OnCloseDocument()
{

	///////////////////////////////// Replace Back to MainFrame Menu  
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	////////////////////////////////////////// SwitchMenu to Init
	pWnd->SwitchMenu(IDR_MAINFRAME); //1 = INIT_MENU/2 = OPEN_MENU 
	////////////////////////////////////////// Hide Boxes
//	pWnd->GetElemBox()->ShowWindow(FALSE);
//	pWnd->GetDrawBox()->ShowWindow(FALSE);								
	////////////////////////////////////////// StatusBoxes       
	pWnd->GetSBarTop()->ShowWindow(SW_HIDE);
	pWnd->RecalcLayout();
	pWnd->GetSBarBot()->ShowWindow(SW_HIDE);
	pWnd->RecalcLayout();
	pWnd->GetStatusBar()->ShowWindow(SW_SHOW);
	pWnd->RecalcLayout();
	////////////////////////////////////////// Base Class
	COleDocument::OnCloseDocument();
	/////////////////////////////
	return;
} 

HMENU CDrGrafDoc::GetDefaultMenu()
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////
	//	Provide OUTPUT MENU for 3d & Addl3dView
	//	Provide INPUT  MENU for 12,23,31Views
	///////////////////////////////////////

	return (HMENU)NULL;
}

void CDrGrafDoc::ReadDefaults()
{

}

void CDrGrafDoc::Init()
{

	////////////////////////////////////////////////////////////// set pointer in DrGraf 
	((CDrGrafApp*)AfxGetApp())->SetDocument(this);
	////////////////////////////////////////////////////////////// Read In Defaults
	ReadDefaults();
    ////////////////////////////////////////////////////////////// Init ObjectMgr
	GetObjectMgr()->Init();
    ////////////////////////////////////////////////////////////// Init MeshObjectMgr
	GetMsObjMgr()->Init();
    ////////////////////////////////////////////////////////////// Init AuxiObjectMgr
	GetAxObjMgr()->Init();
	////////////////////////////////////////////////////////////// Reset GrafFrame
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////
	pWnd->Init();
	/////////////  
	
}
/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc server implementation

COleServerItem* CDrGrafDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CDrGrafSrvrItem* pItem = new CDrGrafSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc diagnostics

#ifdef _DEBUG
void CDrGrafDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CDrGrafDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc commands
void CDrGrafDoc::OnEditClearAll()
{      
	 
	////////////////////////////////////
	CString strDel 	 =	"This will DELETE EVERYTHING!";
	strDel 			+=  "\nEVERYTHING will be zip,nada,caput !!"; 
	strDel			+=	"\nAre You REALLY Sure !!!"; 
	if(AfxMessageBox(strDel,MB_YESNO) == IDNO)
		return;
	//////////////////////////////////////////////////////// GO DELETE EVERYTHING	
	DeleteContents();    
	SetModifiedFlag(FALSE);   	// Document has been Cleaned
							// needed during File Close
	UpdateAllViews(NULL);
	/////////////////////
}

void CDrGrafDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	//////////////////////////////////////////////////////////  
	CObjectMgr* pObjectMgr = GetObjectMgr(); 
	////////////////////////////////////
	pCmdUI->Enable(IsModified());
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafDoc::DeleteContents()
{
	//////////////////////////////////////////////////////////  
	CObjectMgr* pObjectMgr = GetObjectMgr();
	//////////////////////////////////////
	for(int iList=0;iList<MAX_LIST_ARRAY;iList++)
	{
		CDListMgr* pList = pObjectMgr->GetObjectListFromIndex(iList);	// 
		int nCount = pList->GetCount();
		if(nCount<=0)
			continue;
		///////////////////////////////////////////////////////////
		POSITION pos;
		CString pID;
		int dodo;
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			//////////////////
			pID = pObject->GetObjectID();
			if(pID == "zz")
				dodo = 1;
			/////////////////
		}
		///////////////////////////////////////////////////////////
		for (pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrObject* pObject 	= (CDrObject*)pList->GetNextObject(pos);
			///////////////////////////////////////////	
			int nElemType = pObject->GetElemType();
		 	if (nElemType <0) 
		 		continue;  // not viewable 
		  	//////////////////////////////////////////////// Remove
		 	int index = pList->GetObjectIndex(pObject);
		 	/////////////////
		 	pID = pObject->GetObjectID();
		 	if(pID == "zz")
				dodo = 1;
			/////////////////
			if(index>=0)
			pList->DeleteObject(index);
			///////////////			
		}
	}
}
	
void CDrGrafDoc::OnSpecLayer()
{

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(LAYER);
	//////////////////////////////////
	UpdateAllViews(NULL);
	
}

void CDrGrafDoc::OnSpecObj3d()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafDoc::OnUpdateSpecObj3d(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafDoc::OnSpecPatch()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafDoc::OnUpdateSpecPatch(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
//////////////////////////////////////////////////////////////////// c3D
/*
void CDrGrafDoc::SetRendAttr(colorFactor r,colorFactor g,colorFactor b)
{
	int i;

	RA.R				=	r;
	RA.G				=	g;
	RA.B				=	b;
	RA.frameColor.red	=	32767;
	RA.frameColor.green	=	32767;
	RA.frameColor.blue	=	32767;
	RA.lightSource		=	FALSE;
	RA.distanceEffect	=	TRUE;
	RA.ambientEffect	=	TRUE;
	RA.normalVisibility	=	TRUE;
	RA.framed			=	FALSE;
	RA.wireframed		=	FALSE;
	RA.patterned		=	FALSE;
	RA.grayScaled		=	FALSE;
	RA.hazing			=	FALSE;
	RA.texture			=	TX_NONE;
	RA.diffusion		= 	f_0p5;
	RA.specIndex		= 	20;
	RA.specularity		=	f_0p25;
	RA.ambience			=	0;
	RA.absorption		=	0;
	RA.translucence		=	0;
	RA.refraction		=	0;
	RA.transparency		=	0;
	for( i = TXI_MIN; i<=TXI_MAX; i++ ) {
		SetPt3d( &RA.tx[i].txRotations, f_0,f_0,f_0 );
		SetPt3d( &RA.tx[i].txScalars, f_1,f_1,f_1 );
		SetPt3d( &RA.tx[i].txTranslations, f_0,f_0,f_0 );
	}
	RA.tx[TXI_WOOD].txArgument[0] = 0;		// add noise?
	RA.tx[TXI_WOOD].txArgument[1] = f_0p6;	// light grain %
	RA.tx[TXI_WOOD].txArgument[2] = f_0p5;	// dark grain %
	RA.tx[TXI_WOOD].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_ROCK].txArgument[0] = f_16;	// width of band
	RA.tx[TXI_ROCK].txArgument[1] = f_0p6;	// light grain %
	RA.tx[TXI_ROCK].txArgument[2] = f_0p5;	// med grain %
	RA.tx[TXI_ROCK].txArgument[3] = f_0p25; // dark grain %
	RA.tx[TXI_RGB].txArgument[0] = 0;		// add noise?
	RA.tx[TXI_RGB].txArgument[1] = 0;		// N.A.
	RA.tx[TXI_RGB].txArgument[2] = 0;		// N.A.
	RA.tx[TXI_RGB].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_DEPTH].txArgument[0] = 0; 	// add noise?
	RA.tx[TXI_DEPTH].txArgument[1] = f_32;	// modulus
	RA.tx[TXI_DEPTH].txArgument[2] = 0; 	// N.A.
	RA.tx[TXI_DEPTH].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_BUMPS].txArgument[0] = 0; 	// field scalar
	RA.tx[TXI_BUMPS].txArgument[1] = f_0p6; // cos scalar
	RA.tx[TXI_BUMPS].txArgument[2] = f_0p5; // sin scalar
	RA.tx[TXI_BUMPS].txArgument[3] = 0;		// N.A.
	RA.tx[TXI_PICT].txArgument[0] = 0;		// PICT id NULL
	RA.tx[TXI_PICT].txArgument[1] = 0;		// repeating?
	RA.tx[TXI_PICT].txArgument[2] = f_180;	// latitude rng
	RA.tx[TXI_PICT].txArgument[3] = f_360;	// longitude rng 
	
}
*/

void CDrGrafDoc::OnMeshOff()
{
	GetObjectMgr()->SetMeshGenOn(FALSE);	
	GetObjectMgr()->SetMeshType(MESH_NONE);	
}

void CDrGrafDoc::OnUpdateMeshOff(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_NONE);
}


void CDrGrafDoc::OnMeshLinr()
{
	GetObjectMgr()->SetMeshGenOn(TRUE);	
	GetObjectMgr()->SetMeshType(MESH_LINR);	
}

void CDrGrafDoc::OnUpdateMeshLinr(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_LINR);
	
}
void CDrGrafDoc::OnMeshQuad()
{
	GetObjectMgr()->SetMeshGenOn(TRUE);	
	GetObjectMgr()->SetMeshType(MESH_QUAD);	
}

void CDrGrafDoc::OnUpdateMeshQuad(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_QUAD);
}

void CDrGrafDoc::OnMeshHerm()
{
	GetObjectMgr()->SetMeshGenOn(TRUE);	
	GetObjectMgr()->SetMeshType(MESH_HERM);	
}

void CDrGrafDoc::OnUpdateMeshHerm(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_HERM);
}

void CDrGrafDoc::OnMeshBspl()
{
	GetObjectMgr()->SetMeshGenOn(TRUE);	
	GetObjectMgr()->SetMeshType(MESH_BSPL);	
}

void CDrGrafDoc::OnUpdateMeshBspl(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_BSPL);
}

void CDrGrafDoc::OnMeshBezi()
{
	GetObjectMgr()->SetMeshGenOn(TRUE);	
	GetObjectMgr()->SetMeshType(MESH_BEZI);	
}

void CDrGrafDoc::OnUpdateMeshBezi(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((GetObjectMgr()->GetMeshType()) == MESH_BEZI);
}

void CDrGrafDoc::OnViewDatabaseSheetform() 
{
	// TODO: Add your command handler code here
	
}

void CDrGrafDoc::OnUpdateViewDatabaseSheetform(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck();
}

void CDrGrafDoc::OnSpecDoubleratio() 
{
}

void CDrGrafDoc::OnSpecColinear() 
{
}

void CDrGrafDoc::OnSpecCoplanar() 
{
}
/////////////////////////////////////////////////////////////////////////////
// CDrGrafDoc serialization

void CDrGrafDoc::Serialize(CArchive& ar)
{
	/////////////////////////////////   
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////////////////////////////
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
	COleServerDoc::Serialize(ar);
//	CDocument::Serialize(ar);
	//////////////////////////////////////////////			 
	GetObjectMgr()->Serialize(ar);
	////////////////////////////////////////////// Mouse
//	GetMouseMgr()->Serialize(ar);	   
	//////////////////////////////////////////////
}
/////////////////////////////// end of Module /////////////////////
