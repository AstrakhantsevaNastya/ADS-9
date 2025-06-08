// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> inputChars = {'1', '2', '3'};
  PMTree tree(inputChars);

  auto allPermutations = tree.getAllPerms();
  std::cout << "All permutations:\n";
  for (const auto& perm : allPermutations) {
    for (char ch : perm) {
      std::cout << ch;
    }
    std::cout << '\n';
  }

  std::cout << "\nSelected permutations:\n";
  std::cout << "Permutation #1: ";
  auto firstPerm = tree.getPerm1(1);
  for (char ch : firstPerm) std::cout << ch;
  std::cout << '\n';

  std::cout << "Permutation #2: ";
  auto secondPerm = tree.getPerm2(2);
  for (char ch : secondPerm) std::cout << ch;
  std::cout << '\n';

  return 0;
}
