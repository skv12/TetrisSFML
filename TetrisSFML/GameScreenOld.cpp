#include "GameScreen.h"
#include "Application.h"
#include "ManagersInstance.h"
#include "SceneManager.h"
using namespace sf;
const int M = 20; //Высота игрового поля
const int N = 20; //Ширина игрового поля

int field[M][N] = { 0 }; //Игровое поле

//Массив фигурок-тетрамино
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

struct Point1
{
	int x, y;
} a1[4], b1[4];

struct Point2
{
	int x, y;
} a2[4], b2[4];

//Проверка на выход за границы игрового поля
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


//Проверка на столкновение объектов
bool check_collision()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		if ((a1[i].y == a2[j].y) && (a1[i].x == a2[j].x))
			return 0;

	return 1;
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
	background->draw(renderer);
}
GameScreen::~GameScreen() {
}
GameScreen::GameScreen()
{
	srand(time(0));

	RenderWindow window(VideoMode(1280, 720), "The Game!");
	backgroundTexture.loadFromFile("resources/background.png");

	background = new Background();
	background->setTexture(&backgroundTexture);
	//Создание и загрузка текстуры
	Texture texture, texture_background;
	texture.loadFromFile("resources/tiles.png");
	texture_background.loadFromFile("resources/background.png");

	//Создание спрайта
	Sprite sprite1(texture), sprite2(texture), sprite_background(texture_background);
	//Вырезаем из спрайта отдельный квадратик размером 32 пикселей
	sprite1.setTextureRect(IntRect(0, 0, 32, 32));
	sprite2.setTextureRect(IntRect(0, 0, 32, 32));

	//Переменные для горизонтального перемещения и вращения
	int dx1 = 0, dx2 = 0; bool rotate1 = 0, rotate2 = 0; int colorNum1 = 1, colorNum2 = 1; bool beginGame = true; bool flag1 = true, flag2 = true; int n1 = rand() % 7, n2 = rand() % 7;



	//Переменные для таймера и задержки
	float timer1 = 0, timer2 = 0, delay1 = 1, delay2 = 1;
	int Score = 0, Lines = 0, Level = 1;
	//Часы (таймер)
	Clock clock;


	//Главный цикл приложения. Выполняется, пока открыто окно.
	while (window.isOpen())
	{
		//Работа с текстами (Счет, Скорость, Линии)
		sf::Font font;//шрифт 
		font.loadFromFile("resources/VCR_OSD_MONO_1.001.ttf");//передаем нашему шрифту файл шрифта
		Text text_score("", font, 32);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		text_score.setFillColor(sf::Color::Yellow);//покрасили текст в желтый
		text_score.setStyle(sf::Text::Bold);//жирный текст

		String Score_Nuliki = "0";
		int kolvo_nuley_Score = 10 - std::to_string(Score).length();
		while (kolvo_nuley_Score > 0)
		{
			kolvo_nuley_Score--;
			Score_Nuliki = Score_Nuliki + "0";
		}
		text_score.setString(Score_Nuliki + std::to_string(Score));//задает строку тексту
		text_score.setPosition(875, 70);//задаем позицию текста, центр камеры

	


		Text text_lines("", font, 32);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		text_lines.setFillColor(sf::Color::Yellow);//покрасили текст в желтый
		text_lines.setStyle(sf::Text::Bold);//жирный текст

		String Lines_Nuliki = "0";
		int kolvo_nuley_lines = 10 - std::to_string(Lines).length();
		while (kolvo_nuley_lines > 0)
		{
			kolvo_nuley_lines--;
			Lines_Nuliki = Lines_Nuliki + "0";
		}
		text_lines.setString(Lines_Nuliki + std::to_string(Lines));//задает строку тексту
		text_lines.setPosition(875, 310);//задаем позицию текста, центр камеры

		
		Text text_level("", font, 32);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
		text_level.setFillColor(sf::Color::Yellow);//покрасили текст в желтый
		text_level.setStyle(sf::Text::Bold);//жирный текст
		text_level.setString(std::to_string(Level));
		text_level.setPosition(980, 190);


		//Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer1 += time;
		timer2 += time;
		//Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			
			//Пользователь нажал на «крестик» и хочет окно закрыть?
			if (event.type == Event::Closed)
				//Тогда закрываем его
				window.close();
			//Была нажата кнопка на клавиатуре?
			if (event.type == Event::KeyPressed)
				//Эта кнопка – стрелка вверх?…
				if (event.key.code == Keyboard::W) rotate1 = true;
			//…или же стрелка влево?…
				else if (event.key.code == Keyboard::A) dx1 = -1;
			////…ну тогда может это стрелка вправо?
				else if (event.key.code == Keyboard::D) dx1 = 1;

			if (event.type == Event::KeyPressed)
				//Эта кнопка – стрелка вверх?…
				if (event.key.code == Keyboard::Up) rotate2 = true;
			//…или же стрелка влево?…
				else if (event.key.code == Keyboard::Left) dx2 = -1;
			////…ну тогда может это стрелка вправо?
				else if (event.key.code == Keyboard::Right) dx2 = 1;


		}
		
		//Нажали кнопку "вниз"? Ускоряем падение тетрамино
		if (Keyboard::isKeyPressed(Keyboard::S)) delay1 = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay2 = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
		//// Горизонтальное перемещение ////
		for (int i = 0; i < 4; i++) 
		{ 
			b1[i] = a1[i]; a1[i].x += dx1;
			b2[i] = a2[i]; a2[i].x += dx2;
		}
		//Вышли за пределы поля после перемещения? Тогда возвращаем старые координаты 
		if (!check1() || !check_collision()) for (int i = 0; i < 4; i++) a1[i] = b1[i];
		if (!check2() || !check_collision()) for (int i = 0; i < 4; i++) a2[i] = b2[i];

		////// Вращение //////
		if (rotate1)
		{
			Point1 p1 = a1[1]; //Задаем центр вращения
			for (int i = 0; i < 4; i++)
			{
				int x = a1[i].y - p1.y; //y-y0
				int y = a1[i].x - p1.x; //x-x0
				a1[i].x = p1.x - x;
				a1[i].y = p1.y + y;
			}
			//Вышли за пределы поля после поворота? Тогда возвращаем старые координаты 
			if (!check1() || !check_collision()) { for (int i = 0; i < 4; i++) a1[i] = b1[i]; }

		}

		////// Вращение //////
		if (rotate2)
		{
			Point2 p2 = a2[1]; //Задаем центр вращения
			for (int i = 0; i < 4; i++)
			{
				int x = a2[i].y - p2.y; //y-y0
				int y = a2[i].x - p2.x; //x-x0
				a2[i].x = p2.x - x;
				a2[i].y = p2.y + y;
			}
			//Вышли за пределы поля после поворота? Тогда возвращаем старые координаты 
			if (!check2() || !check_collision()) { for (int i = 0; i < 4; i++) a2[i] = b2[i]; }

		}

		////// Движение тетрамино вниз («Тик» таймера) //////
		if (timer1 > delay1)
		{

			for (int i = 0; i < 4; i++) { b1[i] = a1[i]; a1[i].y += 1; }
			if (!check1())
			{
				for (int i = 0; i < 4; i++) field[b1[i].y][b1[i].x] = colorNum1;
				colorNum1 = 1 + rand() % 7;
				n1 = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a1[i].x = figures[n1][i] % 2;
					a1[i].y = figures[n1][i] / 2;
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

		if (timer2 > delay2)
		{

			for (int i = 0; i < 4; i++) { b2[i] = a2[i]; a2[i].y += 1; }
			if (!check2())
			{
				for (int i = 0; i < 4; i++) field[b2[i].y][b2[i].x] = colorNum2;
				colorNum2 = 1 + rand() % 7;
				n2 = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a2[i].x = figures[n2][i] % 2;
					a2[i].y = figures[n2][i] / 2;
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



		//----ПРОВЕРКА ЛИНИИ----//
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

		//Подсчёт очков
		switch (count_explouded)
		{
		case 1:
		{
			Score += 100;
			Lines++;
			count_explouded = 0;
			break;
		}
		case 2:
		{
			Score += 300;
			Lines += 2;
			count_explouded = 0;
			break;
		}
		case 3:
		{
			Score += 700;
			Lines += 3;
			count_explouded = 0;
			break;
		}
		case 4:
		{
			Score += 1500;
			Lines += 4;
			count_explouded = 0;
			break;
		}
		default:
		{
			count_explouded = 0;
			break;
		}
		}
		// Поражение
		for (int i = 0; i < M; i++)
			if (field[0][i])
			{
				window.close();
			}

		//Первое появление тетрамино на поле?
		if (beginGame)
		{
			beginGame = false;
			n1 = rand() % 7;
			n2 = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a1[i].x = figures[n1][i] % 2;
				a1[i].y = figures[n1][i] / 2;
				a2[i].x = figures[n2][i] % 2;
				a2[i].y = figures[n2][i] / 2;
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
		dx1 = 0; rotate1 = 0; delay1 = 1, dx2 = 0; rotate2 = 0; delay2 = 1;
		//----ОТРИСОВКА----//
		//Задаем цвет фона (Белый)
		window.clear(Color::White);
		window.draw(sprite_background);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) 
					continue;
				sprite1.setTextureRect(IntRect(field[i][j] * 32, 0, 32, 32));
				sprite1.setPosition(j * 32, i * 32);
				sprite1.move(40, 40); //Смещение
				window.draw(sprite1);

				sprite2.setTextureRect(IntRect(field[i][j] * 32, 0, 32, 32));
				sprite2.setPosition(j * 32, i * 32);
				sprite2.move(40, 40); //Смещение
				window.draw(sprite2);
			}

		for (int i = 0; i < 4; i++)
		{

			//Разукрашиваем тетрамино
			sprite1.setTextureRect(IntRect(colorNum1 * 32, 0, 32, 32));
			//Устанавливаем позицию каждого кусочка тетрамино
			sprite1.setPosition(a1[i].x * 32, a1[i].y * 32);
			sprite1.move(40, 40); //Смещение
			
			//Отрисовка спрайта
			window.draw(sprite1);


			//Разукрашиваем тетрамино
			sprite2.setTextureRect(IntRect(colorNum2 * 32, 0, 32, 32));
			//Устанавливаем позицию каждого кусочка тетрамино
			sprite2.setPosition(a2[i].x * 32, a2[i].y * 32);
			sprite2.move(40, 40); //Смещение

			//Отрисовка спрайта
			window.draw(sprite2);
		}
		window.draw(text_score);//Отрисовка текста счета
		window.draw(text_lines);//Отрисовка текста линий
		window.draw(text_level);//Отрисовка текста левелов
		//Отрисовка окна
		window.display();
	}
}