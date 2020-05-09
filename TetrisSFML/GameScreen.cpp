#include "GameScreen.h"
#include "ManagersInstance.h"
#include "SceneManager.h"
using namespace sf;
const int M = 20; //������ �������� ����
const int N = 20; //������ �������� ����

int field[M][N] = { 0 }; //������� ����
int Level = 1;
//������ �������-���������
int figures[7][4] =
{
	1,3,5,7, 
	2,4,5,7, 
	3,5,4,6, 
	3,5,4,7, 
	2,3,5,7, 
	3,5,7,6, 
	2,3,4,5, 
};
struct myclass {
	bool operator() (int i, int j) { return (i < j); }
} myobject;
struct Point1
{
	int x, y;
} a1[4], b1[4];

struct Point2
{
	int x, y;
} a2[4], b2[4];

struct Point3
{
	int x, y;
} a3[4], b3[4];

struct Point4
{
	int x, y;
} a4[4], b4[4];



//�������� �� ����� �� ������� �������� ����
bool check1()
{
	for (int i = 0; i < 4; i++)
		if (a1[i].x < 0 || a1[i].x >= N || a1[i].y >= M) return 0;
		else if (field[a1[i].y][a1[i].x]) return 0;


	return 1;
};

bool check2()
{
	for (int i = 0; i < 4; i++)
		if (a2[i].x < 0 || a2[i].x >= N || a2[i].y >= M) return 0;
		else if (field[a2[i].y][a2[i].x]) return 0;
	return 1;
};


//�������� �� ������������ ��������
bool check_collision()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		if ((a1[i].y == a2[j].y) && (a1[i].x == a2[j].x))
			return 0;

	return 1;
}

int check_score(int sc)
{
	int levelnew = sc / 1000 + 1;
	if (levelnew > 8)
		levelnew = 8;
	return levelnew;
}
bool GameScreen::handleEvent(const Event& aEvent) {
	if (aEvent.type == sf::Event::KeyPressed) {
		if (aEvent.key.code == sf::Keyboard::Q) {
			GET_SCENE_MANAGER()->popScene();
		}
	}
	/*exitButton->handleEvent(aEvent);
	highButton->handleEvent(aEvent);
	playButton->handleEvent(aEvent);*/
	return true;
}

void GameScreen::draw(RenderTarget& renderer) {
	renderer.draw(background);
}

GameScreen::~GameScreen() {

}

