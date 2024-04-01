// Constant3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingBeta1.h"
#include "afxdialogex.h"
#include "Constant3Dlg.h"


// CConstant3Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant3Dlg, CDialog)

CConstant3Dlg::CConstant3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT3, pParent)
	, m_constant3(0)
{

}

CConstant3Dlg::~CConstant3Dlg()
{
}

void CConstant3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT3, m_constant3);
	DDV_MinMaxDouble(pDX, m_constant3, 0.00001, 4);
}


BEGIN_MESSAGE_MAP(CConstant3Dlg, CDialog)
END_MESSAGE_MAP()


// CConstant3Dlg 메시지 처리기
