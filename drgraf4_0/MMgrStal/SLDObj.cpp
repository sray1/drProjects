// Mouse.cpp : implementation file
//


#include "stdafx.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// elements
#include "Def_IGen.h"
///////////////////// Static Loads
#include "Str_StaL.h"
#include "Def_StaL.h"
#include "DrStatic.h" 
#include "MI_StaL.h" 
//////////////////////
#include "MSTLMgr.h" 
//////////////////////
#include "SLDObj.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
////////////////////////////////////
IMPLEMENT_SERIAL(CSLDObj,CObject,1)
/////////////////////////////////////////////////////////////////////////////
CSLDObj::CSLDObj()
{

	m_nNodPos_S_Beg		= 0;		// index of Bezier Segment in s direction, -1= All Segments
	m_nNodPos_S_End		= 0;		// index of Bezier Segment in s direction, -1= All Segments
									// now,useful for CProf internally
//todo									// later for UserInterface of BezSeg dependent input
	m_nNodPos_T_Beg		= 0;		// index of Bezier Segment in s direction, -1= All Segments
	m_nNodPos_T_End		= 0;		// index of Bezier Segment in s direction, -1= All Segments
									// later,useful for PProf internally
	m_nNodPos_R_Beg		= 0;		// index of Bezier Segment in s direction, -1= All Segments
	m_nNodPos_R_End		= 0;		// index of Bezier Segment in s direction, -1= All Segments
									// later,useful for SProf internally
	m_nStartIndex	= 0;		// index in StaLList         
	m_nTotal		= 0;		// total generated in StaLList having
									// this StaLCard Properties         
	/////////////////////////////////////////// Static
	m_StaLProc		= STL_FORCE;
	m_bTx			= FALSE;
	m_bTy			= FALSE;
	m_bTz			= FALSE;
	m_bRx			= FALSE;
	m_bRy			= FALSE;
	m_bRz			= FALSE;
	///////////////////////
	m_dTx			= 0.0;
	m_dTy			= 0.0;
	m_dTz			= 0.0;
	m_dRx			= 0.0;
	m_dRy			= 0.0;
	m_dRz			= 0.0;
	/////////////////////
	m_aNid			= "";
	m_bCN_a			= FALSE;		// nid_a is Control Node?		
	m_bNid			= "";
	m_bCN_b			= FALSE;		// nid_b is Control Node?		
//	m_SkewDir		= ;
//	m_GenKind		= ;		//
	m_bTanCur		= FALSE;		 
	m_bTanPat		= FALSE;		 
	m_bNorPat		= FALSE;		 
	m_ID_CP			= "";		
	m_jcType		= JC_DEFAULT;		//	JC_DEFAULT,
	m_bUniform		= FALSE;	// Uniform distribution
	m_bConOrDis		= TRUE;		// IsoParametric Concentrated or Distributed Input
	m_bIso			= FALSE;
	m_cid_Iso		= "";		// Iso  or NonIso to this Curve				
	m_cid_ParentT	= "";	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	m_cid_ParentR	= "";	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	/////////////////////// NonIso
	m_bNonIso		= TRUE;
	m_CID			= "";
	m_bIncrement	= FALSE;
	m_Orient		= "";
	m_dScale		= 1.0;
	m_dStep			= 1.0;
	m_dStart		= 1.0;
	//////////////////////////
	m_bGravMul		= FALSE;

}

CSLDObj::~CSLDObj()
{
}

