# 一、茶壶旋转

## 1、实验内容

1. 使用OpenGL画茶壶并旋转；
2. 使用opengl库函数对3D图像的坐标位置进行定位，使用相关函数进行旋转。设置输入输出语句，配合scanf人机交互，由用户对旋转轴和角度进行指定。填充图定位在固定点，旋转线框图来进行对照。

## 2、实验原理

1. 调用gult函数库实现茶壶的绘制

   ```c++
   glutSolidTeapot(1.5);
   ```



2. 实现茶壶的缩放

   ```c++
   glScalef(1.0,1.0,1.0);//缩放比
   glTranslatef(-1.0,-5.0,0.0);//下一个图形坐标
   ```

   

3. 茶壶的旋转使用glut函数库

   ```c++
   glRotatef(thera,x,y,z);
   glutWireTeapot(1.5);
   ```





# 二、鼠标、键盘交互操作

## 1、实验内容

1. 熟悉OpenGL Glut中常用的回调函数；
2. 一个旋转的三角形，用空闲回调函数实现；

## 2、实验原理

1. 用鼠标回调函数实现:

   创建鼠标回调函数：

   ```c++
   void myMouse(int button, int state, int x, int y)
   {
      //按下鼠标左键
   	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   		theta += 5.0;
          FirstPoint=(x1,y1);
          SecondPoint=(x2,y2);
      //按下鼠标右键
   	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
   		theta -= 5.0;
     if (theta>360) theta -=360;
     if (theta<0) theta +=360;
     glutPostRedisplay(); //重新调用绘制函数
   }
   ```

   

2. 用键盘回调函数实现

   创建键盘回调函数：

   ```c++
   void myKeyboard(unsigned char key,  int x, int y)
   {
   	if(key == 'a' || key == 'A')
   		theta += 5.0;
   	if(key == 's' || key == 'S')
   		theta -= 5.0;
       if(key == 'c' || key == 'C')
   		exit(0);
   	if (theta>360) theta -=360;
   	if (theta<0) theta +=360;
   	glutPostRedisplay(); //重新调用绘制函数
   }
   ```

   