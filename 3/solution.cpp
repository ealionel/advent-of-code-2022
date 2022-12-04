#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

char find_repeating_char(string s1, string s2) {
    unordered_map<char, int> count_s1;
    unordered_map<char, int> count_s2;

    for (auto c : s1) {
        count_s1[c]++;
    }

    for (auto c : s2) {
        if (count_s1.find(c) != count_s1.end()) {
            return c;
        }
    }

    return 0;
}

char find_repeating_char_2(string s1, string s2, string s3) {
    unordered_map<char, int> count_s1;
    unordered_map<char, int> count_s2;

    for (auto c : s1) {
        count_s1[c]++;
    }

    for (auto c : s2) {
        count_s2[c]++;
    }

    for (auto c : s3) {
        if (count_s1.find(c) != count_s1.end() &&
            count_s2.find(c) != count_s2.end()) {
            return c;
        }
    }

    cout << "not found?" << endl;

    return 0;
}

unordered_map<char, int> compute_object_priority() {
    unordered_map<char, int> priorities;
    int count = 1;
    for (char c = 'a'; c <= 'z'; c++) {
        priorities[c] = count;
        count++;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        priorities[c] = count;
        count++;
    }

    return priorities;
}

int main() {
    string line;

    vector<string> lines;

    while (cin >> line) {
        lines.push_back(line);
    }

    auto priorities = compute_object_priority();

    int solution1 = 0;

    for (auto l : lines) {
        int n = l.size();
        char repeating_char =
            find_repeating_char(l.substr(0, n / 2), l.substr(n / 2));

        solution1 += priorities[repeating_char];
    }

    cout << "Solution 1: " << solution1 << endl;

    int solution2 = 0;

    for (int i = 0; i < lines.size(); i += 3) {
        char repeating_char =
            find_repeating_char_2(lines[i], lines[i + 1], lines[i + 2]);

        cout << "Group " << i / 3 << " : " << repeating_char << endl;

        solution2 += priorities[repeating_char];
    }

    cout << "Solution 2: " << solution2 << endl;

    return 0;
}