# 二、DDA直线生成算法

## 1、实验内容

1. 使用DDA算法（数值微分法），在给定的直线段两端点P0(x0,y0)和P1(x1,y1)，画出直线段；
2. 使用OpenGL实现DDA算法的代码程序。

## 2、实验目的

1. DDA算法原理：

   直线的微分方程：

   ![image-20220527181124928](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527181124928.png)

   

- ​	max(|△x|,|△y|)=|△x|，即|k|≤1的情况：

  ![image-20220527181534946](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527181534946.png)

  

- max(|△x|,|△y|)=|△y|，此时|k|≥1：

  ![image-20220527181553175](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527181553175.png)

  

  如图为两种情况下的坐标取值方式：

  ![image-20220527181952070](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527181952070.png)

  

## 3、实验代码

1. 当dx>dy时，此时斜率k<1，去上式第一种情况，否则取第二种情况

```c++
void LineDDA(int x0,int y0,int xEnd,int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - 0, steps,k;
    float xIncrement, yIncrement,x = x0, y = y0;

    if(fabs(dx)>fabs(dy))
        steps = fabs(dx); //斜率K<1
    else
        steps = fabs(dy); //斜率K>1

    xIncrement = float(dx)/float(steps); //计算增量
    yIncrement = float(dy)/float(steps);

    SetPixel(round(x),round(y));
    for(k=0; k<steps; k++){
        x += xIncrement; 
        y += yIncrement;
        SetPixel(round(x),round(y));
    }
}
```



2. 画点函数SetPixel：

   ```c++
   void SetPixel(GLint x,GLint y)
   {
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd( );
   }
   ```

   

3. 完整程序如下：

   ```c++
   #include<windows.h>
   #include<stdlib.h>
   #include<math.h>
   #include<Gl/glu.h>
   #include<Gl/glut.h>
   #include<iostream>
   using namespace std;
   
   inline int round(const float a)
   {
       return int(a+0.5);
   }
   
   void SetPixel(GLint x,GLint y)
   {
       glBegin(GL_POINTS);
       glVertex2i(x,y);
       glEnd( );
   }
   
   void LineDDA(int x0,int y0,int xEnd,int yEnd)
   {
       int dx = xEnd - x0, dy = yEnd - 0, steps,k;
       float xIncrement, yIncrement,x = x0, y = y0;
   
       if(fabs(dx)>fabs(dy))
           steps = fabs(dx); //斜率K<1
       else
           steps = fabs(dy); //斜率K>1
   
       xIncrement = float(dx)/float(steps);   //计算增量
       yIncrement = float(dy)/float(steps);
   
       SetPixel(round(x),round(y));
       for(k=0; k<steps; k++){
           x += xIncrement;
           y += yIncrement;
           SetPixel(round(x),round(y));
       }
   }
   
   void myDisplay(void)
   {
       glClearColor(1.0, 1.0, 1.0, 0.0);
       glClear(GL_COLOR_BUFFER_BIT);
       glViewport(0, 0, 500, 500);
   
       GLint x1,y1,x2,y2;
       LineDDA(0,0,500,600);
       glFlush( );
   }
   
   int main(int argc,char** argv)
   {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
       glutInitWindowSize(500, 500);
       glutInitWindowPosition(0, 0);
       glutCreateWindow("DDA_line");
   
       glutDisplayFunc(myDisplay);
       glColor3f(0.0, 1.0, 1.0);
       gluOrtho2D(0.0, 500.0, 0.0, 500.0);
       glutMainLoop();
       return 0;
   }
   ```

   

4. 编译结果：

​	![image-20220527183151854](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527183151854.png)



