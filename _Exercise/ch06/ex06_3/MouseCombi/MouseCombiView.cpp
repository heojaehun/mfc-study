
// MouseCombiView.cpp : implementation of the CMouseCombiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MouseCombi.h"
#endif

#include "MouseCombiDoc.h"
#include "MouseCombiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseCombiView

IMPLEMENT_DYNCREATE(CMouseCombiView, CView)

BEGIN_MESSAGE_MAP(CMouseCombiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_WM_MOUSEMOVE()
ON_WM_PAINT()
ON_WM_CREATE()
//ON_WM_MOUSELEAVE()
//ON_WM_NCMOUSEMOVE()
//ON_WM_NCMOUSEHOVER()
//ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

// CMouseCombiView construction/destruction

CMouseCombiView::CMouseCombiView() noexcept
{
	// TODO: add construction code here
	m_bDragFlag = false;
}

CMouseCombiView::~CMouseCombiView()
{
}

BOOL CMouseCombiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMouseCombiView drawing

void CMouseCombiView::OnDraw(CDC* /*pDC*/)
{
	CMouseCombiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMouseCombiView printing

BOOL CMouseCombiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMouseCombiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMouseCombiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMouseCombiView diagnostics

#ifdef _DEBUG
void CMouseCombiView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseCombiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseCombiDoc* CMouseCombiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseCombiDoc)));
	return (CMouseCombiDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseCombiView message handlers


void CMouseCombiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_bDragFlag = true;

	CView::OnLButtonDown(nFlags, point);
}


void CMouseCombiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	m_bDragFlag = false;

	CView::OnLButtonUp(nFlags, point);
}


void CMouseCombiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDblClk(nFlags, point);
}


void CMouseCombiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragFlag)
		RedrawWindow();

	CView::OnMouseMove(nFlags, point);
}


void CMouseCombiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages

	CString str;
	char strClassName[128];
	
	if (m_bDragFlag)
	{
		GetCursorPos(&m_ptPos);

		str.Format(TEXT("X: %03d"), m_ptPos.x);
		dc.TextOutW(10, 10, str);

		str.Format(TEXT("Y: %03d"), m_ptPos.y);
		dc.TextOutW(10, 30, str);
				
		m_hPointWnd = ::WindowFromPoint(m_ptPos);
		GetClassName(m_hPointWnd, (LPWSTR)(LPCSTR)strClassName, 128);
		str.Format(TEXT("HWND: %d"), m_hPointWnd);
		dc.TextOutW(10, 50, str);

		str.Format(TEXT("Class Name: %s"), strClassName);
		dc.TextOutW(10, 70, str);
		
	}
	else
	{
		str.Format(TEXT("X: ---"));
		dc.TextOutW(10, 10, str);

		str.Format(TEXT("Y: ---"));
		dc.TextOutW(10, 30, str);

		str.Format(TEXT("HWND: ---"));
		dc.TextOutW(10, 50, str);

		str.Format(TEXT("Class Name: ---"));
		dc.TextOutW(10, 70, str);
	}
}


int CMouseCombiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}