GameScreen::GameScreen()
{
 
	std::ifstream fin;
	fin.open("records.txt");
	

	RenderWindow window(VideoMode(1280, 720), "Tetris");

	//�������� � �������� ��������
	Texture texture, texture_background;
	texture.loadFromFile("resources\\tiles.png");
	texture_background.loadFromFile("resources\\background.png");
	background.setTexture(&texture_background);
	background.setSize({ 1280, 720 });
	background.setPosition({ 0.f, 0.f });
	//�������� �������
	Sprite sprite1(texture), sprite2(texture), sprite3(texture), sprite4(texture), sprite_background(texture_background);
	//�������� �� ������� ��������� ��������� �������� 32 ��������
	sprite1.setTextureRect(IntRect(0, 0, 32, 32));
	sprite2.setTextureRect(IntRect(0, 0, 32, 32));
	sprite3.setTextureRect(IntRect(0, 0, 32, 32));
	sprite4.setTextureRect(IntRect(0, 0, 32, 32));

	//����������
	int dx1 = 0, dx2 = 0; bool rotate1 = 0, rotate2 = 0; int colorNum1 = 1, colorNum2 = 1, colorNum3 = 1 + rand() % 7, colorNum4 = 1 + rand() % 7; bool beginGame = true; bool flag1 = true, flag2 = true; int n1, n2;

	//���������� ��� ������� � ��������
	float timer1 = 0, timer2 = 0, delay1 = 0.5 - Level * 0.05, delay2 = 0.5 - Level * 0.05;

	std::vector<int> records(10);
	if (fin.is_open())
	{
		for (int j = 0; j < 10; j++)
			fin >> records[j];
	}
	fin.close();
	std::ofstream fout;
	fout.open("records.txt");
	int Score = 0, Lines = 0;
	//���� (������)
	Clock clock;


	//������� ���� ����������. �����������, ���� ������� ����.
	while (window.isOpen())
	{



		//������ � �������� (����, ��������, �����)
		sf::Font font;//����� 
		font.loadFromFile("resources/VCR_OSD_MONO_1.001.ttf");//�������� ������ ������ ���� ������
		Text text_score("", font, 32);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		text_score.setFillColor(sf::Color::Yellow);//��������� ����� � ������
		text_score.setStyle(sf::Text::Bold);//������ �����

		String Score_Nuliki = "0";
		int kolvo_nuley_Score = 10 - std::to_string(Score).length();
		while (kolvo_nuley_Score > 0)
		{
			kolvo_nuley_Score--;
			Score_Nuliki = Score_Nuliki + "0";
		}
		text_score.setString(Score_Nuliki + std::to_string(Score));//������ ������ ������
		text_score.setPosition(875, 70);//������ ������� ������, ����� ������

	


		Text text_lines("", font, 32);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		text_lines.setFillColor(sf::Color::Yellow);//��������� ����� � ������
		text_lines.setStyle(sf::Text::Bold);//������ �����

		String Lines_Nuliki = "0";
		int kolvo_nuley_lines = 10 - std::to_string(Lines).length();
		while (kolvo_nuley_lines > 0)
		{
			kolvo_nuley_lines--;
			Lines_Nuliki = Lines_Nuliki + "0";
		}
		text_lines.setString(Lines_Nuliki + std::to_string(Lines));//������ ������ ������
		text_lines.setPosition(875, 310);//������ ������� ������, ����� ������

		
		Text text_level("", font, 32);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
		text_level.setFillColor(sf::Color::Yellow);//��������� ����� � ������
		text_level.setStyle(sf::Text::Bold);//������ �����
		text_level.setString(std::to_string(Level));
		text_level.setPosition(980, 190);










		//�������� �����, ��������� � ������ �������, � ������������ ��� � �������
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer1 += time;
		timer2 += time;
		//������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			
			//������������ ����� �� �������� � ����� ���� �������?
			if (event.type == Event::Closed)
				//����� ��������� ���
			{
				window.close();
				records.push_back(Score);
				sort(records.begin(), records.end(), std::greater<int>());
				if (fout.is_open())
				{
					for (int j = 0; j < 10; j++)
						fout << records[j] << " ";
				}
				fout.close();
			}
			//���� ������ ������ �� ����������?
			if (event.type == Event::KeyPressed)
				//��� ������ � ������� �����?�
				if (event.key.code == Keyboard::W) rotate1 = true;
			//���� �� ������� �����?�
				else if (event.key.code == Keyboard::A) dx1 = -1;
			////��� ����� ����� ��� ������� ������?
				else if (event.key.code == Keyboard::D) dx1 = 1;

			if (event.type == Event::KeyPressed)
				//��� ������ � ������� �����?�
				if (event.key.code == Keyboard::Up) rotate2 = true;
			//���� �� ������� �����?�
				else if (event.key.code == Keyboard::Left) dx2 = -1;
			////��� ����� ����� ��� ������� ������?
				else if (event.key.code == Keyboard::Right) dx2 = 1;


		}
		
		//������ ������ "����"? �������� ������� ���������
		if (Keyboard::isKeyPressed(Keyboard::S)) delay1 = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay2 = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
			records.push_back(Score);
			sort(records.begin(), records.end(), std::greater<int>());
			if (fout.is_open())
			{
				for (int j = 0; j < 10; j++)
					fout << records[j] << " ";
			}
			fout.close();
		}
		//// �������������� ����������� ////
		for (int i = 0; i < 4; i++) 
		{ 
			b1[i] = a1[i]; a1[i].x += dx1;
			b2[i] = a2[i]; a2[i].x += dx2;
		}
		//����� �� ������� ���� ����� �����������? ����� ���������� ������ ���������� 
		if (!check1() || !check_collision()) for (int i = 0; i < 4; i++) a1[i] = b1[i];
		if (!check2() || !check_collision()) for (int i = 0; i < 4; i++) a2[i] = b2[i];

		////// �������� //////
		if (rotate1)
		{
			Point1 p1 = a1[1]; //������ ����� ��������
			for (int i = 0; i < 4; i++)
			{
				int x = a1[i].y - p1.y; //y-y0
				int y = a1[i].x - p1.x; //x-x0
				a1[i].x = p1.x - x;
				a1[i].y = p1.y + y;
			}
			//����� �� ������� ���� ����� ��������? ����� ���������� ������ ���������� 
			if (!check1() || !check_collision()) { for (int i = 0; i < 4; i++) a1[i] = b1[i]; }

		}

		////// �������� //////
		if (rotate2)
		{
			Point2 p2 = a2[1]; //������ ����� ��������
			for (int i = 0; i < 4; i++)
			{
				int x = a2[i].y - p2.y; //y-y0
				int y = a2[i].x - p2.x; //x-x0
				a2[i].x = p2.x - x;
				a2[i].y = p2.y + y;
			}
			//����� �� ������� ���� ����� ��������? ����� ���������� ������ ���������� 
			if (!check2() || !check_collision()) { for (int i = 0; i < 4; i++) a2[i] = b2[i]; }

		}

		////// �������� ��������� ���� (���� �������) //////
		if (timer1 > (delay1))
		{

			for (int i = 0; i < 4; i++) { b1[i] = a1[i]; a1[i].y += 1; }
			if (!check1())
			{
				for (int i = 0; i < 4; i++) field[b1[i].y][b1[i].x] = colorNum1;
				colorNum1 = colorNum3;
				for (int i = 0; i < 4; i++)
				{
					a1[i].x = figures[n1][i] % 2;
					a1[i].y = figures[n1][i] / 2;
				}
				colorNum3 = 1 + rand() % 7;

				n1 = rand() % 7;

				for (int i = 0; i < 4; i++)
				{
					a3[i].x = figures[n1][i] % 2;
					a3[i].y = figures[n1][i] / 2;
				}
				flag1 = true;
			}
			if (!check_collision())
			{
				for (int i = 0; i < 4; i++)
					a1[i] = b1[i];
			}

			timer1 = 0;
		}

		if (timer2 > (delay2))
		{

			for (int i = 0; i < 4; i++) { b2[i] = a2[i]; a2[i].y += 1; }
			if (!check2())
			{
				for (int i = 0; i < 4; i++) field[b2[i].y][b2[i].x] = colorNum2;
				colorNum2 = colorNum4;
				for (int i = 0; i < 4; i++)
				{
					a2[i].x = figures[n2][i] % 2;
					a2[i].y = figures[n2][i] / 2;
				}
				colorNum4 = 1 + rand() % 7;
				n2 = rand() % 7;

				for (int i = 0; i < 4; i++)
				{
					a4[i].x = figures[n2][i] % 2;
					a4[i].y = figures[n2][i] / 2;
				}

				flag2 = true;
			}
			if (!check_collision())
			{
				for (int i = 0; i < 4; i++)
					a2[i] = b2[i];
			}

			timer2 = 0;
		}



		//----�������� �����----//
		int k = M - 1, count_explouded = 0;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < N) 
				k--;
			else
			{
				count_explouded++;
			}
		}

		//������� �����
		switch (count_explouded)
		{
		case 1:
		{
			Score += 100;
			Lines++;
			count_explouded = 0;
			Level = check_score(Score);
			break;
		}
		case 2:
		{
			Score += 300;
			Lines += 2;
			count_explouded = 0;
			Level = check_score(Score);
			break;
		}
		case 3:
		{
			Score += 700;
			Lines += 3;
			count_explouded = 0;
			Level = check_score(Score);
			break;
		}
		case 4:
		{

			Level = check_score(Score);
			Score += 1500;
			Lines += 4;
			Level = check_score(Score);
			count_explouded = 0;
			break;
		}
		default:
		{
			count_explouded = 0;
			break;
		}
		}

		// ����� ����

		for (int i = 0; i < M; i++)
			if (field[0][i])
			{
				
				window.close();
				records.push_back(Score);
				sort(records.begin(), records.end(), std::greater<int>());
				if (fout.is_open())
				{
					for (int j = 0; j < 10; j++)
						fout << records[j] << " ";
				}
				fout.close();
			}

		//������ ��������� ��������� �� ����?
		if (beginGame)
		{
			beginGame = false;
			int n1_first = rand() % 7;
			int n2_first = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a1[i].x = figures[n1_first][i] % 2;
				a1[i].y = figures[n1_first][i] / 2;
				a2[i].x = figures[n2_first][i] % 2;
				a2[i].y = figures[n2_first][i] / 2;
			}
			n1 = rand() % 7;
			n2 = rand() % 7;

			for (int i = 0; i < 4; i++)
			{
				a3[i].x = figures[n1][i] % 2;
				a3[i].y = figures[n1][i] / 2;
				a4[i].x = figures[n2][i] % 2;
				a4[i].y = figures[n2][i] / 2;
			}
		}
		if (flag1)
		{
			for (int i = 0; i < 4; i++)
				a1[i].x += 3;
			flag1 = false;
		}
		if (flag2)
		{
			for (int i = 0; i < 4; i++)
				a2[i].x += 15;
			flag2 = false;
		}
		dx1 = 0; rotate1 = 0; delay1 = 0.5 - Level * 0.05, dx2 = 0; rotate2 = 0; delay2 = 0.5 - Level * 0.05;
		//----���������----//
		//������ ���� ���� (�����)
		window.clear(Color::White);
		window.draw(sprite_background);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) 
					continue;
				sprite1.setTextureRect(IntRect(field[i][j] * 32, 0, 32, 32));
				sprite1.setPosition(j * 32, i * 32);
				sprite1.move(40, 40); //��������
				window.draw(sprite1);

				sprite2.setTextureRect(IntRect(field[i][j] * 32, 0, 32, 32));
				sprite2.setPosition(j * 32, i * 32);
				sprite2.move(40, 40); //��������
				window.draw(sprite2);
			}
		for (int i = 0; i < 4; i++)
		{
			//������������� ���������
			sprite1.setTextureRect(IntRect(colorNum1 * 32, 0, 32, 32));
			//������������� ������� ������� ������� ���������
			sprite1.setPosition(a1[i].x * 32, a1[i].y * 32);
			sprite1.move(40, 40); //��������
			
			//��������� �������
			window.draw(sprite1);
			//������������� ���������
			sprite2.setTextureRect(IntRect(colorNum2 * 32, 0, 32, 32));
			//������������� ������� ������� ������� ���������
			sprite2.setPosition(a2[i].x * 32, a2[i].y * 32);
			sprite2.move(40, 40); //��������

			//��������� �������
			window.draw(sprite2);

			
			
			sprite3.setTextureRect(IntRect(colorNum3 * 32, 0, 32, 32));
			sprite3.setPosition(a3[i].x * 32, a3[i].y * 32);
			sprite3.move(800, 500); //��������

			//��������� ������� ��������� ������
			window.draw(sprite3);


			sprite4.setTextureRect(IntRect(colorNum4 * 32, 0, 32, 32));
			sprite4.setPosition(a4[i].x * 32, a4[i].y * 32);
			sprite4.move(1080, 500); //��������

			//��������� ������� ��������� ������
			window.draw(sprite4);
		}

		window.draw(text_score);//��������� ������ �����
		window.draw(text_lines);//��������� ������ �����
		window.draw(text_level);//��������� ������ �������
		//��������� ����
		window.display();
	}
}