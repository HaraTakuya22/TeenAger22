#pragma once
#include <DxLib.h>

#include "VECTOR2.h"

#define lpConnect Connection::GetIns()

// ‚à‚¤ˆê‘ä‚ÌÊß¿ºİ‚É“n‚µ‚Ä‚ ‚°‚éî•ñ
struct Data
{
	// ÌßÚ²Ô°‚ÌÎß¼Ş¼®İ
	VECTOR2 PreyPos;
	// ‹S‚ÌÎß¼Ş¼®İ
	VECTOR2 ItPos;

	// €‚ñ‚¾Ì×¸Ş
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

	// ‘—‚éÃŞ°À‚Ì¾¯Ä
	// p_pos:ÌßÚ²Ô°‚ÌÎß¼Ş¼®İ i_pos:‹S‚ÌÎß¼Ş¼®İ deathF:€‚ñ‚¾‚©‚ÌÌ×¸Ş
	void SetSendData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);
	// ó‚¯æ‚éÃŞ°À‚Ì¾¯Ä
	void SetReceiveData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF);

	// ó‚¯æ‚Á‚½ÃŞ°À‚ğæ“¾
	const Data& GetReceiveData()
	{
		return receiveData;
	}

	// ‘—‚Á‚½ÃŞ°À‚ğæ“¾
	const Data& GetSendData()
	{
		return sendData;
	}

private:

	Connection();
	~Connection();

	// UDP’ÊM—p‚ÌSocketÊİÄŞÙ‚ğì¬
	int NetUDPHandle;
	// ‘—‚é•û‚ÌÃŞ°À
	Data sendData;
	// ó‚¯æ‚é•û‚ÌÃŞ°À
	Data receiveData;
};

