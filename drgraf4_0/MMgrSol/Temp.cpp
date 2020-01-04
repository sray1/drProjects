int CMS_Duct::GoDoIt 
				(
					BOOL							bGenBCurve,
					BOOL							bGenBPatch,
					int								nTwistType,
									// 1 = Given: Twist Distribution
									// 2 = Given: Twist Increments etc
					//////////////////////////////////////////
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// given Spine Curve
					CList<CURVELATCH,CURVELATCH>*	pCLatchList,
					//////////////////////////////////////////
					CDListMgr*						pPatchList,	// given Xsec. Patch always taken as UV-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<PATCHLATCH,PATCHLATCH>*	pPLatchList,
					//////////////////////////////////////////
					CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
					double							TwistMult,	// if nTwistType = 2 
					BOOL							bIncrement,
					double							TwistStart,
					//////////////////////////////////////////////
					CView*							pView
				) 
//////////////////////////////////////////////////////////////////////////////////// PreProcess
BOOL CMS_Duct::IsDataCompatible(CDListMgr* pNodeList,
					CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>*	pCLatchList,
					CDListMgr* pPatchList,CList<PATCHLATCH,PATCHLATCH>*	pPLatchList,
									CList<double,double>* pTwistList,int nTwistType)
int CMS_Duct::TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
																		BOOL bIncremental)
int CMS_Xtrud::SetSolidDataFromPatch(CDrPatch* pPatch)
int CMS_Duct::GetPatCNodeCoords_N_Wts_XSection(CDrPatch* pPatch, PATCHLATCH pLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
int CMS_Duct::GetSolidInfoFromSpine_R(CDrCurve* pCurve)
int CMS_Duct::GetCNodeCoords_N_WtsAtJnPts_Spine(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
int CMS_Duct::CreateTangentsAtJnPts_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents)
int CMS_Duct::SolCNCoords_N_WtsAtJns(WORLD wAnchorPt,pWORLD pPatConBZ_ST,pDOUBLE pWtsBZ_ST,int nPatConBZ_ST,
										pWORLD pConJnBZ_R,pWORLD pTanJnBZ_R,int nConJnBZ_R,pDOUBLE pTwist,
																pWORLD pSolCons,pDOUBLE pSolWts,int nTotOut)
int CMS_Duct::PostSolBezInfoUsingBlendingInfo(CDrSolid* pSolid,CDrCurve* pSpineCurve,
								pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ_S,,int nConBZ_T
												int nPatches/*nConBZJn_R*/,int nConBZ_R)
int CMS_Duct::PostPatBezInfo(CDrSolid* pSolid,CDListMgr& TemCNodeList,pDOUBLE pTemSolWts_BZ,
															int nCon_S,int nCon_T,int nCon_R)
int CMS_Duct::TempPostSolBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ_ST,int nRowCol,
												int nPatches,CDListMgr* pINodeList)
int CMS_Duct::PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ_ST,int nRowCol,
												int nPatches,pDOUBLE pTemWts_BZ)
int CMS_Duct::GeneratePatchBezInfoFromSpineCurve(
						BLENDEND BlendEnd,CDrCurve* pSpineCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pSolCNodeList,
						pDOUBLE pSolWts_BZ,double Ratio,CString& SolidID,int nCon_R,int nRowCol)
int CMS_Duct::Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pSolCNodeList,
														CString& SolidID,int nRowCol)
int CMS_Duct::Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_R,int nRowCol)
int CMS_Duct::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pPatchList_U,CDListMgr* pCurveList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
)
void CMS_Duct::SetInfoForDataBase_1(CDrSolid* pDrObject,
					CDListMgr* pCurveList_W,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CDListMgr* pPatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pCurveLatchList_U,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
)
///////////////////////////////// end of module ///////////////////
