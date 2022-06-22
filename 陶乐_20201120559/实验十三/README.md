# 一、Bezier算法生成曲线

## 1、实验内容

1. 使用Bezier算法实现生成二维三次样条曲线的Bezier混合函数的计算；
2. 使用OpenGL函数库实现程序；

## 2、实验原理

1. 实验步骤：

   - 首先根据Bezier算法的原理，在xy平面上定义四个控制点，使用宽度为4的像素绘制沿曲线路径的1000个像素点。

   - 二项式系数的值用过程BinomialCoeffs计算，而沿曲线路径的坐标位置在过程computeBezPt函数中计算。

   - 将计算的值传给Bezier函数，并调用OpenGL画点函数绘制出这些像素位置。

     

2. 计算二项式系数值

   ```c++
   void binomialCoeffs(GLint n, GLint * c)
   {
       GLint k,j;
       for(k = 0; k<=n; k++){
           c[k] = 1;
           for(j = n; j>=k+1; j--)
               c[k] *= j;
           for(j = n-k; j>=2; j--)
               c[k] /= j;
       }
   }
   ```

   

3. 计算像素坐标位置

   ```c++
   void computeBezPt(GLfloat u, wcPt3D * bezPt, GLint nCtrlPts, wcPt3D * ctrlPts, GLint * c)
   {
       GLint k,n = nCtrlPts -1;
       GLfloat bezBlendFcn;
   
       bezPt->x = bezPt->y = bezPt->z = 0.0;
   
       for(k = 0; k<nCtrlPts; k++){
           bezBlendFcn  = c[k] * pow(u,k) *pow(1-u,n-k);
           bezPt->x += ctrlPts [k].x * bezBlendFcn;
           bezPt->y += ctrlPts [k].y * bezBlendFcn;
           bezPt->z += ctrlPts [k].z * bezBlendFcn;
       }
   
   }
   ```



## 3、实验运行结果

1. 编译结果

![work14](https://user-images.githubusercontent.com/86522948/174920844-737b0edf-23eb-4197-b217-b05793698fed.png)