#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <stdexcept> // For exceptions like std::invalid_argument

#include "Services/SolverService.hpp"

// in the end i set the bottom two within solver service
// bad design but whatever
// constexpr uint ROW_SIZE = 4;
// constexpr uint SIZE = ROW_SIZE*ROW_SIZE;

using byte = unsigned char;

int main(int argc, char* argv[]) {
    std::cout << "hello world" << std::endl;

    // For each command-line argument
    for (int i = 1; i < argc; ++i) { // Start from index 1 (argv[0] is the program name)
        std::string filename = argv[i];
        std::cout << filename << std::endl;

        // std::vector<unsigned char> tiles;
        std::array<byte, N*N> tiles;
        int n = -1;

        try {
            std::ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                throw std::runtime_error("Could not open file: " + filename);
            }

            inputFile >> n;
            if (n <= 0) {
                throw std::invalid_argument("Invalid board size n");
            }
            // tiles.resize(n * n);
            for (int j = 0; j < n * n; ++j) {
                int tileValue;
                inputFile >> tileValue;
                if (tileValue < 0 || tileValue > 255) {
                    throw std::invalid_argument("Tile value out of range");
                }
                tiles[j] = static_cast<unsigned char>(tileValue);
            }
            inputFile.close();
        } catch (const std::exception& e) {
            std::cerr << "Error reading file: " << e.what() << std::endl;
            continue; // Skip to the next file
        }

        // Solve the slider puzzle
        auto initial = Board::make_init_board(tiles);
        if (!initial.isSolvable()) {
            std::cout << "No solution possible\n" << std::endl;
        } else {
            Solver solver = Solver(initial);

            auto startTime = std::chrono::high_resolution_clock::now();
            auto boards = solver.solution();
            auto endTime = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

            std::cout << "Minimum number of moves = " << solver.getMoves() << "\n" << std::endl;
            std::cout << "Time elapsed: " << elapsed << " ms" << std::endl;
        }
    }

    return 0;
}