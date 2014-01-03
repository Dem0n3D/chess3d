#include "Board.h"

//--------------------------------------------------------------------------------------

#include "../../System.h"

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

const float g_cubeVertices[4][3] =
{
	{ -1.0f, 0.0f,-1.0f },
	{ -1.0f, 0.0f, 1.0f },
	{  1.0f, 0.0f, 1.0f },
	{  1.0f, 0.0f,-1.0f }
};

enum FIGURE_FIGURES { FIGURE_ROOK = 0, FIGURE_HORSE = 1, FIGURE_BISHOP = 2, FIGURE_QUEEN = 3, FIGURE_KING = 4, FIGURE_PAWN = 5 };

////////////////////////////////////////////////////////////////////////////////////////

NL::Scene::Objects::Board::Board()
{

};

NL::Scene::Objects::Board::~Board()
{

};

void NL::Scene::Objects::Board::Initialize()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			B[i][j] = NULL;
		}
	}

	bool bUseVBO = isExtensionSupported("ARB_vertex_buffer_object");

//#define __LOAD_FROM_FILE__ // Если закомментировать эту строку, данные не будут загржуться из файла

#ifdef __LOAD_FROM_FILE__
	
	std::ifstream fi("figures.txt");

	memset(Fcnt,0,12*sizeof(int));

	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			char f;

			fi >> f;

			int fn;

			switch(f)
			{
			case 'r':
				{
					B[j][i] = new Rook();
					B[j][i]->Load("Data/Chess.nlm","Rook");	
					B[j][i]->Set_Name("Pawn_");

					fn = FIGURE_ROOK;

					break;
				}
			case 'h':
				{
					B[j][i] = new Horse();
					B[j][i]->Load("Data/Chess.nlm","Horse");	
					B[j][i]->Set_Name("Horse_");

					fn = FIGURE_HORSE;

					break;
				}
			case 'b':
				{
					B[j][i] = new Bishop();
					B[j][i]->Load("Data/Chess.nlm","Bishop");	
					B[j][i]->Set_Name("Bishop_");

					fn = FIGURE_BISHOP;

					break;
				}
			case 'q':
				{
					B[j][i] = new Queen();
					B[j][i]->Load("Data/Chess.nlm","Queen");	
					B[j][i]->Set_Name("Queen_");

					fn = FIGURE_QUEEN;

					break;
				}
			case 'k':
				{
					B[j][i] = new King();
					B[j][i]->Load("Data/Chess.nlm","King");	
					B[j][i]->Set_Name("King_");

					fn = FIGURE_KING;

					break;
				}
			case 'p':
				{
					B[j][i] = new Pawn();
					B[j][i]->Load("Data/Chess.nlm","Pawn");	
					B[j][i]->Set_Name("Pawn_");					

					fn = FIGURE_PAWN;

					break;
				}
			}

			if (B[j][i])
			{
				char c;

				fi >> c;

				if (c == 'w')
				{
					B[j][i]->Set_Name("White_" + B[j][i]->Get_Name() + IntToStr(++Fcnt[1][fn]));
					B[j][i]->Set_color(WHITE);

					if (f == 'h')
						B[j][i]->Rotate(0,PI,0);

					if (f == 'k')
						w_king = (King *)B[j][i];
				}
				else
				{
					B[j][i]->Set_Name("Black_" + B[j][i]->Get_Name() + IntToStr(++Fcnt[0][fn]));
					B[j][i]->Set_color(BLACK);

					if (f == 'k')
						b_king = (King *)B[j][i];
				}

				B[j][i]->Set_pos(Cell(j,i));
				B[j][i]->Set_bUseVBO(bUseVBO);
				//B[j][i]->Scale(0.025f,0.025f,0.025f);
				//B[j][i]->Move(0,1,0);
			}

		}
	}

	fi.close();

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#else

	// Расставляем белые фигуры

	for (int i = 0; i <= 7; i++)
	{
		Pawn *p = new Pawn();
		p->Load("Data/Chess.nlm","Pawn");
		p->Set_Name("White_Pawn_" + IntToStr(i+1));
		p->Set_color(WHITE);
		p->Set_pos(Cell(i,1));
		p->Set_bUseVBO(bUseVBO);
		B[i][1] = p;
	}

	Horse *h = new Horse();
	h->Load("Data/Chess.nlm","Horse");
	h->Set_Name("White_Horse_1");
	h->Set_color(WHITE);
	h->Set_pos(Cell(1,0));
	h->Set_bUseVBO(bUseVBO);
	h->Rotate(0,PI,0); // Белых коней нужно повернуть
	B[1][0] = h;

	h = new Horse();
	h->Load("Data/Chess.nlm","Horse");
	h->Set_Name("White_Horse_2");
	h->Set_color(WHITE);
	h->Set_pos(Cell(6,0));
	h->Set_bUseVBO(bUseVBO);
	h->Rotate(0,PI,0); // Белых коней нужно повернуть
	B[6][0] = h;

	Rook *r = new Rook();
	r->Load("Data/Chess.nlm","Rook");
	r->Set_Name("White_Rook_1");
	r->Set_color(WHITE);
	r->Set_pos(Cell(0,0));
	r->Set_bUseVBO(bUseVBO);
	B[0][0] = r;

	r = new Rook();
	r->Load("Data/Chess.nlm","Rook");
	r->Set_Name("White_Rook_2");
	r->Set_color(WHITE);
	r->Set_pos(Cell(7,0));
	r->Set_bUseVBO(bUseVBO);
	B[7][0] = r;

	Bishop *b = new Bishop();
	b->Load("Data/Chess.nlm","Bishop");
	b->Set_Name("White_Bishop_1");
	b->Set_color(WHITE);
	b->Set_pos(Cell(2,0));
	b->Set_bUseVBO(bUseVBO);
	B[2][0] = b;

	b = new Bishop();
	b->Load("Data/Chess.nlm","Bishop");
	b->Set_Name("White_Bishop_2");
	b->Set_color(WHITE);
	b->Set_pos(Cell(5,0));
	b->Set_bUseVBO(bUseVBO);
	B[5][0] = b;

	Queen *q = new Queen();
	q->Load("Data/Chess.nlm","Queen");
	q->Set_Name("White_Queen_1");
	q->Set_color(WHITE);
	q->Set_pos(Cell(3,0));
	q->Set_bUseVBO(bUseVBO);
	B[3][0] = q;

	w_king = new King();
	w_king->Load("Data/Chess.nlm","King");
	w_king->Set_Name("White_King_1");
	w_king->Set_color(WHITE);
	w_king->Set_pos(Cell(4,0));
	w_king->Set_bUseVBO(bUseVBO);
	B[4][0] = w_king;

	// Расставляем чёрные фигуры

	for (int i = 0; i <= 7; i++)
	{
		Pawn *p = new Pawn();
		p->Load("Data/Chess.nlm","Pawn");
		p->Set_Name("Black_Pawn_" + IntToStr(i+1));
		p->Set_color(BLACK);
		p->Set_pos(Cell(i,6));
		p->Set_bUseVBO(bUseVBO);
		B[i][6] = p;
	}

	h = new Horse();
	h->Load("Data/Chess.nlm","Horse");
	h->Set_Name("Black_Horse_" + IntToStr(1));
	h->Set_color(BLACK);
	h->Set_pos(Cell(1,7));
	h->Set_bUseVBO(bUseVBO);
	B[1][7] = h;

	h = new Horse();
	h->Load("Data/Chess.nlm","Horse");
	h->Set_Name("Black_Horse_" + IntToStr(2));
	h->Set_color(BLACK);
	h->Set_pos(Cell(6,7));
	h->Set_bUseVBO(bUseVBO);
	B[6][7] = h;

	r = new Rook();
	r->Load("Data/Chess.nlm","Rook");
	r->Set_Name("Black_Rook_1");
	r->Set_color(BLACK);
	r->Set_pos(Cell(0,7));
	r->Set_bUseVBO(bUseVBO);
	B[0][7] = r;

	r = new Rook();
	r->Load("Data/Chess.nlm","Rook");
	r->Set_Name("Black_Rook_2");
	r->Set_color(BLACK);
	r->Set_pos(Cell(7,7));
	r->Set_bUseVBO(bUseVBO);
	B[7][7] = r;

	b = new Bishop();
	b->Load("Data/Chess.nlm","Bishop");
	b->Set_Name("Black_Bishop_1");
	b->Set_color(BLACK);
	b->Set_pos(Cell(2,7));
	b->Set_bUseVBO(bUseVBO);
	B[2][7] = b;

	b = new Bishop();
	b->Load("Data/Chess.nlm","Bishop");
	b->Set_Name("Black_Bishop_2");
	b->Set_color(BLACK);
	b->Set_pos(Cell(5,7));
	b->Set_bUseVBO(bUseVBO);
	B[5][7] = b;

	q = new Queen();
	q->Load("Data/Chess.nlm","Queen");
	q->Set_Name("Black_Queen_1");
	q->Set_color(BLACK);
	q->Set_pos(Cell(3,7));
	q->Set_bUseVBO(bUseVBO);
	B[3][7] = q;

	b_king = new King();
	b_king->Load("Data/Chess.nlm","King");
	b_king->Set_Name("Black_King_1");
	b_king->Set_color(BLACK);
	b_king->Set_pos(Cell(4,7));
	b_king->Set_bUseVBO(bUseVBO);
	B[4][7] = b_king;

