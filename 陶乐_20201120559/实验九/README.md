# 一、三维几何变换



## 1、实验内容

1. 通过三维变换矩阵，实现三维图像的平移、旋转、放大、缩小、对称等操作；

2. 使用OpenGL实现程序运行代码。

   

## 2、实验原理

1. 三维齐次坐标变换矩阵

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529185624456.png" alt="image-20220529185624456" style="zoom:67%;" />

2. 平移变换

   T~x~，T~y~，T~z~分别表示沿x轴、y轴、z轴平移：

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529182452515.png" alt="image-20220529182452515" style="zoom:33%;" />



3. 比例变换

   a，e，c分别表示放大或者缩小的因子

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529182729246.png" alt="image-20220529182729246" style="zoom:35%;" />



4. 整体比例变换：

   s>1表示整体放大，0<s<1表示整体缩小

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529182855430.png" alt="image-20220529182855430" style="zoom:35%;" />

   

5. 循环变换

   旋转方向设置：

   顺时针θ为负，逆时针θ为正：

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529182946328.png" alt="image-20220529182946328" style="zoom:30%;" />

   - 绕Z轴旋转

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183102690.png" alt="image-20220529183102690" style="zoom:45%;" />

     

   - 绕X轴旋转

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183128213.png" alt="image-20220529183128213" style="zoom:45%;" />

     

   - 绕Y轴旋转

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183149349.png" alt="image-20220529183149349" style="zoom:40%;" />

6. 对称变换

   关于坐标平面对称：

   - 关于XOY平面对称：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183431874.png" alt="image-20220529183431874" style="zoom:35%;" />

     

   - 关于XOZ平面对称：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183515649.png" alt="image-20220529183515649" style="zoom:31%;" />

     

   - 关于YOZ平面对称：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183455209.png" alt="image-20220529183455209" style="zoom:32%;" />

     同理关于坐标轴对称时，关于哪个坐标轴对称，哪一行对应的值1，其他轴为-1.

     

7. 错切变换

   - 沿x轴错切：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183820068.png" alt="image-20220529183820068" style="zoom:33%;" />

     

   - 沿y轴错切：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183831016.png" alt="image-20220529183831016" style="zoom:33%;" />

     

   - 沿z轴错切：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529183842925.png" alt="image-20220529183842925" style="zoom:33%;" />

     

   ### 3、实验代码

   1. 平移，放大、缩小\、旋转通过键盘输入按键控制：

      对于不规则的三维图形，可以直接调用OpenGL中的三维几何变换函数来实现，如下所示：

      ```c++
      switch (key)
      	{
      	case 'a': case 'A': glTranslated(0.1, 0, 0); break;     //向左平移0.1
      	case 'd': case 'D': glTranslated(-0.1, 0, 0); break;     //向右平移0.1
      	case 'w': case 'W': glTranslated(0, 0.1, 0); break;     //向上平移0.1
      	case 's': case 'S': glTranslated(0, -0.1, 0); break;     //向下平移0.1
      	case 'q': case 'Q': glTranslated(0, 0, 0.1); break;     //向外平移0.1
      	case 'e': case 'E': glTranslated(0, 0, -0.1); break;     //向里平移0.1
          case 'j': case 'J': glRotated(10, 0, 1, 0); break;      //绕y轴旋转20度
      	case 'l': case 'L': glRotated(20, 0, -1, 0); break;
      	case 'i': case 'I': glRotated(20, 1, 0, 0); break;      //绕x轴旋转45度
      	case 'k': case 'K': glRotated(45, -1, 0, 0); break;
      	case 'u': case 'U': glRotated(45, 0, 0, 1); break;      //绕z轴旋转45度
      	case 'o': case 'O': glRotated(45, 0, 0, -1); break;
      
      ```

      

   2. 完整代码如下：

      ```c++
      #include<GL/glu.h>
      #include<GL/glut.h>
      #include<stdio.h>
      #include<GL/glext.h>
      using namespace std;
      
      void init(void)
      {
      	glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色
      }
      
      void display(void)
      {
      	glClear(GL_COLOR_BUFFER_BIT);
      	glColor3f(1.0, 1.0, 1.0); //画笔白色
      
      	glLoadIdentity();  //加载单位矩阵
      
      	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
      	glutSolidOctahedron();
      	glutSwapBuffers();
      }
      
      void reshape(int w, int h)
      {
      	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
      	glMatrixMode(GL_PROJECTION);
      	glLoadIdentity();
      	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
      	glMatrixMode(GL_MODELVIEW);
      	glLoadIdentity();
      	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
      }
      
      void myKeyboard(unsigned char key, int x, int y)
      {
      	glMatrixMode(GL_MODELVIEW);
      	glMatrixMode(GL_PROJECTION);
      	switch (key)
      	{
      	case 'a': case 'A': glTranslated(0.1, 0, 0); break;     //向左平移0.1
      	case 'd': case 'D': glTranslated(-0.1, 0, 0); break;     //向右平移0.1
      	case 'w': case 'W': glTranslated(0, 0.1, 0); break;     //向上平移0.1
      	case 's': case 'S': glTranslated(0, -0.1, 0); break;     //向下平移0.1
      	case 'q': case 'Q': glTranslated(0, 0, 0.1); break;     //向外平移0.1
      	case 'e': case 'E': glTranslated(0, 0, -0.1); break;     //向里平移0.1
      
      	case 'j': case 'J': glRotated(20, 0, 1, 0); break;      //绕y轴旋转10度
      	case 'l': case 'L': glRotated(20, 0, -1, 0); break;
      	case 'i': case 'I': glRotated(45, 1, 0, 0); break;      //绕x轴旋转10度
      	case 'k': case 'K': glRotated(45, -1, 0, 0); break;
      	case 'u': case 'U': glRotated(45, 0, 0, 1); break;      //绕z轴旋转10度
      	case 'o': case 'O': glRotated(45, 0, 0, -1); break;
      
      	case 'z': case 'Z': glScalef(1.5, 1.5, 1.5); break;         //放大
      	case 'x': case 'X': glScalef(0.5, 0.5, 0.5); break;         //缩小
      
      	default: break;
      	}
      
      	glutPostRedisplay();      //重新绘制
      }
      
      void myDisplay(void)
      {
      	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      	glutWireIcosahedron();
      	//glTranslated(0, 0, 0);
      	glFlush();
      	glutSwapBuffers();      //显示刚才绘制的图像，双缓冲
      }
      
      int main(int argc, char** argv)
      {
      	glutInit(&argc, argv);
      	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      	glutInitWindowSize(500, 500);
      	glutInitWindowPosition(100, 100);
      	glutCreateWindow(argv[0]);
      	init();
      	glutDisplayFunc(display);
      	glutReshapeFunc(reshape);
      
      	glutKeyboardFunc(myKeyboard);
      	glutDisplayFunc(myDisplay);
      	glutMainLoop();
      	return 0;
      }
      ```

      

   3. 编译结果如下：

      - 平移

        <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529185246418.png" alt="image-20220529185246418" style="zoom:100%;" />

        

      - 放大和缩小：

        ![image-20220529185341837](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529185341837.png)

        ![image-20220529185407770](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529185407770.png)

        

      - 旋转：

        ![image-20220529185450587](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220529185450587.png)

        