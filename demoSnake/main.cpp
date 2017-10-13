// demo by Nguyễn Trung Thành (abcxyz tcIT)
// Facebook: fb.me/abcxyztcIT

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE


#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"

#define consoleWidth	25
#define consoleHeight	25


enum TrangThai {UP, DOWN, LEFT, RIGHT};

struct ToaDo
{
	int y, x;	// y là tung độ, x là hoành độ
};


struct HoaQua
{
	ToaDo td;
};


struct Snake
{
	ToaDo dot[31];
	int n;
	TrangThai tt;
};


void KhoiTao (Snake &snake, HoaQua &hq)
{
	snake.n = 1;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;

	snake.tt = RIGHT;

	hq.td.x = 10;
	hq.td.y = 10;
}


void HienThi (Snake snake, HoaQua hq)
{
	clrscr();

	// in ra rào bên phải
	TextColor (default_ColorCode);
	for (int i = 0; i < consoleHeight; i++)
	{
		gotoXY (consoleWidth, i);
		putchar (179);
	}

	// in ra hoa quả
	TextColor (ColorCode_Green);
	gotoXY (hq.td.x, hq.td.y);
	putchar ('A');

	// in ra con rắn nè
	TextColor (ColorCode_Pink);
	gotoXY (snake.dot[0].x, snake.dot[0].y);
	putchar (2);

	for (int i = 1; i < snake.n; i++)
	{
		gotoXY (snake.dot[i].x, snake.dot[i].y);
		putchar ('*');
	}
}


void DieuKhien_DiChuyen (Snake &snake)
{
	// truyền trạng thái cho đốt cũ
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i-1];

	if (_kbhit()) // nếu phát hiện có phím nhấn vào
	{
		int key = _getch();

		// điều khiển cái đầu mà thôi
		if (key == 'A' || key == 'a')
			snake.tt = LEFT;
		else if (key == 'D' || key == 'd')
			snake.tt = RIGHT;
		else if (key == 'W' || key == 'w')
			snake.tt = UP;
		else if (key == 'S' || key == 's')
			snake.tt = DOWN;
	}


	if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == LEFT)
		snake.dot[0].x--;
	else if (snake.tt == RIGHT)
		snake.dot[0].x++;
}


// trả về 0 nếu không có gì
// trả về -1 nếu thua game
int XuLy (Snake &snake, HoaQua &hq, int &ThoiGianSleep)
{
	if (snake.dot[0].x < 0 || snake.dot[0].x >= consoleWidth ||
		snake.dot[0].y < 0 || snake.dot[0].y >= consoleHeight)
			return -1;

	for (int i = 1; i < snake.n; i++)
		if (snake.dot[0].x == snake.dot[i].x &&
			snake.dot[0].y == snake.dot[i].y )
				return -1;


	if (snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y)
	{
		// ăn được hoa quả
		// việc ăn được hoa quả rồi mới chèn thêm cái đầu mới thì thật sự chưa giải quyết tốt cho lắm
		// các bạn cần suy nghĩ thêm để tốt hơn

		for (int i = snake.n; i > 0; i--)
			snake.dot[i] = snake.dot[i-1];

		snake.n++;

		if (snake.tt == UP)
			snake.dot[0].y--;
		else if (snake.tt == DOWN)
			snake.dot[0].y++;
		else if (snake.tt == LEFT)
			snake.dot[0].x--;
		else if (snake.tt == RIGHT)
			snake.dot[0].x++;

		hq.td.x = rand() % consoleWidth;
		hq.td.y = rand() % consoleHeight;

		if (ThoiGianSleep > 30)
			ThoiGianSleep -= 20;
	}

	return 0;
}


int main()
{
	srand(time(NULL));	// khởi tạo bộ sinh số ngẫu nhiên

	Snake snake;
	HoaQua hq;

	KhoiTao (snake, hq);

	int ma = 0;
	int ThoiGianSleep = 200;

	while (1)
	{
		// hiển thị
		HienThi (snake, hq);

		// điều khiển
		DieuKhien_DiChuyen (snake);

		// xử lý ăn hoa quả, thua game
		ma = XuLy (snake, hq, ThoiGianSleep);

		// thua game, thắng game
		if (ma == -1)	// thua game đó nha
		{
			gotoXY (consoleWidth + 1, 10);
			printf ("Ban thua roi, liu liu");
			
			while (_getch() != 13)	;

			break;
		}

		Sleep (ThoiGianSleep);
	}


	return 0;
}