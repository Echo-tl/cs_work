# 一、直线段生成算法

## 1、实验内容

	1. 熟悉OpenGL，通过示例程序生成直线段；
	1. 使用OpenGL绘制点线等图元；

## 2、实验目的

 	1. 熟悉openGl中glut等函数库的调用，使用基本的函数，比如窗口设置、指定颜色背景、置点等函数的使用。
 	2. 通过两点画线法，指定顶点，实现直线段画图。

## 3、实验代码

- 头文件引用，在codeBlock编译器中首句应包含`#include<Windows.h>`文件

```c++
#include<Windows.h>
#include<GL/glut.h>
```

- 指定、清空背景颜色

  ```
  glClearColor (1.0, 1.0, 1.0, 0.0)
  ```

- 指定顶点，两点绘制直线

  ```c++
   glBegin (GL_LINES);
          glVertex2i (180, 15);       // 指定顶点
          glVertex2i (10, 145);
   glEnd ( );
  ```

- main主函数中，初始化GLUT，一般的主函数中需要包括的初始化操作

  ```c++
    glutInit (&argc, argv);                         // 初始 GLUT.
      glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
      glutInitWindowPosition (50, 100);   // 设定窗口位置
      glutInitWindowSize (400, 300);      // 设定窗口大小
      glutCreateWindow ("An Example OpenGL Program"); // 用前面指定参数创建窗口，并定义窗口名称
  ```



- 总的主程序代码如下：

  ```c++
  #include<Windows.h>
  #include <GL/glut.h>     
  
  void init (void)
  {
      glClearColor (1.0, 1.0, 1.0, 0.0);  // 指定清空颜色（背景色）为白色
      gluOrtho2D (0.0, 400.0, 0.0, 300.0);   //指定二维坐标系中被显示的区域
  }
  
  void display (void)
  {
      glClear (GL_COLOR_BUFFER_BIT);  // 清空显示窗口
      glColor3f (0.0, 0.0, 1.0);      // 指定前景色（当前绘制颜色）为蓝色
      glBegin (GL_LINES);
          glVertex2i (180, 15);       // 指定顶点
          glVertex2i (10, 145);
      glEnd ( );
      glFlush ( );     // 使绘制立即反映到屏幕上
  }
  
  void main (int argc, char** argv)
  {
      glutInit (&argc, argv);                         // 初始 GLUT.
      glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
      glutInitWindowPosition (50, 100);   // 设定窗口位置
      glutInitWindowSize (400, 300);      // 设定窗口大小
      glutCreateWindow ("An Example OpenGL Program"); // 用前面指定参数创建窗口，并定义窗口名称
      init ( );                            // 进行一些初始化工作
      glutDisplayFunc (display);       // 指定绘制的回调函数
      glutMainLoop ( );          // 进入无穷循环，等待事件处理
  }
  ```

  

- 运行结果

![image-20220527175332871](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527175332871.png)