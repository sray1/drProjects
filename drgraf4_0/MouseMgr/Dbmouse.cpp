// Mouse.cpp : implementation file
//
/*
    ////////////////////////////////////////////////// Add Plate to DrObjectList 
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	/////////////////////////////////////////////
    CNewObjs* pNewObjs;
    CDrPlat* pAddPlat 	= (CDrPlat*)(pNewObjs->NewObject(PLATE));
	///////////////////////////////////////////////
    SetInfoForDataBase(pAddPlat);
   	pDListMgr->InsertObject(pAddPlat);          				// add and set active index 
    ////////////////////////////////////////////////////////////// 
*/
#include "stdafx.h"

#include "drgraf.h"
#include "drgrafrm.h"
/////////////////////// 
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
//#include "globals.h"  
///////////////////// dialogMgr
#include "DDlgMgr.h"
/////////////////////// cursor
#include "curdef.h"
/////////////////////// Specials
#include "Def_Spec.h"
#include "booleans.h"
#include "mapfacto.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
#include "DrFreHnd.h"
#include "DrGrid.h"
//////////////////////  
#include "dbmouse.h"  

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////
IMPLEMENT_SERIAL(CDBMouse,CMouse,1)
/////////////////////////////////////////////////////////////////////////////
CDBMouse::CDBMouse()
{

	m_bDragOn      = FALSE;
	m_bDragging	   = FALSE;
	m_bMoving	   = FALSE;	
	//////////////////////////// Label     
	m_CurrentLabelID    = "";
	//////////////////////////// FreeHand     
	m_nFHNumberCurrent	= 0;
	//////////////////////////// Next  

}
CDBMouse::~CDBMouse()
{
}


void CDBMouse::DBoxLBDown_FREEHAND(CPoint point)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen* pDrPen   		= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	///////////////////////////////////////////// get latest number
	int nCurNum = GetFHNumberCurrent();
	nCurNum++;
	SetFHNumberCurrent(nCurNum);
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrFreeHand* pFreeHand 	= (CDrFreeHand*)(pObjectMgr->AddToDataBase(nActiveIndex,FREEHAND));
	///////////////////////////////////////////////
	pObjectMgr->SetActiveObjectType(FREEHAND);
	pObjectMgr->SetActiveObjectIndex(nActiveIndex);		    // set Active Index									
	//////////////////////////////////////////												    
	int nCurrentIndex = pObjectMgr->GetActiveObjectIndex();
	/////////////////////// set FreeHand Info
	pFreeHand->AddPoint(point); 				// add first point
												// to the new FreeHand 
	pFreeHand->SetFreeHandNum(nCurNum);	
	pFreeHand->SetViewNum(m_nView);	
	pFreeHand->SetLayer(pLayer->GetCurrentLayer());
	pFreeHand->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	//////////////////////////////////////////////// save Index(for mouse move/up later
	SetFHIndexCurrent(nCurrentIndex);
	////////////////////////////////////
	m_ptPrev = point;     // Serves as the MoveTo() anchor point for the
			     		  // LineTo() the next point, as the user drags the
						  // mouse.
	return;

} 

void CDBMouse::DBoxMMove_FREEHAND(CClientDC* pdc,CPoint point)
{                                           

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen* pDrPen   		= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FREEHAND);
    /////////////////////////////////////////////////
	CDrFreeHand* pFreeHandCur;
    ///////////////////////////////////
    int nCurrentIndex = pObjectMgr->GetActiveObjectIndex();
	pFreeHandCur = (CDrFreeHand*)(pDListMgr->GetObject(nCurrentIndex)  );
	//////////////////////////////
	pFreeHandCur->AddPoint(point);
    //////////////////////////////
	// Draw a line from the previous detected point in the mouse
	// drag to the current point.
	CPen* pOldPen;
	//////////////////////////
	pOldPen = pdc->SelectObject(pDrPen->GetCurrentPen());
	////////////////////////
	pdc->MoveTo(m_ptPrev);
	pdc->LineTo(point); 

	pdc->SelectObject(pOldPen);
	////////////////////////
	m_ptPrev = point;     // LOG
	////////////////////////	
	return;         
}	

