# 一、三维观察

## 1、实验内容

1. 掌握OpenGL中的正交投影和透视投影;
2. 使用OpenGL实现正方形的透视投影；
3. 实现金字塔的三维观察代码演示。

## 2、实验原理

1. 正方形在平面xy平面上定义，观察坐标系按原点按观察前平面选定，选择正方形的中心为注视点，使用glFrustum函数得到一个透视图。

2. glFrustum（xwmin, xwamx, ywmin,ywamx，dnear, dfar)函数是openGL通用的透视投影函数，前四个参数设定平面上的裁剪窗口坐标，后两个参数指定坐标原点沿负z轴到近和远裁剪平面的距离。

   

3. 设置窗口大小位置，调用透视投影函数，使用

   ```c++
   void init(void)
   {
       glClearColor(1.0,1.0,1.0,0.0);
       glMatrixMode(GL_MODELVIEW); 
       gluLookAt(x0,y0,z0,xref,yref,zref,Vx,Vy,Vz);
       glMatrixMode(GL_PROJECTION); //声明下一步要做的是透视投影
       glFrustum(xwmin,xwmax,ywmin,ywmax,dnear,dfar);//调用透视投影函数
   
   }
   ```



## 3、程序运行结果

<img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220608100032370.png" alt="image-20220608100032370" style="zoom: 67%;" />

# 一、三维观察

## 1、实验内容

1. 掌握OpenGL中的正交投影和透视投影;
2. 使用OpenGL实现正方形的透视投影；
3. 实现金字塔的三维观察代码演示。

## 2、实验原理

1. 正方形在平面xy平面上定义，观察坐标系按原点按观察前平面选定，选择正方形的中心为注视点，使用glFrustum函数得到一个透视图。

2. glFrustum（xwmin, xwamx, ywmin,ywamx，dnear, dfar)函数是openGL通用的透视投影函数，前四个参数设定平面上的裁剪窗口坐标，后两个参数指定坐标原点沿负z轴到近和远裁剪平面的距离。

   

3. 设置窗口大小位置，调用透视投影函数，使用

   ```c++
   void init(void)
   {
       glClearColor(1.0,1.0,1.0,0.0);
       glMatrixMode(GL_MODELVIEW); 
       gluLookAt(x0,y0,z0,xref,yref,zref,Vx,Vy,Vz);
       glMatrixMode(GL_PROJECTION); //声明下一步要做的是透视投影
       glFrustum(xwmin,xwmax,ywmin,ywmax,dnear,dfar);//调用透视投影函数
   
   }
   ```



## 3、程序运行结果

<img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220608100032370.png" alt="image-20220608100032370" style="zoom: 67%;" />



# 二、金字塔的投影变化

## 1、实验内容

1. 变reshape函数中的投影函数及相关参数，体会OpenGL中投影变换的设置；

## 2、实验原理

1. reshape（）函数调用

   ```c++
   void reshape(int w, int h) //重绘回调函数，在窗口首次创建或用户改变窗口尺寸时被调用
   ```

2. 生成一个金字塔，通过键盘控制旋转的角度，当使用者按下对应按键时，对应金字塔的不同角度投影颜色。