# 一、计算机图形学实验期末报告



### 题目：OpenGL实现对茶壶渲染

### 摘要：

使用OpenGL工具库，对三维图像渲染，本次实验包括了对茶壶三维图像的添加纹理，色彩以及光照、阴影等效果。并采用了光线跟踪、光照明模型等算法的使用。在codeBlocks环境下，实现茶壶的三维模型模拟的真实感。

### 关键字：openGL 光照 纹理 茶壶



## 1、实验背景

1. 三维纹理贴图绘制技术是一项重要的图形学技术，并且应用范围广，涉及到各个领域。真实感图形显示是计算机图像学的一个重要的研究方向，这涉及**几何造型**、**图像消隐**、**光线明暗处理**、**光线跟踪**、**颜色空间**、**纹理映射**等诸多方面。三维场景中的物体在没有光照度情况下。看起来没有立体感，因此增加三维图形的真实感效果非常必要。

2. 在追求更具真实感图像方面，关于在其的光栅图像合成的最多的批判就是极度光滑的表面，没有纹理、凹凸、划痕、灰尘。纹理映射技术是一个产生复杂表面的相对有效的手段。自从70年年代中期Catmull首次采用纹理映射技术设生成景物表面的纹理细节以来，纹理映射技术得到了广泛的研究和应用。

3. 传统的纹理映射技术一般用于增加计算机生成图像的真实感，在近几年，这项技术的主要研究领域以及从软件的绘制系统转向高效的图像硬件领域。正因为纹理映射的如此作用，所以它被作为图形软件接口和计算机图像硬件的标准的成像技术。总之，纹理映射技术是近年来发展最快的3D技术，其真实感也更加高效。

4. 真实感图形技术一直是计算机图形学研究的前沿领域。纹理映射技术是OpenGL的一个重要的技术，在教学模型转换和投影转换都能执行该操作。一般根据纹理的表现形式可以分为颜色纹理、几何纹理和过程纹理。

5. 基于OpenGL的纹理映射主要包括几个步骤：

   - 指定纹理
   - 指定纹理应用方式
   - 激活纹理绘制
   - 指定纹理坐标和景物的集合坐标，绘制场景。

6. 纹理通常为二维的，OpenGL定义二维纹理的函数是**glTexImage2D()**。

   ​																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																

## 2、实验内容

1. 利用codeblocks，OpenGL，c++等工具，实现三维图形渲染，实现三维图像如茶壶的渲染，渲染过程须加入纹理、色彩、光照、阴影、透明等效果，可采用光线跟踪、光照明模型、纹理贴图、纹理映射等算法。



## 3、程序设计及基本模块介绍

1. 本次实验主要基于OpenGL三维图形软件包，并利用c++程序语言，在codeBlocks平台实现茶壶的光照与纹理贴图。

2. 程序设计的主要模块主要分为以下几个部分：

- 光照

  - OpenGL环境下可知设置至少八光源，在设置光照时有三种光：环境反射光、镜面反射光、漫反射光照模型。在openGL中，使用光源可用如下代码：

    ```c++
      glEnable( GL_LIGHTING );  // 开启光照模式
    ```

  - 在本次实验中，使用了三个光源从茶壶的右上方、左侧、左下方进行照射，并采用点光源的形式:

    ```c++
    glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);//设置第0号光源的光照位置
    ```

  

- 读取纹理图片

  - 利用C标准库中的fopen函数，加载pmg图像，已RGB形式存储

    ```c
    filePtr = fopen( filename , "rb" );
    ```

    

- 加载纹理

  - 加载纹理的形式主要为二维图像纹理，并利用GL库函数下进行纹理的加载：

    ```c++
    glBindTexture(GL_TEXTURE_2D, texture);
    ```

    

- 纹理贴图

  - 将加载好的纹理进行纹理贴图，只要把纹理与茶壶结合，并利用gl库函数实现：

    ```c++
    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[index]); //选择纹理texture[index]
         ……
    glDisable(GL_TEXTURE_2D);//关闭纹理texture[index]
    ```

    

- 通过键盘的交互控制茶壶旋转功能

  - 通过定义键盘中断特殊键 **'+' **和 **'-'** 等实现茶壶顺时针及逆时针旋转功能。

- 定义display函数以及reshape函数实现功能，并在main主函数中调用display（）和reshape()函数。



## 4、关键算法的理论介绍

1. 光照

   - OpenGL下设置光照时，需要开启光照模式，对于一个光源，我们首先需要确定它的位置，这个光源可以是点光源，也可以是平行光源，本次实验使用的是点光源，并采用红、绿、蓝三种颜色的点光照：

   ```c++
   glEnable(GL_LIGHT1);//开启光照模式
   GLfloat light1_ambient[]={0.0,1,0.0,0.0};
   GLfloat light1_diffuse[]={0.0,1,0.0,0.0};
   GLfloat light1_specular[]={0.0,1,0.0,0.0};
   GLfloat light1_position[] = {-1.0,0.0,0.0,0.0};
   glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);//设置0号光源的光照位置
   glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
   glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
   glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
   ```

   

