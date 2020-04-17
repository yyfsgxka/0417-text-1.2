#include <opencv.hpp>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	
	//练习一：宽长比
	Mat inputMat,result,bnyMat;
	inputMat = imread("rim.png", 0);
	result = imread("rim.png");
	
	//二值化
	Mat inversedMat;
	subtract(cv::Scalar(255, 255, 255), inputMat, inversedMat);
	threshold(inversedMat, bnyMat, 150, 255, THRESH_OTSU);
	//获得连通域
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(7, 11));//椭圆形
	morphologyEx(bnyMat, bnyMat, MORPH_CLOSE, element);
 
	vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;
	//CV_RETR_EXTERNAL只检测最外围轮廓
	//CV_CHAIN_APPROX_NONE保存物体边界上所有连续的轮廓点到contours向量内
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); i++)
	{
	   //绘制轮廓及最小外接四边形(contours是个向量）
	    drawContours(result, contours, i, Scalar(0,255,255),3, 8);
	   //获得轮廓的最小外接四边形
	   RotatedRect rbox = minAreaRect(contours[i]);
	   Point2f vtx[4];
	   rbox.points(vtx);
	   for (int j = 0; j < 4; ++j) {
		//两点距离公式求边长
		   float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
		   float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
		  //宽长比
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
	imshow("原图", inputMat);
	imshow("result", result);



	//练习二
	Mat input, out, bny;
	input = imread("die_on_chip.png", 0);
	out = imread("die_on_chip.png");

	//二值化
	Mat inversed;
	subtract(cv::Scalar(255, 255, 255), input, inversed);
	threshold(inversed, bny, 150, 255, THRESH_OTSU);
	//获得连通域
	Mat element1 = getStructuringElement(MORPH_CROSS, Size(6,6));//矩形
	morphologyEx(bny, bny, MORPH_CROSS, element1);


	vector<vector<Point>> contours1;
	//vector<Vec4i> hierarchy;
	//CV_RETR_EXTERNAL只检测最外围轮廓
	//CV_CHAIN_APPROX_NONE保存物体边界上所有连续的轮廓点到contours向量内
	findContours(bny, contours1, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours1.size(); i++)
	{
		//绘制轮廓及最小外接四边形(contours是个向量）
		drawContours(out, contours1, i, Scalar(0,255,255), 3, 8);
		//获得轮廓的最小外接四边形
		RotatedRect rbox = minAreaRect(contours1[i]);
		Point2f vtx[4];
		rbox.points(vtx);
		for (int j = 0; j < 4; ++j) {

			//两点距离公式求边长
			float Y = sqrt((vtx[0].y - vtx[1].y) * (vtx[0].y - vtx[1].y) + (vtx[0].x - vtx[1].x) * (vtx[0].x - vtx[1].x));
			float X = sqrt((vtx[1].y - vtx[2].y) * (vtx[1].y - vtx[2].y) + (vtx[1].x - vtx[2].x) * (vtx[1].x - vtx[2].x));
			//面积
			float square_area1[10];
			square_area1[i] = Y*X;
			//宽长比
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