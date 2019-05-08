#include "Connection.h"



bool Connection::Send(void)
{

	return true;
}

bool Connection::Receive(void)
{
	return true;
}

void Connection::SetSendData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF)
{
	sendData.PreyPos = p_pos;
	sendData.ItPos = i_pos;
	sendData.deathFlag = deathF;
}

void Connection::SetReceiveData(VECTOR2 p_pos, VECTOR2 i_pos,bool deathF)
{
	receiveData.PreyPos = p_pos;
	receiveData.ItPos = i_pos;
	receiveData.deathFlag = deathF;
}

Connection::Connection()
{
	//NetUDPHandle = MakeUDPSocket(9850);

	sendData.PreyPos = { 0,0 };
	sendData.ItPos = { 0,0 };
}


Connection::~Connection()
{
	DeleteUDPSocket(NetUDPHandle);
}
