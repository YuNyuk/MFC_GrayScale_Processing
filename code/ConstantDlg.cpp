// ConstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessingBeta1.h"
#include "afxdialogex.h"
#include "ConstantDlg.h"


// CConstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDlg, CDialog)

CConstantDlg::CConstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT, pParent)
	, m_constant(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constant);
	DDV_MinMaxDouble(pDX, m_constant, -255, 255);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialog)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기
