#include <SFML/Graphics.hpp>
#include "Application.h"
using namespace app;
using namespace sf;

Application::Application() {
	window = new RenderWindow(VideoMode(1280, 720), "Tetris", Style::Close);
}
Application::~Application() {
	delete window;
	 
}


const int singleM = 20; 
const int singleN = 10; 
const int multiM = 20;
const int multiN = 20;
int field_single[singleM][singleN] = { 0 }; 
int field_multi[multiM][multiN] = { 0 };
//������ �������-���������
int figures[7][4]=
{
	0,2,4,6, // �����
	3,4,5,6, // ��� Z
	0,2,3,5, // ��� S
	1,2,3,5, // ������������ �
	2,3,5,7, // ������� L
	1,3,4,5, // �������� ������� L
	2,3,4,5, // �����
};

struct Point
{
	int x, y;
} a[4], b[4];


void Application::run(){

	//�������� � �������� ��������
	Texture texture;
	texture.loadFromFile("resources\\tiles.png");

	//�������� �������
	Sprite sprite(texture);
	int dx = 0;
	bool rotate = false;
	bool speedDown = false;
	float timer = 0, delay = 0.3;

	// ���� (������)
	Clock clock;

	while (window->isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		//������������ ������� ������� � �����
		Event event;
		while (window->pollEvent(event))
		{
			//������������ ����� �� �������� � ����� ���� �������?
			if (event.type == Event::Closed)
				//����� ��������� ���
				window->close();
			if (event.type == Event::KeyPressed) {
				// ��� ������ � ������� �����?
				if (event.key.code == Keyboard::Up) rotate = true;

				else if (event.key.code == Keyboard::Down) speedDown = true;
				// ��� ����� ������� �����?
				else if (event.key.code == Keyboard::Left) dx = -1;
				// ��� ������� ������?
				else if (event.key.code == Keyboard::Right) dx = 1;
			}
		}
		for (int i = 0; i < 4; i++) a[i].x += dx;
		if (rotate)
		{
			Point p = a[1]; // ��������� ����� ��������
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y; // y - y0
				int y = a[i].x - p.x; // x - x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			rotate = false;
		}
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) a[i].y += 1;
			timer = 0;

		}
		int n = 0; //������ ��� ���������
		if (a[0].x == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] / 2;
				a[i].y = figures[n][i] % 2;
				
			}
		}

		//������ ���� ���� (�����)
		//window->clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			sprite.setTextureRect(IntRect(0 + 32 * n, 0, 32, 32));
			sprite.setPosition(a[i].x * 32 +100, a[i].y * 32+ 100);
			//��������� �������
			window->draw(sprite);
		}

		//��������� ����
		window->display();
	}
}