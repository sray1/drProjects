// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
#include "drgrafrm.h"
#include "UserMsg.h"
#include "drawView.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
/////////////////////
#include "Def_Objs.h"                    
#include "Def_Mous.h"                    
#include "Def_CuPS.h"                    
///////////////////// dialogMgr
//#include "MSPLMgr.h"  
///////////////////// elements
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
///////////////////// DynLObjs
#include "Def_DynL.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h" 	
///////////////////// specials
#include "Def_Spec.h"
#include "Obj3DMnu.h"
#include "PatchMnu.h"
#include "DrPen.h"
#include "Layer.h"
#include "booleans.h"
#include "precison.h"
/////////////////////
#include "mouse.h"
#include "DListMgr.h"
//////////////////////
#include "SpLMouse.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSpLMouse,CSLDMouse,1)
/////////////////////////////////////////////////////////////////////////////
CSpLMouse::CSpLMouse()
{

}

CSpLMouse::~CSpLMouse()
{
}

void CSpLMouse::Serialize(CArchive& ar)
{

	CSLDMouse::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SPLMouse:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SPLMouse:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