2. 定义纹理：

   - 通常将纹理定义到数组中，此数组可以表达网格上的纹理值，并通过坐标变换，将纹理映射到模型上

     ```c++
     GLuint filter;         // 滤波类型
     GLuint texture[3];     // 3种纹理的储存空间
     ```

     ```c++
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //纹理映射函数
     ```

     - 设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理；

     - 第二个参数为纹理指定多级渐远纹理的级别，这里我们填0，表示基本级别；

     - 纹理储存为何种格式，应把把纹理储存为`RGB`值

     - 第四个和第五个参数设置最终的纹理的宽度和高度

     - 最后一个参数是真正的图像数据

       

3. 滤波：

   - 通常情况下纹理图像是长方形，但现实世界的景物不可能是长方形，比如茶壶，当把纹理映射到这些不规则的图像上时，当需要放大滤波时，将单独的某个像素点对应上纹理中的多个元素，当需要减小滤波时，则对应纹理中非常多元素。

     ```c++
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//放大滤波
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//缩小滤波
     ```

     

4. 生成纹理：

   - OpenGL纹理映射中，可以利用**glGenTextures**函数生成纹理的数量，并利用 `glBindTexture(GL_TEXTURE_2D, texture)` 函数让之后的纹理指令都可以配置当前绑定的纹理。

   

## 5、程序实现步骤

<img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220620203128480.png" alt="image-20220620203128480" style="zoom:80%;" />



## 6、源代码

1. 程序如下：

   ```c++
   #include <windows.h>
   #ifdef __APPLE__
   #include <GLUT/glut.h>
   #else
   #include <GL/glut.h>
   #endif
   
   #include <stdlib.h>
   #include<GL/glext.h>
   
   #include <stdio.h>
   #include<math.h>
   #include<stdlib.h>
   
   #include "GL\gl.h"
   #include "GL\glu.h"
   #include "GL\glaux.h"
   #include "GL\glut.h"
   
   double angle = 0.0;
   
   GLdouble size;
   
   GLuint texture;     //种纹理的储存空间
   
   void init(void)
   {
   	glClearColor(0.0,0.0,0.0,0.0);
   	glShadeModel(GL_SMOOTH);
   	glEnable(GL_LIGHTING);
   
   	glEnable(GL_LIGHT0);
   	GLfloat light0_ambient[]={1,0.0,0.0,0.0}; //定义光照
   	GLfloat light0_diffuse[]={1,0.0,0.0,0.0};
   	GLfloat light0_specular[]={1,0.0,0.0,0.0};
   	GLfloat light0_position[] = {2.0,2.0,2.0,0.0};//(x 为正是右 y为正是上 z为正是前)
   	glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient); //光照0
   	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
   	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);
   	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
   
   	glEnable(GL_LIGHT1);
   	GLfloat light1_ambient[]={0.0,1,0.0,0.0};
   	GLfloat light1_diffuse[]={0.0,1,0.0,0.0};
   	GLfloat light1_specular[]={0.0,1,0.0,0.0};
   	GLfloat light1_position[] = {-1.0,0.0,0.0,0.0};
   	glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient); //光源1
   	glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
   	glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
   	glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
   
   	glEnable(GL_LIGHT2);
   	GLfloat light2_ambient[]={0.0,0.0,1,0.0}; //光源2
   	GLfloat light2_diffuse[]={0.0,0.0,1,0.0};
   	GLfloat light2_specular[]={0.0,0.0,1,0.0};
   	GLfloat light2_position[] = {-1.0,-1.0,1.0,0.0};
   	glLightfv(GL_LIGHT2,GL_AMBIENT,light2_ambient);
   	glLightfv(GL_LIGHT2,GL_DIFFUSE,light2_diffuse);
   	glLightfv(GL_LIGHT2,GL_SPECULAR,light2_specular);
   	glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
   
   	glEnable(GL_DEPTH_TEST);
   	glTranslatef(1.5,1.5,0);
   }
   
   //导入图片的函数
   LoadTexture(const char * filename, int width, int height)
   {
   
   	GLuint texture;
   	unsigned char * data;
   	FILE * file;
   
   	//读文件
   	file = fopen(filename, "rb");
   	if (file == NULL) return 0;
   
   	data = (unsigned char *)malloc(width * height * 3);
   	fread(data, width * height * 3, 1, file);
   	fclose(file);
   
   	glGenTextures(1, &texture);
   	glBindTexture(GL_TEXTURE_2D, texture);
   	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   
   
   	//线性滤图
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
   
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
   	//生成纹理
   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   	free(data); //释放纹理
   	return texture;
   
   }
   
   //定义个设置背景的函数
   void Background()
   {
       //导入纹理
   	texture = LoadTexture("D:\codeblocks_workplace\teapot_final\teapot_final\photo1.bmp", 640, 640);
   	glBindTexture(GL_TEXTURE_2D, texture); //位置
   
   	glBegin(GL_QUADS);
   	glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
   	glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
   	glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
   	glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
   	glEnd();
   
   }
   
   static void resize(int width, int height)
   {
       //指定视口
       glViewport(0, 0, width, height);
   
       //投影变换---平截头体
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(40.0,(GLdouble)width/(GLdouble)height,0.1,10000.0);
   
   }
   
   
   static void display(void)
   {
       glPushMatrix();
   	glutSolidTeapot(size);
   	glPopMatrix();
   
   
       //视图变换，指定相机
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(0.0,0.0,5.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
   
       //模型变换
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
       glColor3f(1.0,0.0,0.0);
   
       glPushMatrix();
       glRotatef(angle,0.0,1.0,0.0);
       glutSolidTeapot(1.0);
       glPopMatrix();
   
       glDisable(GL_DEPTH_TEST);
   	glLoadIdentity();
   
   	    //导入纹理
   	texture = LoadTexture("D:\codeblocks_workplace\teapot_final\teapot_final\photo1.bmp", 640, 640);
   
   	glEnable(GL_TEXTURE_2D);
   
   	glPushMatrix();
   		glScalef(100, 70, 1);
   		glTranslatef(0, 0, -150);
   		Background();					//背景方块
   	glPopMatrix();
   
       glutSwapBuffers();
   
   }
   
   
   static void key(unsigned char key, int x, int y)
   {
       switch (key)
       {
       case 27 :
       case 'q':
           exit(0);
           break;
   
       case '+':
           angle++; //旋转
           break;
   
       case '-':
           angle--;
           break;
       }
   
       glutPostRedisplay();
   }
   
   
   /* Program entry point */
   int main(int argc, char *argv[])
   {
       glutInit(&argc, argv);
       glutInitWindowSize(640,480);
       glutInitWindowPosition(10,10);
       glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   
       glutCreateWindow("GLUT Shapes");
   
       init();
   
       glutReshapeFunc(resize);//主函数调用，窗口显示
       glutDisplayFunc(display);
       glutKeyboardFunc(key);
   
       glutMainLoop();
   
       return EXIT_SUCCESS;
   }
   
   ```

   

