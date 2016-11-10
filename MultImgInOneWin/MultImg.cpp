//将多张图片显示在同一窗口中
//版本：Version 1.0
//留作双目匹配备用

#include "opencv2/opencv.hpp"  

using namespace cv;
using namespace std;

void MultiImage_OneWin(const std::string& MultiShow_WinName, const vector<Mat>& SrcImg_V, CvSize SubPlot, CvSize ImgMax_Size = cvSize(400, 280));

int main()
{
	Mat left, right;
	
	VideoCapture capleft(1);
	VideoCapture capright(0);
	
	vector<Mat> imgs(4);
   
	IplImage* img1 = cvCreateImage(cvSize(320, 180), IPL_DEPTH_8U, 3);
	Mat black = cvarrToMat(img1);
	for (int i = 0; i < img1->height; i++)
	{
		uchar *ptrImage = (uchar*)(img1->imageData + i * img1->widthStep);
		for (int j = 0; j < img1->width; j++)
		{
			ptrImage[3 * j + 0] = 0;
			ptrImage[3 * j + 1] = 0;
			ptrImage[3 * j + 2] = 0;
		}
	}
	imgs[0] = black;
	imgs[1] = black;
	imgs[2] = black;
	imgs[3] = black;
	cout << "Press Q to quit the program" << endl;
	
	
	while (1)
	{
		capleft >> left;
		capright >> right;
		imgs[0] = left;
		imgs[1] = right;
		imgs[2] = left;
		imgs[3] = right;
		MultiImage_OneWin("Mult_Camera_Calibratin", imgs, cvSize(2, 2), cvSize(400, 280));
		if (waitKey(10) == 'q') break;
	}
	return 0;
}

//显示函数
void MultiImage_OneWin(const std::string& MultiShow_WinName, const vector<Mat>& SrcImg_V, CvSize SubPlot, CvSize ImgMax_Size)
{

	Mat Disp_Img;
	//Width of source image  
	CvSize Img_OrigSize = cvSize(SrcImg_V[0].cols, SrcImg_V[0].rows);
	//******************** Set the width for displayed image ********************//  
	//Width vs height ratio of source image  
	float WH_Ratio_Orig = Img_OrigSize.width / (float)Img_OrigSize.height;
	CvSize ImgDisp_Size = cvSize(100, 100);
	if (Img_OrigSize.width > ImgMax_Size.width)
		ImgDisp_Size = cvSize(ImgMax_Size.width, (int)ImgMax_Size.width / WH_Ratio_Orig);
	else if (Img_OrigSize.height > ImgMax_Size.height)
		ImgDisp_Size = cvSize((int)ImgMax_Size.height*WH_Ratio_Orig, ImgMax_Size.height);
	else
		ImgDisp_Size = cvSize(Img_OrigSize.width, Img_OrigSize.height);
	//******************** Check Image numbers with Subplot layout ********************//  
	int Img_Num = (int)SrcImg_V.size();
	if (Img_Num > SubPlot.width * SubPlot.height)
	{
		cout << "Your SubPlot Setting is too small !" << endl;
		exit(0);
	}
	//******************** Blank setting ********************//  
	CvSize DispBlank_Edge = cvSize(80, 60);
	CvSize DispBlank_Gap = cvSize(15, 15);
	//******************** Size for Window ********************//  
	Disp_Img.create(Size(ImgDisp_Size.width*SubPlot.width + DispBlank_Edge.width + (SubPlot.width - 1)*DispBlank_Gap.width,
		ImgDisp_Size.height*SubPlot.height + DispBlank_Edge.height + (SubPlot.height - 1)*DispBlank_Gap.height), CV_8UC3);
	Disp_Img.setTo(0);//Background  
					  //Left top position for each image  
	int EdgeBlank_X = (Disp_Img.cols - (ImgDisp_Size.width*SubPlot.width + (SubPlot.width - 1)*DispBlank_Gap.width)) / 2;
	int EdgeBlank_Y = (Disp_Img.rows - (ImgDisp_Size.height*SubPlot.height + (SubPlot.height - 1)*DispBlank_Gap.height)) / 2;
	CvPoint LT_BasePos = cvPoint(EdgeBlank_X, EdgeBlank_Y);
	CvPoint LT_Pos = LT_BasePos;

	//Display all images  
	for (int i = 0; i < Img_Num; i++)
	{
		//Obtain the left top position  
		if ((i%SubPlot.width == 0) && (LT_Pos.x != LT_BasePos.x))
		{
			LT_Pos.x = LT_BasePos.x;
			LT_Pos.y += (DispBlank_Gap.height + ImgDisp_Size.height);
		}
		//Writting each to Window's Image  
		Mat imgROI = Disp_Img(Rect(LT_Pos.x, LT_Pos.y, ImgDisp_Size.width, ImgDisp_Size.height));
		resize(SrcImg_V[i], imgROI, Size(ImgDisp_Size.width, ImgDisp_Size.height));

		LT_Pos.x += (DispBlank_Gap.width + ImgDisp_Size.width);
	}
	putText(Disp_Img, "Left Capture", cv::Point(200, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
	putText(Disp_Img, "Right Capture", cv::Point(600, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
	putText(Disp_Img, "Left Chessboard", cv::Point(175, 342), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));
	putText(Disp_Img, "Right Chessboard", cv::Point(575, 342), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255));

	cvShowImage(MultiShow_WinName.c_str(), &(IplImage(Disp_Img)));
}