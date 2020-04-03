#include "Render.h"
#include "Board.h"

//이미지 그리기 (MemDC,MyBitmap,파일경로,좌상단 좌표(x,y),이미지 길이
void drawing_img(HDC MemDC, const wchar_t *str, int x, int y, int width, int height) {
	Graphics graphic(MemDC);
	Image image(str);
	graphic.DrawImage(&image, x, y, width, height);
}

// 투명도 값 0.1f ~ 1.0
void drawing_img_transparent(HDC MemDC, const wchar_t *str, float transparent, int x, int y, int width, int height) {

	Graphics graphic(MemDC);
	Image image(str);

	int nImageWidth = image.GetWidth();
	int nImageHeight = image.GetHeight();

	// 투명도 값
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
	Matrix m;	//회전을 위한 행렬

	Graphics graphic(MemDC);
	Image image(str);
	//현재 팔의 위치가 어긋난 만큼 조정
	m.RotateAt(angle, PointF(float(angleX), float(angleY)));
	graphic.SetTransform(&m);

	graphic.DrawImage(&image, x, y, width, height);
}

//선 그리기 (MemDC,MyBitmap ,시작 좌표(x1,y1) ,끝 좌표(x2,y2) , 투명처리할 값 ,rgb
void drawing_line(HDC MemDC, int x1, int y1, int x2, int y2, int transparent, int r, int g, int b, int thick) {
	Graphics graphic(MemDC);
	Pen pen(Color(transparent, r, g, b), thick);	//펜색
	graphic.DrawLine(&pen, x1, y1, x2, y2);
}

//사각형 그리기 (MemDC ,시작 좌표(x1,y1) ,길이(x2,y2) , 투명처리할 값 ,rgb
//judge		 0(fillColor), 1(lineColor)
void drawing_rect(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge)
{
	Graphics graphic(MemDC);
	if (judge) {
		SolidBrush brush(Color(transparent, r, g, b));	//채울색
		graphic.FillRectangle(&brush, x1, y1, width, length);
	}
	else {
		Pen pen(Color(transparent, r, g, b));	//펜색
		graphic.DrawRectangle(&pen, x1, y1, width, length);
	}
}

//원 그리기 (MemDC,MyBitmap ,시작 좌표(x1,y1) , 길이(x2,y2) , 투명처리할 값 ,rgb
void drawing_ellipse(HDC MemDC, int x1, int y1, int width, int length, int transparent, int r, int g, int b, int judge)
{
	Graphics graphic(MemDC);
	if (judge) {
		SolidBrush brush(Color(transparent, r, g, b));	//채울색
		graphic.FillEllipse(&brush, x1, y1, width, length);
	}
	else {
		Pen pen(Color(transparent, r, g, b));	//펜색
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


	//없어도되나? > 안됨 ㅎ
	MyBitmap = CreateCompatibleBitmap(whdc, MAP_W, MAP_H);
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);


	PatBlt(MemDC, 0, 0, MAP_W, MAP_H, WHITENESS);

	//테두리
	drawing_line(MemDC, 100 - BLANK, 100 - BLANK, 100 - BLANK, 1000 + BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 100 - BLANK, 100 - BLANK, 1000 + BLANK, 100 - BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 1000 + BLANK, 1000 + BLANK, 100 - BLANK, 1000 + BLANK, 255, 255, 0, 255);
	drawing_line(MemDC, 1000 + BLANK, 1000 + BLANK, 1000 + BLANK, 100 - BLANK, 255, 255, 0, 255);

	//중간라인
	for (int i = 0; i < 19; i++)
		drawing_line(MemDC, 100 + i * 50, 100, 100 + i * 50, 1000, 255, 0, 0, 0, 1);
	for (int i = 0; i < 19; i++)
		drawing_line(MemDC, 100, 100 + i * 50, 1000, 100 + i * 50, 255, 0, 0, 0, 1);

	//바둑돌
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

	//TODO : 바둑돌 있으면 ,마우스위치 바둑돌 안나오게 수정
	int mx = mouseX / 50 - 1;	int my = mouseY / 50 - 1;
	//마우스 위치 바둑돌
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