2. 运行结果：
![teapot_final1](https://user-images.githubusercontent.com/86522948/174919219-58b169a5-b393-48dd-8fda-0b36e117a7ee.png)

![teapot_final2](https://user-images.githubusercontent.com/86522948/174919237-7a9e9cff-140d-4a0b-b88d-144ab1a40e12.png)



## 7、 实验体会与总结

1. 本次实验中我们通过对茶壶的简单真实感图像处理，对一般的茶壶进行简单的三维旋转、光照处理、纹理映射等处理，对不规则的图形进行渲染，使其呈现出简单三维效果。通过键盘实现对茶壶的旋转，用到了三维物体的几何变换部分；通过设置点光源实现对茶壶的不同方向的光照处理，通过直接调用openGl中的函数可以直接实现对光照度处理，并且可以使用不同颜色的光照射；在纹理映射时，我认为是最困难的部分，在实验中，对于不规则的三维图像，在纹理映射时，需要设置纹理的坐标，并将其存储为 `RGB` 格式，在调用滤波函数，以及纹理映射函数。

2. 在实验中，对光照以及纹理的处理中，只需要调用OpenGL的函数便可实现，但是在具体代码实现时，总是会报各种错误，比如添加纹理、打开文件等情况，并且需要引入 `glaux` 函数库，有时映射函数的问题，就导致运行窗口没有结果如下：

![teapot_final3](https://user-images.githubusercontent.com/86522948/174919252-c32cc217-6913-42dd-be1d-dc97f9229b59.png)

   

3. 总之，通过本次实验让我了解到三维图像的真实感处理其实是非常复杂的，虽然我们处理的只是茶壶这一简单的三维图像，而在现实中有各种各样不规则的图像，而纹理映射、纹理贴图的方式各种各样，对应于OpenGL总有各种的算法，我们目前所学到的OpenGL图形学处理的算法只是很小的一部分，所以我们需要学习的OpenGL的算法还有很多，技术也会更加复杂。如何在已有的算法基础上，不断提高改进也是亟待解决的问题。