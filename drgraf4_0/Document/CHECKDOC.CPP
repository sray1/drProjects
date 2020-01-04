// checkdoc.cpp : implementation of the CChkBookDoc class
#include "stdafx.h"
#include "chkbook.h"

#define FIRST_CHECK_NO 101
#define CHECK_BOOK_FILE_SIGNATURE 0x6f7e471d

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Operations, called by book view and check view

void CChkBookDoc::GetCheck(UINT nCheckNo, DWORD& dwCents, CString& strPayTo,
		CString& strDate, CString& strMemo)
{
	UINT nRecord = CheckNoToRecordIndex(nCheckNo);
	GetRecord(nRecord, &m_record);
	ParseRecord(dwCents, strPayTo, strDate, strMemo);
}


void CChkBookDoc::UpdateCheck(CView* pSourceView, UINT nCheckNo,
		DWORD dwCents, const char* szPayTo, const char* szDate,
		const char* szMemo)
{
	UINT nRecord = CheckNoToRecordIndex(nCheckNo);
	PackRecord(dwCents, szPayTo, szDate, szMemo);
	UpdateRecord(pSourceView, nRecord, &m_record);
}

void CChkBookDoc::ChangeSelectionNextCheckNo(BOOL bNext)
{
	if (bNext)
	{
		if (m_nActiveRecord < (GetRecordCount() - 1))
		{
			if (!MaybeCommitDirtyCheck())
				return;
			UpdateAllViewsWithRecord(NULL, ++m_nActiveRecord);
		}
	}
	else
	{
		if (m_nActiveRecord > 0)
		{
			if (!MaybeCommitDirtyCheck())
				return;
			UpdateAllViewsWithRecord(NULL, --m_nActiveRecord);
		}
	}
}

void CChkBookDoc::ChangeSelectionToCheckNo(UINT nNewActiveCheckNo)
{
	if (!MaybeCommitDirtyCheck())
		return;
	m_nActiveRecord = CheckNoToRecordIndex(nNewActiveCheckNo);
	UpdateAllViewsWithRecord(NULL, m_nActiveRecord);
}
/////////////////////////////////////////////////////////////////////////////
// Implementation

void CChkBookDoc::PackRecord(DWORD dwCents, const char* szPayTo,
			const char* szDate, const char* szMemo)
{
	m_record.dwCents = dwCents;
	strncpy(m_record.szPayTo, szPayTo, sizeof(m_record.szPayTo) - 1);
	m_record.szPayTo[sizeof(m_record.szPayTo) - 1] = 0;
	strncpy(m_record.szDate, szDate, sizeof(m_record.szDate) - 1);
	m_record.szDate[sizeof(m_record.szDate) - 1] = 0;
	strncpy(m_record.szMemo, szMemo, sizeof(m_record.szMemo) - 1);
	m_record.szMemo[sizeof(m_record.szMemo) - 1] = 0;

}

void CChkBookDoc::ParseRecord(DWORD& dwCents, CString& strPayTo,
			CString& strDate, CString& strMemo)
{
	dwCents = m_record.dwCents;
	strPayTo = m_record.szPayTo;
	strDate = m_record.szDate;
	strMemo = m_record.szMemo;
}

UINT CChkBookDoc::CheckNoToRecordIndex(UINT nCheckNo)
{
	return (nCheckNo - m_extraHeader.nFirstCheckNo);
}

UINT CChkBookDoc::RecordIndexToCheckNo(UINT nRecordIndex)
{
	return (nRecordIndex + m_extraHeader.nFirstCheckNo);
}

UINT CChkBookDoc::GetActiveCheckNo()
{
	return (m_nActiveRecord + m_extraHeader.nFirstCheckNo);
}

UINT CChkBookDoc::GetFirstCheckNo()
{
	return m_extraHeader.nFirstCheckNo;
}

UINT CChkBookDoc::GetLastCheckNo()
{
	return (m_extraHeader.nFirstCheckNo + GetRecordCount() - 1);
}

/////////////////////////////////////////////////////////////////////////////
// CChkBookDoc commands

void CChkBookDoc::NewCheck()
{
	// Before creating a new record, which will become the new selection,
	// ask the user whether she wants to commit data entered in the
	// check view for the previously selected check.

	if (!MaybeCommitDirtyCheck())
		return;

	m_nActiveRecord = CreateNewRecord();
}

void CChkBookDoc::OnNextCheck()
{
	ChangeSelectionNextCheckNo(TRUE);
}

void CChkBookDoc::OnUpdateNextCheck(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nActiveRecord < (GetRecordCount() - 1));
}

void CChkBookDoc::OnPrevCheck()
{
	ChangeSelectionNextCheckNo(FALSE);
}

void CChkBookDoc::OnUpdatePrevCheck(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nActiveRecord > 0);

}
