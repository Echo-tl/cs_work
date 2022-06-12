# 一、直线段裁剪算法



## 1、实验内容

1. 理解并掌握 Cohen-Sutherland算法，根据直线段的裁剪算法对落在窗口内的直线段进行裁剪；

2. 利用OpenGL实现直线段的裁剪算法程序。

   

## 2、实验原理

1. 对每条直线段p1(x1,y1)，p2(x2,y2)分三种情况处理：

   - 直线段完全可见，“简取”之；

   - 直线段完全不可见，“简弃”之；

   - 以上情况不满足的，对直线段按交点进行分段，分段后重复上述处理。

     

2. 编码：

   对任意端点，根据其区域，对该点坐标进行二进制编码，按如下规则：

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220528195748170.png" alt="image-20220528195748170" style="zoom:33%;" />



3. 算法步骤

   - 对直线段的两端点坐标：p1(x1,y1)，p2(x2,y2)进行编码分别为code1，code2.

   - 若code1|code2=0，对直线段应简取；

   - 若code1&code2≠0，对直线段可简弃之；

   - 否则说明直线段一部分在窗口内，一部分在窗口外，求出直线段与窗口边界的交点，赋为p1点，在进行编码判断；

   - 调用函数，画出该直线。

     

4. 采用DDA算法，画直线，代码如下：

   ```c++
   void DrawLine(float x0, float y0, float x1, float y1) {
   	float a, b, d1, d2, d, x, y, k;
   	a = y0 - y1, b = x1 - x0, d = 2 * a + b;
   	d1 = 2 * a, d2 = 2 * (a + b);
   	x = x0, y = y0;
   	while (x <= x1) {
   		if (d <= 0) {
   			x++, y++, d += d2; //下一个点位(x+1，y+1)，更新d值
   		}
   		else {
   			x++, d += d1; //下一个点(x+1，y),更新d值
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
   ```

   

5. 根据编码原则，对点进行编码：

   ```c++
   int Encode(float x, float y) {
   	int c = 0;
   	if (x < xl)c = c | Left;
   	if (x>xr)c = c | Right;
   	if (y < yb)c = c | Bottom;
   	if (y>yt)c = c | Top;
   	return c;
   }
   ```

   

6. 裁剪过程：

   根据编码的值判断是简取还是简弃，否则求出该直线方程，并求出与窗口交点，在进行判断。

   ```c++
   while (code1 != 0 || code2 != 0) {
   		if (code1&&code2 != 0)return; //简弃
   		if (code1 != 0)code = code1;
   		else code = code2; 
   		if ((Left&code) != 0) { //说明交点在左窗口
   			x = xl;
   			y = y1 + (y2 - y1)*(xl - x1) / (x2 - x1);
   		}
   		else if ((Right&code) != 0) { //交点在右窗口
   			x = xr;
   			y = y1 + (y2 - y1)*(xr - x1) / (x2 - x1);
   		}
   		else if ((Bottom&code) != 0) { //交点位于下窗口
   			y = yb;
   			x = xl + (x2 - x1)*(yb - y1) / (y2 - y1);
   		}
   		else if ((Top&code) != 0) { //交点在上窗口
   			y = yt;
   			x = xl + (x2 - x1)*(yt - y1) / (y2 - y1);
   		}
   		if (code == code1) { //重新进行编码
   			x1 = x; y1 = y; code1 = Encode(x, y);
   		}
   		else {
   			x2 = x; y2 = y; code2 = Encode(x, y);
   		}
   	}
   	DrawLine(x1, y1, x2, y2); //简取，并画出该直线
   ```

   

## 3、实验代码

1. 完整代码：

   ```c++
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
   		if (code1&&code2 != 0)return; //简弃
   		if (code1 != 0)code = code1;
   		else code = code2; 
   		if ((Left&code) != 0) { //说明交点在左窗口
   			x = xl;
   			y = y1 + (y2 - y1)*(xl - x1) / (x2 - x1);
   		}
   		else if ((Right&code) != 0) { //交点在右窗口
   			x = xr;
   			y = y1 + (y2 - y1)*(xr - x1) / (x2 - x1);
   		}
   		else if ((Bottom&code) != 0) { //交点位于下窗口
   			y = yb;
   			x = xl + (x2 - x1)*(yb - y1) / (y2 - y1);
   		}
   		else if ((Top&code) != 0) { //交点在上窗口
   			y = yt;
   			x = xl + (x2 - x1)*(yt - y1) / (y2 - y1);
   		}
   		if (code == code1) { //重新进行编码
   			x1 = x; y1 = y; code1 = Encode(x, y);
   		}
   		else {
   			x2 = x; y2 = y; code2 = Encode(x, y);
   		}
   	}
   	DrawLine(x1, y1, x2, y2); //简取，并画出该直线
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
   	glutCreateWindow("裁剪直线算法");
   	creat();
   	glutDisplayFunc(display);
   	glutMainLoop();
   	return 0;
   }
   ```

   

2. 编译结果：

   ![image-20220528201703743](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220528201703743.png)