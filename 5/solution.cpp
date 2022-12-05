#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<char>> parse_stack_raw(vector<string> raw) {
    vector<vector<char>> parsed(9, vector<char>());

    for (int i = raw.size() - 1; i >= 0; i--) {
        for (int j = 1; j < raw[i].size(); j += 4) {
            int current_stack = (j - 1) / 4;
            int current_char = raw[i][j];

            if (current_char != ' ') {
                parsed[current_stack].push_back(raw[i][j]);
            }
        }
    }

    return parsed;
}

vector<int> parse_instructions(string line) {
    vector<int> output;

    stringstream ss(line);
    string buffer;

    getline(ss, buffer, ' ');
    getline(ss, buffer, ' ');

    output.push_back(stoi(buffer));
    cout << buffer << endl;

    getline(ss, buffer, ' ');
    getline(ss, buffer, ' ');
    output.push_back(stoi(buffer));
    getline(ss, buffer, ' ');
    getline(ss, buffer, ' ');
    output.push_back(stoi(buffer));

    // cout << output[0] << " " << output[1] << " " << output[2] << endl;
    return output;
}

void process_stacks(vector<vector<char>>& stacks, vector<int>& instruction) {
    int amount = instruction[0];
    int from = instruction[1] - 1;
    int to = instruction[2] - 1;

    vector<int> crates_buffer;

    for (int i = 0; i < amount; i++) {
        if (stacks[from].size() > 0) {
            crates_buffer.push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }

    for (int i = amount - 1; i >= 0; i--) {
        stacks[to].push_back(crates_buffer[i]);
    }
}

string get_top_of_stacks(vector<vector<char>>& stacks) {
    string output = "";

    for (auto stack : stacks) {
        output += stack.back();
    }

    return output;
}

int main() {
    string buffer;
    vector<string> stack_raw;

    while (getline(cin, buffer, '\n')) {
        if (buffer.size() == 0) {
            break;
        }
        if (buffer[0] != '[') {
            continue;
        }
        cout << buffer << endl;
        stack_raw.push_back(buffer);
    }

    auto stacks = parse_stack_raw(stack_raw);

    for (auto v : stacks) {
        for (auto k : v) {
            cout << k << endl;
        }
        cout << endl;
    }

    vector<string> instructions_raw;
    vector<vector<int>> instructions;

    while (getline(cin, buffer, '\n')) {
        auto parsed = parse_instructions(buffer);
        instructions.push_back(parsed);
    }

    // process_stacks(stacks, instructions[0]);

    for (auto instruction : instructions) {
        process_stacks(stacks, instruction);
    }

    for (auto v : stacks) {
        for (auto k : v) {
            cout << k << endl;
        }
        cout << endl;
    }

    string solution1 = get_top_of_stacks(stacks);

    cout << "Solution: " << solution1 << endl;

    return 0;
}