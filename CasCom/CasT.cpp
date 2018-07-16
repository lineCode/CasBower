// NanhuaAS.cpp
#include "StdAfx.h"
#include "CasT.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <time.h>

const BYTE auchCRCHi[]=  
{  
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,  
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,  
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,  
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,  
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,  
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,  
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
	0x40  
};  

const BYTE auchCRCLo[] =  
{  
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,  
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,  
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,  
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,  
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,  
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,  
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,  
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,  
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,  
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,  
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,  
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,  
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,  
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,  
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,  
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,  
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,  
	0x40  
};

typedef union  
{  
	float fdata;  
	unsigned long ldata;  
}FloatLongType;

const BYTE g_bAd = 0x01;
const BYTE g_bCode = 0x03;

using namespace std;

CasT::CasT(void)
	: m_hComm(INVALID_HANDLE_VALUE)
{
	::InitializeCriticalSection(&m_sCriticalSection);
}

CasT::~CasT(void)
{
	// ��������ʱ,�رմ�����Դ
	Close();

	::DeleteCriticalSection(&m_sCriticalSection);
}
// �򿪴���
DWORD CasT::Open(const BYTE bPort, const int nBaudRate /* = CBR_9600 */, const int nCheck/* =NOPARITY */)
{
	assert(0 != bPort);

	// �ر��Ѵ��ڵĴ��ھ��
	Close();

	wchar_t *pwchPort = new wchar_t[20]();
	swprintf_s(pwchPort, 20, L"\\\\.\\COM%hhu", bPort);
	m_hComm = CreateFileW(pwchPort,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	delete[] pwchPort;
	if (INVALID_HANDLE_VALUE == m_hComm)
	{
		// �򿪴���ʧ��
		OutputDebugStringW(L"Error:fail to open com port\n");
		return SEN_OPEN_FAIL;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////// ��ʼ�����ڲ���begin
	// ��������������������С
	SetupComm(m_hComm, 512, 256);
	// ����DCB�ṹ
	DCB dcb;
	// ��ȡȱʡ��DCB�ṹ��ֵ
	GetCommState(m_hComm, &dcb);
	// �趨������
	dcb.BaudRate = nBaudRate; //change for qin
	// �趨У��
	dcb.Parity = nCheck;
	// �趨����λΪ8
	dcb.ByteSize = 8;
	// �趨һ��ֹͣλ
	dcb.StopBits = ONESTOPBIT;
	// ���ô����豸���Ʋ���
	SetCommState(m_hComm, &dcb);
	// ���г�ʱ���ã�3000����֮��Ҫִ�����д������
	COMMTIMEOUTS CommTimeouts;
	CommTimeouts.ReadIntervalTimeout = 100;// �������ʱ
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;// ��ʱ��ϵ��
	CommTimeouts.ReadTotalTimeoutConstant = 2000;// ��ʱ�䳣��
	CommTimeouts.WriteTotalTimeoutMultiplier = 0;// дʱ��ϵ��
	CommTimeouts.WriteTotalTimeoutConstant = 1000;// дʱ�䳣��
	SetCommTimeouts(m_hComm, &CommTimeouts);
	/////////////////////////////////////////////////////////////////////////////////////////////// ��ʼ�����ڲ���end
	return SEN_OPEN_SUCCEED;
}

bool CasT::IsOpen(void) const
{
	return m_hComm != INVALID_HANDLE_VALUE;
}
// �رմ���
DWORD CasT::Close(void)
{
	if (IsOpen())
	{
		BOOL b = CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
		if (b)
		{
			// �رմ��ڳɹ�
			return SEN_CLOSE_SUCCEED;
		}
		else
		{
			// �رմ���ʧ�ܣ�ִ��win32����ʧ��
			return SEN_CLOSE_FAIL_WIN32_API;
		}
	}
	else
	{
		// �رմ���ʧ�ܣ�����û�гɹ���
		return SEN_CLOSE_FAIL_NO_OPEN_PORT;
	}
}

DWORD CasT::WriteData(BYTE *const pbWriteBuffer,
	const DWORD dwWriteLength,
	const bool bNeedWriteChkSum,
	const bool bPurgeComm)
{
	assert(NULL != pbWriteBuffer);

	::EnterCriticalSection(&m_sCriticalSection);
	if(IsOpen())
	{
		// �ɹ�д��������ֽ���
		DWORD dwBytesWritten(0);

		// �ж��Ƿ����ô��ڲ���
		if (bPurgeComm)
		{
			PurgeComm(m_hComm, PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT);
		}

		// �ж�д�������Ƿ���Ҫ����У��
		if (dwWriteLength>1 && bNeedWriteChkSum)
		{
			pbWriteBuffer[dwWriteLength-3] = CheckSum(pbWriteBuffer, dwWriteLength-3);
		}
		//�������ݰ�β**************************************

		if (WriteFile(m_hComm, pbWriteBuffer, dwWriteLength, &dwBytesWritten, NULL))
		{
			::LeaveCriticalSection(&m_sCriticalSection);
			return SEN_WR_SUCCEED;
		}
		else
		{
			::LeaveCriticalSection(&m_sCriticalSection);
			return SEN_WR_WRITE_SPECIFIED_DATA_FAIL;
		}
	}
	else
	{
		::LeaveCriticalSection(&m_sCriticalSection);
		// �������󣺴���û�д�
		return SEN_WR_PORT_NOT_OPEN;
	}
}

DWORD CasT::ReadData(BYTE *const pbReadBuffer,
	const DWORD dwReadLength,
	const bool bDecryption,
	const bool bNeedReadChkSum)
{
	assert(NULL!=pbReadBuffer);
	assert(0UL!=dwReadLength);

	::EnterCriticalSection(&m_sCriticalSection);
	if(IsOpen())
	{
		// �ɹ������������ֽ���
		DWORD dwBytesRead(0);

		// һ�ζ���Ԥ��Ҫ���յ��ֽ���
		BOOL bSucceed = ReadFile(m_hComm, pbReadBuffer, dwReadLength, &dwBytesRead, NULL);
		PurgeComm(m_hComm, PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT);
		if (bSucceed && dwReadLength==dwBytesRead)
		{
			::LeaveCriticalSection(&m_sCriticalSection);
			// �����ɹ�
			return SEN_WR_SUCCEED;
		}
		else
		{
			::LeaveCriticalSection(&m_sCriticalSection);
			// �������󣺶�ָ������ʧ��
			return SEN_WR_READ_SPECIFIED_DATA_FAIL;
		}
	}
	else
	{
		::LeaveCriticalSection(&m_sCriticalSection);
		// �������󣺴���û�д�
		return SEN_WR_PORT_NOT_OPEN;
	}
}

BYTE CasT::CheckSum(const BYTE *const pb, const UINT un)
{
	assert(NULL!=pb && 0UL!=un);

	BYTE bSum(0);
	for (UINT ui=0; ui<un; ui++)
	{
		bSum += pb[ui];
	}
	// ȡ����һ
	bSum = ~bSum + 1;
	return bSum;
}

// 
DWORD CasT::GetData(const short sType, float *const pfResult)
{
	BYTE bReadBuf[50];

	ZeroMemory(bReadBuf, sizeof(bReadBuf));

	DWORD dw = ReadData(bReadBuf, 50);

	//if (SEN_WR_SUCCEED == dw)
	{
		// ��ʼֵ
		if (NULL != pfResult)
		{
			string strSrc, strDec;
			strSrc = (char*)bReadBuf;
			int nStart(0);
			int nEnd(0);
			dw = 0x02;
			bool bSub(false);//����

			if (sType == 1)
			{
				while ((nStart= strSrc.find("GS", nStart))!=string::npos && strSrc.size()>(nStart+14))
				{
					strDec = strSrc.substr(nStart+13, 2);

					if (strDec == "\r\n")
					{
						strDec = strSrc.substr(nStart+2, 1);
						if (strDec == "-")
						{
							bSub = true;
						}
						strDec = strSrc.substr(nStart+4, 12);
						string::iterator it;
						for (it =strDec.begin(); it!=strDec.end();)
						{
							if (*it == ' ' || *it == 0x67 || *it == 0x6B || *it == 0x2C)
							{
								strDec.erase(it);
							}
							else
							{
								++it;
							}
						}
						if (bSub)
						{
							*pfResult = -atof(strDec.c_str());
						} 
						else
						{
							*pfResult = atof(strDec.c_str());
						}

						dw = 0x00;
						break;
					}
					nStart += 2;
					// ����Э��
				}
			}
			else if (sType == 2)
			{
				while ((nStart= strSrc.find("GS", nStart))!=string::npos && strSrc.size()>(nStart+15))
				{
					strDec = strSrc.substr(nStart+14, 2);

					if (strDec == "\r\n")
					{
						strDec = strSrc.substr(nStart+3, 1);
						if (strDec == "-")
						{
							bSub = true;
						}
						strDec = strSrc.substr(nStart+5, 11);
						string::iterator it;
						for (it =strDec.begin(); it!=strDec.end();)
						{
							if (*it == ' ' || *it == 0x67 || *it == 0x6B || *it == 0x2C)
							{
								strDec.erase(it);
							}
							else
							{
								++it;
							}
						}
						if (bSub)
						{
							*pfResult = -atof(strDec.c_str());
						} 
						else
						{
							*pfResult = atof(strDec.c_str());
						}
						dw = 0x00;
						break;
					}
					nStart += 2;
					// ����Э��
				}
			}
			else if (sType==3 || sType==4)
			{
				while ((nStart= strSrc.find("GS", nStart))!=string::npos && strSrc.size()>(nStart+13))
				{
					strDec = strSrc.substr(nStart+12, 2);

					if (strDec == "\r\n")
					{
						strDec = strSrc.substr(nStart+2, 1);
						if (strDec == "-")
						{
							bSub = true;
						}
						strDec = strSrc.substr(nStart+4, 12);
						string::iterator it;
						for (it =strDec.begin(); it!=strDec.end();)
						{
							if (*it == ' ' || *it == 0x67 || *it == 0x6B || *it == 0x2C)
							{
								strDec.erase(it);
							}
							else
							{
								++it;
							}
						}
						if (bSub)
						{
							*pfResult = -atof(strDec.c_str());
						} 
						else
						{
							*pfResult = atof(strDec.c_str());
						}
						dw = 0x00;
						break;
					}
					nStart += 2;
					// ����Э��
				}
			}




			if (dw == 0x00)
			{
				//���ȶ�
				if (strSrc.find("US") != string::npos)
				{
					dw = 0x01;
				}
				else
				{
					dw = 0x00;
				}
			}
		}
	}
	//else
	//{
	//	dw = 0x01;
	//}

	return dw;
}

DWORD CasT::GetData(float *const pfResult)
{
	BYTE bReadBuf[50]= {0};

	ZeroMemory(bReadBuf, sizeof(bReadBuf));

	DWORD dw = ReadData(bReadBuf, 50);

	// ��ʼֵ
	if (NULL != pfResult)
	{
		string strSrc, strDec;
		strSrc = (char*)bReadBuf;
		int nStart(0);
		int nEnd(0);
		dw = 0x02;
		bool bSub(false);//����

		while ((nStart= strSrc.find(02, nStart))!=string::npos && strSrc.size()>(nStart+13))
		{
			strDec = strSrc.substr(nStart+12, 2);

			if (strDec == "\r\n")
			{
				strDec = strSrc.substr(nStart+1, 1);
				if (strDec == "-")
				{
					bSub = true;
				}
				strDec = strSrc.substr(nStart+2, 10);
				string::iterator it;
				for (it =strDec.begin(); it!=strDec.end();)
				{
					if (*it == ' ' || *it == 0x47 || *it == 0x4B)
					{
						strDec.erase(it);
					}
					else
					{
						++it;
					}
				}
				if (bSub)
				{
					*pfResult = -atof(strDec.c_str());
				} 
				else
				{
					*pfResult = atof(strDec.c_str());
				}
				dw = 0x00;
				break;
			}
			nStart += 2;
			// ����Э��
		}

	}



	return dw;
}

DWORD CasT::SetData(const float fData)
{
	return 0x00;
}

DWORD CasT::SetZero(void)
{
	return 0x00;
}

void CasT::GetSum(int *pnData, int nLength, char *chSendBuf)
{
	int nSum(0), nOne(0), nTen(0), count(0);
	//char chSendBuf[100] = {0};

	for(int i=1; i<nLength; i++)
	{
		nSum = nSum + pnData[i];	
	}

	nTen = nSum%0x100/0x10+0x30;
	nOne = nSum%0x10+0x30;
	if(nTen > 0x39)
		nTen = nTen+0x07;
	if(nOne > 0x39)
		nOne = nOne+0x07;

	for(int i=0; i<nLength; i++)
	{
		chSendBuf[i] = pnData[i];
		count++;
	}

	chSendBuf[count++] = nTen;
	chSendBuf[count++] = nOne;
	chSendBuf[count++] = 0x0D;
	chSendBuf[count++] = 0x0A;
	chSendBuf[count++] = '\0';

}

int CasT::CheckOpen(char *pchPort)
{
	char chSendBuf[100] = {0};
	int nTmp[15] = {0x05,0x30,0x30,0x46,0x46,0x42,0x52,0x33};
	//for(int i=0; i<8; i++)
	//	nTmp[i] = ReadCode[i];

	for(int i=8,j=0; i<13; i++,j++)
		nTmp[i] = pchPort[j];

	nTmp[13] = 0x30;
	nTmp[14] = 0x31;

	GetSum(nTmp, 15, chSendBuf);
	DWORD dw = WriteData((BYTE*)chSendBuf, 19);
	//д��֮��Ҫ��ʱ��ȡ
	//Sleep(100);
	BYTE bReadBuf[20] = {0};
	dw = ReadData(bReadBuf, 10);


	//if(!readPlc(channel))
	//	return -1;

	if(bReadBuf[5] == 0x30)
		return 0;//��
	else if(bReadBuf[5] == 0x31)
		return 1;//��


	return -1;

}

/*
int channel��ͨ�Ŷ˿�
char port[]��PLC��Ӧ�Ķ˿�
bool On���Ƿ�򿪶�Ӧ�˿ڣ�Ϊ��ʱΪ�رն˿ڲ���
*/
bool CasT::ForceBit(char *pchPort, bool bOn)
{
	char chSendBuf[100] = {0};
	int nTmp[16] = {0x05,0x30,0x30,0x46,0x46,0x42,0x57,0x33};
	//for(int i=0;i<8;i++)
	//	nTmp[i]=WriteCode[i];


	for(int i=8,j=0; i<13; i++,j++)
		nTmp[i] = pchPort[j];


	nTmp[13] = 0x30;
	nTmp[14] = 0x31;
	if(bOn)
		nTmp[15] = 0x31;
	else
		nTmp[15] = 0x30;


	GetSum(nTmp,16, chSendBuf);

	if(SEN_WR_SUCCEED != WriteData((BYTE*)chSendBuf, 20))
		return true;
	else
		return false;
}

DWORD CasT::WriteAndReadData(BYTE *const pbWriteBuffer, 
									  const DWORD dwWriteLength, 
									  BYTE *const pbReadBuffer, 
									  const DWORD dwReadLength, 
									  const bool bNeedWriteChkSum, 
									  const bool bNeedReadChkSum, 
									  const bool bPurgeComm)
{
	assert(NULL!=pbWriteBuffer);
	assert(0UL!=dwWriteLength);
	assert(NULL!=pbReadBuffer);
	assert(0UL!=dwReadLength);

	::EnterCriticalSection(&m_sCriticalSection);
	if(IsOpen())
	{
		// �ɹ�д��������ֽ���
		DWORD dwBytesWritten(0);
		// �ɹ������������ֽ���
		DWORD dwBytesRead(0);

		// �ж��Ƿ����ô��ڲ���
		if (bPurgeComm)
		{
			PurgeComm(m_hComm, PURGE_RXCLEAR|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_TXABORT);
		}

		// �ж��Ƿ���Ҫ����д���ݲ���
		if (NULL != pbWriteBuffer)
		{
			// ��Ҫ����д�����ݲ���

			// �ж�д�������Ƿ���Ҫ����У��
			if (dwWriteLength>1 && bNeedWriteChkSum)
			{
				pbWriteBuffer[dwWriteLength-1] = CheckSum(pbWriteBuffer, dwWriteLength-1);
			}
			WriteFile(m_hComm, pbWriteBuffer, dwWriteLength, &dwBytesWritten, NULL);
		}

		// һ�ζ���Ԥ��Ҫ���յ��ֽ���

		BOOL bSucceed = ReadFile(m_hComm, pbReadBuffer, dwReadLength, &dwBytesRead, NULL);
		if (bSucceed && dwReadLength==dwBytesRead)
		{
			if (dwReadLength>1 && bNeedReadChkSum)
			{
				// ��֤У���
				if (pbReadBuffer[dwReadLength-1] != CheckSum(pbReadBuffer, dwReadLength-1))
				{
					::LeaveCriticalSection(&m_sCriticalSection);

					// ��������У���������ʧ��
					return SEN_WR_CHECK_SUM_FAIL;
				}
				else
				{
					::LeaveCriticalSection(&m_sCriticalSection);

					// �����ɹ�
					return SEN_WR_SUCCEED;
				}
			}
			else
			{
				::LeaveCriticalSection(&m_sCriticalSection);

				// �����ɹ�
				return SEN_WR_SUCCEED;
			}
		}
		else
		{
			::LeaveCriticalSection(&m_sCriticalSection);

			// �������󣺶�ָ������ʧ��
			return SEN_WR_READ_SPECIFIED_DATA_FAIL;
		}
	}
	else
	{
		::LeaveCriticalSection(&m_sCriticalSection);

		// �������󣺴���û�д�
		return SEN_WR_PORT_NOT_OPEN;
	}
}

bool CasT::GetAllCyStatus(BYTE *const pbStatus, const DWORD dwReadLength)
{
	BYTE bWriteBuf[9] = {1, 2, 3};
	BYTE bReadBuf[8] = {0};
	//ZeroMemory(bReadBuf, sizeof(bReadBuf));
	DWORD dw = WriteAndReadData(bWriteBuf, 9, bReadBuf, 8, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{
		//// (1) ET�������¶�
		//// ����Ϊ�����߸���,���shortǿ��ת��
		//*pfET = (short)(MAKEWORD(bReadBuf[2], bReadBuf[1])) / 10.0f;
		//// (2) AP������ѹ��
		//// ����Ϊ�����߸���,���shortǿ��ת��
		//*pfAP = (short)(MAKEWORD(bReadBuf[4], bReadBuf[3])) / 10.0f;
		//// (3) RH�����ʪ��
		//*pfRH = (short)(MAKEWORD(bReadBuf[6], bReadBuf[5])) / 10.0f;
		for (int i=0; i<dwReadLength; i++)
		{
			pbStatus[i] = bReadBuf[i];
		}

		return true;
	}

	return false;
}

UINT CasT::FlowCheck(BYTE * puchMsg, UINT usDataLen) 
{
	BYTE uchCRCHi = 0xFF;               /* ��CRC�ֽڳ�ʼ�� */ 
	BYTE uchCRCLo = 0xFF;               /* ��CRC �ֽڳ�ʼ�� */ 
	BYTE uIndex;                        /* CRCѭ���е����� */ 
	while (usDataLen--)                  /* ������Ϣ������ */ 
	{ 
		uIndex = uchCRCHi ^ *puchMsg++;   /* ����CRC */ 
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
		uchCRCLo = auchCRCLo[uIndex];
	}
	return (uchCRCHi << 8 | uchCRCLo);
}


float CasT::Data2Float(BYTE FloatByte1, BYTE FloatByte2, BYTE FloatByte3, BYTE FloatByte4)
{   
	FloatLongType fl;  
	fl.ldata = 0;  
	fl.ldata = FloatByte1;  
	fl.ldata = (fl.ldata<<8)|FloatByte2;  
	fl.ldata = (fl.ldata<<8)|FloatByte3;  
	fl.ldata = (fl.ldata<<8)|FloatByte4;  
	return fl.fdata;
}

//��˲ʱ����
bool CasT::GetFlowRTRateData(float *const pfData)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = 0x01;                 
	bWriteBuf[1] = 0x03;                  
	bWriteBuf[2] = 0x07;             
	bWriteBuf[3] = 0xD8;
	bWriteBuf[4] = 0x00;              
	bWriteBuf[5] = 0x02;
	bWriteBuf[6] = 0x45;               
	bWriteBuf[7] = 0x44;               
	BYTE bReadBuf[9] = {0};
	//ZeroMemory(bReadBuf, sizeof(bReadBuf));
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 9, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==0x01
			&& bReadBuf[1]==0x03
			&& bReadBuf[2]==0x04)
		{
			*pfData = Data2Float(bReadBuf[3],bReadBuf[4],bReadBuf[5],bReadBuf[6]);
			return true;
		}		
	}
	return false;
}

