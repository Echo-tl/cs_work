# 一、圆的扫描转换—中点Bresenham画圆

## 1、实验内容

1. 理解掌握中点Bresenham画圆算法的原理；
2. 根据算法原理实现程序代码，生成圆。

## 2、实验原理

1. 构造函数F(x,y) = y^2^+ x^2^ - R^2^

   <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527192152052.png" alt="image-20220527192152052" style="zoom: 33%;" />

   

2. M点为中点，M(xi +1,yi-0.5)

   - 当F(xM,yM)<0时，取Pu(xi +1,yi)

   - 当F(xM,yM)>0时，取Pd(xi +1,yi-1）

   - 当F(xM,yM)=0时，约定取Pu。

     - [ ] 计算判别式：

     <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527194955073.png" alt="image-20220527194955073" style="zoom:67%;" />

     根据判别式d的值：

     - 当d≤0时，下一点取Pu(xi +1,yi)；

       <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527195048253.png" alt="image-20220527195048253" style="zoom:33%;" />

     - 当d>0时，下一点取Pd(xi +1,yi-1)。

       ​												<img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527195121304.png" alt="image-20220527195121304" style="zoom:33%;" />	

       - [ ] 判别式的初始值：d0 = 1.25 - R

       - [ ] 下一点的坐标值：x = x + 1；

         - y = y ,  d≤0

         - y = y - 1 ,  d >0

## 3、实验代码

1. 采用八分法画圆；首先划分四个象限，并在每个象限内按 y = x 将此象限划分为两个部分，每个部分调用画点函数。

```c++
//x0,y0是圆心坐标
void CirclePlot(int x0,int y0,int x,int y)
{
   //1
    setPixel((x0+x),(y0+y)); //y = x 的下方
    setPixel((x0+y),(y0+x)); //y = x 的上方

    //2
    setPixel((x0+x),(y0-y)); //y = -x 的下方
    setPixel((x0+y),(y0-x)); //y = -x 的上方

    //3
    setPixel((x0-x),(y0-y)); //y = x 的下方
    setPixel((x0-y),(y0-x)); //y = x 的上方

    //4
    setPixel((x0-x),(y0+y)); //y = -x 的下方
    setPixel((x0-y),(y0+x)); //y = -x 的上方

}
```



2. 构造函数，实现Bresenham画圆算法

   ```c++
   //中点画圆算法
   void Midpoint_circle(int x0,int y0,int r)
   {
       int x = 0;
       int y = r;
       int d = 1-r; //d初值
       CirclePlot(x0,y0,x,y);
   
       while(x<y){
           if(d<=0){
               d += 2*x +3; //y值不变
           }
           else{
               d += 2*(x-y)+5;
               y--;  // y = y-1
           }
           x++;
           CirclePlot(x0,y0,x,y); //画下一个点
       }
   }
   ```

   

3. 完整程序代码：

   ```c++
   #include<windows.h>
   #include<gl/glut.h>
   #include<gl/glu.h>
   #include<gl/gl.h>
   #include<iostream>
   #include<cmath>
   
   //画点
   void setPixel(int x,int y)
   {
       glColor3f(0.0,0.0,1.0);
       glPointSize(2.0f);
       glBegin(GL_POINTS);
           glVertex2f(x,y);
       glEnd();
       glFlush();
   }
   
   //x0,y0是圆心坐标
   void CirclePlot(int x0,int y0,int x,int y)
   {
      //1
       setPixel((x0+x),(y0+y));//y = x 的下方
       setPixel((x0+y),(y0+x)); //y = x 的上方
       
       //2
       setPixel((x0+x),(y0-y));
       setPixel((x0+y),(y0-x));
   
       //3
       setPixel((x0-x),(y0-y));
       setPixel((x0-y),(y0-x));
   
       //4
       setPixel((x0-x),(y0+y));
       setPixel((x0-y),(y0+x));
   
   }
   
   //中点画圆算法
   void Midpoint_circle(int x0,int y0,int r)
   {
       int x = 0;
       int y = r;
       int d = 1-r; //d初值
       CirclePlot(x0,y0,x,y);
   
       while(x<y){
           if(d<=0){
               d += 2*x +3;  //y值不变
           }
           else{
               d += 2*(x-y)+5;
               y--; // y = y-1
           }
           x++;
           CirclePlot(x0,y0,x,y); //画下一个点
       }
   }
   
   void changeSize(GLsizei w, GLsizei h)
   {
       if (h == 0){
               h = 1;
       }
       glViewport(0, 0, w, h);
   
       // 重置坐标系统
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
   
       // 建立修剪空间的范围
       if (w <= h)
           glOrtho(0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
       else
           glOrtho(0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);
   
   }
   
   void display(void)
   {
       glClear(GL_COLOR_BUFFER_BIT);
       int x0 = 100, y0 = 100, r = 80;
       Midpoint_circle(x0,y0,r);
   }
   
   int main(int argc,char* argv[])
   {
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
       glutInitWindowPosition(200,200);
       glutInitWindowSize(400,400);
       glutCreateWindow("midCircle");
       glutDisplayFunc(display);
       glutReshapeFunc(changeSize);
   
       glutMainLoop();
       return 0;
   }
   ```

   

4. 编译结果：

   ![image-20220527200722979](C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220527200722979.png)