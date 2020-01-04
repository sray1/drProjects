// Element dataBase.cpp : implementation of the CNewObjs class
//

#include "stdafx.h"

#include "drobject.h"
///////////////////////////// TopLevels
//#include "TLDefine.h" 
///////////////////////////// 3D Drawing Operations
//#include "3Ddefine.h"
//#include "XForm.h"
///////////////////////////// ElemObjs
#include "elextern.h"
#include "eldefine.h"
#include "DrNode.h"
#include "DrPipe.h"
#include "DrCurve.h"
#include "DrProf_C.h"
#include "DrPlate.h"
#include "DrFE3D.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
///////////////////////////// DrawObjs
#include "drextern.h"
#include "drdefine.h"
#include "DrLabel.h"
#include "DrfreHnd.h"
#include "DrGrid.h"
///////////////////////////// SpecObjs
#include "spextern.h"
#include "spdefine.h"
#include "booleans.h"
#include "datawind.h"
#include "drfont.h"
#include "drpen.h"
#include "layer.h"
#include "hitnet.h"
#include "precison.h"
#include "Mapfacto.h"
#include "ScaleFac.h"
#include "unit.h"
#include "Obj3DMnu.h"
#include "PatchMnu.h" 
/////////////////////////////
#include "NewObjs.h" 


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif 
/*
BEGIN_MESSAGE_MAP(CNewObjs, CObject)
	//{{AFX_MSG_MAP(CNewObjs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

IMPLEMENT_DYNCREATE(CNewObjs,CObject)

CNewObjs::CNewObjs()
{
}

CNewObjs::~CNewObjs()
{
}

///////////////////////////////////////////////////////////////////////

void CNewObjs::AssertValid() const
{
	CObject::AssertValid();
}

void CNewObjs::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

CDrObject* CNewObjs::NewObject(int nObjectType)
{
 
	///////////////////////////////////////////////////////
	CDrObject* pObject;
	//////////////////
	switch (nObjectType)
	{

		///////////////////////////////////////////////// TopLevel	
		case OBJ3D:
			
			pObject = new CDrObj3D;
			break;
			   
		case SOLID:
			
			pObject = new CDrSolid;
			break;
			   
		case PATCH:
			
			pObject = new CDrPatch;
			break;
			   
		case CURVE:
			
			pObject = new CDrCurve;
			break;

		case C_PROFILE:
			
			pObject = new CDrProf_C;
			break;
		///////////////////////////////////////////////// ElemObjs	
		case NODE:
			
			pObject = new CDrNode;
			break;
			   
		case PIPE:
			
			pObject = new CDrPipe;
			break;
			   
		case PLATE:
			
			pObject = new CDrPlat;
			break;
			   
		case FE3D:
			
//			pObject = new CDrFE3D;
			break;
		///////////////////////////////////////////////// 3D Drawing Operations	
//		case XFORM:
			
//			pObject = new CXForm;
//			break;
			   
		///////////////////////////////////////////////// DrawObjs	
		case LABEL:
			
			pObject = new CDrLabel;
			break;
			
		case FREEHAND:
			
			pObject = new CDrFreeHand;
			break;

		case GRID:
			
			pObject = new CDrGrid;
			break;
			
		///////////////////////////////////////////////// SpecObjs	
		case BOOLEANS:
			pObject = new CBooleans;
			break; 
			
		case DATAWINDOW:
			pObject = new  CDataWindow;
			break; 
			
		case DRFONT:
			pObject = new CDrFont;
			break; 
			
		case DRPEN:
			pObject = new CDrPen;
			break; 
			
		case HITNET:
			pObject = new CHitNet;
			break;
			
		case LAYER:
			pObject = new CLayer;
			break;
			
		case MAPFACTOR:
			pObject = new CMapFactor;
			break;
			
		case PRECISION:
			pObject = new CPrecision;
			break; 
			
		case SCALEFACTOR:
			pObject = new CScaleFactor;
			break; 
			
		case UNIT:
			pObject = new CUnit;
			break; 
			
		case OBJ3DMNU:
			pObject = new CObj3DMnu;
			break; 
			
		case PATCHMNU:
			pObject = new CPatchMnu;
			break; 
			

		default:			   
		
			pObject = (CDrObject*)NULL;
			break;
			
	}
	///////////////////////////////////
	if(!pObject)
	{
	   	CString name = "";
   		//////////////////////////////////// ElemObj
   		for (int i = 0;i<nMax_ElemTypes;i++)
   			if(ElTypes[i].num == nObjectType) 
   			{
   				name = ElTypes[i].ObjName;
   				break;
   			}	
   		//////////////////////////////////// DrawObj
   		if(name == "")
   		{
   			for (int i = 0;i<nMax_DrawTypes;i++)
   				if(DrTypes[i].num == nObjectType) 
   				{
   					name = DrTypes[i].ObjName;
   					break;
   				}
   		}			
   		//////////////////////////////////// SpecObj
   		if(name == "")
   		{
   			for (int i = 0;i<nMax_SpecTypes;i++)
   				if(SpTypes[i].num == nObjectType) 
   				{
   					name = SpTypes[i].ObjName;
   					break;
   				}
   		}			
		/////////////////////////
        name += " Object Generation Problem\nLow Memory? : NewObj";
		AfxMessageBox(name);
		return (CDrObject*)NULL;		 
	}	
	return pObject;
}
												
///////////////////////////////// end of module ///////////////////
