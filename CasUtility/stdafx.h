// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>


# ifdef BUILD_CASUTILITY_DLL
#   define CASUTILITY_EXPORT _declspec(dllexport)
# else
#   define CASUTILITY_EXPORT _declspec(dllimport)
# endif 
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
