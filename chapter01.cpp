#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>


using namespace cv;

Mat function() {

	// 创建一个500*500的图片
	Mat ima(500, 500, CV_8U, 50);
	
	return ima;
}

int main() {

	// 创建一个240*320的白色图片
	Mat image1(240, 320, CV_8U, 255);
	//也可以写成
	//Mat image1(240,320,CV_8U,cv::Scalar(255));


	// 重新分配一个新图像 
	// （仅在大小或类型不同时）
	image1.create(200, 200, CV_8U);
	image1 = 200;
	//namedWindow("Image 1"); 
	//namedWindow("Image 2"); 
	//namedWindow("Image 3"); 
	//namedWindow("Image 4"); 
	//namedWindow("Image 5"); 
	//namedWindow("Image");




	// 创建一个红色图像 
	// 通道次序是BGR
	Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));
	//也可写成
	// Mat image2(cv::Size(320,240),CV_8UC3);
	// image2= cv::Scalar(0,0,255);
	
	
	
	

	////读取图片
	Mat image3 = imread("lena.jpg");

	// 所有这些图像都指向同一个数据块
	Mat image4(image3);
	image1 = image3;

	// 这些图像是源图像的副本图像
	image3.copyTo(image2);
	Mat image5 = image3.clone();

	// 翻转
	flip(image3, image3, 1);

	//// 2，5不变，1，4随着3的翻转而改变
	//浅拷贝是指, 修改3对象的属性和方法会影响到1，4对象的属性和方法, 深拷贝是指, 修改3对象的属性和方法不会影响到2，5对象的属性和方法
	//imshow("Image 3", image3);
	//imshow("Image 1", image1);
	//imshow("Image 2", image2);
	//imshow("Image 4", image4);
	//imshow("Image 5", image5);

	

	// 调用函数
	Mat gray = function();

	// 灰度图
	image1 = imread("lena.jpg", 0);

	// 一个图像复制到另一个图像中，而两者的数据类型不一 定相同，那就要使用convertTo
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);
        
	Mat image = imread("lena.jpg");
	Mat logo = imread("logo.jpg");

	// 在图像的右下角定义一个ROI
	Mat imageROI(image,
		Rect(image.cols - logo.cols, //ROI坐标
		image.rows - logo.rows,
		logo.cols, logo.rows));// ROI大小


	logo.copyTo(imageROI);


	// imageROI= image(Range(image.rows-logo.rows,image.rows), 
	//                 Range(image.cols-logo.cols,image.cols));

	// 把标志作为掩码（必须是灰度图像）
	Mat mask(logo);

	// 插入标志，只复制掩码不为0的位置
	logo.copyTo(imageROI, mask);


	waitKey(0); // 等待按键
	return 0;
}

