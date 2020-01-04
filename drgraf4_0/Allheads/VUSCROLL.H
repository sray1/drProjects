
/////////////////////////////////////////////////////////////////////////////
// class CDrScrollVu supports simple scrolling and scaling
#ifndef	_DRSCROLLVU
#define _DRSCROLLVU 
                    

class CDrScrollVu : public CView
{
        DECLARE_DYNAMIC(CDrScrollVu)

// Constructors
protected:
        CDrScrollVu();

public:
        static const SIZE AFXAPI_DATA sizeDefault;
                // used to specify default calculated page and line sizes

        // in logical units - call one of the following Set routines
        void SetScaleToFitSize(SIZE sizeTotal);
        void SetScrollSizes(int nMapMode, SIZE sizeTotal,
                                const SIZE& sizePage = sizeDefault,
                                const SIZE& sizeLine = sizeDefault);

// Attributes
public:
        CPoint GetScrollPosition() const;       // upper corner of scrolling
        CSize GetTotalSize() const;             // logical size

        // for device units
        CPoint GetDeviceScrollPosition() const;
        void GetDeviceScrollSizes(int& nMapMode, SIZE& sizeTotal,
                        SIZE& sizePage, SIZE& sizeLine) const;

// Operations
public:
        void ScrollToPosition(POINT pt);    // set upper left position
        void FillOutsideRect(CDC* pDC, CBrush* pBrush);
        void ResizeParentToFit(BOOL bShrinkOnly = TRUE);

// Implementation
protected:
        int m_nMapMode;
        CSize m_totalLog;         // total size in logical units (no rounding)
        CSize m_totalDev;         // total size in device units
        CSize m_pageDev;          // per page scroll size in device units
        CSize m_lineDev;          // per line scroll size in device units

        BOOL m_bCenter;          // Center output if larger than total size
        BOOL m_bInsideUpdate;    // internal state for OnSize callback
        void CenterOnPoint(CPoint ptCenter);
        void ScrollToDevicePosition(POINT ptDev); // explicit scrolling no checking

protected:
        virtual void OnDraw(CDC* pDC) = 0;      // pass on pure virtual
        virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

        void UpdateBars(); // adjust scrollbars etc
        BOOL GetTrueClientSize(CSize& size, CSize& sizeSb); // size with no bars
public:
        virtual ~CDrScrollVu();
#ifdef _DEBUG
        virtual void Dump(CDumpContext&) const;
        virtual void AssertValid() const;
#endif //_DEBUG

        void OnScroll(int nBar, UINT nSBCode, UINT nPos);
        //{{AFX_MSG(CDrScrollVu)
        afx_msg void OnSize(UINT nType, int cx, int cy);
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};
#endif
/////////////////////////////////////////////////////////////////////////////
