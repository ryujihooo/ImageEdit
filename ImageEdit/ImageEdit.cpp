#include"opencv2/opencv.hpp"
#include<iostream>

using namespace std;
using namespace cv;

Mat src;

//밝기
void on_Brightness(int pos, void* userdata)
{
	Mat dst;
	int contrast = *(static_cast<int*>(userdata));

	//밝기와 대비 값 계산
	int iBrightness = pos - 300;
	double dContrast = contrast / 50.0;

	//밝기와 대비 계산 값을 이용해 변환
	src.convertTo(dst, -1, dContrast, iBrightness);

	//변환 이미지 출력
	imshow("src", dst);
}

//대비
void on_Contrast(int pos, void* userdata)
{
	Mat dst;
	int brightness = *(static_cast<int*>(userdata));

	//밝기와 대비 값 계산
	int iBrightness = brightness - 50;
	double dContrast = pos / 50.0;

	//밝기와 대비 계산 값을 이용해 변환
	src.convertTo(dst, -1, dContrast, iBrightness);

	imshow("src", dst);
}

//필터
void colormap(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst;
	if (pos == 0) {		// 필터를 적용하지 않았을 때
		dst = src;
	}
	else if (pos == 1) {	//1번 필터 적용
		// COLORMAP_BONE 컬러맵을 이용하여 컬러를 다시 매핑
		applyColorMap(src, dst, COLORMAP_BONE);
	}
	else if (pos == 2) {	//2번 필터 적용
		// COLORMAP_OCEAN 컬러맵을 이용하여 컬러를 다시 매핑
		applyColorMap(src, dst, COLORMAP_OCEAN);
	}
	else if (pos == 3) {	//3번 필터 적용
		// COLORMAP_DEEPGREEN 컬러맵을 이용하여 컬러를 다시 매핑
		applyColorMap(src, dst, COLORMAP_DEEPGREEN);
	}
	else if (pos == 4) {	//4번 필터 적용
		// COLORMAP_HOT 컬러맵을 이용하여 컬러를 다시 매핑
		applyColorMap(src, dst, COLORMAP_HOT);
	}
	else {	//5번 필터 적용
		// COLORMAP_PINK 컬러맵을 이용하여 컬러를 다시 매핑
		applyColorMap(src, dst, COLORMAP_PINK);
	}

	imshow("src", dst);
}

//이진화
void threadhold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst;
	if (pos == 0) {	//이진화를 적용하지 않았을 때
		dst = src;
	}
	else {	//이진화 적용했을 때, 트랙바를 이용해 임계값을 설정
		//이진화를 위해 이미지를 그레이스케일 영상으로 바꿈
		src = imread("./proj.jpg", IMREAD_GRAYSCALE);
		threshold(src, dst, pos, 230, THRESH_TOZERO);	//이진화 적용
	}

	imshow("src", dst);
}

//회전
void on_rotaion(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = Mat();
	Size dsize = Size(src.cols, src.rows);

	//회전의 중심을 영상의 중심으로 설정
	Point center = Point(src.cols / 2.0, src.rows / 2.0);

	//회전을 나타내는 행렬 계산
	Mat M = getRotationMatrix2D(center, pos, 1.0);

	//변환 행렬을 이용해 실제 변환 수행
	warpAffine(src, dst, M, dsize, INTER_LINEAR);

	imshow("src", dst);

}

int main(int argc, char** argv)
{
	src = imread("./proj.jpg");

	if (src.data == false)
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	namedWindow("src", 1);

	int brightvalue = 100;
	int contrastvalue = 100;

	createTrackbar("밝기", "src", &brightvalue, 200, on_Brightness, &contrastvalue);

	createTrackbar("대비", "src", &contrastvalue, 200, on_Contrast, &brightvalue);

	createTrackbar("필터", "src", 0, 5, colormap, (void*)&src);

	createTrackbar("임계값", "src", 0, 230, threadhold, (void*)&src);
	setTrackbarPos("임계값", "src", 0);

	createTrackbar("회전", "src", 0, 360, on_rotaion, (void*)&src);
	setTrackbarPos("회전", "src", 0);

	imshow("src", src);

	waitKey(0);


	return 0;
}