#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
   public:
    Node* parent;
    unordered_map<string, Node*> children;  // Name -> Node=*
    int size = 0;
    string filename;

    bool is_directory = false;

    Node(Node* parent, bool is_directory, string filename, int file_size)
        : parent(parent),
          is_directory(is_directory),
          filename(filename),
          size(file_size) {}

    void add_child(Node* child) { children[child->filename] = child; }

    Node* get_node(string filename) { return children[filename]; }
};

vector<string> tokenize_line(string line) {
    vector<string> parsed_command;
    stringstream ss(line);
    string buffer;

    getline(ss, buffer, ' ');

    if (buffer == "$") {
        getline(ss, buffer, ' ');
        parsed_command.push_back(buffer);

        if (buffer == "cd") {
            getline(ss, buffer, ' ');
            parsed_command.push_back(buffer);
        }
    } else {
        // It lists a directory or file
        if (buffer == "dir") {
            parsed_command.push_back("dir");
            getline(ss, buffer, ' ');
            parsed_command.push_back(buffer);  // filename
        } else {
            parsed_command.push_back("file");
            string file_size = buffer;
            getline(ss, buffer, ' ');  // filename
            parsed_command.push_back(buffer);
            parsed_command.push_back(file_size);
        }
    }

    return parsed_command;
}

void print_node(Node* node, int level = 0) {
    cout << setw(level * 2) << " - ";
    cout << node->filename << " (" << node->size << ")" << endl;
    if (node->is_directory) {
        for (auto child : node->children) {
            print_node((child.second), level + 1);
        }
    }
}

int compute_dir_size(Node* root) {
    if (!root->is_directory) {
        return root->size;
    }

    int sum = 0;
    if (root->is_directory) {
        for (auto child_pair : root->children) {
            Node* node = child_pair.second;
            sum += compute_dir_size(node);
        }
    }

    root->size = sum;

    return sum;
}

void run_program(vector<string> input, Node* root) {
    Node* current = root;

    for (auto line : input) {
        auto tokens = tokenize_line(line);

        // cout << line << endl;

        string command = tokens[0];

        if (command == "ls") {
            // ignore command
        } else if (command == "cd") {
            string to = tokens[1];

            if (to == "..") {
                current = current->parent;
            } else {
                current = current->get_node(to);
            }
        } else if (command == "file") {
            string file_name = tokens[1];
            int file_size = stoi(tokens[2]);

            Node* file_node = new Node(current, false, file_name, file_size);

            current->add_child(file_node);
        } else if (command == "dir") {
            string file_name = tokens[1];
            Node* dir_node = new Node(current, true, file_name, 0);
            current->add_child(dir_node);
        }
    }
}

int find_dir_less_than(Node* root, int max_size) {
    int sum = 0;
    if (root->is_directory) {
        if (root->size <= max_size) {
            sum += root->size;
        }
        for (auto child_pair : root->children) {
            Node* node = child_pair.second;

            sum += find_dir_less_than(node, max_size);
        }
    }

    return sum;
}

int find_min_size_higher_than(Node* root, int min_size) {
    int output = INT_MAX;
    if (root->is_directory) {
        for (auto child_pair : root->children) {
            Node* node = child_pair.second;

            output = min(output, find_min_size_higher_than(node, min_size));
        }

        if (root->size >= min_size) {
            output = min(output, root->size);
        }
    }

    return output;
}

int main() {
    string buffer;
    getline(cin, buffer);  // Ignore first

    vector<string> input;

    while (getline(cin, buffer)) {
        input.push_back(buffer);
    }

    Node root(nullptr, true, "root", 0);
    Node* rootptr = &root;

    run_program(input, &root);
    int root_size = compute_dir_size(rootptr);

    int solution1 = find_dir_less_than(rootptr, 100000);

    cout << "Solution 1 : " << solution1 << endl;

    // Part 2
    int amount_to_delete = root_size + 30000000 - 70000000;
    int solution2 = find_min_size_higher_than(rootptr, amount_to_delete);

    cout << "Amount to delete " << amount_to_delete << endl;
    cout << "Solution 2 : " << solution2 << endl;

    return 0;
}