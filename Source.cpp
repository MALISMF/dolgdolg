#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // ��� 1: ��������� �����������
    Mat img = imread("ph.png", IMREAD_COLOR);


    // ����������� ����������� � �������� ������
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // ��������� ������ ������ ��� ���������� ����
    GaussianBlur(gray, gray, Size(5, 5), 0);

    // ��������� ���������� ��� ����������� �����������
    Mat binary;
    threshold(gray, binary, 100, 255, THRESH_BINARY_INV);

    // ����� ��������
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // ����� ������������ � ����������� Y-���������� ����� ���� ��������
    int minY = img.rows;
    int maxY = 0;

    for (size_t i = 0; i < contours.size(); i++) {
        for (size_t j = 0; j < contours[i].size(); j++) {
            int y = contours[i][j].y;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }
    }

    // ������ �����������
    int imgHeight = img.rows;

    // ������������� ���������� �������� Y � �������� �������� �� ��� Y (-2000 �� 1000)
    float realMinY = 1000 - (3000.0 / imgHeight) * minY;
    float realMaxY = 1000 - (3000.0 / imgHeight) * maxY;

    // ������ ����� �� ��������� �������� ��� ������������
    line(img, Point(0, minY), Point(img.cols, minY), Scalar(0, 0, 255), 2); // ������ �������
    line(img, Point(0, maxY), Point(img.cols, maxY), Scalar(0, 255, 0), 2); // ������� �������

    // ���������� ����������
    cout << "����������� Y-���������� (� ��������): " << minY << endl;
    cout << "������������ Y-���������� (� ��������): " << maxY << endl;
    cout << "����������� Y-���������� (��������): " << realMinY << " ���" << endl;
    cout << "������������ Y-���������� (��������): " << realMaxY << " ���" << endl;

    // �������� ���������
    imshow("Result", img);
    waitKey(0);
    return 0;
}


