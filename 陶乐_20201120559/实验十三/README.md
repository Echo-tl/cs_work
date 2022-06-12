# 一、多面体

## 1、实验内容

1. 本次实验采用了OpenGL库函数下的多面体图形的生成

2. 包括一些规则的多面体和一些不规则的多面体；

3. 使用gl包下的函数，例如：

   ```c++
       glScalef(1.5,2.0,1.0);
       glutWireCube(1.0); //调用gl下函数生成立方体
   ```

   

# 二、二次曲面

## 1、实验内容

1. 使用openGL下二次曲面的生成；

2. 球体：

   ```c++
     	glPushMatrix( );
   	glTranslatef(1.0,1.0,0.0);
       glutWireSphere(0.75,8,6); 
       glPopMatrix( );
   ```

   

3. 锥体：

   ```c++
       glPushMatrix( );
       glTranslatef(1.0,-0.5,0.5);
       glutWireCone(0.7,2.0,7,6);
       glPopMatrix( );
   ```
    

4. 圆柱体：

   ```c++
       cylinder = gluNewQuadric( );
       gluQuadricDrawStyle(cylinder,GLU_LINE);
       gluCylinder(cylinder,0.6,0.6,1.5,6,4);
       glPopMatrix( );
   ```

   