//��˲ʱ����
bool CasT::GetFlowRTSpeedData(float *const pfData)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = g_bAd;                  //�豸��ַ
	bWriteBuf[1] = g_bCode;                  //modbus������
	bWriteBuf[2] = 0x1012 / 256;             //StartΪ�Ĵ�����ַ
	bWriteBuf[3] = 0x1012 % 256;
	bWriteBuf[4] = 0x02 / 256;               //LenΪ��ȡ�Ĵ�������
	bWriteBuf[5] = 0x02 % 256;
	uiCRCWrite = FlowCheck(bWriteBuf, 6);
	bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	BYTE bReadBuf[9] = {0};
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 9, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==g_bAd
			&& bReadBuf[1]==g_bCode
			&& bReadBuf[2]==4)
		{
			uiCRCRead = FlowCheck(bReadBuf, 7);
			if (bReadBuf[7] == (uiCRCRead>>8)
				&& bReadBuf[8] == (uiCRCRead & 0x00ff))
			{
				*pfData = Data2Float(bReadBuf[3],bReadBuf[4],bReadBuf[5],bReadBuf[6]);
				return true;
			}
		}		
	}
	return false;
}

//���ۻ�����
bool CasT::GetFlowAllRateData(float *const pfData)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = 0x01;                 
	bWriteBuf[1] = 0x03;                  
	bWriteBuf[2] = 0x0A;             
	bWriteBuf[3] = 0x31;
	bWriteBuf[4] = 0x00;              
	bWriteBuf[5] = 0x02;
	bWriteBuf[6] = 0x96;               
	bWriteBuf[7] = 0x1C;               
	BYTE bReadBuf[9] = {0};
	//ZeroMemory(bReadBuf, sizeof(bReadBuf));
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 9, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==0x01
			&& bReadBuf[1]==0x03
			&& bReadBuf[2]==0x04)
		{
			*pfData = Data2Float(bReadBuf[3],bReadBuf[4],bReadBuf[5],bReadBuf[6]);
			return true;
		}		
	}
	return false;
}

