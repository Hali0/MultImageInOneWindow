//������ͼƬ��ʾ��ͬһ������
//�汾��Version 2.0
//����˫Ŀƥ�䱸��

#include "opencv2/opencv.hpp"  

using namespace cv;

int main()
{
	Mat left, right;
	Mat canvas;
	int w, h;
	w = 640;
	h = 480;

	VideoCapture capleft(1);
	VideoCapture capright(0);

	while (1)
	{
		capleft >> left;
		capright >> right;

		canvas.create(h, w * 2, CV_8UC3);

		//��ͼ�񻭵�������

		//�õ�������һ���� 
		Mat canvasPart = canvas(Rect(w * 0, 0, w, h));
		//��ͼ�����ŵ���canvasPartһ����С
		resize(left, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
		//��ͼ�񻭵�������

		//��û�������һ����
		canvasPart = canvas(Rect(w, 0, w, h));
		resize(right, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		imshow("Output", canvas);
		if (waitKey(10) == 'q') break;
	}
	return 0;
}