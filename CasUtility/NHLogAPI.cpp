#include "StdAfx.h"
#include "NHCommonAPI.h"
#include "NHLogAPI.h"

#include <io.h>
#include <stdio.h>
#include <time.h>
//#include "afxmt.h"

HANDLE CNHLogAPI::m_hWriteMutex = NULL;
//CSemaphore g_shWriteMutex;
CRITICAL_SECTION g_CS;

CNHLogAPI::CNHLogAPI(void)
{
	InitializeCriticalSection(&g_CS);
}

CNHLogAPI::~CNHLogAPI(void)
{
	DeleteCriticalSection(&g_CS);
}

DWORD CNHLogAPI::OpenMutexHandle()
{
	m_hWriteMutex = CreateMutex( NULL, FALSE, NULL );
	if (NULL == m_hWriteMutex)
	{
		return 0xff;
	}
	else
	{
		return 0x00;
	}
}

DWORD CNHLogAPI::CloseMutexHandle()
{
	if (NULL == m_hWriteMutex)
	{
		return 0x00;
	}
	WaitForSingleObject(m_hWriteMutex, 1000L);
	ReleaseMutex(m_hWriteMutex);	
	if (CloseHandle(m_hWriteMutex))
	{
		m_hWriteMutex = NULL;
		return 0x00;
	}
	else
	{
		return 0xff;
	}
}

DWORD CNHLogAPI::WriteLog(const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[])
{
	__time64_t now;
	struct tm  when;
	time(&now);
	_localtime64_s( &when, &now );
	wchar_t wchFileName[51] = {0};
	wcsftime(wchFileName, 50, L"%Y-%m-%d.log", &when);

	wchar_t wchFilePath[MAX_PATH] = {0};
	// �ȴ������߳��ͷŻ������
	//WaitForSingleObject(m_hWriteMutex, INFINITE);
	EnterCriticalSection(&g_CS);
	// �����ļ�·��
	// ���ܻ���ļ������½�����
	CNHCommonAPI::GetFilePathEx(L"LOG", wchFileName, wchFilePath, true);
	// �ͷŻ������
	//ReleaseMutex(m_hWriteMutex);
	LeaveCriticalSection(&g_CS);
	return WriteLogEx(wchFilePath, wchType, wchModule, wchContent);
}

DWORD CNHLogAPI::WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[])
{
	// �ȴ������߳��ͷŻ������
	//WaitForSingleObject(m_hWriteMutex, INFINITE);
	EnterCriticalSection(&g_CS);

	// ��ȡ�ļ���·��
	wchar_t wchFolderPath[MAX_PATH] = {0};
	wcsncpy_s(wchFolderPath, wcslen(wchFolderPath), wchFilePath, _TRUNCATE);
	// ����1��
	wchar_t *pwchDest = wcsrchr(wchFolderPath, L'\\');
	*pwchDest = L'\0';

	// �ж��ļ��Ƿ����
	if (_waccess(wchFilePath, 00))
	{
		// �ļ�������

		// �ж��ļ����Ƿ����
		if (_waccess(wchFolderPath, 00))
		{
			// �ļ��в�����
			// �����ļ���
			if (!CreateDirectory(wchFolderPath, NULL))
			{ 
				// �����ļ���ʧ��
				//ReleaseMutex(m_hWriteMutex); // �ͷŻ������
				LeaveCriticalSection(&g_CS);
				return 0x01;
			}
		}

		// ����Unicode�ļ�
		if (0x00 != CNHCommonAPI::CreateUnicodeFile(wchFilePath))
		{
			// �����ļ�ʧ��
			//ReleaseMutex(m_hWriteMutex); // �ͷŻ������
			LeaveCriticalSection(&g_CS);
			return 0x02;
		}
	}

	// ȥ���ļ�ֻ������
	DWORD dwAttributes(0);
	dwAttributes = ::GetFileAttributes(wchFilePath);
	dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
	::SetFileAttributes(wchFilePath, dwAttributes);

	__time64_t now;
	struct tm when;
	time(&now);
	_localtime64_s( &when, &now );
	wchar_t wchTime[51] = {0};
	wcsftime(wchTime, 50, L"%H:%M:%S", &when);

	FILE *fp = NULL;
	_wfopen_s(&fp, wchFilePath, L"a+,ccs=UNICODE");
	if (NULL == fp)
	{
		// �ͷŻ������
		//ReleaseMutex(m_hWriteMutex);
		LeaveCriticalSection(&g_CS);
		// д��ʧ��
		return 0x03;
	}
	fwprintf(fp, L"[%s]\t%s\t%s\t%s\n", wchTime, wchType, wchModule, wchContent);
	fclose(fp);

	// �ͷŻ������
	//ReleaseMutex(m_hWriteMutex);
	LeaveCriticalSection(&g_CS);
	return 0x00;
}

