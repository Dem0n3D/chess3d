#include "Client.h"

//--------------------------------------------------------------------------------------

#include <time.h>

#include <CEGUI.h>

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Client::Client()
{

};

NL::Scene::Objects::Client::~Client()
{

};

bool NL::Scene::Objects::Client::Start()
{
	IsReqSended = false;

	NLsocket sock;

	NLaddress   addr;

	sock = nlOpen(0,NL_TCP_PACKETS);

	if(sock == NL_INVALID)
	{
		Net::NetError();
	}

	nlStringToAddr(adress.c_str(),&addr);
	nlSetAddrPort(&addr,7000);

	if(!nlConnect(sock,&addr))
	{
		Net::NetError();
	}

	//ADD_LOG("Connecting...",true);

	//htMutexInit(&mut);

	//--------------------------------------------------------------------------------------

	//String str = '\1' + String(&char(Name.length())) + Name;

	char p[] = { 1, BYTE(Name.length()), 0 };
	String str = p + Name;
	nlWrite(sock,&str[0],NLint(str.size()+1));

	nlClose(sock);

	//htThreadCreate(&NL::Scene::Objects::Client::ClientLoop,this,NL_FALSE);

	return true;
};

void NL::Scene::Objects::Client::OnTurn(void *args)
{
	std::vector<DWORD> param = *((std::vector<DWORD> *)args);

	NLsocket sock;

	NLaddress   addr;

	nlStringToAddr(adress.c_str(),&addr);
	nlSetAddrPort(&addr,7000);

	sock = nlOpen(0,NL_TCP_PACKETS);

	if(!nlConnect(sock,&addr))
	{
		Net::NetError();
	}

	//--------------------------------------------------------------------------------------

	String str = '\2'+IntToStr(param[0])+IntToStr(param[1])+IntToStr(param[2])+IntToStr(param[3]);//+IntToStr(param[4]);

	/*std::vector<DWORD> params(5);
	params[0] = selected.x; // Откуда (горизонталь)
	params[1] = selected.y; // Откуда (вертикаль)
	params[2] = pick.x; // Куда (горизонталь)
	params[3] = pick.y; // Куда (вертикаль)
	params[4] = turns_list.size(); // Номер хода*/

	nlWrite(sock,&str[0],NLint(str.size()+1));
};

bool NL::Scene::Objects::Client::Update(float fElapsedTime)
{
	if (!IsReqSended)
	{			
		IsReqSended = true;

		htThreadCreate(&NL::Scene::Objects::Client::SendRequest,this,NL_FALSE);		
	}
	
	return true;
};

void *NL::Scene::Objects::Client::SendRequest(void *args)
{
	Client *client = (Client *)args;

	NLsocket sock;

	NLaddress   addr;

	nlStringToAddr(client->adress.c_str(),&addr);
	nlSetAddrPort(&addr,7000);

	sock = nlOpen(0,NL_TCP_PACKETS);

	if(!nlConnect(sock,&addr))
	{
		Net::NetError();
	}

	String str = "\3";
	nlWrite(sock,&str[0],NLint(str.size()+1));

	char buffer[1024] = "";

	long start_req_time = clock();

	client->console->lines.push_back("> Время запроса = 0мс.");
	size_t strnum = client->console->lines.size()-1;

// 	static int strnum = -1; 
// 	if (strnum == -1)
// 	{
// 		client->console->lines.push_back("> Время запроса = 0мс.");
// 		strnum = client->console->lines.size()-1;
// 	}	

	while(nlRead(sock,buffer,sizeof(buffer)) <= 0)
	{
		long millisecs = (1000*(clock()-start_req_time))/CLOCKS_PER_SEC;

		client->console->lines[strnum] = "> Время запроса = " + IntToStr(millisecs) + "мс.";

		if (millisecs > 1000)
		{
			// Время запроса превысило 10 секунд!!!

			client->console->lines.push_back("> Время запроса превысило 1 секунду!!!");

			client->IsReqSended = false;

			return NULL;
		}

		htThreadYield();
	}

	if (buffer[0] != -1)
	{
		Cell from(buffer[0],buffer[1]);
		Cell to(buffer[2],buffer[3]);

		//client->console->lines.push_back("> " + String((client->board->at(from)->Get_color()) ? "White" : "Black") + " from (" + IntToStr(from.x) + "," + IntToStr(from.y) + ") to (x2,y2)"); // Жесть, согласе ;-)

		if (client->board->turns_list.size() == 0 || client->board->turns_list[client->board->turns_list.size()-1] != Turn(from,to))
		{
			client->board->MakeTurn(from,to);
		}
	}

	client->IsReqSended = false;

	return NULL;
};