#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    - O(n) time complexity (iterate one time each character of the string)
    - O(1) space compleixity (store 26 elements in hashmap)
*/

int find_first_marker(string input, int window_size) {
    unordered_map<char, int> count;
    int current_size = 0;

    int repeating = 0;

    for (int i = 0; i < input.size(); i++) {
        char character = input[i];
        char begin_char = input[i - window_size + 1];

        count[character]++;

        if (current_size < window_size) current_size++;

        if (count[character] == 2) {
            repeating++;
        }

        // cout << input.substr(i, -current_size) << " " << repeating << " "
        //      << " +" << character << " -" << begin_char << endl;

        if (current_size == window_size) {
            if (repeating == 0) {
                return i + 1;
            }

            count[begin_char]--;
            if (count[begin_char] == 1) {
                repeating--;
            }
        }
    }

    cout << "Marker not found" << endl;
    return -1;
}

int main() {
    string input;
    cin >> input;
    int solution1 = find_first_marker(input, 4);

    cout << endl
         << "Solution 1: " << solution1 << " " << input.substr(solution1 - 4, 4)
         << endl;

    int solution2 = find_first_marker(input, 14);

    cout << endl
         << "Solution 2: " << solution2 << " "
         << input.substr(solution2 - 14, 14) << endl;
}