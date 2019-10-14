#include "stdafx.h"
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>


using namespace cv;
using namespace std;



// Test 0
// using .ptr and []
void colorReduce0(Mat image, int div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量

	for (int j = 0; j < nl; j++) {

		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			data[i] = data[i] / div*div + div / 2;

			//像素处理结束 ----------------

		}  
	}
}

// Test 1
// using .ptr and * ++
void colorReduce1(Mat image, int div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			//利用指针运算从一列移到下一列

			*data = *data / div*div + div / 2;
			data++;

			//像素处理结束 ----------------

		}  
	}
}

// Test 2
// using .ptr and * ++ and modulo
void colorReduce2(Mat image, int div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			int v = *data;
			*data++ = v - v%div + div / 2;
			//                 *data++= *data - *data%div + div/2;

			//像素处理结束 ----------------

		}  
	}
}

// Test 3
// using .ptr and * ++ and bitwise
void colorReduce3(Mat image, uchar div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = div >> 1;

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			*data &= mask;     // masking
			*data++ += div2;   // add div/2

			//像素处理结束 ----------------

		}  
	}
}


// Test 4
// direct pointer arithmetic
void colorReduce4(Mat image, int div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	int step = image.step; // effective width
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	// get the pointer to the image buffer
	uchar *data = image.data;

	for (int j = 0; j < nl; j++) {

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			*(data + i) &= mask;
			*(data + i) += div >> 1;

			//像素处理结束 ----------------

		}  

		data += step;  // next line
	}
}

// Test 5
// using .ptr and * ++ and bitwise with image.cols * image.channels()
void colorReduce5(Mat image, int div = 64) {

	int nl = image.rows; 
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < image.cols * image.channels(); i++) {

			// 处理每个像素 ---------------------

			*data &= mask;
			*data++ += div >> 1;

			//像素处理结束 ----------------

		}  
	}
}

// Test 6
// using .ptr and * ++ and bitwise (continuous)
void colorReduce6(Mat image, int div = 64) {

	int nl = image.rows; 
	int nc = image.cols * image.channels(); // 每行的元素数量

	if (image.isContinuous())  {
		//   没有填充的像素
	
		nc = nc*nl;
		nl = 1;  
	}

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			*data &= mask;
			*data++ += div >> 1;

			//像素处理结束 ----------------

		}  
	}
}

// Test 7
// using .ptr and * ++ and bitwise (continuous+reshape)
void colorReduce7(Mat image, int div = 64) {

	if (image.isContinuous()) {
		// no padded pixels
		image.reshape(1,   // new number of channels
			1); // new number of rows
	}
	// number of columns set accordingly

	int nl = image.rows; 
	int nc = image.cols*image.channels(); // 每行的元素数量

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			*data &= mask;
			*data++ += div >> 1;

			//像素处理结束 ----------------

		}  
	}
}

// Test 8
// using Mat_ iterator
void colorReduce8(Mat image, int div = 64) {

	// get iterators
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();

	for (; it != itend; ++it) {

		// 处理每个像素 ---------------------

		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;

		//像素处理结束 ----------------
	}
}

// Test 8b
// using Mat_ iterator and Vec3b operator
void colorReduce8b(Mat image, int div = 64) {

	// get iterators
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();

	const cv::Vec3b offset(div / 2, div / 2, div / 2);

	for (; it != itend; ++it) {

		// 处理每个像素 ---------------------

		*it = *it / div*div + offset;
		//像素处理结束 ----------------
	}
}

// Test 9
// using Mat_ iterator and bitwise
void colorReduce9(Mat image, int div = 64) {

	// div must be a power of 2
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	// get iterators
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();

	// scan all pixels
	for (; it != itend; ++it) {

		// 处理每个像素 ---------------------

		(*it)[0] &= mask;
		(*it)[0] += div >> 1;
		(*it)[1] &= mask;
		(*it)[1] += div >> 1;
		(*it)[2] &= mask;
		(*it)[2] += div >> 1;

		//像素处理结束 ----------------
	}
}

// Test 10
// using MatIterator_
void colorReduce10(Mat image, int div = 64) {

	// get iterators
	cv::Mat_<cv::Vec3b> cimage = image;
	cv::Mat_<cv::Vec3b>::iterator it = cimage.begin();
	cv::Mat_<cv::Vec3b>::iterator itend = cimage.end();

	for (; it != itend; it++) {

		// 处理每个像素 ---------------------

		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;

		//像素处理结束 ----------------
	}
}