bool CasT::GetFlowAllRateData1(long *const plData)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = g_bAd;                  //�豸��ַ
	bWriteBuf[1] = g_bCode;                  //modbus������
	bWriteBuf[2] = 0x1018 / 256;             //StartΪ�Ĵ�����ַ
	bWriteBuf[3] = 0x1018 % 256;
	bWriteBuf[4] = 0x02 / 256;               //LenΪ��ȡ�Ĵ�������
	bWriteBuf[5] = 0x02 % 256;
	uiCRCWrite = FlowCheck(bWriteBuf, 6);
	bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	BYTE bReadBuf[9] = {0};
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 9, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==g_bAd
			&& bReadBuf[1]==g_bCode
			&& bReadBuf[2]==4)
		{
			uiCRCRead = FlowCheck(bReadBuf, 7);
			if (bReadBuf[7] == (uiCRCRead>>8)
				&& bReadBuf[8] == (uiCRCRead & 0x00ff))
			{
				*plData = bReadBuf[3]*256*256*256 + bReadBuf[4]*256*256 + bReadBuf[5]*256 + bReadBuf[6];
				return true;
			}
		}		
	}
	return false;
}

bool CasT::GetFlowAllRateData2(float *const pfData)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = g_bAd;                  //�豸��ַ
	bWriteBuf[1] = g_bCode;                  //modbus������
	bWriteBuf[2] = 0x101A / 256;             //StartΪ�Ĵ�����ַ
	bWriteBuf[3] = 0x101A % 256;
	bWriteBuf[4] = 0x02 / 256;               //LenΪ��ȡ�Ĵ�������
	bWriteBuf[5] = 0x02 % 256;
	uiCRCWrite = FlowCheck(bWriteBuf, 6);
	bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	BYTE bReadBuf[9] = {0};
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 9, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==g_bAd
			&& bReadBuf[1]==g_bCode
			&& bReadBuf[2]==4)
		{
			uiCRCRead = FlowCheck(bReadBuf, 7);
			if (bReadBuf[7] == (uiCRCRead>>8)
				&& bReadBuf[8] == (uiCRCRead & 0x00ff))
			{
				*pfData = Data2Float(bReadBuf[3],bReadBuf[4],bReadBuf[5],bReadBuf[6]);
				return true;
			}
		}		
	}
	return false;
}

