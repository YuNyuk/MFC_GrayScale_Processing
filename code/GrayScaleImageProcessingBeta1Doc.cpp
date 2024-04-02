
// GrayScaleImageProcessingBeta1Doc.cpp: CGrayScaleImageProcessingBeta1Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessingBeta1.h"
#endif

#include "GrayScaleImageProcessingBeta1Doc.h"

#include <propkey.h>
#include "ConstantDlg.h" // 정수 값
#include "Constant2Dlg.h" // 감마
#include "Constant3Dlg.h" // 배율
#include "Constant4Dlg.h" // 각도


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleImageProcessingBeta1Doc

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingBeta1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingBeta1Doc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleImageProcessingBeta1Doc 생성/소멸

CGrayScaleImageProcessingBeta1Doc::CGrayScaleImageProcessingBeta1Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingBeta1Doc::~CGrayScaleImageProcessingBeta1Doc()
{
}

BOOL CGrayScaleImageProcessingBeta1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleImageProcessingBeta1Doc serialization

void CGrayScaleImageProcessingBeta1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleImageProcessingBeta1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleImageProcessingBeta1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleImageProcessingBeta1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleImageProcessingBeta1Doc 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingBeta1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleImageProcessingBeta1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleImageProcessingBeta1Doc 명령


unsigned char** CGrayScaleImageProcessingBeta1Doc::OnMalloc2D(int h, int w, int initVal)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;

	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char[w];

	return retMemory;
}


void CGrayScaleImageProcessingBeta1Doc::OnFree2D(unsigned char** memory, int h)
{
	if (memory == NULL)
		return;
	for (int i = 0; i < h; i++)
		delete memory[i];
	delete[] memory;
	// TODO: 여기에 구현 코드 추가.
}


double** CGrayScaleImageProcessingBeta1Doc::mallocDoubleMemory(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];
	return retMemory;
}


void CGrayScaleImageProcessingBeta1Doc::freeDoubleMemory(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == nullptr)
		return;
	for (int i = 0; i < h; i++)
		delete[] memory[i];
	delete[] memory;
	memory = nullptr;
}


BOOL CGrayScaleImageProcessingBeta1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 선택된 파일 열기
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일의 크기를 파악 --> 가로세로 크기 결정
	ULONGLONG fLength = File.GetLength();
	// 입력 이미지 높이와 폭을 결정
	// 기존 메모리 모두 해제하고, 관련 값 초기화
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 입력 이미지의 높이와 폭을 결정 + 메모리 할당
	m_inH = m_inW = (int)sqrt((double)fLength);
	m_inImage = OnMalloc2D(m_inH, m_inW, 0);

	// 파일 --> 메모리
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);

	File.Close();

	return TRUE;
}


void CGrayScaleImageProcessingBeta1Doc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 기존 메모리 모두 해제하고, 관련 값 초기화
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;


	CDocument::OnCloseDocument();
}


BOOL CGrayScaleImageProcessingBeta1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_outW);
		File.Close();
	}

	return true;
}


// 화소 점 처리


void CGrayScaleImageProcessingBeta1Doc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[i][k] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnGrayImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] < 127)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = 255;
		}
	}

}


void CGrayScaleImageProcessingBeta1Doc::OnReverseImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[i][k] = 255 - m_inImage[i][k];
		}
	}

}


void CGrayScaleImageProcessingBeta1Doc::OnAddImage()
{
	
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int value = (int)dlg.m_constant;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (m_inImage[i][k] + value > 255)
				m_outImage[i][k] = 255;
			else if (m_inImage[i][k] + value < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = m_inImage[i][k] + value;
		}
	}

}


