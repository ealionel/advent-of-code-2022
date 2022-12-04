#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool are_range_containing(pair<int, int> range1, pair<int, int> range2) {
    if (range1.first >= range2.first && range1.second <= range2.second) {
        return true;
    }

    if (range2.first >= range1.first && range2.second <= range1.second) {
        return true;
    }

    return false;
}

bool are_range_overlapping(pair<int, int> range1, pair<int, int> range2) {
    return range1.first <= range2.second && range1.second >= range2.first;
}

pair<pair<int, int>, pair<int, int>> parse_line(string line) {
    pair<int, int> range1;
    pair<int, int> range2;

    string s1 = line.substr(0, line.find(','));
    string s2 = line.substr(line.find(',') + 1);

    auto delimiter_pos = s1.find('-');
    range1.first = stoi(s1.substr(0, delimiter_pos));
    range1.second = stoi(s1.substr(delimiter_pos + 1));

    auto delimiter_pos2 = s2.find('-');
    range2.first = stoi(s2.substr(0, delimiter_pos2));
    range2.second = stoi(s2.substr(delimiter_pos2 + 1));

    return make_pair(range1, range2);
}

int main() {
    string line_buffer;
    vector<pair<pair<int, int>, pair<int, int>>> all_ranges;

    while (cin >> line_buffer) {
        all_ranges.push_back(parse_line(line_buffer));
    }

    int solution1 = 0;

    for (auto ranges : all_ranges) {
        if (are_range_containing(ranges.first, ranges.second)) {
            solution1++;
        }
    }

    cout << "Solution 1 : " << solution1 << endl;

    int solution2 = 0;

    for (auto ranges : all_ranges) {
        if (are_range_overlapping(ranges.first, ranges.second)) {
            solution2++;
        }
    }

    cout << "Solution 2 : " << solution2 << endl;
    return 0;
}