//��˲ʱ������λ
bool CasT::GetFlowRTRateUnit(UINT *const pType)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = g_bAd;                  //�豸��ַ
	bWriteBuf[1] = g_bCode;                  //modbus������
	bWriteBuf[2] = 0x1020 / 256;             //StartΪ�Ĵ�����ַ
	bWriteBuf[3] = 0x1020 % 256;
	bWriteBuf[4] = 0x01 / 256;               //LenΪ��ȡ�Ĵ�������
	bWriteBuf[5] = 0x01 % 256;
	uiCRCWrite = FlowCheck(bWriteBuf, 6);
	bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	BYTE bReadBuf[7] = {0};
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 7, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==g_bAd
			&& bReadBuf[1]==g_bCode
			&& bReadBuf[2]==2)
		{
			uiCRCRead = FlowCheck(bReadBuf, 5);
			if (bReadBuf[5] == (uiCRCRead>>8)
				&& bReadBuf[6] == (uiCRCRead & 0x00ff))
			{
				*pType = bReadBuf[3]<<8 + bReadBuf[4];
				return true;
			}
		}		
	}
	return false;
}

//������������λ
bool CasT::GetFlowAllRateUnit(UINT *const pType)
{
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = g_bAd;                  //�豸��ַ
	bWriteBuf[1] = g_bCode;                  //modbus������
	bWriteBuf[2] = 0x1021 / 256;             //StartΪ�Ĵ�����ַ
	bWriteBuf[3] = 0x1021 % 256;
	bWriteBuf[4] = 0x01 / 256;               //LenΪ��ȡ�Ĵ�������
	bWriteBuf[5] = 0x01 % 256;
	uiCRCWrite = FlowCheck(bWriteBuf, 6);
	bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	BYTE bReadBuf[7] = {0};
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 7, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==g_bAd
			&& bReadBuf[1]==g_bCode
			&& bReadBuf[2]==2)
		{
			uiCRCRead = FlowCheck(bReadBuf, 5);
			if (bReadBuf[5] == (uiCRCRead>>8)
				&& bReadBuf[6] == (uiCRCRead & 0x00ff))
			{
				*pType = bReadBuf[3]<<8 + bReadBuf[4];
				return true;
			}
		}		
	}
	return false;
}

