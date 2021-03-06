
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
ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// CMouseCombiView construction/destruction

CMouseCombiView::CMouseCombiView() noexcept
{
	// TODO: add construction code here
	m_ptItemText = CPoint(10, 50);
	m_bDragFlag = false;
	m_bTrack = false;

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
	GetClientRect(&m_rcWindowSize);

	if (point.x >= m_ptItemText.x - 32 &&
		point.x <= m_ptItemText.x + 32 &&
		point.y >= m_ptItemText.y - 32 &&
		point.y <= m_ptItemText.y + 32)
	{
		SetCapture();
		m_bDragFlag = true;
		RedrawWindow();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMouseCombiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragFlag)
	{
		m_bDragFlag = false;

		//m_ptItemText = point;
		RedrawWindow();
		ReleaseCapture();
	}

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
	if (m_bTrack == false)
	{
		TRACKMOUSEEVENT MouseEvent;
		::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

		MouseEvent.cbSize = sizeof(MouseEvent);
		MouseEvent.dwFlags = TME_LEAVE;
		MouseEvent.hwndTrack = m_hWnd;
		MouseEvent.dwHoverTime = 0; 

		m_bTrack = ::_TrackMouseEvent(&MouseEvent);

		if (m_bTrack)
		{
			RedrawWindow();
		}
	}


	if (m_bDragFlag)
	{
		if (point.x > 0 && point.y > 0 && point.x < m_rcWindowSize.right - 32 && point.y < m_rcWindowSize.bottom - 32)
		{
			m_ptItemText = point;
			RedrawWindow();
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CMouseCombiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages

	if (m_bDragFlag)
		dc.TextOutW(10, 10, TEXT("DRAG"));
	else
		dc.TextOutW(10, 10, TEXT("----"));

	if (m_bTrack)
		dc.TextOutW(10, 30, TEXT("Mouse Tracking!"));
	else
		dc.TextOutW(10, 30, TEXT("Mouse Leave..."));

	dc.TextOutW(m_ptItemText.x, m_ptItemText.y, TEXT("내 컴퓨터"));
}


int CMouseCombiView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_wndTrack.Create(TEXT("STATIC"), TEXT("TRACK TEST"), WS_CHILD | WS_VISIBLE | WS_BORDER | SS_NOTIFY, CRect(200, 10, 400, 160), this, 1234);

	return 0;
}


void CMouseCombiView::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	TRACKMOUSEEVENT MouseEvent;
	::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

	MouseEvent.cbSize = sizeof(MouseEvent);
	MouseEvent.dwFlags = TME_CANCEL;
	MouseEvent.hwndTrack = m_hWnd;

	::_TrackMouseEvent(&MouseEvent);

	m_bTrack = false;
	RedrawWindow();

	CView::OnMouseLeave();
}
