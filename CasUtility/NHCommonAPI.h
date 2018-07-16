/*
* Copyright (c) 
* All rights reserved.
*
* �ļ����ƣ�NHCommonAPI.h
* �ļ���ʶ��
* ������ͨ�ýӿں���
*
* �汾��1.0
* ���ߣ�Castle
* ���ڣ�2010-09-03
*
*/

#pragma once



#define SAFEFREE(x) if (x){delete x;x = NULL;}
#define SAFEFREE_ARRAY(x) if (x){delete[] x;x = NULL;}
#include <xstring>
#include <vector>
using namespace std;


class CASUTILITY_EXPORT CNHCommonAPI
{
public:
	CNHCommonAPI(void);
	virtual ~CNHCommonAPI(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHCommonAPI(const CNHCommonAPI &);
	CNHCommonAPI & operator =(const CNHCommonAPI &);

public:
	// ��ȡ�ļ�·��
	// (in)chFileFolder:�ļ���
	// (in)chFileName:�ļ���
	// (out)chFilePath:�ļ�·��
	// (in)bCreateFile:���ļ�������ʱ���Ƿ񴴽��ļ�
	// (return)�������:
	// 0x00:������
	// ��0x00:�쳣(0x01:�����ļ���ʧ��,0x02:�ļ�������,0x03:�����ļ�ʧ��)
	// ע��: �ļ��������ļ���ǰ�߲���Ҫ��"\\"
	// ����: <L"Config"> �� <L"CasInfo.ini">
	static DWORD GetFilePathEx(const wchar_t wchFileFolder[MAX_PATH], const wchar_t wchFileName[MAX_PATH], wchar_t wchFilePath[MAX_PATH], const bool bCreateFile = false);

	// �ַ�����ת������
	static wchar_t * ANSIToUnicode(const char *str);
	static char * UnicodeToANSI(const wchar_t *str);
	static wchar_t * UTF8ToUnicode(const char *str);
	static char * UnicodeToUTF8(const wchar_t *str);
	static char * ANSIToUTF8(const char *str);
	static char * UTF8ToANSI(const char *str);

	// ��������
	static int round(const float f);
	static int round(const double d);
	//Castle�ж��Ƿ�����
	static bool IsNum(const wchar_t *str);

	// ��ȡ�ļ�·��
	// ��ǰĿ¼��CD=Current Directory
	// �ϼ�Ŀ¼��HLD=Higher Level Directory
	// �¼�Ŀ¼��LLD=Lower Level Directory
	// ������
	// pwchFileFolder:�ļ�����
	// pwchFileName:�ļ���
	// pwchFilePath:�ļ�·��
	// bCreateFile:���ļ�������ʱ���Ƿ񴴽��ļ�
	// ���أ��������:
	// 0x00:������
	// ��0x00:�쳣(0x01:�����ļ���ʧ��,0x02:�ļ�������,0x03:�����ļ�ʧ��)
	// ע��: �ļ��������ļ���ǰ�߲���Ҫ��"\\"
	// ����: <L"Config"> �� <L"CasInfo.ini">
	static DWORD GetCDFilePath(const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);
	static DWORD GetHLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);
	static DWORD GetLLDFilePath(const wchar_t *const pwchFileFolder, const wchar_t *const pwchFileName, wchar_t *const pwchFilePath, const bool bCreateFile = false);

	// ����Unicode�ļ�
	// ������
	// pwchFilePath:�ļ�·��
	// ���أ��������:
	// 0x00:������
	// ��0x00:�쳣
	static DWORD CreateUnicodeFile(const wchar_t *const pwchFilePath);
	static void getMACAddress(char *const strMAC);

	static std::string base64_encode(BYTE const* buf, unsigned int bufLen);
	static std::vector<BYTE> base64_decode(std::string const& encoded_string);
};