#endif

	player = WHITE;

	selected = pick = Cell(255,255);

	SLOT sl_click;
	sl_click.Connect(&NL::Scene::Objects::Board::Click,this);
	NL::System::getSingleton().ConnectSlot(EVENT_MOUSEBUTTON_UP,sl_click);

	//--------------------------------------------------------------------------------------

	bool waiting = false;
	ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

	//--------------------------------------------------------------------------------------

	bool b_w = true;
	ResourceManager::getSingleton().AddResource("mayrok_w",&b_w,sizeof(b_w));

	//--------------------------------------------------------------------------------------
	bool b_b = true;
	ResourceManager::getSingleton().AddResource("mayrok_b",&b_b,sizeof(b_b));

	//--------------------------------------------------------------------------------------

	bool b_r_l_w = true;
	ResourceManager::getSingleton().AddResource("mayrok_r_l_w",&b_r_l_w,sizeof(b_r_l_w));

	//--------------------------------------------------------------------------------------

	bool b_r_r_w = true;
	ResourceManager::getSingleton().AddResource("mayrok_r_r_w",&b_r_r_w,sizeof(b_r_r_w));

	//--------------------------------------------------------------------------------------
	bool b_r_l_b = true;
	ResourceManager::getSingleton().AddResource("mayrok_r_l_b",&b_r_l_b,sizeof(b_r_l_b));

	//--------------------------------------------------------------------------------------

	bool b_r_r_b = true;
	ResourceManager::getSingleton().AddResource("mayrok_r_r_b",&b_r_r_b,sizeof(b_r_r_b));

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
	bool turns_temp[8][8];
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			{
				strikewh[i][j] = 0;
				strikebl[i][j] = 0;
				turns_temp[i][j]=0;
			}
	Strike(B,strikewh,strikebl,w_king,b_king);
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
			if (B[i][j])
			{
				B[i][j]->AllTurns(B,turns_temp,((B[i][j]->Get_color() == WHITE) ? strikebl : strikewh),((B[i][j]->Get_color() == WHITE) ? w_king->Get_pos() : b_king->Get_pos()));
				Cell temp_pos;
				temp_pos.x=i;
				temp_pos.y=j;
				MayTurn(B,turns_temp,temp_pos);
			}
	

	//--------------------------------------------------------------------------------------

	using namespace CEGUI;

	WindowManager::getSingleton().getWindow("Queen")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::Objects::Board::ChangeToQueen,this));
	WindowManager::getSingleton().getWindow("Horse")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::Objects::Board::ChangeToHorse,this));
	WindowManager::getSingleton().getWindow("Rook")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::Objects::Board::ChangeToRook,this));
	WindowManager::getSingleton().getWindow("Bishop")->subscribeEvent(PushButton::EventClicked,Event::Subscriber(&NL::Scene::Objects::Board::ChangeToBishop,this));

	//--------------------------------------------------------------------------------------

	if(isExtensionSupported("ARB_vertex_buffer_object"))
	{
		glGenBuffersARB(1,&quads_vbo_id);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB,quads_vbo_id);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(g_cubeVertices),g_cubeVertices,GL_STATIC_DRAW_ARB);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
	}

	//--------------------------------------------------------------------------------------

	bound = new Mesh();
	bound->Load("Data/Chess.nlm","Bound");
	bound->Set_Name("Bound");
	bound->Set_bUseVBO(bUseVBO);
};