void CGrayScaleImageProcessingBeta1Doc::OnDarkImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] - val > 0)
				m_outImage[i][k] = m_inImage[i][k] - val;
			else
				m_outImage[i][k] = 0;
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	int val = (int)dlg.m_constant2;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			//픽셀 값 0~1로 정규화
			float normalized_pixel = (float)m_inImage[i][k] / 255.0;
			//감마 함수 적용후 보정된 값 계산
			float corrected_pixel = pow(normalized_pixel, val);

			corrected_pixel *= 255.0;

			if (corrected_pixel < 0)
				corrected_pixel = 0;
			if (corrected_pixel > 255)
				corrected_pixel = 255;

			m_outImage[i][k] = (unsigned char)corrected_pixel;
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnParabolCap()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImage[i][k] = 255 - 255 * pow((m_inImage[i][k] / 127), 2);
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnParabolCup()
{
	// TODO: 여기에 구현 코드 추가
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_inH; i++)
	{
		for (int k = 0; k < m_inW; k++)
		{
			m_outImage[i][k] = 255 * pow((m_inImage[i][k] / 127), 2);
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImage[i][k] & (unsigned char)val) >= 255)
				m_outImage[i][k] = 255;
			else if ((m_inImage[i][k] & (unsigned char)val) < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = (unsigned char)(m_inImage[i][k] & (unsigned char)val);
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImage[i][k] | (unsigned char)val) >= 255)
				m_outImage[i][k] = 255;
			else if ((m_inImage[i][k] | (unsigned char)val) < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = (unsigned char)(m_inImage[i][k] | (unsigned char)val);
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if ((m_inImage[i][k] ^ (unsigned char)val) >= 255)
				m_outImage[i][k] = 255;
			else if ((m_inImage[i][k] ^ (unsigned char)val) < 0)
				m_outImage[i][k] = 0;
			else
				m_outImage[i][k] = (unsigned char)(m_inImage[i][k] ^ (unsigned char)val);
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnNotImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int val = (int)dlg.m_constant;
}


// 화소 영역 처리


void CGrayScaleImageProcessingBeta1Doc::OnEmboss()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {-1.0, 0.0, 0.0}, // 엠보싱 마스크
	{ 0.0, 0.0, 0.0},
	{ 0.0, 0.0, 1.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImage = mallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++) // 2 대신 1씩만 더해도 되긴 함
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	// 후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, m_inH + 2);
	freeDoubleMemory(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingBeta1Doc::OnBlur()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {1. / 9, 1. / 9, 1. / 9}, // 블러링 마스크
	  {1. / 9, 1. / 9, 1. / 9},
	  {1. / 9, 1. / 9, 1. / 9} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImage = mallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++) // 2 대신 1씩만 더해도 되긴 함
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	/*후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;*/

	// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, m_inH + 2);
	freeDoubleMemory(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingBeta1Doc::OnSharp()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] =
	{ {0.0, -1.0 ,0.0}, // 샤프닝 마스크
	  {-1.0 ,5.0, -1.0},
	  {0.0, -1.0, 0.0} };
	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImage = mallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++) // 2 대신 1씩만 더해도 되긴 함
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	/*후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;*/

			// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, m_inH + 2);
	freeDoubleMemory(tmpOutImage, m_outH);
}


void CGrayScaleImageProcessingBeta1Doc::OnEdge1()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	////////////////
	// 화소 영역 처리
	/////////////////
	double mask[3][3] = // 수직 에지 검출 마스크
	{ {0.0, 0.0, 0.0},
	{-1.0, 1.0, 0.0},
	{0.0,  0.0, 0.0} };

	// 임시 메모리 할당(실수형)
	double** tmpInImage = mallocDoubleMemory(m_inH + 2, m_inW + 2);
	double** tmpOutImage = mallocDoubleMemory(m_outH, m_outW);

	// 임시 입력 메모리를 초기화(127) : 필요시 평균값
	for (int i = 0; i < m_inH + 2; i++)
		for (int k = 0; k < m_inW + 2; k++) // 2 대신 1씩만 더해도 되긴 함
			tmpInImage[i][k] = 127;

	// 입력 이미지 --> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			tmpInImage[i + 1][k + 1] = m_inImage[i][k];

	// *** 회선 연산 ***
	double S;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			// 마스크(3x3) 와 한점을 중심으로한 3x3을 곱하기
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값.
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					S += tmpInImage[i + m][k + n] * mask[m][n];
				}
				tmpOutImage[i][k] = S;
			}
		}
	}
	//후처리 (마스크 값의 합계에 따라서...)
	for (int i = 0; i < m_outH; i++)
		for (int k = 0; k < m_outW; k++)
			tmpOutImage[i][k] += 127.0;

			// 임시 출력 영상--> 출력 영상. 
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			if (tmpOutImage[i][k] < 0.0)
				m_outImage[i][k] = 0;
			else if (tmpOutImage[i][k] > 255.0)
				m_outImage[i][k] = 255;
			else
				m_outImage[i][k] = (unsigned char)tmpOutImage[i][k];
		}
	}
	freeDoubleMemory(tmpInImage, m_inH + 2);
	freeDoubleMemory(tmpOutImage, m_outH);
}