void CSLDObj::GetObjectInfo(CSLDObj* pObject)
{
	
	/////////////////////////////////////////// Static
	pObject->m_nNodPos_S_Beg		= m_nNodPos_S_Beg;
	pObject->m_nNodPos_S_End		= m_nNodPos_S_End;
	pObject->m_nNodPos_T_Beg		= m_nNodPos_T_Beg;
	pObject->m_nNodPos_T_End		= m_nNodPos_T_End;
	pObject->m_nNodPos_R_Beg		= m_nNodPos_R_Beg;
	pObject->m_nNodPos_R_End		= m_nNodPos_R_End;
	pObject->m_nStartIndex		= m_nStartIndex;
	pObject->m_nTotal			= m_nTotal;
	///
	pObject->m_StaLProc			= m_StaLProc;
	pObject->m_bTx				= m_bTx;
	pObject->m_bTy				= m_bTy;
	pObject->m_bTz				= m_bTz;
	pObject->m_bRx				= m_bRx;
	pObject->m_bRy				= m_bRy;
	pObject->m_bRz				= m_bRz;
	pObject->m_dTx				= m_dTx;			// also for Prs,Thr and LWt
	pObject->m_dTy				= m_dTy;			// also for Prs,Thr and LWt
	pObject->m_dTz				= m_dTz;			// also for             LWt
	pObject->m_dRx				= m_dRx;
	pObject->m_dRy				= m_dRy;
	pObject->m_dRz				= m_dRz;
	/////////////////////
	pObject->m_aNid				= m_aNid;
	pObject->m_bCN_a			= m_bCN_a;		// nid_a is Control Node?		
	pObject->m_bNid				= m_bNid;
	pObject->m_bCN_b			= m_bCN_b;		// nid_b is Control Node?		
	pObject->m_bTanCur			= m_bTanCur;			// already in supMpouse
	pObject->m_bTanPat			= m_bTanPat;			// already in supMpouse
	pObject->m_bNorPat			= m_bNorPat;			// already in supMpouse
	pObject->m_ID_CP			= m_ID_CP;		
	pObject->m_jcType			= m_jcType;		//	JC_DEFAULT,
	pObject->m_bUniform			= m_bUniform;	// Uniform distribution
	pObject->m_bConOrDis		= m_bConOrDis;		// IsoParametric Concentrated or Distributed Input
	pObject->m_bIso				= m_bIso;
	pObject->m_cid_Iso			= m_cid_Iso;		// Iso  or NonIso to this Curve				
	pObject->m_cid_ParentT		= m_cid_ParentT;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	pObject->m_cid_ParentR		= m_cid_ParentR;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	/////////////////////// NonIso
	pObject->m_bNonIso			= m_bNonIso;
	pObject->m_CID				= m_CID;
	pObject->m_bIncrement		= m_bIncrement;
	pObject->m_Orient			= m_Orient;
	pObject->m_dScale			= m_dScale;
	pObject->m_dStep			= m_dStep;
	pObject->m_dStart			= m_dStart;
	//////////////////////////
	pObject->m_bGravMul			= m_bGravMul;
}

void CSLDObj::SetObjectInfo(CSLDObj* pObject)
{
	
	/////////////////////////////////////////// Static
	m_nNodPos_S_Beg			= pObject->m_nNodPos_S_Beg;
	m_nNodPos_S_End			= pObject->m_nNodPos_S_End;
	m_nNodPos_T_Beg			= pObject->m_nNodPos_T_Beg;
	m_nNodPos_T_End			= pObject->m_nNodPos_T_End;
	m_nNodPos_R_Beg			= pObject->m_nNodPos_R_Beg;
	m_nNodPos_R_End			= pObject->m_nNodPos_R_End;
	m_nStartIndex		= pObject->m_nStartIndex;
	m_nTotal			= pObject->m_nTotal;
	///
	m_StaLProc			= pObject->m_StaLProc;
	m_bTx				= pObject->m_bTx;
	m_bTy				= pObject->m_bTy;
	m_bTz				= pObject->m_bTz;
	m_bRx				= pObject->m_bRx;
	m_bRy				= pObject->m_bRy;
	m_bRz				= pObject->m_bRz;
	m_dTx				= pObject->m_dTx;			// also for Prs,Thr and LWt
	m_dTy				= pObject->m_dTy;			// also for Prs,Thr and LWt
	m_dTz				= pObject->m_dTz;			// also for             LWt
	m_dRx				= pObject->m_dRx;
	m_dRy				= pObject->m_dRy;
	m_dRz				= pObject->m_dRz;
	/////////////////////
	m_aNid				= pObject->m_aNid;		
	m_bCN_a				= pObject->m_bCN_a;		// nid_a is Control Node?		
	m_bNid				= pObject->m_bNid;
	m_bCN_b				= pObject->m_bCN_b;		// nid_b is Control Node?		
	m_bTanCur			= pObject->m_bTanCur;			// already in supMpouse
	m_bTanPat			= pObject->m_bTanPat;			// already in supMpouse
	m_bNorPat			= pObject->m_bNorPat;			// already in supMpouse
	m_ID_CP				= pObject->m_ID_CP;		
	m_jcType			= pObject->m_jcType;		//	JC_DEFAULT,
	m_bUniform			= pObject->m_bUniform;	// Uniform distribution
	m_bConOrDis			= pObject->m_bConOrDis;		// IsoParametric Concentrated or Distributed Input
	m_bIso				= pObject->m_bIso;
	m_cid_Iso			= pObject->m_cid_Iso;		// Iso  or NonIso to this Curve				
	m_cid_ParentT		= pObject->m_cid_ParentT;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	m_cid_ParentR		= pObject->m_cid_ParentR;	// for both Iso & NonIso(m_CID) ( Generated or Input Curve)				
	/////////////////////// NonIso
	m_bNonIso			= pObject->m_bNonIso;
	m_CID				= pObject->m_CID;
	m_bIncrement		= pObject->m_bIncrement;
	m_Orient			= pObject->m_Orient;
	m_dScale			= pObject->m_dScale;
	m_dStep				= pObject->m_dStep;
	m_dStart			= pObject->m_dStart;
	//////////////////////////
	m_bGravMul			= pObject->m_bGravMul;
}