void CDBMouse::DBoxLBUp_FREEHAND(CPoint point)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	CDrPen* pDrPen   		= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FREEHAND);
	//////////////////////////
	CDrFreeHand*	pFreeHandCur;
    /////////////////////////////////// 
    int nCurrentIndex = pObjectMgr->GetActiveObjectIndex();
	pFreeHandCur = (CDrFreeHand*)(pDListMgr->GetObject(nCurrentIndex)  );
	//////////////////////////////
	pFreeHandCur->AddPoint(point);
    ////////////////////////////////////////////////////////// done/Invalidate
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,nCurrentIndex,FREEHAND);
	///////////////////////////////////////////////////										
   	m_bMoving = FALSE;
	return;
}

void CDBMouse::DBoxLBDown_OBJECTMOVE(CClientDC* pdc,CPoint point)
{

	CDrGrafDoc* pDoc 	   = ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	CMapFactor* pMapFactor = (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
	/////////////////////////////////////////////////////////
    CDC MemDCMove;
    MemDCMove.CreateCompatibleDC (pdc);
	/////////////////////////////////////////////////////////// MapMode
	MemDCMove.SetMapMode(pMapFactor->GetMapModeIndex());
	////////////////////////////////// 
	CRect ObjectRect;
	ObjectRect = m_ObjectRect;
	///////////////////////	                          
	pdc->LPtoDP(&ObjectRect);
	/////////////////////////////////////////////////////////// Set InvalidRect 
	m_InvalidMoveRect= ObjectRect;
    ////////////////////////////
    m_BitmapSave.CreateCompatibleBitmap
    	(&MemDCMove,ObjectRect.Width(), 	 				//width=pixel
    	            ObjectRect.Height());  				//height=pixel
	m_BitmapSource.CreateCompatibleBitmap
    	(&MemDCMove,ObjectRect.Width(), 	 				//width=pixel
    	            ObjectRect.Height());  				//height=pixel
    ////////////////////////////////// Shift & Draw Focus Rect
    CRect FocusRect = ObjectRect;
    FocusRect.InflateRect(1,1);
    pdc->DPtoLP(&FocusRect);
    FocusRect.NormalizeRect();
    pdc->DrawFocusRect(&FocusRect);
    /////////////////////////////// 
    pdc->DPtoLP(&ObjectRect);
    ///////////////////////////////////////////////  		
    MemDCMove.SelectObject (&m_BitmapSave);
    MemDCMove.PatBlt
    	(
    		0,
     		0,
    		ObjectRect.Width(),
    		ObjectRect.Height(),
    		WHITENESS
    	);
	////////////////////////////////////////////////             		
    MemDCMove.SelectObject (&m_BitmapSource);
    MemDCMove.BitBlt
    	(
    		0,
     		0,
     		ObjectRect.Width(),
     		ObjectRect.Height(),
     		pdc,
     		ObjectRect.left,
     		ObjectRect.top,
     		SRCCOPY
     	);
	////////////////////////
	m_PointOld = point;
	////////////////////////	
 	return;
}		
		
void CDBMouse::DBoxMMove_OBJECTMOVE(CClientDC* pdc,CPoint point)
{                                           

	CDrGrafDoc* pDoc 	   = ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr = pDoc->GetObjectMgr();
	CMapFactor* pMapFactor = (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
    /////////////////////////////////////////
    CDC MemDCMove;
    MemDCMove.CreateCompatibleDC (pdc);
	/////////////////////////////////////////////////////////// MapMode
	MemDCMove.SetMapMode(pMapFactor->GetMapModeIndex());
	/////////////////////////////////////////////////////////// 
	CSize  offset;
	CPoint mousePos;
	CRect  oldRect, newRect,tempRect;
	//////////////////////////////////////////////////////// 
	oldRect = m_ObjectRect;
	mousePos = m_PointOld;
	//////////////////////
	pdc->LPtoDP(oldRect);
	pdc->LPtoDP(&mousePos);  
	pdc->LPtoDP(&point);
	///////////////////////////////
	offset = point - mousePos;
	newRect = oldRect + (CPoint(0, 0) + offset);
	//////////////////////////////////////////////
	CRect FocusRect = oldRect;
   	FocusRect.InflateRect(1,1); 
	pdc->DPtoLP(&FocusRect);
    FocusRect.NormalizeRect();
	pdc->DrawFocusRect(&FocusRect);
    /////////////////////////////// 
    pdc->DPtoLP(&oldRect);
	///////////////////////////////
   	MemDCMove.SelectObject (&m_BitmapSave);
    pdc->BitBlt
	    (oldRect.left,
         oldRect.top,
   	     oldRect.Width(),
         oldRect.Height(),
         &MemDCMove,
         0,
         0,
         SRCCOPY);
    //////////////////////////////////////////////////
    FocusRect = newRect;
    FocusRect.InflateRect(1,1); 
	pdc->DPtoLP(&FocusRect);
    FocusRect.NormalizeRect();
   	pdc->DrawFocusRect(&FocusRect);
    /////////////////////////////// 
    pdc->DPtoLP(&newRect);
	///////////////////////////////
    MemDCMove.BitBlt
    	(0,
         0,
   	     newRect.Width(),
       	 newRect.Height(),
         pdc,
         newRect.left,
         newRect.top,
   	     SRCCOPY); 
	////////////////////////////////////////////////   
    MemDCMove.SelectObject (&m_BitmapSource);

    pdc->BitBlt
        (newRect.left,
   	     newRect.top,
       	 newRect.Width(),
         newRect.Height(),
         &MemDCMove,
         0,
         0,
   	     SRCCOPY);
	///////////////////// save 
	pdc->DPtoLP(&point);
	m_PointOld = point;
	m_ObjectRect = newRect;
	////////////////////////////////////////////// invalidate
	pdc->LPtoDP(&oldRect);
	pdc->LPtoDP(&newRect);
	tempRect.UnionRect(m_InvalidMoveRect,newRect);
	m_InvalidMoveRect = tempRect;
	////////////////////////////////////
    return;
}

void CDBMouse::DBoxLBUp_OBJECTMOVE(CClientDC* pdc,CPoint point,CView* pView)
{

	///////////////////////////////////////////// erase last focusRect	
	CRect FocusRect = m_ObjectRect;
	pdc->LPtoDP(&FocusRect);
   	FocusRect.InflateRect(1,1); 
	pdc->DPtoLP(&FocusRect);
    FocusRect.NormalizeRect();
	pdc->DrawFocusRect(&FocusRect);
   	///////////////////////////////////// Delete BitMaps
   	m_BitmapSave.DeleteObject ();
   	m_BitmapSource.DeleteObject();
	/////////////////////////////////////////////
   	m_bMoving = FALSE;
    ////////////////////////////////////////////////////////// done/Invalidate
    CRect tempRect,clientRect;
	pView->GetClientRect(&clientRect);
	tempRect = m_InvalidMoveRect;
	m_InvalidMoveRect.IntersectRect(tempRect,clientRect);
    pView->InvalidateRect(&m_InvalidMoveRect); 
	//////////////////////////
	return;
}

void CDBMouse::OnDBoxLButtonDown(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point)
{ 

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CMouseMgr* pMouseMgr	= pWnd->GetMouseMgr();
	CDListMgr* pDListMgr;
	//////////////////////////////////////////////////////// LOG
	pdc->DPtoLP(&point);
	////////////////////////////////////////////////////////// Text Insert
	int nActiveObject 	= pWnd->GetActiveObjectType();
	int nActiveTool		= pWnd->GetActiveToolType();    // -1= INSERT
	////////////////////////////////////////////////////////////////
	switch(nActiveTool) 
	{
		
		case INSERT:
		
			switch(nActiveObject)                              
			{
				case GRID:										// LABEL_INSERT:
		
					pObjectMgr->SetActiveObjectType(GRID);       // Set ObjectType 
					pView->SetCapture();       // Capture the mouse until button up.
					//////////////////////////////////////////////
					return; 
					
				case FREEHAND:                                 // FREEHAND_INSERT

					pObjectMgr->SetActiveObjectType(FREEHAND);
					//////////////////////////////////////////
					DBoxLBDown_FREEHAND(point); // LOG
					////////////////////////////////////////////
					pView->SetCapture();       // Capture the mouse until button up.
   					m_bMoving = TRUE;              
           		 	///////////////////
					return;
		
				case LABEL:										// LABEL_INSERT:
		
					pObjectMgr->SetActiveObjectType(LABEL);       // Set ObjectType 
					pView->SetCapture();       // Capture the mouse until button up.
					//////////////////////////////////////////////
					return; 
					
				default:
					break;
			}
			break;
			
		case D_MOVE:				
		
			switch(nActiveObject)                              
			{
				case LABEL:                                 // LABEL_MOVE
			
					pObjectMgr->SetActiveObjectType(LABEL);
					/////////////////////////////// Label Hit Test
					if((m_CurrentMoveObjectIndex =  // ptScrolled: Dev/DeScaled
						IsObjectHit(LABEL,point,&m_ObjectRect))<0)
						return;
					///////////////////////////////			
					DBoxLBDown_OBJECTMOVE(pdc,point);
		 			///////////////////////////
					pView->SetCapture();
			        m_bMoving = TRUE;              
			        pMouseMgr->SetViewCursor ((int)DOUBLEARROW); 
					//////////////////////////////////
					return;
				default:
					break;
			}
			break;
			
		case D_EDIT:				
		
			switch(nActiveObject)                              
			{
				case LABEL:                                 // LABEL_EDIT
		
					pObjectMgr->SetActiveObjectType(LABEL);
					/////////////////////////////// Label Hit Test
					if((m_CurrentMoveObjectIndex =    
						IsObjectHit(LABEL,point,&m_ObjectRect))>=0) 
					{
						///////////////////////////
						pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
						CDrLabel* pLabel = (CDrLabel*)pDListMgr->
								GetObject(m_CurrentMoveObjectIndex);
						///////////////////////////
						if(pLabel->GetType() <0) // Not NodeLabel
						{
							AfxMessageBox("Use Node Dialog");   // Use NodeCard 
							return;
						}	
					}
					else
						return;		
					////////////////////
					CDDlgMgr* pDDlgMgr;
					//////////////////////////////////////////////
					pDDlgMgr->DoModal_Label_Edit(m_CurrentMoveObjectIndex);
					//////////////////////////////////////////////
					return;
			
				default:
					break;
			}
			break;
		default:
			break;
	}		
	
}

void CDBMouse::OnDBoxMouseMove(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point)
{                                           

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	/////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CMouseMgr* pMouseMgr	= pWnd->GetMouseMgr();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////
	pdc->DPtoLP(&point);
	////////////////////
	LPOINT LpLOG;
	LpLOG.x = (long)point.x;
	LpLOG.y = (long)point.y;
	///////////////////////////////////////
    if(!m_bMoving)  // not currently moving 
    { 
    
//	    ::SetCursor (m_hText); 
		//////////////////////////////////////
		LPOINT3 MouseOldTempWIC = GetMouseOldWIC();
	    LPOINT3 MouseTempWIC 	= GetMouseWIC();
   		SetMouseOldWIC(MouseTempWIC);
   		LPOINT3 MouseWIC;
    	//////////////////
    	LOGtoWIC2(&MouseWIC,&LpLOG,&MouseTempWIC);
    	////////////////////                 
    	SetMouseWIC(MouseWIC);
    	///////////////////////////
// 		pDoc->UpdateStatusBar(&dc);  WILL BE CALLED FROM VIEW, JUST SET HERE
		pMouseMgr->SetStatusMouseWIC(MouseWIC);
		////////////////////////////
		///////////////////// recover MouseWIC changed for statusbar update 
	    SetMouseOldWIC(MouseOldTempWIC);
	    SetMouseWIC(MouseTempWIC);

		return;
    }	
	////////////////////////////////////////////////////////////////
	int nActiveObject 	= pWnd->GetActiveObjectType();
	int nActiveTool		= pWnd->GetActiveToolType();    // -1= INSERT
	////////////////////////////////////////////////////////////////
   	CRect clientRect;
	switch(nActiveTool) 
	{
		
		case INSERT:
		
			switch(nActiveObject)                              
			{
				case FREEHAND:                                 // FREEHAND_INSERT

					pObjectMgr->SetActiveObjectType(FREEHAND);
				    ///////////////////////////////////
					if (pView->GetCapture() != pView)
						return; // If this window (view) didn't capture the mouse,
								// then the user isn't drawing in this window.
					/////////////////			
					DBoxMMove_FREEHAND(pdc,point);     //LOG
					/////////////////////////////////// 
					break;
				
				case LABEL:
					break;
					
        		default:
        			break;
			}
			break;	

		case D_MOVE:
		
			switch(nActiveObject)
			{
				case LABEL:                                    // LABEL_MOVE
		
					pObjectMgr->SetActiveObjectType(LABEL);
				    ///////////////////////////////////
					if (pView->GetCapture() != pView)
						return; // If this window (view) didn't capture the mouse,
								// then the user isn't drawing in this window. 
		            //////////////////////////////////
		           	pView->GetClientRect(&clientRect);
		           	pdc->LPtoDP(&point);
		           	if(clientRect.PtInRect(point))
		           	{ 
 		          		//////////////////////////////////////
		           		pdc->DPtoLP(&point);
						DBoxMMove_OBJECTMOVE(pdc,point);    // LOG
						//////////////////////////////////////
		  	       	}
   	       	
				break;	    	        
        		default:
        			break;
			}        			
        	break;
        default:
        	break;
    }

}

void CDBMouse::OnDBoxLButtonUp(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point)
{

	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CDListMgr* pDListMgr;
	//////////////////////////
    pdc->DPtoLP(&point);
	////////////////////////// LabelMove
	int nType;
	////////////////////////////////////////////////////////////////
	int nActiveObject 	= pWnd->GetActiveObjectType();
	int nActiveTool		= pWnd->GetActiveToolType();    // -1= INSERT
	////////////////////////////////////////////////////////////////
	if (pView->GetCapture() != pView)
		return; // If this window (view) didn't capture the mouse,
				// then the user isn't drawing in this window.
	////////////////////////////////////////////////////////////////			 
	CDDlgMgr* pDDlgMgr;
	///////////////////				
	switch(nActiveTool) 
	{
		
		case INSERT:
		
			switch(nActiveObject)                              
			{
				
				case GRID:
				
					//////////////////////////////////////////////
					ReleaseCapture();   // Release the mouse capture established at
										// the beginning of the mouse drag.
					pDDlgMgr->DoModal_Grid_Insert(); 
					//////////////////////////////////////////////
					return;
					
				case LABEL:
				
					//////////////////////////////////////////////
					ReleaseCapture();   // Release the mouse capture established at
										// the beginning of the mouse drag.
					pDDlgMgr->DoModal_Label_Insert(m_nView,point); 
					//////////////////////////////////////////////
					return;
					
				case FREEHAND:                                 // FREEHAND_INSERT
		
					pObjectMgr->SetActiveObjectType(FREEHAND);
					///////////////////////////////
					DBoxLBUp_FREEHAND(point);
					ReleaseCapture();   // Release the mouse capture established at
										// the beginning of the mouse drag.
					///////////////////////////////
					break;
					
					
        		default:
        			break;
			}
			break;	

		case D_MOVE:
		
			switch(nActiveObject)
			{
				case LABEL:                                    // LABEL_MOVE
		
					pObjectMgr->SetActiveObjectType(LABEL);
					///////////////////////////////
					DBoxLBUp_OBJECTMOVE(pdc,point,pView);
					ReleaseCapture();   // Release the mouse capture established at
										// the beginning of the mouse drag.
					///////////////////////////////
					CDrLabel*	pLabelCur;
	 		   		/////////////////////////////////// 
					pDListMgr 	= pObjectMgr->GetObjectList(LABEL);
					pLabelCur = (CDrLabel*)(pDListMgr->GetObject(m_CurrentMoveObjectIndex)  );
	   				///////////////////////////////////// Update Label New Location
					nType	 = pLabelCur->GetType();
					POINT pointLOG;
					pointLOG.x = m_ObjectRect.left;  // Log/DeScaled
					pointLOG.y = m_ObjectRect.top; 
					pLabelCur->SetCorner(pointLOG,m_nView);
					pLabelCur->SetMoved(TRUE); // let label know of move
					//////////////////
					pObjectMgr->SetActiveObjectIndex(m_CurrentMoveObjectIndex);
					pObjectMgr->SetActiveObjectType(LABEL);
					pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,m_CurrentMoveObjectIndex,LABEL);	
					//////////////////////////////////////////////////////////////////////										
	        		break; 
        		default:
        			break;
        	}
        	break;
        default:
        	break;
    }

}


void CDBMouse::OnDBoxRButtonDown(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point)
{ 
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	/////////////////////////////////////////////////////////
//	CScrollView::OnRButtonDown(nFlags, point);

}

void CDBMouse::OnDBoxRButtonUp(CClientDC* pdc,CView* pView,
											UINT nFlags, CPoint point)
{
	m_nFlags				= nFlags;
	m_pView					= pView;
	m_pdc					= pdc;
	/////////////////////////////////////////////////////////
	// TODO: Add your message handler code here and/or call default
	
//	CScrollView::OnRButtonUp(nFlags, point);

}

void CDBMouse::Serialize(CArchive& ar)
{

	CMouse::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	WORD w;
	BYTE bDragOn,bDragging,bMoving; 
	WORD nCurrentMoveObjectIndex;
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" DBMouse:    Storing\n");	
		/////////////////////////////////////////////////
		ar	<</*CString*/	m_CurrentLabelID
			<</*int*/	(WORD)m_nFHNumberCurrent
			<</*int*/	(WORD)m_nFHIndexCurrent;
		ar 	<</*int*/	(WORD)m_CurrentMoveObjectIndex 
			<</*CRect*/	m_InvalidMoveRect 
			<</*POINT*/	m_ptPrev           
			<</*BOOL*/	(BYTE)m_bDragOn 
			<</*BOOL*/	(BYTE)m_bDragging 
			<</*BOOL*/	(BYTE)m_bMoving
			<</*RECT*/	m_ObjectRect
			<</*RECT*/	m_ObjectRectOld;
		/////////////////////////////////////////// 

	}
	else
	{
		TRACE(" DBMouse:    Loading\n");	
		/////////////////////////////////////////////////
		ar	>>/*CString*/	m_CurrentLabelID;
		ar	>>/*int*/		(WORD)w;
		m_nFHNumberCurrent	= (int)w;
		ar	>>/*int*/		(WORD)w;
		m_nFHIndexCurrent	= (int)w;
		ar	>>/*int*/	nCurrentMoveObjectIndex 
			>>/*CRect*/	m_InvalidMoveRect 
			>>/*POINT*/	m_ptPrev           
			>>/*BOOL*/	bDragOn 
			>>/*BOOL*/	bDragging 
			>>/*BOOL*/	bMoving
			>>/*RECT*/	m_ObjectRect
			>>/*RECT*/	m_ObjectRectOld;
 		//////////////////////////////
		m_CurrentMoveObjectIndex	= (int)nCurrentMoveObjectIndex;
		m_bDragOn					= (BOOL)bDragOn;
		m_bDragging					= (BOOL)bDragging;
		m_bMoving					= (BOOL)bMoving;
	
	}        
}

		 
///////////////////////////////////// end of Module //////////////////////		

