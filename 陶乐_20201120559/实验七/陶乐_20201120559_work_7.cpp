//Cohen-Sutherland直线段裁剪算法
#include<windows.h>
#include <GL/glut.h>
#define Left 1
#define Right 2
#define Bottom 4
#define Top 8
#define xl 200
#define xr 400
#define yb 200
#define yt 400

void creat()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, 480, 0.0, 480);
}
void Drawpixel(float x, float y) {
	glPointSize(1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2i((float)(x), (float)(y));
}
void DrawLine(float x0, float y0, float x1, float y1) {
	float a, b, d1, d2, d, x, y, k;
	a = y0 - y1, b = x1 - x0, d = 2 * a + b;
	d1 = 2 * a, d2 = 2 * (a + b);
	x = x0, y = y0;
	while (x <= x1) {
		if (d <= 0) {
			x++, y++, d += d2;
		}
		else {
			x++, d += d1;
		}
		Drawpixel(x, y);
	}
	if (x0 = x1) {
		while (y < y1) {
			Drawpixel(x, y);
			y++;
		}
	}

}
int Encode(float x, float y) {
	int c = 0;
	if (x < xl)c = c | Left;
	if (x>xr)c = c | Right;
	if (y < yb)c = c | Bottom;
	if (y>yt)c = c | Top;
	return c;
}
void CS_LineClip(float x1, float y1, float x2, float y2) {
	int code1, code2, code;
	float x, y;
	code1 = Encode(x1, y1);
	code2 = Encode(x2, y2);
	while (code1 != 0 || code2 != 0) {
		if (code1&&code2 != 0)return;
		if (code1 != 0)code = code1;
		else code = code2;
		if ((Left&code) != 0) {
			x = xl;
			y = y1 + (y2 - y1)*(xl - x1) / (x2 - x1);
		}
		else if ((Right&code) != 0) {
			x = xr;
			y = y1 + (y2 - y1)*(xr - x1) / (x2 - x1);
		}
		else if ((Bottom&code) != 0) {
			y = yb;
			x = xl + (x2 - x1)*(yb - y1) / (y2 - y1);
		}
		else if ((Top&code) != 0) {
			y = yt;
			x = xl + (x2 - x1)*(yt - y1) / (y2 - y1);
		}
		if (code == code1) {
			x1 = x; y1 = y; code1 = Encode(x, y);
		}
		else {
			x2 = x; y2 = y; code2 = Encode(x, y);
		}
	}
	DrawLine(x1, y1, x2, y2);
}
void display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	CS_LineClip(150, 200, 350, 300);
	CS_LineClip(350, 300, 220, 400);
	//CS_LineClip(300, 350, 220, 300);
	DrawLine(200, 200, 200, 400);
	DrawLine(200, 200, 400, 200);
	DrawLine(200, 400, 400, 400);
	DrawLine(400, 200, 400, 400);
	glEnd();
	glFlush();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(300, 200);
	glutCreateWindow(" Cohen-Sutherland");
	creat();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

