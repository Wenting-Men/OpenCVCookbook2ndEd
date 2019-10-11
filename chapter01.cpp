#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>


using namespace cv;

Mat function() {

	// ����һ��500*500��ͼƬ
	Mat ima(500, 500, CV_8U, 50);
	
	return ima;
}

int main() {

	// ����һ��240*320�İ�ɫͼƬ
	Mat image1(240, 320, CV_8U, 255);
	//Ҳ����д��
	//Mat image1(240,320,CV_8U,cv::Scalar(255));


	// ���·���һ����ͼ�� 
	// �����ڴ�С�����Ͳ�ͬʱ��
	image1.create(200, 200, CV_8U);
	image1 = 200;
	//namedWindow("Image 1"); 
	//namedWindow("Image 2"); 
	//namedWindow("Image 3"); 
	//namedWindow("Image 4"); 
	//namedWindow("Image 5"); 
	//namedWindow("Image");




	// ����һ����ɫͼ�� 
	// ͨ��������BGR
	Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));
	//Ҳ��д��
	// Mat image2(cv::Size(320,240),CV_8UC3);
	// image2= cv::Scalar(0,0,255);
	
	
	
	

	////��ȡͼƬ
	Mat image3 = imread("C:\\Users\\Crystal008\\Desktop\\lena.jpg");

	// ������Щͼ��ָ��ͬһ�����ݿ�
	Mat image4(image3);
	image1 = image3;

	// ��Щͼ����Դͼ��ĸ���ͼ��
	image3.copyTo(image2);
	Mat image5 = image3.clone();

	// ��ת
	flip(image3, image3, 1);

	//// 2��5���䣬1��4����3�ķ�ת���ı�
	//ǳ������ָ, �޸�3��������Ժͷ�����Ӱ�쵽1��4��������Ժͷ���, �����ָ, �޸�3��������Ժͷ�������Ӱ�쵽2��5��������Ժͷ���
	//imshow("Image 3", image3);
	//imshow("Image 1", image1);
	//imshow("Image 2", image2);
	//imshow("Image 4", image4);
	//imshow("Image 5", image5);

	

	// ���ú���
	Mat gray = function();

	// �Ҷ�ͼ
	image1 = imread("C:\\Users\\Crystal008\\Desktop\\lena.jpg", 0);

	// һ��ͼ���Ƶ���һ��ͼ���У������ߵ��������Ͳ�һ ����ͬ���Ǿ�Ҫʹ��convertTo
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);


	waitKey(0); // �ȴ�����
	return 0;
}