DWORD CNHLogAPI::DeleteLog(const SYSTEMTIME &st)
{
	// �����ļ�·��
	wchar_t wchFilePath[MAX_PATH] = {0};
	// ������ļ����������û��Ᵽ��
	CNHCommonAPI::GetFilePathEx(L"LOG", L"", wchFilePath);
	return DeleteLogEx(wchFilePath, st);
}

DWORD CNHLogAPI::DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st)
{
	wchar_t wchFilePath[MAX_PATH] = {0};
	// �ļ�·��
	wcsncpy_s(wchFilePath, wcslen(wchFilePath), wchFileFolder, _TRUNCATE);
	wcscat_s(wchFilePath, wcslen(wchFilePath), L"\\*.log");
	
	// ��������־�ļ�
	WIN32_FIND_DATAW fd;
	HANDLE hFindFile = FindFirstFile(wchFilePath, &fd);
	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		return 0xff;
	}

	FILETIME ft;
	ZeroMemory(&ft, sizeof(FILETIME));
	SystemTimeToFileTime(&st, &ft);

	// �ȴ������߳��ͷŻ������
	//WaitForSingleObject(m_hWriteMutex, INFINITE);
	EnterCriticalSection(&g_CS);
	
	// �Աȵ�1���ļ��������ڻ��ߵ����趨ʱ�̵�ɾ��
	FILETIME ftLocalLastWriteTime;
	ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
	// ������޸�ʱ��ת���ɱ���ʱ�䣨��������
	// ������޸�ʱ�䣬��ʹ�ô���ʱ�䣨����ʱ���ڸ��ƺ��ı䣩��
	FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
	if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft ���� ftLocalLastWriteTime
	{
		ZeroMemory(wchFilePath, sizeof(wchFilePath));
		wcsncpy_s(wchFilePath, wcslen(wchFilePath), wchFileFolder, _TRUNCATE);
		wcscat_s(wchFilePath, wcslen(wchFilePath), fd.cFileName);
		DeleteFile(wchFilePath);
	}

	// �ҵ���ָ����һ���ļ�
	while (FindNextFile(hFindFile, &fd))
	{
		// �Ա��ļ��������ڻ��ߵ����趨ʱ�̵�ɾ��
		ZeroMemory(&ftLocalLastWriteTime, sizeof(FILETIME));
		// ������޸�ʱ��ת���ɱ���ʱ�䣨��������
		// ������޸�ʱ�䣬��ʹ�ô���ʱ�䣨����ʱ���ڸ��ƺ��ı䣩��
		FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &ftLocalLastWriteTime);
		if (1 == CompareFileTime(&ft, &ftLocalLastWriteTime)) // ft ���� ftLocalLastWriteTime
		{
			ZeroMemory(wchFilePath, sizeof(wchFilePath));
			wcsncpy_s(wchFilePath, wcslen(wchFilePath), wchFileFolder, _TRUNCATE);
			wcscat_s(wchFilePath, wcslen(wchFilePath), fd.cFileName);
			DeleteFile(wchFilePath);
		}
	}
	
	// �ͷŻ������
	//ReleaseMutex(m_hWriteMutex);
	LeaveCriticalSection(&g_CS);

	// �رվ��
	FindClose(hFindFile);
	return 0x00;
}