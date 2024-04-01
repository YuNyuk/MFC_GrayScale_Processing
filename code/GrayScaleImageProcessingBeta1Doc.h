
// GrayScaleImageProcessingBeta1Doc.h: CGrayScaleImageProcessingBeta1Doc 클래스의 인터페이스
//


#pragma once


class CGrayScaleImageProcessingBeta1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingBeta1Doc() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingBeta1Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGrayScaleImageProcessingBeta1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImage = NULL;
	// // 출력 영상 2차원 배열
	unsigned char** m_outImage = NULL;
	int m_inH;
	int m_inW;
	int m_outH;
	int m_outW;
	unsigned char** OnMalloc2D(int h, int w, int initVal);
	void OnFree2D(unsigned char** memory, int h);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnGrayImage();
	void OnReverseImage();
	void OnAddImage();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnDarkImage();
	void OnGammaImage();
	void OnParabolCap();
	void OnParabolCup();
	void OnAndImage();
	void OnOrImage();
	void OnXorImage();
	void OnNotImage();
	void OnEmboss();
	void OnBlur();
	void OnSharp();
	void OnEdge1();
	void OnZoomIn1();
	void OnZoomIn2();
	void OnZoomIn3();
	void OnZoomOut();
	void OnMove();
	void OnRotate1();
	void OnRotate2();
	void OnRotate3();
	void OnReverse1();
	void OnReverse2();
	void OnHistoStretch();
	void OnEndIn();
	void OnHistoEqual();
	double** mallocDoubleMemory(int h, int w);
	void freeDoubleMemory(double** memory, int h);
};
