// Elem.h : header file
//
#ifndef _ELDATAVW_H
#define _ELDATAVW_H       

#include "stdafx.h" 

#include "Elements.h"
/////////////////////////////////////////////////////////////////////////////
// CElDataVw  ///////////////////////////////////////////////////////////////
class CElDataVw: public CDrElem
{
public:
// Construction                 
	CElDataVw(){};
	DECLARE_DYNAMIC(CElDataVw)
	
// Operations
public:

			void 	Do_Element_DataView(CDC* PtrDC,int y,int nRowIndex);
	        void	Do_Element_DrawView(CDC*PtrDC,BOOL bPenChange,int nElemIndex,int nViewNumber);
	// overrides of CDrElem 
	// for DATAVIEW
	virtual	void	DoDataView(CDC* PtrDC,int y){};
	// for VIEW12,VIEW23 etc.
	virtual	void	DoDrawView(CDC* PtrDC,BOOL bPenChange,int nViewNumber){};
	virtual	int 	GetObjectType(){return (int)NULL;};
	virtual	UINT 	GetObjectNo(){return (UINT)NULL;};
//	virtual	int 	GetObjectIndex(){return (int)NULL;};
	virtual CRect	GetBoundingRect(){return (CRect)NULL;};
// Helper functions
pr	!��rTr!�sq�q!��q?q!�GgG	!��g�
!�MrM
!���
�] � �
%S*    ��
�S+    ��
R,    ��
�Q-    &�
&] � ^�
�| � i