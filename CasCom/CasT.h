#pragma once

// ����ִ�н��
#define SEN_OPEN_SUCCEED						0x00  // �򿪴��ڳɹ�
#define SEN_OPEN_FAIL							0x01  // �򿪴���ʧ��
#define SEN_CLOSE_SUCCEED						0x00  // �رմ��ڳɹ�
#define SEN_CLOSE_FAIL_WIN32_API				0x01  // �رմ���ʧ�ܣ�ִ��win32 API(CloseHandle)ʧ��
#define SEN_CLOSE_FAIL_NO_OPEN_PORT				0x02  // �رմ���ʧ�ܣ�û�п��ԹرյĴ���
#define SEN_WR_SUCCEED							0x00  // д���ɹ�
#define SEN_WR_PORT_NOT_OPEN					0x01  // д��ʧ�ܣ�����δ��
#define SEN_WR_READ_SPECIFIED_DATA_FAIL			0x02  // д��ʧ�ܣ���ָ������ʧ��
#define SEN_WR_WRITE_SPECIFIED_DATA_FAIL		0x03  // д��ʧ�ܣ�дָ������ʧ��
#define SEN_WR_EQUIP_RETURE_0X15				0x04  // д��ʧ�ܣ��������ش�����루0x15��
#define SEN_WR_CHECK_SUM_FAIL					0x05  // д��ʧ�ܣ���������У���ʧ��
#define SEN_WR_UNKNOWN_ERROR					0xFF  // д��ʧ�ܣ�δ֪����

#define PLC_PROT_ERROR	0
//�򿪷���==�պ�
#define PLC_PROT_BIHE	1
//�رշ���==�Ͽ�
#define PLC_PROT_DUAN	2
#define PLC_SET_OK		3
#define PLC_SET_WRONG	4

#define PLC_OPEN_ERROR	-1

#	ifdef BUILD_CASCOM
#	define CASCOM_EXPORTS __declspec(dllexport)
#else
#	define CASCOM_EXPORTS __declspec(dllimport)
#endif

class CASCOM_EXPORTS CasT
{
public:
	CasT(void);
	~CasT(void);

public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ���ڲ���start
	// �򿪴���
	// �򿪴���ǰ���Զ�ʶ���Ƿ��Ѿ������Ѿ��򿪵Ĵ�����Դ������У��ڴ�֮ǰ���ȹر���ǰ�򿪵Ĵ�����Դ
	// in bPort�����ں�(1~255)
	// in nBaudRate�������� (110��300��600��1200��2400��4800��9600��14400��19200��38400��56000��57600��115200��128000��256000)
	// ���ش򿪽����
	// ANA_OPEN_SUCCEED
	// ANA_OPEN_FAIL
	DWORD Open(const BYTE bPort, const int nBaudRate = CBR_9600, const int nCheck=NOPARITY);

	// �رմ���
	// �Զ�ʶ���Ƿ��п��Բ��رյĴ�����Դ
	// ���عرս����
	// ANA_CLOSE_SUCCEED
	// ANA_CLOSE_FAIL_WIN32API
	// ANA_CLOSE_FAIL_NOOPENPORT
	DWORD Close(void);

	// �жϴ����ǻ��
	bool IsOpen(void) const;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ���ڲ���end

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ��������start 
	// 1ȡʵʱ����
	// (out)pfResult,���
	// ���غ���ִ�н����
	// SEN_WR_SUCCEED
	// SEN_WR_PORT_NOT_OPEN
	// SEN_WR_READ_SPECIFIED_DATA_FAIL
	// SEN_WR_EQUIP_RETURE_0X15
	// SEN_WR_CHECK_SUM_FAIL
	//�ۼ�
	DWORD GetData(const short sType, float *const pfResult = NULL);
	//����
	DWORD GetData(float *const pfResult = NULL);
	// ����
	DWORD SetZero(void);
	// ����SN����
	// SEN_WR_SUCCEED
	// SEN_WR_PORT_NOT_OPEN
	// SEN_WR_READ_SPECIFIED_DATA_FAIL
	// SEN_WR_EQUIP_RETURE_0X15
	// SEN_WR_CHECK_SUM_FAIL
	DWORD SetData(const float fData);
	void GetSum(int *pnData, int nLength, char *chSendBuf); //У��ͼ���ͷ�������ļ���
	int CheckOpen(char *pchPort);
	bool ForceBit(char *pchPort, bool bOn);

	bool GetAllCyStatus(BYTE *const pbStatus, const DWORD dwReadLength);

	//Flow*************
	//��˲ʱ����
	bool GetFlowRTRateData(float *const pfData);	
	//���ۻ�����
	bool GetFlowAllRateData(float *const pfData);
	//������״̬
	bool GetFlowAlarm(UINT *const pType);

	bool PLCSet(const char *pchPort, bool bOn);

	int PLCRead(const char *pchPort);


