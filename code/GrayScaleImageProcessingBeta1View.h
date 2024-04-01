
// GrayScaleImageProcessingBeta1View.h: CGrayScaleImageProcessingBeta1View 클래스의 인터페이스
//

#pragma once


class CGrayScaleImageProcessingBeta1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingBeta1View() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingBeta1View)

// 특성입니다.
public:
	CGrayScaleImageProcessingBeta1Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGrayScaleImageProcessingBeta1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnGrayImage();
	afx_msg void OnReverseImage();
	afx_msg void OnAddImage();
	afx_msg void OnDarkImage();
	afx_msg void OnGammaImage();
	afx_msg void OnParabolCap();
	afx_msg void OnParabolCup();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
	afx_msg void OnNotImage();
	afx_msg void OnEmboss();
	afx_msg void OnBlur();
	afx_msg void OnSharp();
	afx_msg void OnEdge1();
	afx_msg void OnZoomIn1();
	afx_msg void OnZoomIn2();
	afx_msg void OnZoomIn3();
	afx_msg void OnZoomOut();
	afx_msg void OnMove();
	afx_msg void OnRotate1();
	afx_msg void OnRotate2();
	afx_msg void OnRotate3();
	afx_msg void OnReverse1();
	afx_msg void OnReverse2();
	afx_msg void OnHistoStretch();
	afx_msg void OnEndIn();
	afx_msg void OnHistoEqual();
};

#ifndef _DEBUG  // GrayScaleImageProcessingBeta1View.cpp의 디버그 버전
inline CGrayScaleImageProcessingBeta1Doc* CGrayScaleImageProcessingBeta1View::GetDocument() const
   { return reinterpret_cast<CGrayScaleImageProcessingBeta1Doc*>(m_pDocument); }
#endif

