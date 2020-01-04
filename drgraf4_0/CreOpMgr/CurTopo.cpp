// DrCurves.cpp : implementation of the CCurve_3 class
//

#include "stdafx.h"
///////////////////
#include "CurTopo.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNAMIC(CCurTopo, CObject)
//////////////////// 
CCurTopo::CCurTopo()
{
} 

int CCurTopo::SpawnConnectedCurves_CopyOff(CDrCurve* pCurrentCurve,BOOL bUsingDlg,
												CDListMgr* pNDoneList,CDListMgr* pCDoneList)
{
	// Walk the graph connected to the given curve
	////////////////
	int nResult = 0;
	////////////////
	int index	= pCDoneList->GetObjectIndex(pCurrentCurve);
	if(index<0) // NOT DONE yet
	{
		/////////////////////////////////////////////////////////// Spawn End Nodes(NodTopoList)
		CDListMgr* pNodList;
		int i,nNodCount;
		POSITION pos;
		//////////////////////////////////////////////// Curves
		pNodList	= pCurrentCurve->GetNodTopoList(); 
		nNodCount	= pNodList->GetCount();
		///////////
		for(i=0;i<nNodCount;i++)
		{
			pos					= pNodList->FindIndex(i);
			CDrNode* pEndNode	= (CDrNode*)(pNodList->GetAt(pos));
			int index			= pNDoneList->GetObjectIndex(pEndNode);
			if(index<0) // NOT DONE yet
			{
				nResult = NodeSpawnCopyOff(pEndNode,bUsingDlg);
				///
				if(nResult == -1)
				{
					AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_1");
					return nResult;
				}
				pNDoneList->InsertObject(pEndNode);
			}
		}
		/////////////////////////////////////////////////////////// Spawn Curve(rest of Lists)
		nResult = ShowCurveToSpawnCopyOff(pCurrentCurve,bUsingDlg);
		if(nResult == -1)
		{
			AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_2");
			return nResult;
		}
		pCDoneList->InsertObject(pCurrentCurve);
	}
	/////////////////////////////////////////////////////////// XForm Connecting CURVES
	CDListMgr* pCurList;
	int i,nCurCount;
	POSITION pos;
	//////////////////////////////////////////////// Curves
	pCurList	= pCurrentCurve->GetCurveList(); 
	nCurCount	= pCurList->GetCount();
	///////////
	for(i=0;i<nCurCount;i++)
	{
		pos					= pCurList->FindIndex(i);
		CDrCurve* pCurve	= (CDrCurve*)(pCurList->GetAt(pos));
		int index			= pCDoneList->GetObjectIndex(pCurve);
		if(index<0) // NOT DONE yet
		{
			//////////////////////////////////////////////////////////////////////// recursion
			int nResult = CurTopo_SpawnConnectedCurves_CopyOff(pCurve,bUsingDlg,pNDoneList,pCDoneList);
			if(nResult == -1)
			{
				AfxMessageBox("Internal ERROR\nCNodCreOp::CurTopo_SpawnConnectedCurves_CopyOff_3");
				return nResult;
			}
		}
	}
	///////
	return nResult;
}

////////////////////////////////// end of module ///////////////////// 

