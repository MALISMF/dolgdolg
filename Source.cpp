#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // Шаг 1: Загрузить изображение
    Mat img = imread("ph.png", IMREAD_COLOR);


    // Преобразуем изображение в градации серого
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Применяем фильтр Гаусса для уменьшения шума
    GaussianBlur(gray, gray, Size(5, 5), 0);

    // Пороговая фильтрация для бинаризации изображения
    Mat binary;
    threshold(gray, binary, 100, 255, THRESH_BINARY_INV);

    // Поиск контуров
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Поиск максимальной и минимальной Y-координаты среди всех контуров
    int minY = img.rows;
    int maxY = 0;

    for (size_t i = 0; i < contours.size(); i++) {
        for (size_t j = 0; j < contours[i].size(); j++) {
            int y = contours[i][j].y;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }
    }

    // Высота изображения
    int imgHeight = img.rows;

    // Пересчитываем пиксельные значения Y в реальные значения по оси Y (-2000 до 1000)
    float realMinY = 1000 - (3000.0 / imgHeight) * minY;
    float realMaxY = 1000 - (3000.0 / imgHeight) * maxY;

    // Рисуем линии на найденных границах для визуализации
    line(img, Point(0, minY), Point(img.cols, minY), Scalar(0, 0, 255), 2); // нижняя граница
    line(img, Point(0, maxY), Point(img.cols, maxY), Scalar(0, 255, 0), 2); // верхняя граница

    // Отображаем результаты
    cout << "Минимальная Y-координата (в пикселях): " << minY << endl;
    cout << "Максимальная Y-координата (в пикселях): " << maxY << endl;
    cout << "Минимальная Y-координата (реальная): " << realMinY << " нТл" << endl;
    cout << "Максимальная Y-координата (реальная): " << realMaxY << " нТл" << endl;

    // Показать результат
    imshow("Result", img);
    waitKey(0);
    return 0;
}


