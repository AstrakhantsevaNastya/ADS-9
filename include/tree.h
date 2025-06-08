// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#pragma once
#include <vector>
#include <memory>

struct PMNode {
    char value;
    std::vector<std::unique_ptr<PMNode>> children;

    PMNode(char val) : value(val) {}
};

class PMTree {
public:
    std::unique_ptr<PMNode> root;

    PMTree(const std::vector<char>& elements);

private:
    std::unique_ptr<PMNode> buildTree(const std::vector<char>& elements);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
