#include "Render.h"
#include "Board.h"

//�̹��� �׸��� (MemDC,MyBitmap,���ϰ��,�»�� ��ǥ(x,y),�̹��� ����
void drawing_img(HDC MemDC, const wchar_t *str, int x, int y, int width, int height) {
	Graphics graphic(MemDC);
	Image image(str);
	graphic.DrawImage(&image, x, y, width, height);
}

// ���� �� 0.1f ~ 1.0
void drawing_img_transparent(HDC MemDC, const wchar_t *str, float transparent, int x, int y, int width, int height) {

	Graphics graphic(MemDC);
	Image image(str);

	int nImageWidth = image.GetWidth();
	int nImageHeight = image.GetHeight();

	// ���� ��
	REAL rTransparency = transparent;    // 0.1f ~ 1.0
	ColorMatrix colorMatrix =
	{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, rTransparency, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);

	graphic.DrawImage(&image, Rect(x, y, image.GetWidth(), image.GetHeight()),
		0, 0, image.GetWidth(), image.GetHeight(), UnitPixel, &imageAtt);
}

void drawing_img_rotate(HDC MemDC, const wchar_t *str, int angle, int angleX, int angleY,
	int x, int y, int width, int height) {
	Matrix m;	//ȸ���� ���� ���

	Graphics graphic(MemDC);
	Image image(str);
	//���� ���� ��ġ�� ��߳� ��ŭ ����
	m.RotateAt(angle, PointF(float(angleX), float(angleY)));
	graphic.SetTransform(&m);

	graphic.DrawImage(&image, x, y, width, height);
}

//�� �׸��� (MemDC,MyBitmap ,���� ��ǥ(x1,y1) ,�� ��ǥ(x2,y2) , ����ó���� �� ,rgb
void drawing_line(HDC MemDC, int x1, int y1, int x2, int y2, int transparent, int r, int g, int b, int thick) {
	Graphics graphic(MemDC);
	Pen pen(Color(transparent, r, g, b), thick);	//���
	graphic.DrawLine(&pen, x1, y1, x2, y2);
}

//�簢�� �׸��� (MemDC ,���� ��ǥ(x1,y1) ,����(x2,y2) , ����ó���� �� ,rgb
//judge		 0(fillColor), 1(lineColor)
void drawing_rect(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge)
{
	Graphics graphic(MemDC);
	if (judge) {
		SolidBrush brush(Color(transparent, r, g, b));	//ä���
		graphic.FillRectangle(&brush, x1, y1, width, length);
	}
	else {
		Pen pen(Color(transparent, r, g, b));	//���
		graphic.DrawRectangle(&pen, x1, y1, width, length);
	}
}

//�� �׸��� (MemDC,MyBitmap ,���� ��ǥ(x1,y1) , ����(x2,y2) , ����ó���� �� ,rgb
void drawing_ellipse(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge)
{
	Graphics graphic(MemDC);
	if (judge) {
		SolidBrush brush(Color(transparent, r, g, b));	//ä���
		graphic.FillEllipse(&brush, x1, y1, width, length);
	}
	else {
		Pen pen(Color(transparent, r, g, b));	//���
		graphic.DrawEllipse(&pen, x1, y1, width, length);
	}
}

extern HWND hWnd;
extern Board* board;
extern int mouseX;
extern int mouseY;
#define WHITE 1
#define BLACK -1
#define NONE 0

void Render() {
	HBITMAP MyBitmap, OldBitmap;
	HDC whdc = GetDC(hWnd);
	HDC MemDC = CreateCompatibleDC(whdc);


	//����ǳ�? > �ȵ� ��
	MyBitmap = CreateCompatibleBitmap(whdc, MAP_W, MAP_H);
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);


	PatBlt(MemDC, 0, 0, MAP_W, MAP_H, WHITENESS);

	//�׵θ�
	drawing_line(MemDC, 100 - BLANK, 100 - BLANK, 100 - BLANK, 1000 + BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 100 - BLANK, 100 - BLANK, 1000 + BLANK, 100 - BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 1000 + BLANK, 1000 + BLANK, 100 - BLANK, 1000 + BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 1000 + BLANK, 1000 + BLANK, 1000 + BLANK, 100 - BLANK, 255, 255, 0, 255);

	//�߰�����
	for (int i = 0; i < 19; i++)
		drawing_line(MemDC, 100 + i * 50, 100, 100 + i * 50, 1000, 255, 0, 0, 0, 1);
	for (int i = 0; i < 19; i++)
		drawing_line(MemDC, 100, 100 + i * 50, 1000, 100 + i * 50, 255, 0, 0, 0, 1);

	//�ٵϵ�
	int(*arr)[20] = board->ReturnArray();
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j < 20; j++) {
			if (arr[i][j] == WHITE) {
				drawing_ellipse(MemDC, 50+i*50- RADIUS, 50+j*50 - RADIUS, RADIUS * 2, RADIUS * 2, 255, 255, 255, 255, 1); 
				drawing_ellipse(MemDC, 50+i*50 - RADIUS, 50+j*50 - RADIUS, RADIUS * 2, RADIUS * 2, 255, 0, 0, 0, 0); 
			}			
			else if (arr[i][j] == BLACK) 
				drawing_ellipse(MemDC, 50+i*50 - RADIUS, 50+j*50 - RADIUS, RADIUS * 2, RADIUS * 2, 255, 0, 0, 0, 1); 			
		}
	}

	//TODO : �ٵϵ� ������ ,���콺��ġ �ٵϵ� �ȳ����� ����
	int mx = mouseX / 50 - 1;	int my = mouseY / 50 - 1;
	//���콺 ��ġ �ٵϵ�
	if (arr[mx][my] == NONE) {
		if (board->getOffense() == BLACK)
			drawing_ellipse(MemDC, mouseX - RADIUS, mouseY - RADIUS, RADIUS * 2, RADIUS * 2, 255, 0, 0, 0, 1);
		if (board->getOffense() == WHITE) {
			drawing_ellipse(MemDC, mouseX - RADIUS, mouseY - RADIUS, RADIUS * 2, RADIUS * 2, 255, 255, 255, 255, 1);
			drawing_ellipse(MemDC, mouseX - RADIUS, mouseY - RADIUS, RADIUS * 2, RADIUS * 2, 255, 0, 0, 0, 0);
		}
	}
	
	BitBlt(whdc, 0, 0, MAP_W, MAP_H, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	ReleaseDC(hWnd, whdc);
	DeleteDC(MemDC);
	DeleteObject(MyBitmap);
	DeleteObject(OldBitmap);
}