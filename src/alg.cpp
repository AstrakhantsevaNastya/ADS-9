// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <memory>
#include <vector>
#include  "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    totalPermutations = 0;
    return;
  }
  totalPermutations = factorial(static_cast<int>(elements.size()));
  root = std::make_unique<Node>('\0');
  for (char ch : elements) {
    root->children.push_back(std::make_unique<Node>(ch));
  }
  for (auto& child : root->children) {
    std::vector<char> rest;
    for (char ch : elements) {
      if (ch != child->value) {
        rest.push_back(ch);
      }
    }
    buildTree(child.get(), rest);
  }
}

void PMTree::buildTree(Node* parent, const std::vector<char>& remaining) {
  if (remaining.empty()) {
    return;
  }
  for (char ch : remaining) {
    parent->children.push_back(std::make_unique<Node>(ch));
    std::vector<char> nextRemaining;
    for (char c : remaining) {
      if (c != ch) {
        nextRemaining.push_back(c);
      }
    }
    buildTree(parent->children.back().get(), nextRemaining);
  }
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
  std::vector<std::vector<char>> output;
  if (!root) return output;
  std::vector<char> currentPath;
  for (const auto& child : root->children) {
    collectPerms(child.get(), currentPath, output);
  }
  return output;
}

void PMTree::collectPerms(const Node* node, std::vector<char>& current,
                         std::vector<std::vector<char>>& output) const {
  current.push_back(node->value);
  if (node->children.empty()) {
    output.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPerms(child.get(), current, output);
    }
  }
  current.pop_back();
}

std::vector<char> PMTree::getPerm1(int num) const {
  if (num < 1 || num > totalPermutations || !root) {
    return {};
  }
  std::vector<char> result;
  int count = num;
  for (const auto& child : root->children) {
    if (getPermByTraversal(child.get(), count, result)) {
      return result;
    }
  }
  return {};
}

bool PMTree::getPermByTraversal(const Node* node, int& remaining,
                               std::vector<char>& result) const {
  result.push_back(node->value);
  if (node->children.empty()) {
    remaining--;
    if (remaining == 0) {
      return true;
    }
  } else {
    for (const auto& child : node->children) {
      if (getPermByTraversal(child.get(), remaining, result)) {
        return true;
      }
    }
  }
  result.pop_back();
  return false;
}

std::vector<char> PMTree::getPerm2(int num) const {
  if (num < 1 || num > totalPermutations || !root) {
    return {};
  }
  std::vector<char> result;
  int remaining = num - 1;
  for (const auto& child : root->children) {
    int permsCount = factorial(static_cast<int>(root->children.size()) - 1);
    if (remaining < permsCount) {
      result.push_back(child->value);
      if (getPermByNavigation(child.get(), remaining, result)) {
        return result;
      }
      break;
    }
    remaining -= permsCount;
  }
  return result;
}

bool PMTree::getPermByNavigation(const Node* node, int remaining,
                                std::vector<char>& result) const {
  if (node->children.empty()) {
    return true;
  }
  int permsCount = factorial(static_cast<int>(node->children.size()) - 1);
  for (const auto& child : node->children) {
    if (remaining < permsCount) {
      result.push_back(child->value);
      return getPermByNavigation(child.get(), remaining, result);
    }
    remaining -= permsCount;
  }
  return false;
}

int PMTree::factorial(int n) const {
  return (n <= 1) ? 1 : n * factorial(n - 1);
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  return tree.getPerm1(num);
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  return tree.getPerm2(num);
}