	//��˲ʱ����
	bool GetFlowRTSpeedData(float *const pfData);
	//��˲ʱ������λ
	bool GetFlowRTRateUnit(UINT *const pType);
	//������������λ
	bool GetFlowAllRateUnit(UINT *const pType);

protected:
	// д����������
	// д����Ӧ�������ȡ��Ӧ�ķ�������
	// ��������Ҫ���ֱ��д��Ͷ�ȡ�����ݽ���У�����֤
	// (in)pbWriteBuffer��Ҫд�����������ָ�룬����Ϊ��ָ�룬���Ϊ��ָ�룬�򲻽���д���ݲ���
	// (in)dwWriteLength��Ҫд������ݳ��ȣ��ֽ���������pbWriteBufferΪ��ָ��ʱ���������������
	// (out)pbReadBuffer��Ҫ��ȡ����������ָ�룬����Ϊ��ָ��
	// (in)dwReadLength��Ҫ��ȡ�����ݳ��ȣ��ֽ�����
	// (in)bNeedWriteChkSum��true����ҪдУ�飬false������Ҫ����pbWriteBufferΪ��ָ��ʱ���������������
	// (in)bNeedReadChkSum��true����Ҫ��У�飬false������Ҫ
	// (in)bPurgeComm,�Ƿ����ô��ڲ���,true,���ô��ڲ���(ִ��PurgeComm����),false,�����ô��ڲ���(��ִ��PurgeComm����)
	// ���أ�����ִ�н����
	// ANA_WR_SUCCEED
	// ANA_WR_PORT_NOT_OPEN
	// ANA_WR_READ_SPECIFIED_DATA_FAIL
	// ANA_WR_EQUIP_RETURE_0X15
	// ANA_WR_CHECK_SUM_FAIL
	DWORD WriteAndReadData(BYTE *const pbWriteBuffer, 
		const DWORD dwWriteLength, 
		BYTE *const pbReadBuffer, 
		const DWORD dwReadLength, 
		const bool bNeedWriteChkSum=true, 
		const bool bNeedReadChkSum=true, 
		const bool bPurgeComm=true);

	// д��������
	// д����Ӧ������
	// (in)pbWriteBuffer��Ҫд�����������ָ�룬����Ϊ��ָ�룬���Ϊ��ָ�룬�򲻽���д���ݲ���
	// (in)dwWriteLength��Ҫд������ݳ��ȣ��ֽ���������pbWriteBufferΪ��ָ��ʱ���������������
	// (in)bNeedWriteChkSum��true����ҪдУ�飬false������Ҫ����pbWriteBufferΪ��ָ��ʱ���������������
	// (in)bPurgeComm,�Ƿ����ô��ڲ���,true,���ô��ڲ���(ִ��PurgeComm����),false,�����ô��ڲ���(��ִ��PurgeComm����)
	// ���أ�����ִ�н����
	// SEN_WR_SUCCEED
	// SEN_WR_PORT_NOT_OPEN
	// SEN_WR_WRITE_SPECIFIED_DATA_FAIL
	DWORD WriteData(BYTE *const pbWriteBuffer,
		const DWORD dwWriteLength,
		const bool bNeedWriteChkSum = false,
		const bool bPurgeComm = true);

	// ����������
	// ��ȡ��Ӧ�ķ�������
	// (out)pbReadBuffer��Ҫ��ȡ����������ָ�룬����Ϊ��ָ��
	// (in)dwReadLength��Ҫ��ȡ�����ݳ��ȣ��ֽ�����
	// (in)bDecryption��true����Ҫ���ܣ�false������Ҫ
	// (in)bNeedReadChkSum��true����Ҫ��У�飬false������Ҫ
	// ���أ�����ִ�н����
	// SEN_WR_SUCCEED
	// SEN_WR_PORT_NOT_OPEN
	// SEN_WR_READ_SPECIFIED_DATA_FAIL
	// SEN_WR_CHECK_SUM_FAIL
	DWORD ReadData(BYTE *const pbReadBuffer,
		const DWORD dwReadLength,
		const bool bDecryption = true,
		const bool bNeedReadChkSum = true);

	// ����ǰnλ��У���
	// ��ӣ�Ȼ��ȡ����ֽ�λ
	// (in)p��Ҫ����У�����������ָ��
	// (in)un��Ҫ����У������ݳ���
	// ����У���
	BYTE CheckSum(const BYTE *const p, const UINT un);

	//Flow******************
	//CRC
	UINT FlowCheck(BYTE * puchMsg, UINT usDataLen);
	float Data2Float(BYTE FloatByte1, BYTE FloatByte2, BYTE FloatByte3, BYTE FloatByte4);

	bool GetFlowAllRateData1(long *const plData);
	bool GetFlowAllRateData2(float *const pfData);
protected:
	// ���ھ��
	HANDLE m_hComm;

private:
	//�ͻ���Ϣ�ٽ籣����
	CRITICAL_SECTION m_sCriticalSection;

};