bool NL::Scene::Objects::Board::UpdateAll(float fElapsedTime)
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
		{
			if(B[i][j])
				B[i][j]->UpdateAll(fElapsedTime);
		}

	return Object::UpdateAll(fElapsedTime);
}

void NL::Scene::Objects::Board::MakeTurn(Cell from,Cell to)
{
	B[from.x][from.y]->Turn(to);

	Turn ltr = Turn(Cell(from.x,from.y),Cell(to.x,to.y));

	turns_list.push_back(ltr);

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

  //заполняем  поля под боем для матриц
	Strike(B,strikewh,strikebl,w_king,b_king);
	
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	B[to.x][to.y] = B[from.x][from.y];
	B[from.x][from.y] = NULL;

	player = !player;

	selected = pick = Cell(255,255);

	ResourceManager::getSingleton().AddResource("Last Turn",&ltr,sizeof(ltr));

	//--------------------------------------------------------------------------------------

	CEGUI::MultiColumnList* mcl = (CEGUI::MultiColumnList *)CEGUI::WindowManager::getSingleton().getWindow("Protocol");

	String f = (String(typeid(*B[to.x][to.y]).name()) == "class NL::Scene::Objects::Pawn") ? "" : copy(B[to.x][to.y]->Get_Name(),1,6);

	std::ostringstream text;

	if (String(typeid(*B[to.x][to.y]).name()) == "class NL::Scene::Objects::King")
	{
		if (to.x-from.x == 2)
		{
			text << "O-O";

			if (B[to.x][to.y]->Get_pos().y == 0)
			{
				Cell t;
				t.x=5;
				t.y=0;
				B[7][0]->Turn(t);

				B[t.x][t.y] = B[7][0];
				B[7][0] = NULL;
			}
			else
			{
				Cell t;
				t.x=5;
				t.y=7;
				B[7][7]->Turn(t);

				B[t.x][t.y] = B[7][7];
				B[7][7] = NULL;
			}
		}
		else if (from.x-to.x == 2)
		{
			text << "O-O-O";

			if (B[to.x][to.y]->Get_pos().y == 0)
			{
				Cell t;
				t.x=3;
				t.y=0;
				B[0][0]->Turn(t);

				B[t.x][t.y] = B[0][0];
				B[0][0] = NULL;
			}
			else
			{
				Cell t;
				t.x=3;
				t.y=7;
				B[0][7]->Turn(t);

				B[t.x][t.y] = B[0][7];
				B[0][7] = NULL;
			}
		}
		else
		{
			text << f << char(from.x+'a') << char(from.y+1+'0') << "->" << char(to.x+'a') << char(to.y+1+'0');
		}
	}
	else
	{
		text << f << char(from.x+'a') << char(from.y+1+'0') << "->" << char(to.x+'a') << char(to.y+1+'0');
	}

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	Strike(B,strikewh,strikebl,w_king,b_king); //заполняем матрицу битости.
	//проверка на шах
	bool shax_temp=false;
	if (B[to.x][to.y]->Get_color() == WHITE) shax_temp=Shax(strikewh,b_king->Get_pos());
	else shax_temp=Shax(strikebl,w_king->Get_pos());
	if (shax_temp) 
	{
		bool mat=true;
		bool turns_temp[8][8];
		for (int i=0; i<8;i++)
			for (int j=0; j<8; j++) turns_temp[i][j]=0;
		if (B[to.x][to.y]->Get_color() == BLACK)
		{

			for (int i=0; i<8;i++)
				for (int j=0; j<8; j++)
					if (B[i][j] && B[i][j]->Get_color() == WHITE)
					{
						Cell temp_pos;
						temp_pos.x=i;
						temp_pos.y=j;
						B[i][j]->AllTurns(B,turns_temp,((B[i][j]->Get_color() == WHITE) ? strikebl : strikewh),((B[i][j]->Get_color() == WHITE) ? w_king->Get_pos() : b_king->Get_pos()));
						MayTurn(B,turns_temp,temp_pos);
						for (int i1=0; i1<8;i1++)
							for (int i2=0;i2<8;i2++)
								if (turns_temp[i1][i2]) mat=false;
					}							
					if (mat) 
					{
						//вызов сообщения о мате белым

						CEGUI::WindowManager::getSingleton().getWindow("Message")->setVisible(true);
						CEGUI::WindowManager::getSingleton().getWindow("Message")->setText((CEGUI::utf8 *)"Чёрные выиграли!");
					}
					else
					{
						//вызов сообщения о шахе белым

						CEGUI::WindowManager::getSingleton().getWindow("Message")->setVisible(true);
						CEGUI::WindowManager::getSingleton().getWindow("Message")->setText((CEGUI::utf8 *)"Шах белому королю!");
					}							
		}
		else 
		{
			for (int i=0; i<8;i++)
				for (int j=0; j<8; j++)
					if (B[i][j] && B[i][j]->Get_color() == BLACK)
					{
						Cell temp_pos;
						temp_pos.x=i;
						temp_pos.y=j;
						B[i][j]->AllTurns(B,turns_temp,((B[i][j]->Get_color() == WHITE) ? strikebl : strikewh),((B[i][j]->Get_color() == WHITE) ? w_king->Get_pos() : b_king->Get_pos()));
						MayTurn(B,turns_temp,temp_pos);
						for (int i1=0; i1<8;i1++)
							for (int i2=0;i2<8;i2++)
								if (turns_temp[i1][i2]) mat=false;
					}							
					if (mat) 
					{
						//вызов сообщения о мате черным

						CEGUI::WindowManager::getSingleton().getWindow("Message")->setVisible(true);
						CEGUI::WindowManager::getSingleton().getWindow("Message")->setText((CEGUI::utf8 *)"Белые выиграли!");
					}
					else
					{
						//вызов сообщения о шахе черным

						CEGUI::WindowManager::getSingleton().getWindow("Message")->setVisible(true);
						CEGUI::WindowManager::getSingleton().getWindow("Message")->setText((CEGUI::utf8 *)"Шах чёрному королю!");
					}			
		}
	}
	else
	{
		CEGUI::WindowManager::getSingleton().getWindow("Message")->setVisible(false);				
	}

	Strike(B,strikewh,strikebl,w_king,b_king); //заполняем матрицу битости.

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem((CEGUI::utf8 *)text.str().c_str());
	
	// attempt to add a new row, using the new ListboxTextItem as the initial content for one of the columns
	try
	{
		if (!player)
		{
			int tcnt = (int)turns_list.size();

			CEGUI::ListboxTextItem* item_num = new CEGUI::ListboxTextItem((CEGUI::utf8 *)IntToStr((tcnt % 2 == 0) ? tcnt/2 : tcnt/2+1).c_str());

			mcl->addRow(item_num,1);
			mcl->setItem(item,2,mcl->getRowCount()-1);
		}
		else
		{
			mcl->setItem(item,3,mcl->getRowCount()-1);
		}
	}
	// something went wrong, so cleanup the ListboxTextItem
	catch (CEGUI::InvalidRequestException)
	{
		delete item;
	}
};