// Test 11
// using at method
void colorReduce11(Mat image, int div = 64) {

	int nl = image.rows; // number of lines
	int nc = image.cols; // number of columns

	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++) {

			// 处理每个像素 ---------------------

			image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div*div + div / 2;
			image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div*div + div / 2;
			image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div*div + div / 2;

			//像素处理结束 ----------------

		}  
	}
}

// Test 12
// with input/ouput images
void colorReduce12(const Mat &image, // input image
	cv::Mat &result,      // output image
	int div = 64) {

	int nl = image.rows; // number of lines
	int nc = image.cols; // number of columns
	int nchannels = image.channels(); // number of channels

	// allocate output image if necessary
	result.create(image.rows, image.cols, image.type());


	for (int j = 0; j < nl; j++) {

		// get the addresses of input and output row j
		const uchar* data_in = image.ptr<uchar>(j);
		uchar* data_out = result.ptr<uchar>(j);

		for (int i = 0; i < nc*nchannels; i++) {

			// 处理每个像素 ---------------------

			data_out[i] = data_in[i] / div*div + div / 2;

			//像素处理结束 ----------------

		}  
	}
}

// Test 13
// using overloaded operators
void colorReduce13(Mat image, int div = 64) {

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	// perform color reduction
	image = (image&Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

// Test 14
// using look up table
void colorReduce14(Mat image, int div = 64) {

	cv::Mat lookup(1, 256, CV_8U);

	for (int i = 0; i < 256; i++) {

		lookup.at<uchar>(i) = i / div*div + div / 2;
	}

	LUT(image, lookup, image);
}


#define NTESTS 16
#define NITERATIONS 10

int main()
{
	int64 t[NTESTS], tinit;

	Mat image0;
	Mat image1;
	Mat image2;
	Mat image3;
	Mat image4;
	Mat image5;
	Mat image6;
	Mat image7;
	Mat image8;
	Mat image8b;
	Mat image9;
	Mat image10;
	Mat image11;
	Mat image12;
	Mat image13;
	Mat image14;
	Mat result;

	// read the image
	Mat image = imread("lena.jpg");


	// time and process the image
	const int64 start = getTickCount();
	colorReduce1(image, 64);
	//Elapsed time in seconds
	double duration = (getTickCount() - start) / getTickFrequency();

	// timer values set to 0
	for (int i = 0; i < NTESTS; i++)
		t[i] = 0;

	// repeat the tests several times
	int n = NITERATIONS;
	for (int k = 0; k < n; k++) {

	/*	cout << k << " of " << n << endl;*/

		image0 = imread("lena.jpg");
		if (!image0.data)
			return 0;

		// using .ptr and []
		tinit = getTickCount();
		colorReduce0(image0);
		t[0] += getTickCount() - tinit;

		image1 = imread("lena.jpg");
		// using .ptr and * ++
		tinit = getTickCount();
		colorReduce1(image1);
		t[1] += getTickCount() - tinit;

		image2 = imread("lena.jpg");
		// using .ptr and * ++ and modulo
		tinit = getTickCount();
		colorReduce2(image2);
		t[2] += getTickCount() - tinit;

		image3 = imread("lena.jpg");
		// using .ptr and * ++ and bitwise
		tinit = getTickCount();
		colorReduce3(image3);
		t[3] += getTickCount() - tinit;

		image4 = imread("lena.jpg");
		// using direct pointer arithmetic
		tinit = getTickCount();
		colorReduce4(image4);
		t[4] += getTickCount() - tinit;

		image5 = imread("lena.jpg");
		// using .ptr and * ++ and bitwise with image.cols * image.channels()
		tinit = getTickCount();
		colorReduce5(image5);
		t[5] += getTickCount() - tinit;

		image6 = imread("lena.jpg");
		// using .ptr and * ++ and bitwise (continuous)
		tinit = getTickCount();
		colorReduce6(image6);
		t[6] += getTickCount() - tinit;

		image7 = imread("lena.jpg");
		// using .ptr and * ++ and bitwise (continuous+channels)
		tinit = getTickCount();
		colorReduce7(image7);
		t[7] += getTickCount() - tinit;

		image8 = imread("lena.jpg");
		// using Mat_ iterator
		tinit = getTickCount();
		colorReduce8(image8);
		t[8] += getTickCount() - tinit;

		image8b = imread("lena.jpg");
		// using Mat_ iterator
		tinit = getTickCount();
		colorReduce8b(image8b);
		t[15] += getTickCount() - tinit;

		image9 = imread("lena.jpg");
		// using Mat_ iterator and bitwise
		tinit = getTickCount();
		colorReduce9(image9);
		t[9] += getTickCount() - tinit;

		image10 = imread("lena.jpg");
		// using Mat_ iterator
		tinit = getTickCount();
		colorReduce10(image10);
		t[10] += getTickCount() - tinit;

		image11 = imread("lena.jpg");
		// using at
		tinit = getTickCount();
		colorReduce11(image11);
		t[11] += getTickCount() - tinit;

		image12 = imread("lena.jpg");
		// using input/output images
		tinit = getTickCount();
		colorReduce12(image12, result);
		t[12] += getTickCount() - tinit;


		image13 = imread("lena.jpg");
		// using overloaded operators
		tinit = getTickCount();
		colorReduce13(image13);
		t[13] += getTickCount() - tinit;

		image14 = imread("lena.jpg");
		// using overloaded operators
		tinit = getTickCount();
		colorReduce14(image14);
		t[14] += getTickCount() - tinit;

		//------------------------------
	}

	
	//imshow("Test 0", image0);
	//imshow("Test 1", image1);
	//imshow("Test 2", image2);
	//imshow("Test 3", image3);
	//imshow("Test 4", image4);
	//imshow("Test 5", image5);
	//imshow("Test 6", image6);
	//imshow("Test 7", image7);
	//imshow("Test 8", image8);
	//imshow("Test 8b", image8b);
	//imshow("Test 9", image9);
	//imshow("Test 10", image10);
	//imshow("Test 11", image11);
	//imshow("Result", result);
	//imshow("Test 13", image13);
	//imshow("Test 14", image14);

	// print average execution time
	cout << endl << "-------------------------------------------" << endl << endl;
	cout << "0. using .ptr and [] =" << 1000.*t[0] / getTickFrequency() / n << "ms" << endl;
	cout << "1. using .ptr and * ++ =" << 1000.*t[1] / getTickFrequency() / n << "ms" << endl;
	cout << "2. using .ptr and * ++ and modulo =" << 1000.*t[2] / getTickFrequency() / n << "ms" << endl;
	cout << "3. using .ptr and * ++ and bitwise =" << 1000.*t[3] / getTickFrequency() / n << "ms" << endl;
	cout << "4. using direct pointer arithmetic =" << 1000.*t[4] / getTickFrequency() / n << "ms" << endl;
	cout << "5. using .ptr and * ++ and bitwise with image.cols * image.channels() =" << 1000.*t[5] / getTickFrequency() / n << "ms" << endl;
	cout << "6. using .ptr and * ++ and bitwise (continuous) =" << 1000.*t[6] / getTickFrequency() / n << "ms" << endl;
	cout << "7. using .ptr and * ++ and bitwise (continuous+reshape) =" << 1000.*t[7] / getTickFrequency() / n << "ms" << endl;
	cout << "8. using Mat_ iterator =" << 1000.*t[8] / getTickFrequency() / n << "ms" << endl;
	cout << "8. using Mat_ iterator and Vec3b op=" << 1000.*t[15] / getTickFrequency() / n << "ms" << endl;
	cout << "9. using Mat_ iterator and bitwise =" << 1000.*t[9] / getTickFrequency() / n << "ms" << endl;
	cout << "10. using MatIterator_ =" << 1000.*t[10] / getTickFrequency() / n << "ms" << endl;
	cout << "11. using at =" << 1000.*t[11] / getTickFrequency() / n << "ms" << endl;
	cout << "12. using input/output images =" << 1000.*t[12] / getTickFrequency() / n << "ms" << endl;
	cout << "13. using overloaded operators =" << 1000.*t[13] / getTickFrequency() / n << "ms" << endl;
	cout << "14. using lookup table =" << 1000.*t[14] / getTickFrequency() / n << "ms" << endl;

	waitKey(0);
	return 0;
}
