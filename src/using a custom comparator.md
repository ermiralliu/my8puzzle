// this was the same as hash but whatever

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main() {
    auto customCompare = [](int a, int b) {
        // Custom comparison logic: smaller numbers have higher priority
        return a > b;
    };

    std::priority_queue<int, std::vector<int>, decltype(customCompare)> pq(customCompare);

    pq.push(10);
    pq.push(30);
    pq.push(20);
    pq.push(5);

    std::cout << "Priority queue elements: ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }

    return 0;
}
