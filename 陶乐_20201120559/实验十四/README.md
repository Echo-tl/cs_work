# 一、Z-buffer消隐算法

## 1、实验内容

1. 使用Z-Buffer算法绘制三维物体的的消隐图；
2. OpenGL库实现算法程序

## 2、实验原理

1. 排序

2. 连贯性

   - 创建两个缓存：帧缓存和深度缓存

   - 帧缓存记录每个单元像素存放的颜色值，深度缓存记录对应像素的深度值。

3. 以下程序使用线消隐法实现z-buffer算法。

```c++
    for (i = 0; i < 7; i++) //消隐的部分
    {
        if (f[i] == -1)
        {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(2, 0x3333);
            glBegin(GL_LINE_STRIP);
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);

            }
            glEnd(); glFlush();
            glDisable(GL_LINE_STIPPLE);
        }
        //可见的部分
        else
        {
            glBegin(GL_LINE_STRIP);
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);
            }
            glEnd(); glFlush();
        }
    }
```

## 3、编译结果

![work13](https://user-images.githubusercontent.com/86522948/174921143-45043cea-eba7-4c27-869a-e538a0d7b08b.png)