//������״̬
bool CasT::GetFlowAlarm(UINT *const pType)
{
	//BYTE bWriteBuf[8] = {0};
	//UINT uiCRCWrite, uiCRCRead;
	//BYTE bAd = 0x01;
	//bWriteBuf[0] = g_bAd;                  //�豸��ַ
	//bWriteBuf[1] = g_bCode;                  //modbus������
	//bWriteBuf[2] = 0x1024 / 256;             //StartΪ�Ĵ�����ַ
	//bWriteBuf[3] = 0x1024 % 256;
	//bWriteBuf[4] = 0x01 / 256;               //LenΪ��ȡ�Ĵ�������
	//bWriteBuf[5] = 0x01 % 256;
	//uiCRCWrite = FlowCheck(bWriteBuf, 6);
	//bWriteBuf[6] = uiCRCWrite >> 8;               //CRCУ���λ
	//bWriteBuf[7] = uiCRCWrite & 0x00ff;               //CRCУ���λ
	//BYTE bReadBuf[7] = {0};
	//DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 7, false, false, true);
	//if (SEN_WR_SUCCEED == dw)
	//{		
	//	if (bReadBuf[0]==g_bAd
	//		&& bReadBuf[1]==g_bCode
	//		&& bReadBuf[2]==2)
	//	{
	//		uiCRCRead = FlowCheck(bReadBuf, 5);
	//		if (bReadBuf[5] == (uiCRCRead>>8)
	//			&& bReadBuf[6] == (uiCRCRead & 0x00ff))
	//		{
	//			*pType = bReadBuf[3]<<8 + bReadBuf[4];
	//			return true;
	//		}
	//	}		
	//}
	//return false;
	BYTE bWriteBuf[8] = {0};
	UINT uiCRCWrite, uiCRCRead;
	BYTE bAd = 0x01;
	bWriteBuf[0] = 0x01;                 
	bWriteBuf[1] = 0x03;                  
	bWriteBuf[2] = 0x1A;             
	bWriteBuf[3] = 0xCA;
	bWriteBuf[4] = 0x00;              
	bWriteBuf[5] = 0x01;
	bWriteBuf[6] = 0xA3;               
	bWriteBuf[7] = 0x2C;               
	BYTE bReadBuf[7] = {0};
	//ZeroMemory(bReadBuf, sizeof(bReadBuf));
	DWORD dw = WriteAndReadData(bWriteBuf, 8, bReadBuf, 7, false, false, true);
	if (SEN_WR_SUCCEED == dw)
	{		
		if (bReadBuf[0]==0x01
			&& bReadBuf[1]==0x03
			&& bReadBuf[2]==0x02
			&& bReadBuf[3]==0x00
			&& bReadBuf[4]==0x01 )
		{
			return true;
		}		
	}
	return false;
}

