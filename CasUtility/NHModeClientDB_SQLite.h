/*
* Copyright (c) 2010
* All rights reserved.
*
* �ļ����ƣ�NHModeClientDB_SQLite.h
* �ļ���ʶ��
* ������1��CastleDB���ݿ��������,����ֵ�߼�����ע������ֵ�߼��ĺ����⣬����������ѭ���·��ع���
*		Getxxx��ִ�гɹ�����0x01���޶�Ӧ��¼����0x00���쳣����0xff��Setxxx���ɹ�����0x00���쳣����0xff
*
*
* �汾��1.0.0
* ���ڣ�2010-12-31
* ���ߣ�Chc
* ��������ʽ����ʹ��
*/

#pragma once
#include "NHModeClientDB_Interface.h"

class CASUTILITY_EXPORT CNHModeClientDB_SQLite : public CNHModeClientDB_Interface
{
public:
	CNHModeClientDB_SQLite(void);
	virtual ~CNHModeClientDB_SQLite(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHModeClientDB_SQLite(const CNHModeClientDB_SQLite &);
	CNHModeClientDB_SQLite & operator =(const CNHModeClientDB_SQLite &);


public:
	// return value
	// 0xff : Database exception
	// 0x00 : No record get
	// 0x01 : Get first record successful
	// 0x02 : Get CertificateAuthentication failed
	static DWORD GetDboCertificateOfDepartInfo(wchar_t const * pwchPath, wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength, long& lDataSize);
	// return value
	// 0xff : Database exception
	// 0x00 : Update successful
	// 0x01 : DepartNumber error
	static DWORD SetDboCertificateOfDepartInfo(wchar_t const * pwchPath, wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength);
};