void NL::Scene::Objects::Board::Click(void *args)
{
	bool *waiting = (bool *)ResourceManager::getSingleton().GetResourcePtr("Waiting");

	if (*waiting)
		return;

	std::vector<DWORD> b = *((std::vector<DWORD> *)args);

	if (b[0] != MOUSEBUTTON_LEFT)
		return;
	
	if (pick.x < 8 && pick.y < 8 && selected.x < 8 && selected.y < 8)
	{
		if (B[selected.x][selected.y] && B[pick.x][pick.y] && B[selected.x][selected.y]->Get_color() == B[pick.x][pick.y]->Get_color())
		{
			selected = pick;
			pick = Cell(255,255);
			
			return;
		}

		bool turns[8][8];

		for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			{
				turns[i][j] = 0;
			}
	

		if(selected.x < 8 && selected.y < 8 && B[selected.x][selected.y] && B[selected.x][selected.y]->Get_color() == player)
		{
			B[selected.x][selected.y]->AllTurns(B,turns,((B[selected.x][selected.y]->Get_color() == WHITE) ? strikebl : strikewh),((B[selected.x][selected.y]->Get_color() == WHITE) ? w_king->Get_pos() : b_king->Get_pos()));
			MayTurn(B,turns,selected);
		
		}

		if(turns[pick.x][pick.y] && B[selected.x][selected.y])
		{
//рокировка перемещение ладьи
			// Правка: перемещено в MakeTurn
			/*String s1;
	    	s1="class NL::Scene::Objects::King";
			String s = typeid(*B[selected.x][selected.y]).name();
			if (s==s1)
			{

					if (selected.x==4 && selected.y==0)
					{
						if (pick.x==6)
						{		
							Cell t;
							t.x=5;
							t.y=0;
							B[7][0]->Turn(t);

							B[t.x][t.y] = B[7][0];
							B[7][0] = NULL;
						}
						else
							if (pick.x==2)
							{	
								Cell t;
								t.x=3;
								t.y=0;
								B[0][0]->Turn(t);

								B[t.x][t.y] = B[0][0];
								B[0][0] = NULL;
							}
					}
					else if (selected.x==4 && selected.y==7)
					{
						if (pick.x==6) 
						{
							Cell t;
							t.x=5;
							t.y=7;
							B[7][7]->Turn(t);

							B[t.x][t.y] = B[7][7];
							B[7][7] = NULL;
						}
						else
							if (pick.x==2)
							{
								Cell t;
								t.x=3;
								t.y=7;
								B[0][7]->Turn(t);

								B[t.x][t.y] = B[0][7];
								B[0][7] = NULL;
							}
					}
			}*/
			
			std::vector<DWORD> params(5);
			params[0] = selected.x; // Откуда (горизонталь)
			params[1] = selected.y; // Откуда (вертикаль)
			params[2] = pick.x; // Куда (горизонталь)
			params[3] = pick.y; // Куда (вертикаль)
			params[4] = (DWORD)turns_list.size(); // Номер хода
			NL::System::getSingleton().GenerateEvent(NL::System::Event(EVENT_TURN,params));

			//проверка на взятие на проходе:
			Objects::Turn *lt=(Objects::Turn *)ResourceManager::getSingleton().GetResourcePtr("Last Turn");
			if (lt)
			{
				String s1;
				s1="class NL::Scene::Objects::Pawn";
				String s = typeid(*B[lt->to.x][lt->to.y]).name();
				if(B[selected.x][selected.y]->Get_color() == WHITE)
				{
					if (s1==s)
					{
						if ( lt->from.y==6 && lt->to.y==4)
						{
								if (pick.x==lt->from.x && pick.y==5)
									B[lt->from.x][lt->to.y]=0;
						}
					}
				}
				else
				{
					if (s1==s)
					{
						if ( lt->from.y==1 && lt->to.y==3)
						{
								if (pick.x==lt->from.x && pick.y==2)
									B[lt->from.x][lt->to.y]=0;
						}
					}

				}
			}

			if ((pick.y == 0 || pick.y == 7) && String(typeid(*B[selected.x][selected.y]).name()) == "class NL::Scene::Objects::Pawn")
			{
				CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(true);

				bool waiting = true;
				ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

				turns_list.push_back(Turn(selected,pick));
			}
			else
			{
				MakeTurn(selected,pick);
			}			
		}
	}
	else if(pick.x < 8 && pick.y < 8 && B[pick.x][pick.y] && B[pick.x][pick.y]->Get_color() == player)
	{
		selected = pick;
	}
};

