
void CPatMouse::UpdatePDlg_FALSE_EXTRUDE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Extrusion: Click in@A Curve To Extrude";
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->
																SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			/////
			break;
		case 1:
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Extrusion: Click in@Ist (C)Node defining Extrusion Direction";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Extrusion: Click in@2nd (C)Node defining Extrusion Direction";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node To");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
}

void CPatMouse::UpdatePDlg_FALSE_ROTATE()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Rotation: Click in@A Curve To Rotate";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////////////////////////////
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////////////////////////////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->
																SetWindowText("Rotnl.Curve");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
 			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			/////
			break;
		case 1:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Rotation: Click in@Ist (C)Node defining Rotation Axis";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 2:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Rotation: Click in@2nd (C)Node defining Rotation Axis";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node To");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 3:
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bClosed	= m_bClosed;
			if(m_bClosed)
				m_dLen = 360.;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_dLen		= m_dLen;
			/////
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

void CPatMouse::UpdatePDlg_FALSE_LOFT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Loft Patch:@Provide Number of Curves";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_LoftCurveCount(m_nCurves_U) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
				return;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ORIENT)))->EnableWindow(FALSE);
			/////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_SegAngle	= m_SegAngle;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_bAutoSeg	= m_bAutoSeg;
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Curve# %d of %d Total Curves",
				m_nInfoDone+1,m_nCurves_U);
			//////////////////
			strCurr = "Loft Patch: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:	// fall thro'		
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<m_nCurves_U)
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Curve# %d of %d Total Curves",
					m_nInfoDone+1,m_nCurves_U);
				//////////////////
				strCurr = "Loft Patch: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Loft Patch: Provide B.C. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return;
				}
				///////////////////////////////
				strCurr = "Loft Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

void CPatMouse::UpdatePDlg_FALSE_TENSOR()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Tensor Product Patch:@Provide Number of Nodes";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_TensorNodeCount(m_nNodes_U,m_nNodes_V) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
					return;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_NID		= "";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh		= m_ElPerSeg;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio		= m_Ratio;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_nMesh_V	= m_ElPerSeg_V;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_Ratio_V	= m_Ratio_V;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("NODE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			///
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Node# %d of %d Total Nodes(%dX%d)",
				m_nInfoDone+1,(m_nNodes_U*m_nNodes_V),m_nNodes_U,m_nNodes_V);
			//////////////////
			strCurr = "Tensor Product: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		default:
			if(m_nInfoDone<(m_nNodes_U*m_nNodes_V))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Node# %d of %d Total Nodes(%dX%d)",
					m_nInfoDone+1,(m_nNodes_U*m_nNodes_V),m_nNodes_U,m_nNodes_V);
				//////////////////
				strCurr = "Tensor Product: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Tensor Product: Provide B.C. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return;
				}
				///////////////////////////////
				strCurr = "Tensor Product Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

