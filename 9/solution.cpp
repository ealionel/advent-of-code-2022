#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

unordered_map<string, pair<int, int>> dir_mapping = {
    {"U", {0, 1}}, {"D", {0, -1}}, {"L", {-1, 0}}, {"R", {1, 0}}};

unordered_map<pair<int, int>, int, hash_pair> tail_visits = {{{0, 0}, 1}};
int distinct_tail_visits = 1;

void print_pos(pair<int, int> pos) {
    cout << "(" << pos.first << "," << pos.second << ")" << endl;
}

class Rope {
   private:
    void move_head_to(pair<int, int> to) {
        auto previous = head;

        head.first = to.first;
        head.second = to.second;
        adjust_tail(previous);

        if (id == 9 && tail_visits.find(to) == tail_visits.end()) {
            tail_visits[to] = 1;
            distinct_tail_visits++;
        }
    }

    void move_tail_to(pair<int, int> to) {
        tail.first = to.first;
        tail.second = to.second;

        if (child != nullptr) {
            child->move_head_to(to);
        }
    }

   public:
    // unordered_map<pair<int, int>, int, hash_pair> tail_visits = {{{0, 0},
    // 1}}; int distinct_tail_visits = 1;
    int id;

    Rope* child = nullptr;

    Rope(Rope* child, int id) : child(child), id(id) {}

    bool is_touching() {
        int x_diff = abs(head.first - tail.first);
        int y_diff = abs(head.second - tail.second);

        return (x_diff <= 1 && y_diff <= 1);
    }

    bool is_diagonal() {
        int x_diff = abs(head.first - tail.first);
        int y_diff = abs(head.second - tail.second);

        return x_diff >= 1 && y_diff >= 1;
    }

    pair<int, int> head{0, 0};  // x, y
    pair<int, int> tail{0, 0};

    void adjust_tail(pair<int, int> previous_head_position) {
        if (!is_touching() && is_diagonal()) {
            int diff_x = clamp(head.first - tail.first, -1, 1);
            int diff_y = clamp(head.second - tail.second, -1, 1);

            int new_pos_x = tail.first + diff_x;
            int new_pos_y = tail.second + diff_y;

            move_tail_to({new_pos_x, new_pos_y});
        } else if (!is_touching()) {
            move_tail_to(previous_head_position);
        }
    }

    void move_dir(string direction) {
        auto dir = dir_mapping[direction];

        auto previous_head = head;

        move_head_to({head.first + dir.first, head.second + dir.second});
    }

    void print_position() {
        cout << id << ": H(" << head.first << "," << head.second << ") - ";
        cout << "T(" << tail.first << "," << tail.second << ")" << endl;
    }
};

void print_all_rope(Rope* rope) {
    auto current = rope;

    while (current != nullptr) {
        current->print_position();
        current = current->child;
    }
    cout << endl;
}

vector<Rope*> get_all_ropes(Rope* rope) {
    auto current = rope;
    vector<Rope*> ropes;

    while (current != nullptr) {
        ropes.push_back(current);
        current = current->child;
    }
    return ropes;
}

void print_map(Rope* rope, int min_x, int max_x, int min_y, int max_y) {
    auto pos = get_all_ropes(rope);

    for (int i = max_y; i >= min_y; i--) {
        for (int j = min_x; j < max_x; j++) {
            bool found_rope = false;
            for (auto rope : pos) {
                if (rope->head.first == j && rope->head.second == i) {
                    cout << rope->id;
                    found_rope = true;
                    break;
                }
            }

            if (!found_rope) {
                if (i == 0 && j == 0) {
                    cout << "s";
                } else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    string buffer;

    vector<pair<string, int>> motions;

    while (cin >> buffer) {
        pair<string, int> motion;

        motion.first = buffer;
        cin >> buffer;
        motion.second = stoi(buffer);

        motions.push_back(motion);
    }

    Rope* rope = nullptr;

    for (int i = 0; i < 10; i++) {
        auto new_rope = new Rope(rope, 9 - i);
        rope = new_rope;
    }

    for (auto motion : motions) {
        cout << motion.first << " " << motion.second << endl;
        for (int i = 0; i < motion.second; i++) {
            rope->move_dir(motion.first);
            print_map(rope, -20, 20, -10, 10);
        }
        cout << endl;
    }

    cout << "Solution 1 : " << distinct_tail_visits << endl;

    return 0;
}