int CasT::PLCRead(const char *pchPort)
{
	char chSendBuf[100] = {0x05, 0x46, 0x39, 0x30, 0x30, 0x30, 0x30, 0x46, 0x46, 0x30, 0x30, 0x30, 0x34, 0x30, 0x31, 0x30, 0x30, 0x30, 0x31};
	//for(int i=0; i<8; i++)
	//	nTmp[i] = ReadCode[i];

	for(int i=19,j=0; i<27; i++,j++)
		chSendBuf[i] = pchPort[j];

	chSendBuf[27] = 0x30;
	chSendBuf[28] = 0x30;
	chSendBuf[29] = 0x30;
	chSendBuf[30] = 0x31;
	chSendBuf[31] = 0x0D;
	chSendBuf[32] = 0x0A;
	chSendBuf[33] = 0x00;

	DWORD dw = WriteData((BYTE*)chSendBuf, 33);
	//д��֮��Ҫ��ʱ��ȡ
	//Sleep(100);
	BYTE bReadBuf[20] = {0};
	dw = ReadData(bReadBuf, 15);

	//if(!readPlc(channel))
	//	return -1;

	if(bReadBuf[11] == 0x30)
		return PLC_PROT_DUAN;//�� �Ͽ�
	else if(bReadBuf[11] == 0x31)
		return PLC_PROT_BIHE;//�� �պ�


	return PLC_PROT_ERROR;

}

