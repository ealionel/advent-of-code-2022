#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> create_visibility_map(vector<vector<int>> &map) {
  int rows = map.size();
  int cols = map[0].size();
  vector<vector<int>> visible(rows, vector<int>(cols, 0));

  // Left -> Right
  for (int i = 0; i < rows; i++) {
    int max_so_far = -1;
    for (int j = 0; j < cols; j++) {
      if (map[i][j] > max_so_far) {
        visible[i][j] = 1;
        max_so_far = map[i][j];
      }
    }
  }

  // Right -> Left
  for (int i = 0; i < rows; i++) {
    int max_so_far = -1;
    for (int j = cols - 1; j >= 0; j--) {
      if (map[i][j] > max_so_far) {
        visible[i][j] = 1;
        max_so_far = map[i][j];
      }
    }
  }

  // Top -> Down
  for (int j = 0; j < cols; j++) {
    int max_so_far = -1;
    for (int i = 0; i < rows; i++) {
      if (map[i][j] > max_so_far) {
        visible[i][j] = 1;
        max_so_far = map[i][j];
      } 
    }
  }

  // Down -> Top
  for (int j = 0; j < cols; j++) {
    int max_so_far = -1;
    for (int i = rows - 1; i >= 0; i--) {
      if (map[i][j] > max_so_far) {
        visible[i][j] = 1;
        max_so_far = map[i][j];
      } 
    }
  }

  return visible;
}

int compute_scenic_score(vector<vector<int>> &map, int row, int column) {
  int height = map.size();
  int width = map[0].size();

  int right = 0;
  for (int i = column + 1; i < width; i++) {
    right++;
    if (map[row][i] >= map[row][column]) {
      break;
    }
  }

  int left = 0;
  for (int i = column - 1; i >= 0; i--) {
    left++;
    if (map[row][i] >= map[row][column]) {
      break;
    }
  }

  int down = 0;
  for (int i = row + 1; i < height; i++) {
    down++;
    if (map[i][column] >= map[row][column]) {
      break;
    }
}


  int top = 0;
  for (int i = row - 1; i >= 0; i--) {
    top++;
    if (map[i][column] >= map[row][column]) {
      break;
    }
  }

  int result = left * right * top * down;

  cout << map[row][column] << " " << "(" << row << ", " << column << ") " << left << "," << right << "," << top << "," << down << " = " << result << endl;

  return result;
}

int find_best_scenic_score(vector<vector<int>> &map) {
  int max_score = 0;
  for (int i = 1; i < map.size() - 1; i++) {
    for (int j = 1; j < map[0].size() - 1; j++) {
      max_score = max(compute_scenic_score(map, i, j), max_score);
    }
  }

  return max_score;
}

int count_visible(vector<vector<int>> &visiblity_map) {
  int sum = 0;
  for (auto rows: visiblity_map) {
    for (auto val: rows) {
      sum += val;
    }
  }

  return sum;
}

void print_map(vector<vector<int>>& map) {
  for (auto rows: map) {
    for (auto val: rows) {
      cout << val << " ";
    }
    cout << endl;
  }
}

int main() {

  char character;
  
  vector<vector<int>> map;

  map.push_back({});

  while(cin >> noskipws >> character) {
    if (character == '\n') {
      map.push_back({});
      continue;
    }
    map.back().push_back(character - '0');
  }

  auto visibility_map = create_visibility_map(map);

  // print_map(visibility_map);

  int solution1 = count_visible(visibility_map);

  cout << "Solution 1: " << solution1 << endl;

  int solution2 = find_best_scenic_score(map);

  cout << "Solution 2: " << solution2 << endl;
  return 0;
}