int CSLDObj::FillStLCard(STALCARD& stLCard,CString* pID)
{
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	/////////////////////////////////////////// Static
	stLCard.nNodPos_S_Beg		= m_nNodPos_S_Beg;
	stLCard.nNodPos_S_End		= m_nNodPos_S_End;
	stLCard.nNodPos_T_Beg		= m_nNodPos_T_Beg;
	stLCard.nNodPos_T_End		= m_nNodPos_T_End;
	stLCard.nNodPos_R_Beg		= m_nNodPos_R_Beg;
	stLCard.nNodPos_R_End		= m_nNodPos_R_End;
	stLCard.nStartIndex			= m_nStartIndex;
	stLCard.nTotal				= m_nTotal;
	///////////////////
	stLCard.load_id		= *pID;
	stLCard.StaLProc	= m_StaLProc;
	stLCard.kode[0]		= (BYTE)m_bTx;
	stLCard.kode[1]		= (BYTE)m_bTy;
	stLCard.kode[2]		= (BYTE)m_bTz;
	stLCard.kode[3]		= (BYTE)m_bRx;
	stLCard.kode[4]		= (BYTE)m_bRy;
	stLCard.kode[5]		= (BYTE)m_bRz;

	stLCard.value[0]	= m_dTx;
	stLCard.value[1]	= m_dTy;
	stLCard.value[2]	= m_dTz;
	stLCard.value[3]	= m_dRx;
	stLCard.value[4]	= m_dRy;
	stLCard.value[5]	= m_dRz;
	/////////////////////
	stLCard.nid_a		= m_aNid;
	stLCard.bCN_a		= m_bCN_a;		// nid_a is Control Node?		
	stLCard.nid_b		= m_bNid;			
	stLCard.bCN_b		= m_bCN_b;		// nid_b is Control Node?		
	stLCard.bTanCur		= m_bTanCur;				
	stLCard.bTanPat		= m_bTanPat;				
	stLCard.bNorPat		= m_bNorPat;				
	stLCard.ID_CP		= m_ID_CP;		
	stLCard.jcType		= m_jcType;		//	JC_DEFAULT,
	stLCard.bUniform	= m_bUniform;	// Uniform distribution
	stLCard.bConOrDis	= m_bConOrDis;		// IsoParametric Concentrated or Distributed Input
	stLCard.bIso		= m_bIso;				
	stLCard.cid_Iso		= m_cid_Iso;				
	stLCard.cid_ParentT	= m_cid_ParentT;				
	stLCard.cid_ParentR	= m_cid_ParentR;				
	/////////////////////////////////// NonIso
	stLCard.bNonIso		= m_bNonIso;
	stLCard.bIncrement	= m_bIncrement;
	stLCard.Orient		= m_Orient;
	stLCard.dScale		= m_dScale;
	stLCard.dStep		= m_dStep;
	stLCard.dStart		= m_dStart;
	/////////////////////////////////////////////////// Create, if Fixed Skewed Direction
	if(m_jcType == JC_X_FIXEDDIR)	
	{
		CDListMgr* pList;
		WORLD		NewX;
		pWORLD		pNewX = &NewX;	// 
	
		int			index;
		CDrNode*	pNodeA;
		CDrNode*	pNodeB;
		WORLD		CNodPosA,CNodPosB;		
		////////////////
		pList				= pObjectMgr->GetObjectList(m_bCN_a?CNODE:NODE);
		index				= pList->GetObjectIndex(NODE,stLCard.nid_a);
		pNodeA				= (CDrNode*)pList->GetObject(index);
		CNodPosA			= *(pNodeA->GetLocalPos());
		//
		pList				= pObjectMgr->GetObjectList(m_bCN_b?CNODE:NODE);
		index				= pList->GetObjectIndex(NODE,stLCard.nid_b);
		pNodeB				= (CDrNode*)pList->GetObject(index);
		CNodPosB			= *(pNodeB->GetLocalPos());
		////////////////////////////////////////////////////// Get NewX Direction
		C3DMath Math3D;
		Math3D.Sub3DPts(&CNodPosB,&CNodPosA,pNewX);
		Math3D.Normalize(pNewX,pNewX);
		////////////////////////////////////////////////////// Save
		stLCard.SkewDir.x = pNewX->x;
		stLCard.SkewDir.y = pNewX->y;
		stLCard.SkewDir.z = pNewX->z;
		/////////////////////////////
	}
	///////////////////////////////////
	return 0;
}


