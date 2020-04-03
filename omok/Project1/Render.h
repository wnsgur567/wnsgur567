#pragma once

#define WHITE 1
#define BLACK -1
#define NONE 0
#define BLANK 30
#define RADIUS 23

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;



//�̹��� �׸��� (MemDC,MyBitmap,���ϰ��,�»�� ��ǥ(x,y),�̹��� ����
void drawing_img(HDC MemDC, const wchar_t *str,
	int x, int y, int width = 70, int height = 70);
void drawing_img_rotate(HDC MemDC, const wchar_t *str, int angle, int angleX, int angleY,
	int x, int y, int width = 70, int height = 70);
void drawing_img_transparent(HDC MemDC, const wchar_t *str, float transparent,
	int x, int y, int width = 70, int height = 70);

//�� �׸��� (MemDC,MyBitmap ,���� ��ǥ(x1,y1) ,�� ��ǥ(x2,y2) , ����ó���� �� ,rgb
void drawing_line(HDC MemDC, int x1, int y1, int x2, int y2, int transparent, int r, int g, int b, int thick = 2);

//�簢�� �׸��� (MemDC ,���� ��ǥ(x1,y1) ,�� ��ǥ(x2,y2) , ����ó���� �� ,rgb
//judge		 0(fillColor), 1(lineColor)
void drawing_rect(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge = 0);

//�� �׸��� (MemDC,MyBitmap ,���� ��ǥ(x1,y1) ,�� ��ǥ(x2,y2) , ����ó���� �� ,rgb
void drawing_ellipse(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge = 0);

void Render();