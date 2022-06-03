# 一、中点Bresenham算法

## 1、实验内容

1. 通过给定直线的两端点坐标P0(x0,y0)和P1(x1,y1)，使用中点Bresenham算法画出直线段；
2. 利用OpenGL代码是实现Bresenham算法。

## 2、实验原理

1. F(x,y) = y - kx - b = 0

   当斜率0<k<=1时：

![image-20220527184025038](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527184025038.png)

- [ ] 计算判别式：

  ![image-20220527184431110](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527184431110.png)

  - 当d<0时：

    说明下一个点取y = y + 1,则可知中点为（x+2 , y+1.5)

  <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527184546136.png" alt="image-20220527184546136" style="zoom:33%;" />

  - 当d>=0时：

    说明中点为（x+2 , y+0.5)

  <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527184650685.png" alt="image-20220527184650685" style="zoom:33%;" />

  

- [ ] 计算初始值可得 d0 = 0.5 - k

  则可知算法：x = x + 1；y的取值如下：

<img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527185248660.png" alt="image-20220527185248660" style="zoom:33%;" />

2. 当斜率k<1时，x = x + 1，计算d值；

   若d<0，则(x,y)更新为(x+1,y+1)，d更新为 d+2△x-2△y

   否则(x,y)更新为(x+1,y), d更新为d-2△y。

   ```c++
   SetPixel(x, y);
           p1 =  2*abs(dy) - abs(dx);
           for (i = min(x1, x2); i < max(x1, x2); i++){
               x = x + 1;
               if(p1 >= 0){
                   if(dx*dy >= 0){
                       y = y+1; //(x,y)更新为(x+1,y+1)
                   }
                   else{
                       y = y-1;
                   }
                   p1 = p1 + 2*(abs(dy) - abs(dx)); //更新d值
               }
               else{
                   y = y;   //(x,y)更新为(x+1,y)
                   p1 = p1 + 2*abs(dy);
               }
               SetPixel(x, y);
           }
       }
   ```

   

3. 同理，当斜率k>1时，y = y + 1，计算x值；

   ```c++
   SetPixel(x, y);
   
   		p1 = 2*abs(dx) - abs(dy);
   		for (i = min(y1, y2); i < max(y1, y2); i++){
               y = y + 1;
               if(p1 >= 0){
                   if(dx*dy >=0){
                       x = x+1;  //(x,y)更新为(x+1,y+1)
                   }
                   else{
                       x = x-1;
                   }
                   p1 = p1 + 2*(abs(dy) - abs(dx));
               }
               else{
                   x = x; //(x,y)更新为(x,y+1)
                   p1 = p1 + 2*abs(dx);
               }
                SetPixel(x, y);
   		}
       }
   ```

   

## 3、程序代码

1. 完整程序代码：

   ```c++
   #include<windows.h>
   #include <GL/glut.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <graphics.h>
   #include<math.h>
   
   int max(int x1,int x2)
   {
       if(x2>=x1){
           return x2;
       }
       else{
           return x1;
       }
   }
   
   int min(int x1,int x2)
   {
       if(x2 <= x1){
           return x2;
       }
       else{
           return x1;
       }
   }
   
   void SetPixel(GLint x,GLint y)
   {
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd( );
   }
   
   void lineBres(int x1,int y1,int x2,int y2)
   {
       int x, y, dx, dy, p1, i;
       dx = x2-x1;
       dy = y2-y1;
       if(abs(dx > dy)){
           if(x1<x2){
               x = x1;
               y = y1;
           }
           else{
               x = x2;
               y = y2;
           }
           SetPixel(x, y);
           p1 =  2*abs(dy) - abs(dx);
           for (i = min(x1, x2); i < max(x1, x2); i++){
               x = x + 1;
               if(p1 >= 0){
                   if(dx*dy >= 0){
                       y = y+1;
                   }
                   else{
                       y = y-1;
                   }
                   p1 = p1 + 2*(abs(dy) - abs(dx));
               }
               else{
                   y = y;
                   p1 = p1 + 2*abs(dy);
               }
               SetPixel(x, y);
           }
       }
       else{
           if(y1<y2){
               x = x1;
               y = y1;
           }
           else{
               x= x2;
               y = y2;
           }
           SetPixel(x, y);
   
   		p1 = 2*abs(dx) - abs(dy);
   		for (i = min(y1, y2); i < max(y1, y2); i++){
               y = y + 1;
               if(p1 >= 0){
                   if(dx*dy >=0){
                       x = x+1;
                   }
                   else{
                       x = x-1;
                   }
                   p1 = p1 + 2*(abs(dy) - abs(dx));
               }
               else{
                   x = x;
                   p1 = p1 + 2*abs(dx);
               }
                SetPixel(x, y);
   		}
       }
   }
   void My_Display(void)
   {
       glClearColor(1.0, 1.0, 1.0, 0.0);
       glClear(GL_COLOR_BUFFER_BIT);
       glViewport(0, 0, 500, 500);
   
       lineBres(0,0,400,200);
       lineBres(0,0,200,300);
       glFlush( );
   }
   
   int main(int argc,char** argv)
   {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(0, 0);
       glutCreateWindow("Bream_line");
   
       glutDisplayFunc(My_Display);
       glColor3f(0.0, 1.0, 1.0);
       gluOrtho2D(0.0, 500.0, 0.0, 500.0);
       glutMainLoop();
       return 0;
   }
   ```

   

2. 编译结果：

   ![image-20220527190531142](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527190531142.png)