void CPatMouse::UpdatePDlg_FALSE_GORDON()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	CMPatMgr MPatMgr;
	CString* pstrNode;
	char* buf;
	///////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	//////////////////////////////////////
	switch(m_nInfoDone)
	{
		case 0:	// need minimum of 2	
			/////////////////////////////////////// GetMatrix Info.
			strCurr = "Gordon Patch:@Provide Number of Curves";
			pWnd->SetstrCurrID(strCurr);
			pWnd->UpdateCurrStat(strCurr);
			//////////////////////////////
			if(MPatMgr.DoModal_Patch_GordonCurveCount(m_nCurves_U,m_nCurves_V) == IDCANCEL)
			{
				//////////////////////////////
				Terminate_PAT(TRUE);
				return;
			}
			else
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
			{
				pWnd->GetMouseMgr()->SetCurrentProcessDone(FALSE);
				/////////////////////
				ResetVariables_PAT();
				m_bPatchDone		= FALSE;	  // 
			}
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->
											GetDlgItem(IDC_ADVANCED)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PatProc	= m_PatProc;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_PID		= m_CurrentPatchID;
			((CBasePage*)(GetPatSheet()->GetActivePage()))->m_CID		= "";
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("CURVE");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			////////////////////////////////
			pstrNode	= new CString;
			buf			= pstrNode->GetBuffer(BUFF_SIZE);
			sprintf(buf,"@Curve# %d of %d Total Curves(%dX%d)",
				m_nInfoDone+1,(m_nCurves_U+m_nCurves_V),m_nCurves_U,m_nCurves_V);
			//////////////////
			strCurr = "Gordon: Left Click in ";
			strCurr += buf;
			delete pstrNode;
			//////
			break;
		case 1:	// fall thro'		
			///
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->EnableWindow(TRUE);
			if(m_Orient == "FORWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
			else
			if(m_Orient == "BACKWARD")
				((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->
								GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
			/////
		default:
			if(m_nInfoDone<(m_nCurves_U+m_nCurves_V))
			{
				pstrNode	= new CString;
				buf			= pstrNode->GetBuffer(BUFF_SIZE);
				sprintf(buf,"@Curve# %d of %d Total Curves(%dX%d)",
				m_nInfoDone+1,(m_nCurves_U+m_nCurves_V),m_nCurves_U,m_nCurves_V);
				//////////////////
				strCurr = "Gordon: Left Click in ";
				strCurr += buf;
				delete pstrNode;
			}
			else
			if(m_bEndCondMode)
			{
				strCurr = "Gordon Patch: Provide Twist Info. for the Iso-Curve.";
				strCurr +="@Done with it? Please Click On Update Button";
			}
			else
			{
				///////////////////////////////////////
				if(GetPatSheet()->GetSafeHwnd() != 0)	//  already created
					GetPatSheet()->DestroyWindow();
				///////////////////////////////////////// Set Tensor Primary Page back
				GetPatSheet()->SetEndCondMode(FALSE);
				///////////////////////////////////////// Create
				if(GetPatSheet()->SetProcPage() != MA_OK) 
				{
					AfxMessageBox(
						"Internal ERROR:\nCPatMouse::UpdatePDlg_FALSE()\n!GetPatSheet()->Create()");
					return;
				}
				///////////////////////////////
				strCurr = "Gordon Patch: ";
				strCurr +="@Ready with other Info.? Click Right Button";
			}
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
	////////////////////////////////////////////////
	if(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetSafeHwnd())
		((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	((CBasePage*)(GetPatSheet()->GetActivePage()))->UpdateData(FALSE); // To screen
	////////////////////////////////////////////////
}

void CPatMouse::UpdatePDlg_FALSE_COONS()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
			((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Coons Method:@Click in The First Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Ist Curve");
			break;
		case 1:
			strCurr = "Patch by Coons Method:@Click in The 2nd Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("2nd Curve");
			break;
		case 2:
			strCurr += "Patch by Coons Method:@Click in The 3rd Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("3rd Curve");
			break;
		case 3:
			strCurr = "Quadrilateral: Select Last Curve@ Triangle: Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Last Curve");
			break;
		case 4:
			strCurr = "Quadrilateral Patch:@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

void CPatMouse::UpdatePDlg_FALSE_DUCT()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr = "Patch by Ducting:@Click in Cross Sectional Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. CurveID");
			break;
		case 1:
			strCurr = "Patch by Ducting:@Click in Spine Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine CurveID");
			break;
		case 2:
			strCurr = "Patch by Ducting:@Click in Twist Distribution Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Twist CurveID");
			break;
		case 3:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Ducting:@Click in Anchor Node";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 4:
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

void CPatMouse::UpdatePDlg_FALSE_SWEEP()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCurr;
	//////////////////////////////////////
	if(m_Orient == "FORWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(0);//FORWARD=0
	else
	if(m_Orient == "BACKWARD")
		((CComboBox*)(((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_ORIENT)))->SetCurSel(1);//BACKWARD=1
	///////////////////
	switch(m_nInfoDone)
	{
		case 0:
			strCurr += "Patch by Sweeping:@Click in Cross Sectional Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Curve");
			break;
		case 1:
			strCurr += "Patch by Sweeping:@Click in Spine Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Spine Curve");
			break;
		case 2:
			strCurr = "Patch by Sweeping:@Click in Twist Distribution Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Twist Curve");
			break;
		case 3:
			strCurr = "Patch by Sweeping:@Click in Radial Distribution Curve";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("Radius Curve");
			break;
		case 4:
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			//////
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_OTHER)->SetWindowText("Z");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
			//////
			strCurr = "Patch by Sweeping:@Click in Anchor Node";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			break;
		case 5:
			strCurr = "Ready with other Info.?@Click Right Button";
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			((CBasePage*)(GetPatSheet()->GetActivePage()))->GetDlgItem(IDC_NID)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
	/////////////////////////////////////////////// CurrStat: Show
	pWnd->SetstrCurrID(strCurr);
	pWnd->UpdateCurrStat(strCurr);
}

