#pragma once
#include <DxLib.h>

#include "VECTOR2.h"

#define lpConnect Connection::GetIns()

// ���������߿�݂ɓn���Ă�������
struct Data
{
	// ��ڲ԰���߼޼��
	VECTOR2 PreyPos;
	// �S���߼޼��
	VECTOR2 ItPos;

	// �����׸�
	bool deathFlag;
};
class Connection
{
public:
	static Connection& GetIns()
	{
		static Connection c_Ins;
		return c_Ins;
	}

	bool Send(void);
	bool Receive(void);

	// �����ް��̾��
	// p_pos:��ڲ԰���߼޼�� i_pos:�S���߼޼�� deathF:���񂾂����׸�
	void SetSendData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);
	// �󂯎���ް��̾��
	void SetReceiveData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);

	// �󂯎�����ް����擾
	const Data& GetReceiveData()
	{
		return receiveData;
	}

	// �������ް����擾
	const Data& GetSendData()
	{
		return sendData;
	}

private:

	Connection();
	~Connection();

	// UDP�ʐM�p��Socket����ق��쐬
	int NetUDPHandle;
	// ��������ް�
	Data sendData;
	// �󂯎������ް�
	Data receiveData;
};