NL::Scene::Objects::Figure *NL::Scene::Objects::Board::at(Cell c) const
{
	return B[c.x][c.y];
};

bool NL::Scene::Objects::Board::Render(WORD pass)
{
	using namespace Math;

	OpenGL *ogl = OpenGL::getSingletonPtr();

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glDisable(GL_COLOR_MATERIAL);
		
	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	switch(pass)
	{
	case RENDER_PASS_MAIN:
		{
			bool white = false;

			bool turns[8][8]; // Матрица подсвечиваемых клеток

			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
				{
					turns[i][j] = 0;
				}

			if(pick.x < 8 && pick.y < 8 && B[pick.x][pick.y] && B[pick.x][pick.y]->Get_color() == player) // Заполнение turns
			{
				B[pick.x][pick.y]->AllTurns(B,turns,((B[pick.x][pick.y]->Get_color() == WHITE) ? strikebl : strikewh),((B[pick.x][pick.y]->Get_color() == WHITE) ? w_king->Get_pos() : b_king->Get_pos()));
			    MayTurn(B,turns,pick);
			}

			//--------------------------------------------------------------------------------------

			bool bMirror = *((bool *)ResourceManager::getSingleton().GetResourcePtr("Mirror"));

			if (bMirror)
			{
				double eqr[] = { 0.0f,0, 0.0f, 0.0f }; // Уравнение плоскости отсечения для отсечения отраженных объектов

				// Использовать буфер трафарета для «пометки» доски

				glEnable(GL_STENCIL_TEST); // Разрешить тест трафарета
				glEnable(GL_DEPTH_TEST); // Разрешить тест глубины

				glStencilFunc(GL_ALWAYS,1,0); // Там, где рисуется доска, будут 1
				glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

				// Рисуем прямоугольники (доска)

				if(isExtensionSupported("ARB_vertex_buffer_object"))
				{
					glEnableClientState(GL_VERTEX_ARRAY);
					glBindBufferARB(GL_ARRAY_BUFFER_ARB,quads_vbo_id);
					glVertexPointer(3,GL_FLOAT,0,0);
				}
				else
				{
					glInterleavedArrays(GL_V3F,0,g_cubeVertices);
				}

				for(int i = 0; i < 8; i++)
				{
					for(int j = 0; j < 8; j++)
					{
						if(white)
							glColor4ub(255,255,255,200); // Белый прямоугольник
						else
							glColor4ub(10,10,10,200); // Чёрный прямоугольник

						if((i == pick.x) && (j == pick.y))
							glColor4ub(150,0,0,200); // Красный прямоугольник

						if(turns[i][j])
							glColor4ub(0,0,150,200); // Синий прямоугольник

						if(i == selected.x && j == selected.y)
							glColor4ub(0,255,0,200); // Зелёный прямоугольник

						DrawQuad(i,j);

						white = !white;
					}

					white = !white;
				}

				glStencilFunc(GL_ALWAYS,2,0); // Заполняем 2 пространство, где рисуются границы доски
				glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

				bound->RenderAll(pass); // Рисуем границы доски

				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

				glColorMask(true,true,true,true); // Установить маску цвета в (true,true,true,true)

				glStencilFunc(GL_EQUAL,1,255); // Рисуем по шаблону (где шаблон=1)

				// Рисуем отражённые фигуры

				Math::Matrix4x4 Sc;
				Sc.Scale(1,-1,1); // "Вверх ногами"

				OpenGL::getSingleton().PushMatrix();
				OpenGL::getSingleton().LoadMatrix(M_WORLD,Sc);
				OpenGL::getSingleton().ApplyTransform();

				for(int i = 0; i < 8; i++)
					for(int j = 0; j < 8; j++)
					{
						if(B[i][j])
							B[i][j]->RenderAll(pass);
					}

					OpenGL::getSingleton().PopMatrix();

					//--------------------------------------------------------------------------------------

					glDisable(GL_CLIP_PLANE0); // Отключение плоскость отсечения
					glDisable(GL_STENCIL_TEST); // Отключение проверки трафарета
			}

			// Используем смешивание
			glEnable(GL_BLEND);
			// В течение использования смешивания отключаем освещение
			glDisable(GL_LIGHTING);
			// Смешивание, основанное на «Source Alpha And 1 Minus Dest Alpha»
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

			// Рисуем прямоугольники (доска)
			// Прозрачность ~80%

			if(isExtensionSupported("ARB_vertex_buffer_object"))
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,quads_vbo_id);
				glVertexPointer(3,GL_FLOAT,0,0);
			}
			else
			{
				glInterleavedArrays(GL_V3F,0,g_cubeVertices);
			}

			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					if(white)
						glColor4ub(255,255,255,200);
					else
						glColor4ub(10,10,10,200);

					if((i == pick.x) && (j == pick.y))
						glColor4ub(150,0,0,200);

					if(turns[i][j])
						glColor4ub(0,0,150,200);

					if(i == selected.x && j == selected.y)
						glColor4ub(0,255,0,200);

					DrawQuad(i,j);

					white = !white;
				}

				white = !white;
			}			

			glEnable(GL_LIGHTING); // Включение освещения
			glDisable(GL_BLEND); // Отключение смешивания
		
			// Рисуем фигуры (нормально)

			OpenGL::getSingleton().PushMatrix();
			OpenGL::getSingleton().LoadMatrix(M_WORLD,M);
			OpenGL::getSingleton().ApplyTransform();

			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
				{
					if(B[i][j])
						B[i][j]->RenderAll(pass);
				}

			OpenGL::getSingleton().PopMatrix();

			BYTE *bordercolor = ((BYTE *)ResourceManager::getSingleton().GetResourcePtr("Border color"));
			glColor3ub(bordercolor[2],bordercolor[1],bordercolor[0]);

			bound->RenderAll(pass); // Рисуем границы доски

			if(isExtensionSupported("ARB_vertex_buffer_object"))
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);

			break;
		}
	case RENDER_PASS_SELECT:
		{
			//std::map<BYTE,String> *buff = new std::map<BYTE,String>(); 

			//size_t buff_size = 0;

			// Рисуем прямоугольники

			if(isExtensionSupported("ARB_vertex_buffer_object"))
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,quads_vbo_id);
				glVertexPointer(3,GL_FLOAT,0,0);
			}
			else
			{
				glInterleavedArrays(GL_V3F,0,g_cubeVertices);
			}

			for(int i = 0; i < 8; i++)
			{
				for(int j = 0; j < 8; j++)
				{
					BYTE color = 10*(i+1) + j + 1;

					glColor3ub(color,0,0);

					DrawQuad(i,j);

					/*String name = "Board_" + IntToStr(i) + "x" + IntToStr(j);
					buff->operator [] (color) = name;

					buff_size += 1 + name.size();*/
				}
			}

			if(isExtensionSupported("ARB_vertex_buffer_object"))
				glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);

			//ResourceManager::getSingleton().AddResource("ColorBuffer",&buff,sizeof(buff));

			break;
		}
	}
	
	return true;
};

