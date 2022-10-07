#include"opencv2/opencv.hpp"
#include<iostream>

using namespace std;
using namespace cv;

Mat src;

//���
void on_Brightness(int pos, void* userdata)
{
	Mat dst;
	int contrast = *(static_cast<int*>(userdata));

	//���� ��� �� ���
	int iBrightness = pos - 300;
	double dContrast = contrast / 50.0;

	//���� ��� ��� ���� �̿��� ��ȯ
	src.convertTo(dst, -1, dContrast, iBrightness);

	//��ȯ �̹��� ���
	imshow("src", dst);
}

//���
void on_Contrast(int pos, void* userdata)
{
	Mat dst;
	int brightness = *(static_cast<int*>(userdata));

	//���� ��� �� ���
	int iBrightness = brightness - 50;
	double dContrast = pos / 50.0;

	//���� ��� ��� ���� �̿��� ��ȯ
	src.convertTo(dst, -1, dContrast, iBrightness);

	imshow("src", dst);
}

//����
void colormap(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst;
	if (pos == 0) {		// ���͸� �������� �ʾ��� ��
		dst = src;
	}
	else if (pos == 1) {	//1�� ���� ����
		// COLORMAP_BONE �÷����� �̿��Ͽ� �÷��� �ٽ� ����
		applyColorMap(src, dst, COLORMAP_BONE);
	}
	else if (pos == 2) {	//2�� ���� ����
		// COLORMAP_OCEAN �÷����� �̿��Ͽ� �÷��� �ٽ� ����
		applyColorMap(src, dst, COLORMAP_OCEAN);
	}
	else if (pos == 3) {	//3�� ���� ����
		// COLORMAP_DEEPGREEN �÷����� �̿��Ͽ� �÷��� �ٽ� ����
		applyColorMap(src, dst, COLORMAP_DEEPGREEN);
	}
	else if (pos == 4) {	//4�� ���� ����
		// COLORMAP_HOT �÷����� �̿��Ͽ� �÷��� �ٽ� ����
		applyColorMap(src, dst, COLORMAP_HOT);
	}
	else {	//5�� ���� ����
		// COLORMAP_PINK �÷����� �̿��Ͽ� �÷��� �ٽ� ����
		applyColorMap(src, dst, COLORMAP_PINK);
	}

	imshow("src", dst);
}

//����ȭ
void threadhold(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst;
	if (pos == 0) {	//����ȭ�� �������� �ʾ��� ��
		dst = src;
	}
	else {	//����ȭ �������� ��, Ʈ���ٸ� �̿��� �Ӱ谪�� ����
		//����ȭ�� ���� �̹����� �׷��̽����� �������� �ٲ�
		src = imread("./proj.jpg", IMREAD_GRAYSCALE);
		threshold(src, dst, pos, 230, THRESH_TOZERO);	//����ȭ ����
	}

	imshow("src", dst);
}

//ȸ��
void on_rotaion(int pos, void* userdata)
{
	Mat src = *(Mat*)userdata;
	Mat dst = Mat();
	Size dsize = Size(src.cols, src.rows);

	//ȸ���� �߽��� ������ �߽����� ����
	Point center = Point(src.cols / 2.0, src.rows / 2.0);

	//ȸ���� ��Ÿ���� ��� ���
	Mat M = getRotationMatrix2D(center, pos, 1.0);

	//��ȯ ����� �̿��� ���� ��ȯ ����
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

	createTrackbar("���", "src", &brightvalue, 200, on_Brightness, &contrastvalue);

	createTrackbar("���", "src", &contrastvalue, 200, on_Contrast, &brightvalue);

	createTrackbar("����", "src", 0, 5, colormap, (void*)&src);

	createTrackbar("�Ӱ谪", "src", 0, 230, threadhold, (void*)&src);
	setTrackbarPos("�Ӱ谪", "src", 0);

	createTrackbar("ȸ��", "src", 0, 360, on_rotaion, (void*)&src);
	setTrackbarPos("ȸ��", "src", 0);

	imshow("src", src);

	waitKey(0);


	return 0;
}