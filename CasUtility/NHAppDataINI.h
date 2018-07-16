/*
* Copyright (c) 2009,
* All rights reserved.
*
* �ļ����ƣ�NHAppDataINI.h
* �ļ���ʶ��
* ժ    Ҫ��App_Data���������ļ���������,���ݽṹ��ʽ����
*
* ��ǰ�汾��1.0
* ��    �ߣ�
* ������ڣ�2010-07-14
*/

#ifndef NHAPPDATAINI_H
#define NHAPPDATAINI_H

// ��ע��������ת����wchar_t���ձ�
// int wchar_t[11] �з���
// short wchar_t[6] �з���
// time wchar_t[19] ��ȷ���� 2008-08-08 23:59:59

#include "CasDef.h"
#include <list>
#include <vector>
using std::list;
using std::vector;

// App_Data
// �û���Ϣ UserInfo.ini

extern "C" void __declspec(dllexport) GetIniUserInfo(PUSERINFO const pIniUserInfo);
extern "C" void __declspec(dllexport) SetIniUserInfo(const USERINFO& iniUserInfo);

//// ASM test result<ResultOfASM>
//extern "C" void __declspec(dllexport) GetIniResultOfASM(PRESULTOFASM const pIniResultOfASM);
//extern "C" void __declspec(dllexport) SetIniResultOfASM(const RESULTOFASM& iniResultOfASM);
//
//// ASM real time data<RealTimeDataOfASM>
//extern "C" void __declspec(dllexport) GetIniRealTimeDataOfASM(list<REALTIMEDATAOFASM>& listRealTimeDataOfASM);
//extern "C" void __declspec(dllexport) GetIniRealTimeDataOfASMVector(vector<REALTIMEDATAOFASM>& vRealTimeDataOfASM);

#endif