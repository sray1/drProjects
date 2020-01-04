// Element dataBase.cpp : implementation of the CNewObjs class
//

#include "stdafx.h"

#include "drobject.h"
///////////////////////////// TopLevels
//#include "TLDefine.h" 
///////////////////////////// 3D Drawing Operations
//#include "3Ddefine.h"
//#include "XForm.h"
///////////////////////////// OGenObjs
#include "Ext_Cur.h"
#include "Ext_Pat.h"
#include "Ext_Sol.h"
#include "Def_IGen.h"
#include "DrProf_C.h"
#include "DrProf_P.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
/////////////////////////// ElemObjs
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "Def_EInf.h"
#include "Ext_EInf.h"
//////////////////////////
#include "ElemInfo.h"
////////////////////////// MeshObjs
#include "DrMesh1D.h"
#include "DrMesh2D.h"
#include "DrMesh3D.h"
////////////////////////// 0D
#include "DrNode.h"
#include "DrFE0D.h"
////////////////////////// 1D
#include "DrFE1D.h"
#include "DrPipe.h"
#include "DrBeam.h"
#include "DrTruss.h"
#include "DrElbow.h"
////////////////////////// 2D
#include "DrFE2D.h"
#include "Dr_Qu_4.h"
#include "Dr_Qu_8.h"
#include "Dr_Qu_9.h"
#include "Dr_Qu_12.h"
#include "Dr_Qu_16.h"
#include "Dr_Tr_3.h"
#include "Dr_Tr_6.h"
#include "Dr_Tr_9.h"
#include "Dr_Tr_10.h"
////////////////////////// 3D
#include "DrFE3D.h"
#include "DrCurve.h"
///////////////////////////// DrawObjs
#include "Ext_Draw.h"
#include "Def_Draw.h"
#include "DrLabel.h"
#include "DrfreHnd.h"
#include "DrGrid.h"
///////////////////////////// SpecObjs
#include "Ext_Spec.h"
#include "Def_Spec.h"
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
///////////////////////////// SuppObjs
#include "Def_Supp.h"
#include "DrLinSup.h"
///////////////////////////// StaLObjs
#include "Def_StaL.h" 
#include "DrStatic.h" 
/*
#include "DrF_MCur.h" 
#include "DrF_M.h" 
#include "DrD_R.h" 
#include "DrPrs.h" 
#include "DrThr.h" 
#include "DrLWt.h" 
*/
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

		///////////////////////////////////////////////// 	
		case ELEMINFO:
			
			pObject = new CElemInfo;
			break;
			   
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

		case P_PROFILE:
			
			pObject = new CDrProf_P;
			break;
		///////////////////////////////////////////////// MeshObjs	
		case MESH1D:
			
			pObject = new CDrMesh1D;
			break;

		case MESH2D:
			
			pObject = new CDrMesh2D;
			break;

		case MESH3D:
			
			pObject = new CDrMesh3D;
			break;

		///////////////////////////////////////////////// ElemObjs	
		////////////////////////////////// 0D			   
		case NODE:	// fall thro'
		case INODE:
		case CNODE:
			
			pObject = new CDrNode;
			break;
			   
		////////////////////////////////// 0D (Mesh Node)			   
		case FE0D:	// fall thro'
		case MNODE:
		case MCNODE:
			
			pObject = new CDrFE0D;
			break;
			   
		////////////////////////////////// 1D			   
		case FE1D:
			
			pObject = new CDrFE1D;
			break;

		case PIPE:
			
			pObject = new CDrPipe;
			break;

		case BEAM:
			
			pObject = new CDrBeam;
			break;

		case TRUSS:
			
			pObject = new CDrTruss;
			break;

		case ELBOW:
			
			pObject = new CDrElbow;
			break;
			   
		////////////////////////////////// 2D			   
		case FE2D:
			
			pObject = new CDrFE2D;
			break;
			   
		case QU_4:
			
			pObject = new CDr_Qu_4;
			break;
			   
		case QU_8:
			
			pObject = new CDr_Qu_8;
			break;
			   
		case QU_9:
			
			pObject = new CDr_Qu_9;
			break;
			   
		case QU_12:
			
			pObject = new CDr_Qu_12;
			break;
			   
		case QU_16:
			
			pObject = new CDr_Qu_16;
			break;
			   
		///////////////////////////	   
		case TR_3:
			
			pObject = new CDr_Tr_3;
			break;
			   
		case TR_6:
			
			pObject = new CDr_Tr_6;
			break;
			   
		case TR_9:
			
			pObject = new CDr_Tr_9;
			break;
			   
		case TR_10:
			
			pObject = new CDr_Tr_10;
			break;
		////////////////////////////////// 3D			   
		case FE3D:
			
			pObject = new CDrFE3D;
			break;

		///////////////////////////////////////////////// SuppObjs	
		case LIN_SUPPORT:
			
			pObject = new CDrLinSup;
			break;
		///////////////////////////////////////////////// StaLObjs	
		case CSTATIC:	// fall thro'
		case FORCE:
		case DISPLACE:
		case PRESSURE:
		case THERMAL:
		case LUMPWT:
		case STATICLOAD:
			
			pObject = new CDrStatic;
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
	int i;
	//////
	if(!pObject)
	{
	   	CString name = "";
   		//////////////////////////////////// ElemObj
   		for (i = 0;i<nMax_ElemTypes;i++)
   			if(ElTypes[i].num == nObjectType) 
   			{
   				name = ElTypes[i].ObjName;
   				break;
   			}	
   		//////////////////////////////////// IGenObj
   		for (i = 0;i<nMax_CurveTypes;i++)
   			if(CuTypes[i].num == nObjectType) 
   			{
   				name = CuTypes[i].ObjName;
   				break;
   			}	
   		for (i = 0;i<nMax_PatchTypes;i++)
   			if(PaTypes[i].num == nObjectType) 
   			{
   				name = PaTypes[i].ObjName;
   				break;
   			}	
   		for (i = 0;i<nMax_SolidTypes;i++)
   			if(SoTypes[i].num == nObjectType) 
   			{
   				name = SoTypes[i].ObjName;
   				break;
   			}	
   		//////////////////////////////////// DrawObj
   		if(name == "")
   		{
   			for (i = 0;i<nMax_DrawTypes;i++)
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
