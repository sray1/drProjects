int CRat_Twist4::MakeTwists		// RATIONAL BEZIER Patches
			(
					BOOL		bClosed_U	//  IsClosed_U
				,	int			nDegree_U	//  Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		//  3= NonRational / 4 = Rational
				,	int			nCon_U		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_U	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_U		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
				,	BOOL		bClosed_V	//  IsClosed_V
				,	int			nDegree_V	//  Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		//  3= NonRational / 4 = Rational
				,	int			nCon_V		//  number of CONTROL points: ALWAYS BEZIER
				,	int			nPatches_V	//  Total Number of Patches in U-dir 
				,	pINT		Num_t_V		//  Number of Segments for each Patch Array 
				,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
				,	pDOUBLE		pWts_UV		//  Total Input Rational Bezier Weights Array		
				,	pWORLD		pCon_UV		//  Total Input CONTROL Points Array
				,	pWORLD		pOut_UV		//  Total Output Tangent Array
			)
int CRat_Twist4::Make_Twists_A_Patch
			(
					pWORLD		pOldCon		//	Control Pt. array for the patch
				,	pDOUBLE		pOldWts		//	Wts. array for the patch	
				,	BOOL		bLast_U		//  Last Patch in V-Dir for Output saving decision
				,	int			nDegree_U	// 	Degree in U-direction: ALWAYS BEZIER
				,	int			nDim_U		// 	3= NonRational / 4 = Rational
				,	int			nt_U		// 	# of subdivision to compute Surface Pts in U-dir
				,	pDOUBLE		Dis_t_U		// Output t distribution Pts.				
				,	BOOL		bLast_V		// 	Last Patch in V-Dir for Output saving decision		
				,	int			nDegree_V	// 	Degree in V-direction: ALWAYS BEZIER
				,	int			nDim_V		// 	3= NonRational / 4 = Rational
				,	int			nt_V		// 	# of subdivision to compute Surface Pts in V-dir
				,	pDOUBLE		Dis_t_V		// Output t distribution Pts.				
				,	pWORLD		pOut		// 	Total Output Tangent Array
//				,	pDOUBLE		pOutWts		// 	Total Output Wts Array
				,	int			nEmitTot_U	//  Total Points for All Patches in U-dir
				,	int			nPatches_U	//  Total Number of Patches in U-dir, needed for t-Dist 
				,	int			nPatches_V	//  Total Number of Patches in V-dir, needed for t-Dist 
			)
int CRat_Twist4::GetaTwistAtaControlNode(WORLD wNodeCoord,WORLD& Twist,
								int nDegree_U,int nPatches_U,int nCon_U,int nDim_U,
								int nDegree_V,int nPatches_V,int nCon_V,int nDim_V,
//								pDOUBLE pWts_UV,pWORLD pCon_UV)
								pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio)
int CRat_Twist4::GetCurrentPatch_N_Controls(WORLD wNodeCoord,
					int& nCtrl_i,int& nCtrl_j,
					int nDegree_U,int nPatches_U,int nCon_U,
					int nDegree_V,int nPatches_V,int nCon_V,
//					pDOUBLE pWts_UV,pWORLD pCon_UV)
					pDOUBLE pWts_UV,pWORLD pCon_UV,double dSameNessRatio,
					pWORLD B, pDOUBLE W)
int CRat_Twist4::GetBezPatCornerTwist_00(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
int CRat_Twist4::GetBezPatCornerTwist_01(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
int CRat_Twist4::GetBezPatCornerTwist_10(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
int CRat_Twist4::GetBezPatCornerTwist_11(WORLD& Twist,
					int nDegree_U,int nDegree_V,pWORLD B, pDOUBLE W)
int CRat_Twist4::CalcCornerTwist(WORLD& Twist,int i00,int i10,int i01,int i11,
														pWORLD B, pDOUBLE W)
int CRat_Twist4::Rat_SubDivide_U(pWORLD Cons, pDOUBLE Wts, double u, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
int CRat_Twist4::Rat_SubDivide_V(pWORLD Cons, pDOUBLE Wts, double u,  
					pWORLD NewC, pDOUBLE NewW, BOOL bLeft, int nOrderU, int nOrderV)
int CRat_Twist4::Rat_SubDivide_UV(pWORLD Cons, pDOUBLE Wts, double u, double v, 
								pWORLD NewC, pDOUBLE NewW, BOOL bLeftU, BOOL bLeftV, 
								int nDegreeU, int nDegreeV)
/////////////////////////////////// end of module /////////////////
