#include <opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	
	//��ϰһ������
	Mat inputMat,result,bnyMat;
	inputMat = imread("rim.png", 0);
	result = imread("rim.png");
	
	//��ֵ��
	Mat inversedMat;
	subtract(cv::Scalar(255, 255, 255), inputMat, inversedMat);
	threshold(inversedMat, bnyMat, 150, 255, THRESH_OTSU);
	//�����ͨ��
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(7, 11));//��Բ��
	morphologyEx(bnyMat, bnyMat, MORPH_CLOSE, element);
 
	vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;
	//CV_RETR_EXTERNALֻ�������Χ����
	//CV_CHAIN_APPROX_NONE��������߽������������������㵽contours������
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
	   //������������С����ı���(contours�Ǹ�������
	    drawContours(result, contours, i, Scalar(0,255,255),3, 8);
	   //�����������С����ı���
	   RotatedRect rbox = minAreaRect(contours[i]);
	   Point2f vtx[4];
	   rbox.points(vtx);
	   for (int j = 0; j < 4; ++j) {
		//������빫ʽ��߳�
		   float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		   float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		  //����
		   float square_vs[10];
		   square_vs[i] = Y / X;
		   float square_area[10];
		   square_area[i] = Y*X;
		   //
		   if(square_vs[i]>0.90&&square_vs[i]<1.17)
		   {
			   if(square_area[i]>700)
			   {  
				   cv::line(result, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			   }
			  
		   }
		
	}
	}
	imshow("ԭͼ", inputMat);
	imshow("result", result);



	//��ϰ��
	Mat input, out, bny;
	input = imread("die_on_chip.png", 0);
	out = imread("die_on_chip.png");

	//��ֵ��
	Mat inversed;
	subtract(cv::Scalar(255, 255, 255), input, inversed);
	threshold(inversed, bny, 150, 255, THRESH_OTSU);
	//�����ͨ��
	Mat element1 = getStructuringElement(MORPH_CROSS, Size(6,6));//����
	morphologyEx(bny, bny, MORPH_CROSS, element1);


	vector<vector<Point>> contours1;
	//vector<Vec4i> hierarchy;
	//CV_RETR_EXTERNALֻ�������Χ����
	//CV_CHAIN_APPROX_NONE��������߽������������������㵽contours������
	findContours(bny, contours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours1.size(); i++)
	{
		//������������С����ı���(contours�Ǹ�������
		drawContours(out, contours1, i, Scalar(0,255,255), 3, 8);
		//�����������С����ı���
		RotatedRect rbox = minAreaRect(contours1[i]);
		Point2f vtx[4];
		rbox.points(vtx);
		for (int j = 0; j < 4; ++j) {

			//������빫ʽ��߳�
			float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
			float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
			//���
			float square_area1[10];
			square_area1[i] = Y*X;
			//����
			float square_vs1[10];
			square_vs1[i] = Y / X;
			
			//
			if (square_vs1[i] >0.8)
			{

				if(square_area1[i]>2000&&square_area1[i]<10000)
				{ 
					cv::line(out, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
				}
			}
			
		}
	}
	imshow("in", input);
	imshow("out", out);

	waitKey(0);
	return 0;
}