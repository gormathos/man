#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int rows = 8;
const int cols = 8;

struct Point {
    int x, y;
    Point(int i, int j) : x(i), y(j) {}
};

bool isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

void bfs(int x, int y, cv::Mat& image, std::vector<std::vector<bool>>& visited) {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    queue<Point> q;
    q.push(Point(x, y));
    visited[x][y] = true;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny) && !visited[nx][ny] && image.at<uchar>(nx, ny) != 255) {
                q.push(Point(nx, ny));
                visited[nx][ny] = true;
            }
        }
    }
}

int countFigures(Mat& image) {
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (image.at<uchar>(i, j) != 255 && !visited[i][j]) {
                bfs(i, j, image, visited);
                count++;
            }
        }
    }

    return count;
}

int main() {
    for (int i = 1; i <= 15; i++) {
        string basename = "rect";
        string filename = basename + to_string(i) + ".png";
        Mat image = imread(filename, IMREAD_GRAYSCALE);

        if (image.empty()) {
            cerr << "Error: Unable to load image." << endl;
            return -1;
        }

        int result = countFigures(image);

        cout << "Number of figures: " << result << endl;
    }
    return 0;
}
