
// GrayScaleImageProcessingBeta1View.cpp: CGrayScaleImageProcessingBeta1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingBeta1.h"
#endif

#include "GrayScaleImageProcessingBeta1Doc.h"
#include "GrayScaleImageProcessingBeta1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleImageProcessingBeta1View

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingBeta1View, CView)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingBeta1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleImageProcessingBeta1View::OnEqualImage)
	ON_COMMAND(IDM_GRAY_IMAGE, &CGrayScaleImageProcessingBeta1View::OnGrayImage)
	ON_COMMAND(IDM_REVERSE_IMAGE, &CGrayScaleImageProcessingBeta1View::OnReverseImage)
	ON_COMMAND(IDM_ADD_IMAGE, &CGrayScaleImageProcessingBeta1View::OnAddImage)
	ON_COMMAND(IDM_DARK_IMAGE, &CGrayScaleImageProcessingBeta1View::OnDarkImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CGrayScaleImageProcessingBeta1View::OnGammaImage)
	ON_COMMAND(IDM_PARABOL_CAP, &CGrayScaleImageProcessingBeta1View::OnParabolCap)
	ON_COMMAND(IDM_PARABOL_CUP, &CGrayScaleImageProcessingBeta1View::OnParabolCup)
	ON_COMMAND(IDM_AND_IMAGE, &CGrayScaleImageProcessingBeta1View::OnAndImage)
	ON_COMMAND(IDM_OR_IMAGE, &CGrayScaleImageProcessingBeta1View::OnOrImage)
	ON_COMMAND(IDM_XOR_IMAGE, &CGrayScaleImageProcessingBeta1View::OnXorImage)
	ON_COMMAND(IDM_NOT_IMAGE, &CGrayScaleImageProcessingBeta1View::OnNotImage)
	ON_COMMAND(IDM_EMBOSS, &CGrayScaleImageProcessingBeta1View::OnEmboss)
	ON_COMMAND(IDM_BLUR, &CGrayScaleImageProcessingBeta1View::OnBlur)
	ON_COMMAND(IDM_SHARP, &CGrayScaleImageProcessingBeta1View::OnSharp)
	ON_COMMAND(IDM_EDGE1, &CGrayScaleImageProcessingBeta1View::OnEdge1)
	ON_COMMAND(IDM_ZOOM_IN1, &CGrayScaleImageProcessingBeta1View::OnZoomIn1)
	ON_COMMAND(IDM_ZOOM_IN2, &CGrayScaleImageProcessingBeta1View::OnZoomIn2)
	ON_COMMAND(IDM_ZOOM_IN3, &CGrayScaleImageProcessingBeta1View::OnZoomIn3)
	ON_COMMAND(IDM_ZOOM_OUT, &CGrayScaleImageProcessingBeta1View::OnZoomOut)
	ON_COMMAND(IDM_MOVE, &CGrayScaleImageProcessingBeta1View::OnMove)
	ON_COMMAND(IDM_ROTATE1, &CGrayScaleImageProcessingBeta1View::OnRotate1)
	ON_COMMAND(IDM_ROTATE2, &CGrayScaleImageProcessingBeta1View::OnRotate2)
	ON_COMMAND(IDM_ROTATE3, &CGrayScaleImageProcessingBeta1View::OnRotate3)
	ON_COMMAND(IDM_REVERSE1, &CGrayScaleImageProcessingBeta1View::OnReverse1)
	ON_COMMAND(IDM_REVERSE2, &CGrayScaleImageProcessingBeta1View::OnReverse2)
	ON_COMMAND(IDM_HISTO_STRETCH, &CGrayScaleImageProcessingBeta1View::OnHistoStretch)
	ON_COMMAND(IDM_END_IN, &CGrayScaleImageProcessingBeta1View::OnEndIn)
	ON_COMMAND(IDM_HISTO_EQUAL, &CGrayScaleImageProcessingBeta1View::OnHistoEqual)
END_MESSAGE_MAP()

// CGrayScaleImageProcessingBeta1View 생성/소멸

CGrayScaleImageProcessingBeta1View::CGrayScaleImageProcessingBeta1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingBeta1View::~CGrayScaleImageProcessingBeta1View()
{
}

BOOL CGrayScaleImageProcessingBeta1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleImageProcessingBeta1View 그리기

void CGrayScaleImageProcessingBeta1View::OnDraw(CDC* pDC)
{
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//unsigned char R, G, B;
	//for (int i = 0; i < pDoc->m_inH; i++) {
	//	for (int k = 0; k < pDoc->m_inW; k++) {
	//		R = G = B = pDoc->m_inImage[i][k];
	//		pDC->SetPixel(k + 5, i + 5, RGB(R, G, B));
	//	}
	//}
	//for (int i = 0; i < pDoc->m_outH; i++) {
	//	for (int k = 0; k < pDoc->m_outW; k++) {
	//		R = G = B = pDoc->m_outImage[i][k];
	//		pDC->SetPixel(k + 10 + pDoc->m_inW, i + 5, RGB(R, G, B));
	//	}
	//}
	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();


}


// CGrayScaleImageProcessingBeta1View 인쇄

BOOL CGrayScaleImageProcessingBeta1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleImageProcessingBeta1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleImageProcessingBeta1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleImageProcessingBeta1View 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingBeta1View::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleImageProcessingBeta1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleImageProcessingBeta1Doc* CGrayScaleImageProcessingBeta1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleImageProcessingBeta1Doc)));
	return (CGrayScaleImageProcessingBeta1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleImageProcessingBeta1View 메시지 처리기


void CGrayScaleImageProcessingBeta1View::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnGrayImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnReverseImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverseImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE); // OnDraw() 호출 효과

}


void CGrayScaleImageProcessingBeta1View::OnDarkImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDarkImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnParabolCap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolCap();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnParabolCup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolCup();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnNotImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNotImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnEmboss()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmboss();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharp();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnEdge1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdge1();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnZoomIn1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn1();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnZoomIn2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnZoomIn3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn3();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnZoomOut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOut();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnMove()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMove();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnRotate1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate1();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnRotate2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnRotate3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate3();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnReverse1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverse1();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnReverse2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnReverse2();
	Invalidate(TRUE); // OnDraw() 호출 효과
}

void CGrayScaleImageProcessingBeta1View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnEndIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndIn();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingBeta1View::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingBeta1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE); // OnDraw() 호출 효과
}
