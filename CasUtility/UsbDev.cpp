#include "StdAfx.h"
#include "UsbDev.h"


CUsbDev::CUsbDev(void)
{
}


CUsbDev::~CUsbDev(void)
{
}


DWORD CUsbDev::GetUsbID(wchar_t* const pwchUSBSN)
{
	DWORD dw(0x00);
	wchar_t wchFilePath[MAX_PATH]={0};

	// ��ȡexe(dll)�ļ�����·��
	GetModuleFileName(NULL, wchFilePath, MAX_PATH);

	if(!::IsCharAlphaW(wchFilePath[0]))
	{
		//������������Ч
		dw = 0x01;
	}
	else
	{
		/**********��ȡ���������֡����кź��ļ�ϵͳ����**********/
		wchar_t wchRootPathName[50] = {0};
		_snwprintf_s(wchRootPathName, _countof(wchRootPathName), _TRUNCATE, L"%c:\\", wchFilePath[0]);
		LPCTSTR lpRootPathName = wchRootPathName;
		LPTSTR lpVolumeNameBuffer = new wchar_t[_MAX_FNAME];
		DWORD nVolumeNameSize = _MAX_FNAME;
		DWORD nVolumeSerialNumber = 0;//������������Чʱ���ж�
		DWORD nMaximumComponentLength;
		DWORD nFileSystemFlags;
		LPTSTR lpFileSystemNameBuffer = new wchar_t[20];//�ļ�ϵͳ(NTFS,FAT)����ж���õĺ���
		DWORD nFileSystemNameSize = 20;
		GetVolumeInformationW(
			lpRootPathName,
			lpVolumeNameBuffer,
			nVolumeNameSize,
			&nVolumeSerialNumber, 
			&nMaximumComponentLength,
			&nFileSystemFlags,
			lpFileSystemNameBuffer,
			nFileSystemNameSize);

		delete[] lpVolumeNameBuffer;
		delete[] lpFileSystemNameBuffer;

		// ���ƶ�����
		if (DRIVE_REMOVABLE == GetDriveTypeW(lpRootPathName))
		{
			if (nVolumeSerialNumber != 0)
			{
				_snwprintf_s(pwchUSBSN, 50, _TRUNCATE, L"%X", nVolumeSerialNumber);
			}
			else
			{
				dw = 0x02;
			}
		}
		else
		{
			dw = 0x03;
		}
	}

	return dw;

}