bool NL::Scene::Objects::Board::Update(float fElapsedTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Render(RENDER_PASS_SELECT);

	//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

	int X,Y;

	System::getSingleton().GetCurPos(&X,&Y);

	BYTE f[3];

	int height = *((int *)ResourceManager::getSingleton().GetResourcePtr("Window height"));

	Log::getSingleton().AddLine(IntToStr(X)+" "+IntToStr(Y));

	glReadPixels(X,/*600-(Y-25)*/height-Y,1,1,GL_RGB,GL_UNSIGNED_BYTE,f);

	if(f[0] > 0 && f[0] < 100)
	{
		pick.x = div(f[0],10).quot-1;
		pick.y = div(f[0],10).rem-1;
	}
	else
	{
		pick.x = pick.y = 255;
	}

	/*std::map<BYTE,String> *bf = new std::map<BYTE,String>();

	ResourceManager::getSingleton().GetResource("ColorBuffer",&bf);

	std::map<BYTE,String> buff = *bf;

	if(buff[f[0]] != "")
	{
		String txt = buff[f[0]];

		pick.x = StrToInt(copy(txt,1,6));
		pick.y = StrToInt(copy(txt,1,8));
	}
	else
	{
		pick.x = pick.y = 255;
	}*/

	return true;
};

bool NL::Scene::Objects::Board::Release()
{
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(B[i][j])
				B[i][j]->ReleaseAll();

			B[i][j] = NULL;
		}
	}

	bound->ReleaseAll();

	if(isExtensionSupported("ARB_vertex_buffer_object"))
		glDeleteBuffersARB(1,&quads_vbo_id);

	ResourceManager::getSingleton().DeleteResource("Last Turn");

	return true;
};

