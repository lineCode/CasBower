/*
* Copyright (c)
* All rights reserved.
*
* �ļ����ƣ�NHLogAPI.h
* �ļ���ʶ��
* ��������־��¼
*
* �汾��1.0
* ���ߣ�Castle
* ���ڣ�2010-05-24

*/

#pragma once


#define LOG_ERR		L"����"
#define LOG_EXP		L"�쳣"
#define LOG_MSG		L"��Ϣ"


class CASUTILITY_EXPORT CNHLogAPI
{

private:
	// ���ÿ������캯���Ϳ�����ֵ����
	CNHLogAPI(void);
	virtual ~CNHLogAPI(void);
	CNHLogAPI(const CNHLogAPI &);
	CNHLogAPI & operator =(const CNHLogAPI &);

	// �򿪻��������
	friend static DWORD OpenMutexHandle(void);
	DWORD static OpenMutexHandle(void);
	// �رջ��������
	friend static DWORD CloseMutexHandle(void);
	DWORD static CloseMutexHandle(void);

public:
	// д����־
	// wchType ��־���ͣ��Ѷ��峣�ú�LOG_ERR/LOG_EXP/LOG_MSG
	// wchContent ��־���� 
	static DWORD WriteLog(const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// ��WriteLog��һ��·������
	static DWORD WriteLogEx(const wchar_t wchFilePath[], const wchar_t wchType[], const wchar_t wchModule[], const wchar_t wchContent[]);
	// ������־�ļ�������޸�ʱ�䣬ɾ��ĳʱ��֮ǰ������ʱ�̣�����־�ļ�
	static DWORD DeleteLog(const SYSTEMTIME &st);
	// ������־�ļ�������޸�ʱ�䣬ɾ��ĳʱ��֮ǰ������ʱ�̣�����־�ļ�, ��ָ����־�ļ������ļ��У��磺��D:\LOG��
	static DWORD DeleteLogEx(const wchar_t wchFileFolder[], const SYSTEMTIME &st);

private:
	static HANDLE m_hWriteMutex;
};

