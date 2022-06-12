# 一、边界填充算法—种子扫描算法

## 1、实验内容

1. 分别利用边界填充算法，使用栈结构实现4-连通边界填充算法和8-连通边界填充算法。
2. 使用OpenGL库函数实验程序代码

## 2、实验原理

1. 4-邻接点

   ​           <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220528165547610.png" alt="image-20220528165547610" style="zoom:50%;" /> 

2. 8-邻接点

​	 		        <img src="C:\Users\h\AppData\Roaming\Typora\typora-user-images\image-20220528165455951.png" alt="image-20220528165455951" style="zoom:50%;" />

3. 算法步骤

   - 种子象素入栈，当栈非空时：

   - 栈顶象素出栈；

   - 出栈象素置成填充色；

   - 若为4-连通区域：

     - 检查出栈象素的4-邻接点，若其中某个象素点不是边界点且未填色，则把该象素入栈，重复以上操作。

   - 若为八连通区域：

     - 检查出栈象素的8-邻接点，若其中某个象素点不是边界点且未填色，则把该象素入栈，重复以上操作。

       

4. 4-连通区域表示方法

   ```c++
   //四连通
   void boundaryFill4(int x, int y, Color fillColor, Color boarderColor) {
       Color interiorColor;
       getpixel(x, y, interiorColor);//获取当前该点颜色
       if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
           setpixel(x, y); 
           //对上下左右四个点像素进行递归填色
           boundaryFill4(x + 1, y, fillColor, boarderColor);
           boundaryFill4(x - 1, y, fillColor, boarderColor);
           boundaryFill4(x, y + 1, fillColor, boarderColor);
           boundaryFill4(x, y - 1, fillColor, boarderColor);
       }
   }
   ```

   

5. 8-连通区域表示方法

   ```c++
   //八连通
   void boundaryFill8(int x, int y, Color fillColor, Color boarderColor) {
       Color interiorColor, a, b, c, d;
       getpixel(x, y, interiorColor);
       getpixel(x + 1, y - 1, a);
       getpixel(x, y - 1, b);
       getpixel(x, y + 1, c);
       getpixel(x - 1, y, d);
       int i = 0;
       if (compareColor(a, boarderColor) == 1) i++;
       if (compareColor(b, boarderColor) == 1) i++;
       if (compareColor(c, boarderColor) == 1) i++;
       if (compareColor(d, boarderColor) == 1) i++;
       if (i <= 1) {
           if (compareColor(interiorColor, fillColor) == 0 && compareColor(interiorColor, boarderColor) == 0) {
               setpixel(x, y);
               //八邻接像素点填色
               boundaryFill8(x + 1, y, fillColor, boarderColor);
               boundaryFill8(x, y - 1, fillColor, boarderColor);
               boundaryFill8(x - 1, y, fillColor, boarderColor);
               boundaryFill8(x, y + 1, fillColor, boarderColor);
               boundaryFill8(x + 1, y - 1, fillColor, boarderColor);
               boundaryFill8(x - 1, y - 1, fillColor, boarderColor);
               boundaryFill8(x - 1, y + 1, fillColor, boarderColor);
               boundaryFill8(x + 1, y + 1, fillColor, boarderColor);
   
           }
       }
   }
   ```

