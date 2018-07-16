/*
* Copyright (c) 2010
* All rights reserved.
*
* �ļ����ƣ�NHModeServerDB.h
* �ļ���ʶ��
* ������NHModeServerDB���ݿ��������,����ֵ�߼�����ע������ֵ�߼��ĺ����⣬����������ѭ���·��ع���
*		Getxxx��ִ�гɹ�����0x01���޶�Ӧ��¼����0x00���쳣����0xff��Setxxx���ɹ�����0x00���쳣����0xff
*
* �汾��1.0
* ���ߣ�
* ���ڣ�2010-07-14
*/


#ifndef NHMODESERVERDB_H
#define NHMODESERVERDB_H

// �����ǵ����ļ�,����Ҫ���¶���
#ifndef SQLMAX
#define SQLMAX 1024 // sql �����������ַ���
#endif

#include "CasDef.h"
#include <list>
using std::list;

extern "C"
{
	// �û���Ϣ<UserInfo> UserInfo������в���

	// ��ȡ�û���Ϣ
	// ���أ�
	// 0x00���޶�Ӧ��¼
	// 0x01����ȡ�ɹ�
	// 0xff�����ݿ��쳣
	DWORD __declspec(dllexport) GetDboUserInfo(const wchar_t wchSql[SQLMAX], PUSERINFO const pDboUserInfo);
	// �����û���Ϣ
	// ���أ�
	// 0x00�����óɹ�
	// 0xff�����ݿ��쳣
	DWORD __declspec(dllexport) SetDboUserInfo(const USERINFO &dboUserInfo);
	// ɾ���û���Ϣ
	// �ò���δʵ��
	DWORD __declspec(dllexport) DelDboUserInfo(const wchar_t wchSql[SQLMAX]);
	// ��ȡ�û�Ȩ��
	// ���أ�
	// 0x01����ȡ�ɹ�
	// 0x02����ȡʧ��
	// 0xff�����ݿ��쳣
	DWORD __declspec(dllexport) GetDboUserPermission(const wchar_t *const pwchName, std::string &strPermission);
	// дȨ�����������ݿ�
	// ���أ�
	// 0x00��д��ɹ�
	// 0xff�����ݿ��쳣
	DWORD __declspec(dllexport) SetDboUserPermission(const wchar_t *const pwchName, const std::string &strPermission);
	// ������֤��Ϣ<DepartInfo>
	// return value
	// 0xff : Database exception
	// 0x00 : No record get
	// 0x01 : Get first record successful
	// 0x02 : Get CertificateAuthentication failed
	DWORD __declspec(dllexport) GetDboCertificateOfDepartInfo(wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength, long& lDataSize);
	// return value
	// 0xff : Database exception
	// 0x00 : Update successful
	// 0x01 : DepartNumber error
	DWORD __declspec(dllexport) SetDboCertificateOfDepartInfo(wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength);
}
#endif