/*
int channel��ͨ�Ŷ˿�
char port[]��PLC��Ӧ�Ķ˿�
bool On���Ƿ�򿪶�Ӧ�˿ڣ�Ϊ��ʱΪ�رն˿ڲ���
*/
bool CasT::PLCSet(const char *pchPort, bool bOn)
{
	char chSendBuf[100] = {0x05, 0x46, 0x39, 0x30, 0x30, 0x30, 0x30, 0x46, 0x46, 0x30, 0x30, 0x31, 0x34, 0x30, 0x31, 0x30, 0x30, 0x30, 0x31};


	for(int i=19,j=0; i<27; i++,j++)
		chSendBuf[i] = pchPort[j];


	chSendBuf[27] = 0x30;
	chSendBuf[28] = 0x30;
	chSendBuf[29] = 0x30;
	chSendBuf[30] = 0x31;
	chSendBuf[32] = 0x0D;
	chSendBuf[33] = 0x0A;
	chSendBuf[34] = 0x00;
	if(bOn)
		chSendBuf[31] = 0x31;
	else
		chSendBuf[31] = 0x30;
	
	DWORD dw = WriteData((BYTE*)chSendBuf, 34);


	BYTE bReadBuf[20] = {0};
	dw = ReadData(bReadBuf, 13);

	//if(!readPlc(channel))
	//	return -1;

	if(bReadBuf[0] == 0x06)
		return true;//�ɹ�
	else 
		return false;//ʧ��
}
