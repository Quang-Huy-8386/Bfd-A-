#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

using namespace std;
typedef pair<int, int> Point;  
int heuristic(Point a, Point b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}
struct Node {
    Point point;
    int g;  
    int f;  
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

vector<Point> bfs_with_a_star(const vector<vector<int>>& grid, Point start, Point goal) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<Point> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    priority_queue<Node, vector<Node>, greater<Node>> open_list;
    unordered_set<string> visited;
    unordered_map<string, Point> came_from;
    open_list.push({start, 0, heuristic(start, goal)});
    visited.insert(to_string(start.first) + "," + to_string(start.second));

    while (!open_list.empty()) {
        Node current_node = open_list.top();
        open_list.pop();
        Point current = current_node.point;
        if (current == goal) {
            vector<Point> path;
            while (came_from.find(to_string(current.first) + "," + to_string(current.second)) != came_from.end()) {
                path.push_back(current);
                current = came_from[to_string(current.first) + "," + to_string(current.second)];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }
        for (auto& dir : directions) {
            Point neighbor = {current.first + dir.first, current.second + dir.second};
            if (neighbor.first >= 0 && neighbor.first < rows &&
                neighbor.second >= 0 && neighbor.second < cols &&
                grid[neighbor.first][neighbor.second] == 0 &&  // 0: có thể di chuyển
                visited.find(to_string(neighbor.first) + "," + to_string(neighbor.second)) == visited.end()) {

                visited.insert(to_string(neighbor.first) + "," + to_string(neighbor.second));
                int g_new = current_node.g + 1; 
                int f_new = g_new + heuristic(neighbor, goal);  
                open_list.push({neighbor, g_new, f_new});
                came_from[to_string(neighbor.first) + "," + to_string(neighbor.second)] = current;
            }
        }
    }
    return {};  
}
int main() {
    int rows, cols;
    cout << "Nhập số hàng và số cột của ma trận (rows cols): ";
    cin >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    cout << "Nhập ma trận (0 cho ô trống, 1 cho tường):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
    int start_x, start_y, goal_x, goal_y;
    cout << "Nhập tọa độ điểm bắt đầu (start_x start_y): ";
    cin >> start_x >> start_y;
    cout << "Nhập tọa độ điểm đích (goal_x goal_y): ";
    cin >> goal_x >> goal_y;
    Point start = {start_x, start_y};
    Point goal = {goal_x, goal_y};
    vector<Point> path = bfs_with_a_star(grid, start, goal);
    if (!path.empty()) {
        cout << "Đường đi tìm được: " << endl;
        for (auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ")" << endl;
        }
    } else {
        cout << "Không tìm thấy đường đi" << endl;
    }
    return 0;
}