void NL::Scene::Objects::Board::DrawQuad(int x,int y)
{
	using namespace Math;

	OpenGL *ogl = OpenGL::getSingletonPtr();

	if(isExtensionSupported("ARB_vertex_buffer_object"))
	{
		ogl->PushMatrix();

		Matrix4x4 wmat;
		wmat.Translate(float(2*x-7),0,float(2*y-7));

		ogl->LoadMatrix(M_WORLD,wmat);

		ogl->ApplyTransform();

		glDrawArrays(GL_QUADS,0,4);

		ogl->PopMatrix();
	}
	else
	{
		ogl->PushMatrix();

		Matrix4x4 wmat;
		wmat.Translate(float(2*x-7),0,float(2*y-7));

		ogl->LoadMatrix(M_WORLD,wmat);

		ogl->ApplyTransform();
		
		glDrawArrays(GL_QUADS,0,4);

		ogl->PopMatrix();
	}
};

bool NL::Scene::Objects::Board::ChangeToQueen(const CEGUI::EventArgs &e)
{
	bool waiting = false;
	ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

	Turn last = turns_list[turns_list.size()-1];

	Queen *q = new Queen();
	q->Load("Data/Chess.nlm","Queen");	
	q->Set_Name(((B[last.from.x][last.from.y]->Get_color() == WHITE) ? "White_" : "Black_") + String("Queen_") + IntToStr(++Fcnt[((B[last.from.x][last.from.y]->Get_color() == WHITE) ? 1 : 0)][FIGURE_QUEEN]));
	q->Set_color(B[last.from.x][last.from.y]->Get_color());
	q->Set_pos(Cell(last.from.x,last.from.y));
	q->Set_bUseVBO(isExtensionSupported("ARB_vertex_buffer_object"));
	
	delete B[last.from.x][last.from.y];

	B[last.from.x][last.from.y] = q;

	CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(false);

	turns_list.erase(turns_list.end()-1);
	MakeTurn(last.from,last.to);

	return true;
};

bool NL::Scene::Objects::Board::ChangeToHorse(const CEGUI::EventArgs &e)
{
	bool waiting = false;
	ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

	Turn last = turns_list[turns_list.size()-1];

	Horse *q = new Horse();
	q->Load("Data/Chess.nlm","Horse");	
	q->Set_Name(((B[last.from.x][last.from.y]->Get_color() == WHITE) ? "White_" : "Black_") + String("Horse_") + IntToStr(++Fcnt[((B[last.from.x][last.from.y]->Get_color() == WHITE) ? 1 : 0)][FIGURE_HORSE]));
	q->Set_color(B[last.from.x][last.from.y]->Get_color());
	q->Set_pos(Cell(last.from.x,last.from.y));
	q->Set_bUseVBO(isExtensionSupported("ARB_vertex_buffer_object"));

	if(q->Get_color() == WHITE)
		q->Rotate(0,PI,0);

	delete B[last.from.x][last.from.y];

	B[last.from.x][last.from.y] = q;

	CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(false);

	turns_list.erase(turns_list.end()-1);
	MakeTurn(last.from,last.to);

	return true;
};

