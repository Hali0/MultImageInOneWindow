//������ͼƬ��ʾ��ͬһ������
//�汾��Version 2.0
//����˫Ŀƥ�䱸��

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

		//����ͼ�񻭵�������
        //�õ�������һ���� 
		Mat canvasPart = canvas(Rect(0, 0, w, h));
		//��ͼ�����ŵ���canvasPartһ����С
		resize(left, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
		
		//����ͼ�񻭵�������
        //��û�������һ����
		canvasPart = canvas(Rect(w, 0, w, h));
		resize(right, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		//����ͼ�񻭵�������
		canvasPart = canvas(Rect(0, h, w, h));
		resize(left, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		//����ͼ�񻭵�������
		canvasPart = canvas(Rect(w, h, w, h));
		resize(right, canvasPart, canvasPart.size(), 0, 0, INTER_LINEAR);

		imshow("Output", canvas);
		if (waitKey(10) == 'q') break;
	}
	return 0;
}