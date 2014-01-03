#include "Server.h"

//--------------------------------------------------------------------------------------

#include <time.h>

#include <CEGUI.h>

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Server::Server()
{

};

NL::Scene::Objects::Server::~Server()
{
	Shutdown = true;
};

bool NL::Scene::Objects::Server::Start()
{
	Shutdown = false;

	sock = nlOpen(7000,NL_TCP_PACKETS);

	if(sock == NL_INVALID)
		Net::NetError();

	if(!nlListen(sock)) 
	{
		nlClose(sock);
		Net::NetError();
	}

	htThreadCreate(&NL::Scene::Objects::Server::ServerLoop,this,NL_FALSE);

	return true;
};

void *NL::Scene::Objects::Server::ServerLoop(void *args)
{
	Server *server = (Server *)args;

	while(!server->Shutdown)
	{
		NLsocket newsock = nlAcceptConnection(server->sock);

		if(newsock != NL_INVALID)
		{
			NLaddress   addr;

			nlGetRemoteAddr(newsock,&addr);

			char buffer[1024] = "";

			int readlen = nlRead(newsock,buffer,sizeof(buffer));

			if (readlen > 0)
			{
				//CEGUI::Window *wnd = CEGUI::WindowManager::getSingleton().getWindow("List");
				//wnd->setText(wnd->getText()+(CEGUI::utf8 *)"\nClient connected...");
				//wnd->setText(wnd->getText()+(CEGUI::utf8 *)" "+(CEGUI::utf8 *)buffer);
	
				switch(buffer[0])
				{
				/*case 1:
					{
						_Client **newclient = (server->clients[0]) ? &server->clients[1] : &server->clients[0];

						*newclient = new _Client();
						(*newclient)->name = "";

						for (int i = 2; i < buffer[1]+2; i++)
						{
							(*newclient)->name += buffer[i];
						}

						break;
					}*/
				case 2:
				    {
						server->turns.push_back(Turn(Cell(buffer[1],buffer[2]),Cell(buffer[3],buffer[4])));

						break;
					}
				case 3:
					{
						//server->turns.push_back(Turn(buffer[1],buffer[2],buffer[3],buffer[4]));

						if (server->turns.size() == 0)
						{
							char str[5] = { 255, 255, 255, 255, 0 };//+IntToStr(param[4]);

							nlWrite(newsock,&str[0],5);

							break;
						}

						Turn tr = server->turns[server->turns.size()-1];

						char str[5] = { tr.from.x - '0', tr.from.y - '0', tr.to.x - '0', tr.to.y - '0', 0 };//+IntToStr(param[4]);

						nlWrite(newsock,&str[0],5);

						break;
					}
				}
			}
			
			//server->clients.push_back(newclient);

			//nlGroupAddSocket(server->group,newclient.sock);
		}
		else
		{
			NLint err = nlGetError();

			if(err == NL_SYSTEM_ERROR || err == NL_NOT_LISTEN)
			{
				Log::getSingleton().AddLine("WARNING: Server shutting down.","red");
				Net::NetError();
			}
		}

		htThreadYield();
	}

	Log::getSingleton().AddLine("Server shutting down.");

	return NULL;
};