// 기하학적 처리


void CGrayScaleImageProcessingBeta1Doc::OnZoomIn1() // 포워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	int scale = (int)dlg.m_constant3;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[(int)(i * scale)][(int)(k * scale)] = m_inImage[i][k];
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnZoomIn2() // 백워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);


	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[(int)(i / scale)][(int)(k / scale)];
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnZoomIn3() // 양선형 보간
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = (int)(m_inH * scale);
	m_outW = (int)(m_inW * scale);

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	double rowRatio = (double)(m_inH - 1) / (m_outH - 1);
	double colRatio = (double)(m_inW - 1) / (m_outW - 1);

	// 출력 이미지의 각 픽셀에 대해 양선형 보간법 수행
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 현재 픽셀의 위치를 기준으로 입력 이미지에서 가장 가까운 네 개의 픽셀을 찾습니다.
			int baseRow = (int)(round(i * rowRatio));
			int baseCol = (int)(round(k * colRatio));

			// 현재 픽셀의 위치와 가장 가까운 네 개의 픽셀 사이의 거리를 계산합니다.
			double dx = (i * rowRatio) - baseRow;
			double dy = (k * colRatio) - baseCol;

			if (baseRow >= 0 && baseRow < m_inH - 1 && baseCol >= 0 && baseCol < m_inW - 1) {
				// 양선형 보간법을 사용하여 현재 픽셀의 값을 계산합니다.
				double interpolatedValue = (1 - dx) * (1 - dy) * m_inImage[baseRow][baseCol] +
					dx * (1 - dy) * m_inImage[baseRow + 1][baseCol] +
					(1 - dx) * dy * m_inImage[baseRow][baseCol + 1] +
					dx * dy * m_inImage[baseRow + 1][baseCol + 1];
				// 계산된 값으로 출력 이미지의 현재 픽셀을 설정합니다.
				m_outImage[i][k] = (unsigned char)interpolatedValue;
			}
			else {
				m_outImage[i][k] = 255;
			}
		}
	}

}


void CGrayScaleImageProcessingBeta1Doc::OnZoomOut()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant3Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	int scale = (int)dlg.m_constant3;
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = (int)(m_inH / scale);
	m_outW = (int)(m_inW / scale);

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[(int)(i / scale)][(int)(k / scale)] = m_inImage[i][k];
		}
	}

}


