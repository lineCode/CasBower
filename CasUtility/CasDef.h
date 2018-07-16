#ifndef CASDEF_H
#define CASDEF_H

// �궨��
#ifndef ERROR_MAX
#define ERROR_MAX 1024 // �����������ַ���
#endif

#ifndef SQLMAX
#define SQLMAX 1024 // sql �����������ַ���
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ����ӳ����Ϣ����begin
#define WM_HOTKEY_VK_F2				WM_USER+0x0701
#define WM_HOTKEY_VK_F3				WM_USER+0x0702
#define WM_HOTKEY_VK_F4				WM_USER+0x0703
#define WM_HOTKEY_VK_F5				WM_USER+0x0704
#define WM_HOTKEY_VK_F6				WM_USER+0x0705
#define WM_HOTKEY_VK_F7				WM_USER+0x0706
#define WM_HOTKEY_VK_F8				WM_USER+0x0707
#define WM_HOTKEY_VK_F9				WM_USER+0x0708
#define WM_HOTKEY_VK_F10			WM_USER+0x0709
#define WM_HOTKEY_VK_F11			WM_USER+0x070A
#define WM_HOTKEY_VK_F12			WM_USER+0x070B
#define WM_HOTKEY_VK_OEM_PLUS		WM_USER+0x070C
#define WM_HOTKEY_VK_OEM_MINUS		WM_USER+0x070D
#define WM_HOTKEY_VK_OEM_5			WM_USER+0x070E
#define WM_HOTKEY_VK_OEM_3			WM_USER+0x070F     //For the US standard keyboard, the '`~' key
#define WM_HOTKEY_VK_ALT_S			WM_USER+0x0710
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ����ӳ����Ϣ����end


// �����ɫ����
enum NHRoleType
{
	ADMIN = 0,		// ����Ա	0
	OPERATOR,		// ����Ա	1
	BILLER,			// ����Ա	2
	SHROFF,			// �ֿ�Ա	3
	ASSESSOR,		// ����Ա	4
};

//////////////////////////////////////////////////////////////////
#define NH_INT_TO_WCHART 12
#define NH_TIME_TO_WCHART 30
#define NH_BOOL_TO_WCHART 2
#define NH_FLOAT_TO_WCHART 20
//////////////////////////////////////////////////////////////////

// �û���Ϣ<UserInfo>
typedef struct UseInfo
{
	wchar_t wchAutoID[NH_INT_TO_WCHART];				// �Զ����
	wchar_t wchName[50];								// �û���
	wchar_t wchPassword[50];							// ����
	wchar_t wchLicenseSn[50];						// ���֤���
	wchar_t wchLicenseStartDate[NH_TIME_TO_WCHART];	// ���֤��ʼ����
	wchar_t wchLicenseEndDate[NH_TIME_TO_WCHART];	// ���֤��������
	wchar_t wchRole[NH_INT_TO_WCHART];				// ��ɫ
	wchar_t wchRemark[1024];							// ��ע
	wchar_t wchReserved1[50];						// �����ֶ�,�Ժ���
	wchar_t wchReserved2[50];						// �����ֶ�,�Ժ���
	wchar_t wchReserved3[50];						// �����ֶ�,�Ժ���

	UseInfo(){ZeroMemory(this, sizeof(UseInfo));}
}USERINFO,*PUSERINFO;

typedef struct CompanyInfo
{
	wchar_t wchName[1024];								// �û���
	wchar_t wchEName[1024];								// �û���
	wchar_t wchAddress[1024];							
	wchar_t wchTel[1024];								
	wchar_t wchFax[1024];								
	wchar_t wchEmail[1024];															
	wchar_t wchRemark[1024];							// ��ע
	wchar_t wchReserved1[50];						// �����ֶ�,�Ժ���
	wchar_t wchReserved2[50];						// �����ֶ�,�Ժ���
	wchar_t wchReserved3[50];						// �����ֶ�,�Ժ���

	CompanyInfo(){ZeroMemory(this, sizeof(CompanyInfo));}
}COMPANYINFO,*PCOMPANYINFO;
#endif