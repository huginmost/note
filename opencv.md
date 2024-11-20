[TOC]
## 基本操作
### 读取 && 复制 && 写入
```c++
Mat src = cv::imread("../opencv.jpg", IMREAD_COLOR); // IMREAD_GREYSCALE
Mat cp = src.copy();
cv::imwrite("../opencv.jpg", src)
```

### 分离通道
```c++
std::vector<Mat> channels(3);
cv::split(this->src, channels);
cv::imshow("B", channels[0]);
cv::imshow("G", channels[1]);
cv::imshow("R", channels[2]);
// merge 合并
cv::merge(channels[0], channels[1], 0) // 合并BG图
```

### 取灰度图
```c++
cv::cvtColor(this->src, grayImg, COLOR_BGR2GRAY);
cv::imshow("gray", grayImg);
```

### ROI (取范围图)  
```c++
Mat crop = this->src(Range(10,170), Range(40, 200));
imshow("crop", crop);
```

### 边界填充
![2](screenshot/2.png)
![1](screenshot/1.png)
![3](screenshot/2.png)

### 数值计算
- `img2 = img1 + 10`
  矩阵的每一个元的值 + 10
- `img1 + img2` 前提：维度一致
  矩阵对应的元相加并 % 256
- `cv::add(img1, img2)`
  不会%256，相应最大值为255，不会越界

### 图像融合
- `img_cat + img_dog`
  `shape` 值不一样，报错
  - `img_cat.shape` : `(400, 500, 3)`
    指的是 图片高（行数）400; 高（列数）500; 颜色通道数为3.
  - 正确融合方式 (python)：
    ```python
    img_dog = cv2.resize(img_dog, (500, 414))
    res = cv2.addWeighted(img_cat, 0,4, img_dog, 0.6, 0)
    # 0.4 0.6 表示图片所占权重，0是偏移
    # 权重越大，融合所展示的越明显
    ```
  - `resize` 另一种
    `res = cv2.resize(img, (0, 0), fx = 3, fy = 1)`
    图像长变为原来的3倍，高不变（1倍）
  - **图像拼接**
    ```c++
    // 拼接膨胀和腐蚀结果
    cv::Mat hstack;
    cv::hconcat(dilated, eroded, hstack);  // 水平拼接
    ```
### 图像缩小与放大
```c++
cv::pyrUp(img, dst_up); //放大
cv::pyrDown(img, dst_down); //缩小
// 放大与缩小不可逆，对图像会造成一定的质量损失

lap = img - pyrDown(dst_up);
```
![15](screenshot/15.png)



### 图像绘制
```c++
line(drawn, Point(100, 200), Point(250, 250), Scalar(255, 0, 0), 2);
rectangle(drawn, Point(150, 250), Point(250, 300), Scalar(255, 255, 255), 2);
circle(drawn, Point(150, 300), 50, Scalar(100, 100, 0), 2);
putText(drawn, "text", Point(200, 250), 0, 0.5f, rgb(0, 0xFF, 0xFF), 2, cv::LINE_8);
imshow("drawn", drawn);
```

### 图像腐蚀 && 膨胀
```c++
Mat kernel = getStructuringElement(MORPH_RECT, Size2f(5.5, 5.5));
Mat dstImage;

cv::erode(this->src, dstImage, kernel);
cv::erode(dstImage, dstImage, kernel);
imshow("erode", dstImage);

cv::dilate(this->src, dstImage, kernel);
cv::dilate(dstImage, dstImage, kernel);
imshow("dilation", dstImage);
```
![4](screenshot/4.png)

## 基本算法
### 开闭运算 && 梯度运算 && 礼帽黑帽

```c++
Mat kernel = getStructuringElement(MORPH_RECT, Size2f(5.5, 5.5));
// 开：先腐蚀，再膨胀
Mat open;
cv::morphologyEx(img, open, MORPH_OPEN, kernel);
// 闭：先膨胀，再腐蚀
Mat closing;
cv::morphologyEx(img, open, MORPH_CLOSE, kernel);
```
--- 
```c++
// 梯度运算（膨胀减去腐蚀）
cv::Mat gradient;
cv::morphologyEx(img, gradient, open, MORPH_GRADIENT, kernel);
```
![5](screenshot/5.png)

