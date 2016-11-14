//将多张图片显示在同一窗口中
//版本：Version 2.0
//留作双目匹配备用

#include "opencv2/opencv.hpp"  

using namespace cv;
using namespace std;
int main()
{
	Mat left, right;
	Mat canvas;
	int w, h;
	w = 320;
	h = 240;

	VideoCapture capleft(1);
	VideoCapture capright(0);
	cout << "Press Q to quit the program" << endl;
	while (1)
	{
		capleft >> left;
		capright >> right;

		canvas.create(h*2, w * 2, CV_8UC3);

		//左上图像画到画布上
        //得到画布的一部分 
		Mat canvasPart = canvas(Rect(0, 0, w, h));
		//把图像缩放到跟canvasPart一样大小
		resize(left, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
		
		//右上图像画到画布上
        //获得画布的另一部分
		canvasPart = canvas(Rect(w, 0, w, h));
		resize(right, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		//左下图像画到画布上
		canvasPart = canvas(Rect(0, h, w, h));
		resize(left, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		//右下图像画到画布上
		canvasPart = canvas(Rect(w, h, w, h));
		resize(right, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		imshow("Output", canvas);
		if (waitKey(10) == 'q') break;
	}
	return 0;
}