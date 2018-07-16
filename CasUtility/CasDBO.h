/*
* Copyright (c) 2014
* All rights reserved.
*
* �ļ����ƣ�NHSQLServerDBO.h
* �ļ���ʶ��
* ������SQLServer���ݿ����
*
* �汾��1.0
* ���ߣ�Castle
* ���ڣ�2011-03-16
*/

#ifndef NH_SQLSERVER_DBO_H
#define NH_SQLSERVER_DBO_H

#import "msado60_Backcompat_i386.tlb" no_namespace rename("EOF","adoEOF")


class CASUTILITY_EXPORT CNHSQLServerDBO
{
	// ���ù��캯������������(��ֹ���ɶ���)
private:
	CNHSQLServerDBO(void);
	virtual ~CNHSQLServerDBO(void);

	// ���ÿ������캯���Ϳ�����ֵ����
private:
	CNHSQLServerDBO(const CNHSQLServerDBO &);
	CNHSQLServerDBO & operator =(const CNHSQLServerDBO &);

public:
	// �����ݿ�(Ĭ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnection);
	// �����ݿ�(ָ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (in)pwchSource:����Դ
	// (in)pwchCatalog:���ݿ�����
	// (in)pwchUserID:�û���
	// (in)pwchPassword:����
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDB(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchInitialCatalog,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// ��Oracle���ݿ�(ָ��������Ϣ)
	// (in&out)pConnection:����ָ������
	// (in)pwchSource:����Դ
	// (in)pwchUserID:�û���
	// (in)pwchPassword:����
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenDBOfOrcale(_ConnectionPtr &pConnectionconst,
		const wchar_t *const pwchDataSource,
		const wchar_t *const pwchUserID,
		const wchar_t *const pwchPassword);
	// �ر����ݿ�
	// (in&out)pConnection:����ָ������
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseDB(_ConnectionPtr &pConnection);
	// �򿪲�ѯ
	// (in)pConnection:����ָ������
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (in)pwchSQL:��ѯ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD OpenQuery(const _ConnectionPtr &pConnection, _RecordsetPtr &pRecordset, const wchar_t *const pwchSQL);
	// �رղ�ѯ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD CloseQuery(_RecordsetPtr &pRecordset);
	// ��ȡ�ֶ�ֵ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (out)vFieldValue:�ֶ�ֵ����
	// (in)pwchFieldName:�ֶ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD GetFieldValue(const _RecordsetPtr &pRecordset, _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	// �����ֶ�ֵ
	// (in&out)pRecordset:��¼��ָ��Ӧ��
	// (out)vFieldValue:�ֶ�ֵ����
	// (in)pwchFieldName:�ֶ����ַ���ָ��
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD PutFieldValue(const _RecordsetPtr &pRecordset, const _variant_t &vFieldValue, const wchar_t *const pwchFieldName);
	// ִ��DML
	// (in&out)pConnection:����ָ������
	// (in)pwchSQL:DML����ַ���ָ��
	// (out)pnRowsInvolved����Ӱ����е���Ŀָ�룬����ΪNULL
	// (return)�������:
	// 0x00:����
	// ��0x00:�쳣
	static DWORD ExecuteDML(const _ConnectionPtr &pConnection, const wchar_t *const pwchSQL, int *const pnRowsInvolved=NULL);
	// ������ݿ������Ϣ�������������ں���־�ļ���
	// (in&out)e:�쳣����
	// (return)��
	static void OutputDBErrMsg(const _com_error& e);
	// ������־�ļ�·��
	// (in&out)e:�쳣����
	// (return)��
	static void SetLogFilePath(const wchar_t *const pFilePath);

private:
	// ��־�ļ�·��
	static wchar_t m_wchLogFilePath[MAX_PATH];
};

#endif