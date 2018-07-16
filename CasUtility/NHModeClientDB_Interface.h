/*
* Copyright (c) 2010
* All rights reserved.
*
* �ļ����ƣ�NHModeClientDB_Interface.h
* �ļ���ʶ��
* ������xxxxxxx
*
* �汾��1.0.0alpha
* ���ڣ�2010-xx-xx
* ���ߣ�Chc
* ��������ʽ����
*/

#pragma once

// �����ǵ����ļ�,����Ҫ���¶���
#ifndef SQLMAX
#define SQLMAX 1024 // sql �����������ַ���
#endif

#include "CasDef.h"
#include <list>

//class CNHModeClientDB_Interface
class CASUTILITY_EXPORT CNHModeClientDB_Interface
{
public:
	CNHModeClientDB_Interface(void);
	virtual ~CNHModeClientDB_Interface(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHModeClientDB_Interface(const CNHModeClientDB_Interface &);
	CNHModeClientDB_Interface & operator =(const CNHModeClientDB_Interface &);

public:
	// return value
	// 0xff : Database exception
	// 0x00 : No record get
	// 0x01 : Get first record successful
	// 0x02 : Get CertificateAuthentication failed
	DWORD GetDboCertificateOfDepartInfo(wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength, long& lDataSize);
	// return value
	// 0xff : Database exception
	// 0x00 : Update successful
	// 0x01 : DepartNumber error
	DWORD SetDboCertificateOfDepartInfo(wchar_t const * pwchDepartNumber, BYTE * const pbCertificateAuthentication, const UINT uiCALength);
};