---
```c++
// 礼帽：原始输入 - 开运算结果
cv::Mat tophat;
cv::morphologyEx(img, gradient, open, MORPH_TOPHAT, kernel);
// 黑帽：闭运算 - 原始输入
cv::Mat blackhat;
cv::morphologyEx(img, gradient, open, MORPH_BLACKHAT, kernel);
```

### Sobel 算子
![6](screenshot/6.png)
![7](screenshot/7.png)
![8](screenshot/8.png)
![9](screenshot/9.png)

### schaar && lapkacian 算子
![10](screenshot/10.png)

## OpenCV 常用模块解读
### threshold
```c++
	// 图片灰度二值化
	void threshold() {
		Mat gray, binary, binary_adaptive, binary_otsu;
		cvtColor(src, gray, COLOR_BGR2GRAY);

		// 普通二值化
		cv::threshold(gray, binary, 10, 255, THRESH_BINARY);
		// 大津算法（基于图片灰度聚类分析，自定义阈值）
		cv::threshold(gray, binary_otsu, 0, 255, THRESH_BINARY + THRESH_OTSU);
		// 图片自适应二值化（划分区块二值化，效果更好） ADAPTIVE_THRESH_GAUSSIAN_C 高斯算法
		cv::adaptiveThreshold(gray, binary_adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 115, 1);

		imshow("gray", gray);
		imshow("binary", binary);
		imshow("adaptive", binary_adaptive);
		imshow("otsu", binary_otsu);
	}

```
![13](screenshot/13.png)
![12](screenshot/12.png)


### 图像平滑处理 - 滤波
```c++
// 均值滤波 简单的平均卷积操作
cv::blur(img, blur, Size(3, 3));

// 方框滤波 可以选择归一化，容易越界
cv::boxFilter(img, box, -1, Size(3, 3), normalize = true)
// 未归一化的情况：简单地将窗口内所有像素的值加起来，然后除以窗口大小（即 k*k）。
// 归一化的情况：除了计算平均值，还会对结果进行缩放，使得图像的亮度保持一致。

// 高斯滤波 离得越近，权重越大 高斯模糊的卷积核里的数值满足高斯分布
cv::GaussianBlur(img, aussian, Size(5, 5), 1)
// sigmaX: X 方向上的标准差，控制高斯分布的宽度，决定了图像的模糊程度。
// sigmaY: Y 方向上的标准差，默认值为 0。如果设置为 0，它会与 sigmaX 相同。如果你需要不同的模糊程度，可以设置不同的 sigmaX 和 sigmaY。
// borderType: 边界处理方式，指定图像边缘如何处理。常用的有 cv::BORDER_REFLECT，cv::BORDER_CONSTANT，cv::BORDER_REPLICATE 等。

// 中值滤波 相当于用中值代替 去噪音点效果最佳
cv::medianBlur(img, median, 5)
```

### Canny
- Canny 原理 `1)-4)`
  ![canny](screenshot/canny.png)
  ![canny-2](screenshot/canny-2.png)
- 方向运算用到了Sobel
  ![canny-3](screenshot/canny-3.png)
- 非极大值抑制
  ![canny-4](screenshot/canny-4.png)
  `c` 若比 `dtmp1` 和 `dtmp2` 都大，则保留
  ![canny-5](screenshot/canny-5.png)
  `A` 若比 `C` 和 `B` 都大，则保留
- 双阈值检测
  ![canny-6](screenshot/canny-6.png)
- Canny 最终效果:
  ![canny-7](screenshot/canny-7.png)
  注：Canny 后两个参数对应的则是`阈值`的`max`与`min`

### 轮廓检测 与 特征 与 近似
![14](screenshot/14.png)
![16](screenshot/16.png)
- 轮廓索引为 `-1` 时绘制为全部轮廓

**特征与近似**
![17](screenshot/17.png)
![18](screenshot/18.png)
![19-3](screenshot/19-3.png)
![19-1](screenshot/19-1.png)
![19-2](screenshot/19-2.png)

**边界矩形**
![20-1](screenshot/20-1.png)
![20-2](screenshot/20-2.png)
![20-3](screenshot/20-3.png)