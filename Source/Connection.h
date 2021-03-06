#pragma once
#include <DxLib.h>

#include "VECTOR2.h"

#define lpConnect Connection::GetIns()

// もう一台のﾊﾟｿｺﾝに渡してあげる情報
struct Data
{
	// ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝ
	VECTOR2 PreyPos;
	// 鬼のﾎﾟｼﾞｼｮﾝ
	VECTOR2 ItPos;

	// 死んだﾌﾗｸﾞ
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

	// 送るﾃﾞｰﾀのｾｯﾄ
	// p_pos:ﾌﾟﾚｲﾔｰのﾎﾟｼﾞｼｮﾝ i_pos:鬼のﾎﾟｼﾞｼｮﾝ deathF:死んだかのﾌﾗｸﾞ
	void SetSendData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);
	// 受け取るﾃﾞｰﾀのｾｯﾄ
	void SetReceiveData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);

	// 受け取ったﾃﾞｰﾀを取得
	const Data& GetReceiveData()
	{
		return receiveData;
	}

	// 送ったﾃﾞｰﾀを取得
	const Data& GetSendData()
	{
		return sendData;
	}

private:

	Connection();
	~Connection();

	// UDP通信用のSocketﾊﾝﾄﾞﾙを作成
	int NetUDPHandle;
	// 送る方のﾃﾞｰﾀ
	Data sendData;
	// 受け取る方のﾃﾞｰﾀ
	Data receiveData;
};