bool NL::Scene::Objects::Board::ChangeToRook(const CEGUI::EventArgs &e)
{
	bool waiting = false;
	ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

	Turn last = turns_list[turns_list.size()-1];

	Rook *q = new Rook();
	q->Load("Data/Chess.nlm","Rook");	
	q->Set_Name(((B[last.from.x][last.from.y]->Get_color() == WHITE) ? "White_" : "Black_") + String("Rook_") + IntToStr(++Fcnt[((B[last.from.x][last.from.y]->Get_color() == WHITE) ? 1 : 0)][FIGURE_ROOK]));
	q->Set_color(B[last.from.x][last.from.y]->Get_color());
	q->Set_pos(Cell(last.from.x,last.from.y));
	q->Set_bUseVBO(isExtensionSupported("ARB_vertex_buffer_object"));
	
	delete B[last.from.x][last.from.y];

	B[last.from.x][last.from.y] = q;

	CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(false);

	turns_list.erase(turns_list.end()-1);
	MakeTurn(last.from,last.to);

	return true;
};

bool NL::Scene::Objects::Board::ChangeToBishop(const CEGUI::EventArgs &e)
{
	bool waiting = false;
	ResourceManager::getSingleton().AddResource("Waiting",&waiting,sizeof(bool));

	Turn last = turns_list[turns_list.size()-1];

	Bishop *q = new Bishop();
	q->Load("Data/Chess.nlm","Bishop");	
	q->Set_Name(((B[last.from.x][last.from.y]->Get_color() == WHITE) ? "White_" : "Black_") + String("Bishop_") + IntToStr(++Fcnt[((B[last.from.x][last.from.y]->Get_color() == WHITE) ? 1 : 0)][FIGURE_BISHOP]));
	q->Set_color(B[last.from.x][last.from.y]->Get_color());
	q->Set_pos(Cell(last.from.x,last.from.y));
	q->Set_bUseVBO(isExtensionSupported("ARB_vertex_buffer_object"));

	delete B[last.from.x][last.from.y];

	B[last.from.x][last.from.y] = q;

	CEGUI::WindowManager::getSingleton().getWindow("Change")->setVisible(false);

	turns_list.erase(turns_list.end()-1);
	MakeTurn(last.from,last.to);

	return true;
};

bool NL::Scene::Objects::Board::Shax(bool M[8][8], Cell p)
{
	if (M[p.x][p.y]==1) return 1;
	else return 0;
};

void NL::Scene::Objects::Board::Strike(Figure *B[8][8], bool strikewh[8][8], bool strikebl[8][8], King *w_king, King *b_king)
{	
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
		{
			strikewh[i][j] = 0;
			strikebl[i][j] = 0;
		}	
		Pawn *temp_pawn=new Pawn();
		for (int i = 0; i<8; i++)   //заполняем первоначально поля под боем для матриц
			for (int j = 0; j<8; j++)
					if (B[j][i])	
					{
						if (B[j][i]->Get_color() == WHITE)
						{
							String s1;
							s1="class NL::Scene::Objects::Pawn";
							String s = typeid(*B[j][i]).name();
							if (s ==s1) 
							{   temp_pawn=(Pawn *)B[j][i];
								temp_pawn->AllStrike(B,strikewh,strikebl,b_king->Get_pos());
							}
							else
								B[j][i]->AllTurns(B,strikewh,strikebl,b_king->Get_pos());
						}
						else
						{
							String s1;
							s1="class NL::Scene::Objects::Pawn";
							String s = typeid(*B[j][i]).name();
							if (s ==s1) 
							{   temp_pawn =(Pawn *)B[j][i];
								temp_pawn->AllStrike(B,strikebl,strikewh,w_king->Get_pos());
							}
							else
								B[j][i]->AllTurns(B,strikebl,strikewh,w_king->Get_pos());
						}
					}
};

void NL::Scene::Objects::Board::MayTurn(Figure *B[8][8], bool T[8][8],Cell p)
{		
	for (int i=0;i<8;i++)
		for (int j=0;j<8;j++)
		{
			if (T[i][j])
			{
				String s1;
				s1="class NL::Scene::Objects::King";
				String s = typeid(*B[p.x][p.y]).name();
				King *w_king_temp=w_king;
				King *b_king_temp=b_king;
				Figure *tmp_f = B[i][j];
				B[i][j]=B[p.x][p.y];
				Cell temp;
				temp.x=i;
				temp.y=j;
				B[i][j]->Set_pos(temp);
				B[p.x][p.y]=0;
				bool strikewh_temp[8][8];
				bool strikebl_temp[8][8];
				if (B[i][j]->Get_color() ==WHITE)
				{
					if (s==s1)
						w_king_temp=(King *)B[i][j];
					Strike(B, strikewh_temp, strikebl_temp, b_king_temp, w_king_temp);
					if (Shax(strikebl_temp,w_king_temp->Get_pos())) 
						T[i][j]=0;
				}
				else
				{
					if (s==s1)
						b_king_temp=(King *)B[i][j];
					Strike(B, strikewh_temp,strikebl_temp,b_king_temp,w_king_temp);
					if (Shax(strikewh_temp,b_king_temp->Get_pos())) 
						T[i][j]=0;
				}

				temp.x=p.x;
				temp.y=p.y;
				B[i][j]->Set_pos(temp);
				B[p.x][p.y]=B[i][j];
				B[i][j]=tmp_f;
			}
		}
};