int CSLDObj::FillInfo_3(CString& Nid,STALCARD stLCard,char* buf, int jStart)
{
	CString dir[] = {"X","Y","Z"};

	int i, j = jStart;
	//////////////////
	switch(stLCard.StaLProc)
	{
		case STL_THERMAL:
			j += sprintf(buf+j,"\n\nLoadType = THERMAL\n");
			break;
		case STL_PRESSURE:
			j += sprintf(buf+j,"\n\nLoadType = PRESSURE (Normal/Shear)\n");
			break;
		case STL_LUMPWT:
			j += sprintf(buf+j,"\n\nLoadType = LUMPWT\n");
			break;
		default:
			break;
	}
	//////////////
	j += sprintf(buf+j,"\nLoadID = %s\n",stLCard.load_id);
	/////////////////////////////////////////////////////////////////////// Translational
	j += sprintf(buf+j,"\nTranslational:\n");
	for(i=0;i<3;i++)
	{
		if((BOOL)stLCard.kode[i])
			j += sprintf(buf+j,"\tDirection %s = %f \n", dir[i],stLCard.value[i]);
		else
			j += sprintf(buf+j,"\tDirection %s = NOLOAD\n", dir[i]);
	}
	/////////////////////////////////////////////////////////////////////// Skewed
	if(m_jcType == JC_X_FIXEDDIR)
	{	
			j += sprintf(buf+j,"\nLoading Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis defined by:\n");
			j += sprintf(buf+j,"\t%s and %s\n",stLCard.nid_a,stLCard.nid_b);
	}
	else
	if(m_jcType == JC_X_TAN_CURVE)
	{	
		j += sprintf(buf+j,"\nLoading Input is Skewed with\n");
		j += sprintf(buf+j,"X-axis Tangent to Curve\n");
		/////////////////////////////////////////////////////////////////////// IsoParametric
		if(stLCard.bIso)
			j += sprintf(buf+j,"\nLoading Input:\nIsoParametric\nto %s Curve\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bNonIso)
			j += sprintf(buf+j,"\nLoading Input:\nNon-IsoParametric\nto %s Curve\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Uniform
		if(stLCard.bUniform)
			j += sprintf(buf+j,"\nLoading Input:\nUniform over\n%s Curve\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Conc or Dist?
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nConcentrated over\n%s Curve\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nDistributed over\n%s Curve\n",
						stLCard.cid_ParentT);
	}
	else
	if(m_jcType == JC_Z_NOR_PATCH || m_jcType == JC_I_TAN_PATCH)
	{	
		j += sprintf(buf+j,"\nLoading Input is Skewed with\n");
		if(m_jcType == JC_Z_NOR_PATCH)
			j += sprintf(buf+j,"Z-axis Normal to Patch\n");
		else
		if(m_jcType == JC_I_TAN_PATCH)
			j += sprintf(buf+j,"Z-axis Normal to Patch\n");
		/////////////////////////////////////////////////////////////////////// IsoParametric
		if(stLCard.bIso)
			j += sprintf(buf+j,"\nLoading Input:\nIsoParametric\nto %s Patch\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bNonIso)
			j += sprintf(buf+j,"\nLoading Input:\nNon-IsoParametric\nto %s Patch\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Uniform
		if(stLCard.bUniform)
			j += sprintf(buf+j,"\nLoading Input:\nUniform over\n%s Patch\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Conc or Dist?
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nConcentrated over\n%s Patch\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nDistributed over\n%s Patch\n",
						stLCard.cid_ParentT);
	}
	/////////
	return j;
}

int CSLDObj::FillInfo_6(CString& Nid,STALCARD stLCard,char* buf, int jStart)
{
	CString dir[] = {"X","Y","Z"};

	int i, j = jStart;
	//////////////////
	switch(stLCard.StaLProc)
	{
		case STL_DISPLACE:
			j += sprintf(buf+j,"\n\nLoadType = DISPLACEMENT/ROTATION\n");
			break;
		case STL_FORCE:
			j += sprintf(buf+j,"\n\nLoadType = FORCE/MOMENT\n");
			break;
		default:
			break;
	}
	//////////////
	j += sprintf(buf+j,"\nLoadID = %s\n",stLCard.load_id);
	/////////////////////////////////////////////////////////////////////// Translational
	j += sprintf(buf+j,"\nTranslational:\n");
	for(i=0;i<3;i++)
	{
		if((BOOL)stLCard.kode[i])
			j += sprintf(buf+j,"\tDirection %s = %f \n", dir[i],stLCard.value[i]);
		else
			j += sprintf(buf+j,"\tDirection %s = NOLOAD\n", dir[i]);
	}
	/////////////////////////////////////////////////////////////////////// Rotational
	j += sprintf(buf+j,"\nRotational:\n");
	for(i=3;i<6;i++)
	{
		if((BOOL)stLCard.kode[i])
			j += sprintf(buf+j,"\tDirection %s = %f \n", dir[i-3],stLCard.value[i]);
		else
			j += sprintf(buf+j,"\tDirection %s = NOLOAD\n", dir[i-3]);
	}
	/////////////////////////////////////////////////////////////////////// Skewed
	if(m_jcType == JC_X_FIXEDDIR)
	{	
			j += sprintf(buf+j,"\nLoading Coordinate is Skewed with\n");
			j += sprintf(buf+j,"X-axis defined by:\n");
			j += sprintf(buf+j,"\t%s and %s\n",stLCard.nid_a,stLCard.nid_b);
	}
	else
	if(m_jcType == JC_X_TAN_CURVE)
	{	
		j += sprintf(buf+j,"\nLoading Input is Skewed with\n");
		j += sprintf(buf+j,"X-axis Tangent to Curve\n");
		/////////////////////////////////////////////////////////////////////// IsoParametric
		if(stLCard.bIso)
			j += sprintf(buf+j,"\nLoading Input:\nIsoParametric\nto %s Curve\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bNonIso)
			j += sprintf(buf+j,"\nLoading Input:\nNon-IsoParametric\nto %s Curve\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Uniform
		if(stLCard.bUniform)
			j += sprintf(buf+j,"\nLoading Input:\nUniform over\n%s Curve\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Conc or Dist?
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nConcentrated over\n%s Curve\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nDistributed over\n%s Curve\n",
						stLCard.cid_ParentT);
	}
	else
	if(m_jcType == JC_Z_NOR_PATCH || m_jcType == JC_I_TAN_PATCH)
	{	
		j += sprintf(buf+j,"\nLoading Input is Skewed with\n");
		if(m_jcType == JC_Z_NOR_PATCH)
			j += sprintf(buf+j,"Z-axis Normal to Patch\n");
		else
		if(m_jcType == JC_I_TAN_PATCH)
			j += sprintf(buf+j,"Z-axis Normal to Patch\n");
		/////////////////////////////////////////////////////////////////////// IsoParametric
		if(stLCard.bIso)
			j += sprintf(buf+j,"\nLoading Input:\nIsoParametric\nto %s Patch\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bNonIso)
			j += sprintf(buf+j,"\nLoading Input:\nNon-IsoParametric\nto %s Patch\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Uniform
		if(stLCard.bUniform)
			j += sprintf(buf+j,"\nLoading Input:\nUniform over\n%s Patch\n",
						stLCard.cid_ParentT);
		/////////////////////////////////////////////////////////////////////// Conc or Dist?
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nConcentrated over\n%s Patch\n",
						stLCard.cid_ParentT);
		else
		if(stLCard.bConOrDis)
			j += sprintf(buf+j,"\nLoading Input:\nDistributed over\n%s Patch\n",
						stLCard.cid_ParentT);
	}
	/////////
	return j;
}

int CSLDObj::Get_Values(STALPROC StaLProc, CString& heading)
{
	CMStLMgr	Mgr;
	UINT		nStatus;
	int i;
	/////////////////////
	BOOL		bKode[6];
	double		dValu[6];
	/////////////////////
	bKode[0]	= m_bTx;
	bKode[1]	= m_bTy;
	bKode[2]	= m_bTz;
	bKode[3]	= m_bRx;
	bKode[4]	= m_bRy;
	bKode[5]	= m_bRz;
	///////////////////////////
	dValu[0]	= m_dTx;
	dValu[1]	= m_dTy;
	dValu[2]	= m_dTz;
	dValu[3]	= m_dRx;
	dValu[4]	= m_dRy;
	dValu[5]	= m_dRz;
	//////////////////////////////////////////////////////////////////
	switch(StaLProc)
	{
		case STL_DISPLACE:	// fall thro'
		case STL_FORCE:

			for(i=0;i<6;i++)
			{
				///////////////
				if(bKode[i])
				{
					nStatus = Mgr.DoModal_Value_In(heading,&(dValu[i]),i,StaLProc);
					////////////////////////////////////////////////////////////////
					if(nStatus == IDCANCEL)
						dValu[i] = 0.0;
				}
			}
			break;


		case STL_PRESSURE:
		case STL_THERMAL:
		case STL_LUMPWT:

			for(i=0;i<3;i++)
			{
				///////////////
				if(bKode[i])
				{
					nStatus = Mgr.DoModal_Value_In(heading,&(dValu[i]),i,StaLProc);
					/////////////////////////////////////////////////////////
					if(nStatus == IDCANCEL)
						dValu[i] = 0.0;
				}
			}
			break;


		default:
			break;
	}
	///////////////////////////
	m_dTx = dValu[0];
	m_dTy = dValu[1];
	m_dTz = dValu[2];
	m_dRx = dValu[3];
	m_dRy = dValu[4];
	m_dRz = dValu[5];
	/////////////////
	return 0;
}

int CSLDObj::Get_Values_ManyDirections(CString& Nid,STALPROC StaLProc)
{
	CMStLMgr	Mgr;
	UINT		nStatus;
	/////////////////////
	BOOL		bKode[6];
	double		dValu[6];
	/////////////////////
	bKode[0]	= m_bTx;
	bKode[1]	= m_bTy;
	bKode[2]	= m_bTz;
	bKode[3]	= m_bRx;
	bKode[4]	= m_bRy;
	bKode[5]	= m_bRz;
	///////////////////////////
	dValu[0]	= m_dTx;
	dValu[1]	= m_dTy;
	dValu[2]	= m_dTz;
	dValu[3]	= m_dRx;
	dValu[4]	= m_dRy;
	dValu[5]	= m_dRz;
	/////////////////////
	nStatus = Mgr.DoModal_ManyValue_In(Nid,dValu,bKode,StaLProc);
	/////////////////////////////////////////////////////////
	if(nStatus == IDCANCEL)
		return -2;
	///////////////////////////
	m_dTx = dValu[0];
	m_dTy = dValu[1];
	m_dTz = dValu[2];
	m_dRx = dValu[3];
	m_dRy = dValu[4];
	m_dRz = dValu[5];
	/////////////////
	return 0;
}

int CSLDObj::Get_Values_Iso_WORLD(CString& wid,WORLD& NodeT,WORLD& NodeR, STALPROC StaLProc)
{
	/////////////////////////////////////// GetValues
	int nResult = Get_Values_ManyDirections(wid,StaLProc);
	///////////////////////////////////////
	if(nResult<0)
		return nResult; 
	/////////////////////////////////////// LocalPos for Node as Forces/Moments
	NodeT.x	= m_dTx;
	NodeT.y	= m_dTy;
	NodeT.z	= m_dTz;
	NodeR.x	= m_dRx;
	NodeR.y	= m_dRy;
	NodeR.z	= m_dRz;
	/////////////
	return 0;
}

void CSLDObj::Serialize(CArchive& ar)
{

	CObject::Serialize( ar);              // must call base class Serializer
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" SLDMousO:    Storing\n");	
		
 			/////////////////////////////////////////////////

	}
	else
	{
		TRACE(" SLDMousO:    Loading\n");	

			/////////////////////////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////////// end of Module //////////////////////		


