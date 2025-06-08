// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <memory>

class PMTree {
 public:
  struct Node {
    char val;
    std::vector<std::unique_ptr<Node>> children;
    explicit Node(char v) : val(v) {}
  };

  explicit PMTree(const std::vector<char>& elems);
  ~PMTree() = default;

  std::vector<std::vector<char>> getAllPerms() const;
  std::vector<char> getPerm1(int index) const;
  std::vector<char> getPerm2(int index) const;

 private:
  std::unique_ptr<Node> root;
  int total_permutations;

  void buildTree(Node* current, const std::vector<char>& remaining);
  void gatherPermutations(const Node* node, std::vector<char>& path,
                          std::vector<std::vector<char>>& output) const;
  bool findPermutationByTraversal(const Node* node, int& count,
                                  std::vector<char>& output) const;
  bool findPermutationByNavigation(const Node* node, int count,
                                   std::vector<char>& output) const;
  int factorial(int n) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
