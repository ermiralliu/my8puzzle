#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    auto customHash = [](const std::string& key) -> std::size_t {
        std::size_t hash = 0;
        for (char c : key) {
            hash ^= std::hash<char>{}(c) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    };

    std::unordered_set<std::string, decltype(customHash)> mySet(10, customHash);
    mySet.insert("hello");
    mySet.insert("world");

    for (const auto& elem : mySet) {
        std::cout << elem << std::endl;
    }

    return 0;
}