void CGrayScaleImageProcessingBeta1Doc::OnMove()
{
	// TODO: 여기에 구현 코드 추가.

	CConstantDlg dlgA;
	if (dlgA.DoModal() != IDOK)
		return;
	int b = (int)dlgA.m_constant;

	CConstantDlg dlgB;
	if (dlgB.DoModal() != IDOK)
		return;

	int a = (int)dlgB.m_constant;

	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 이미지 이동 시 경계를 벗어나는 경우를 고려하여 인덱스를 체크하여 처리
			if (i + a >= 0 && i + a < m_inH && k - b >= 0 && k - b < m_inW)
				m_outImage[i][k] = m_inImage[i + a][k - b];
			else
				m_outImage[i][k] = 0; // 경계를 벗어나는 경우에는 0으로 처리하거나 다른 방법으로 처리
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnRotate1() // 회전
{
	// TODO: 여기에 구현 코드 추가.
	CConstant4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	int degree = (int)dlg.m_constant4;
	double radian = degree * 3.141592 / 180.0;

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			int xs = i;
			int ys = k;
			int xd = cos(radian) * xs - sin(radian) * ys;
			int yd = sin(radian) * xs + cos(radian) * ys;

			if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
				m_outImage[xd][yd] = m_inImage[xs][ys];
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnRotate2() // 회전+중심+백워딩
{
	// TODO: 여기에 구현 코드 추가.
	CConstant4Dlg dlg;
	if (dlg.DoModal() != IDOK)
		return;

	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int degree = (int)dlg.m_constant4;
	double radian = degree * 3.141592 / 180.0;

	// 회전 중심 계산
	int cx = m_inH / 2;
	int cy = m_inW / 2;
	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			int xd = i;
			int yd = k;
			int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
			int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));
			xs += cx;
			ys += cy;
			if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
				m_outImage[xd][yd] = m_inImage[xs][ys];
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnRotate3() // 회전 + 확대 + 백워딩
{
	// TODO: 여기에 구현 코드 추가.

	CConstant4Dlg dlgA;
	if (dlgA.DoModal() != IDOK)
		return;

	CConstant3Dlg dlgB;
	if (dlgB.DoModal() != IDOK)
		return;

	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	int degree = (int)dlgA.m_constant4;
	int scale = (int)dlgB.m_constant3;
	double radian = -degree * 3.141592 / 180.0;

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH * scale;
	m_outW = m_inW * scale;

	// 회전 중심 계산
	int cx = m_inH / 2;
	int cy = m_inW / 2;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			// 회전 및 확대된 픽셀 위치 계산
			int xd = i / scale;
			int yd = k / scale;
			int xs = (int)(cos(radian) * (xd - cx) - sin(radian) * (yd - cy) + cx);
			int ys = (int)(sin(radian) * (xd - cx) + cos(radian) * (yd - cy) + cy);

			// 회전된 픽셀 위치의 유효성 검사
			if (0 <= xs && xs < m_inH && 0 <= ys && ys < m_inW) {
				m_outImage[i][k] = m_inImage[xs][ys];
			}
			else {
				m_outImage[i][k] = 255; // 흰색으로 설정
			}
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnReverse1() // 상하 반전
{
	// TODO: 여기에 구현 코드 추가.

	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[m_inH - 1 - i][k]; // 상하 반전
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnReverse2() // 좌우 반전
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	for (int i = 0; i < m_outH; i++) {
		for (int k = 0; k < m_outW; k++) {
			m_outImage[i][k] = m_inImage[i][m_inW - 1 - k]; // 상하 반전
		}
	}
}


// 히스토그램 처리


void CGrayScaleImageProcessingBeta1Doc::OnHistoStretch() // 히스토그램 스트레칭
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// 여기서부터 영상처리 알고리즘 시작~~
	// new = (old - low) / (high - low) * 255.0
	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k] < low;
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}
	}
	int oldPixel, newPixel;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			oldPixel = m_inImage[i][k];
			newPixel = (int)((double)(oldPixel - low) / (double)(high - low) * 255.0);
			if (newPixel > 255)
				newPixel = 255;
			if (newPixel < 0)
				newPixel = 0;
			m_outImage[i][k] = newPixel;
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnEndIn() // 엔드-인
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	int high = m_inImage[0][0], low = m_inImage[0][0];
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			if (m_inImage[i][k] < low)
				low = m_inImage[i][k] < low;
			if (m_inImage[i][k] > high)
				high = m_inImage[i][k];
		}
	}

	high -= 50;
	low += 50;

	int oldPixel, newPixel;
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			oldPixel = m_inImage[i][k];
			newPixel = (int)((double)(oldPixel - low) / (double)(high - low) * 255.0);
			if (newPixel > 255)
				newPixel = 255;
			if (newPixel < 0)
				newPixel = 0;
			m_outImage[i][k] = newPixel;
		}
	}
}


void CGrayScaleImageProcessingBeta1Doc::OnHistoEqual() // 평활화
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);

	// (중요!) 출력 이미지의 크기를 결정 ---> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;

	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);

	// 1단계 : 빈도수 세기 (=히스토그램)
	int histo[256] = { 0. };
	for (int i = 0; i < m_inH; i++)
		for (int k = 0; k < m_inW; k++)
			histo[m_inImage[i][k]]++;

	// 2단계 : 누적 히스토그램 생성
	int sumHisto[256] = { 0, };
	sumHisto[0] = histo[0];
	for (int i = 1; i < 256; i++)
		sumHisto[i] = sumHisto[i - 1] + histo[i];
	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH*inW) * 255.0;
	double normalHisto[256] = { 1.0, };
	for (int i = 0; i < 256; i++) {
		normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}
	// 4단계 : inImage를 정규화된 값으로 치환
	for (int i = 0; i < m_inH; i++) {
		for (int k = 0; k < m_inW; k++) {
			m_outImage[i][k] = (unsigned char)normalHisto[m_inImage[i][k]];
		}
	}
}




