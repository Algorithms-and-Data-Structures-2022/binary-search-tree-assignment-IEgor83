#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key,value,root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key,root_);
  }

  void BinarySearchTree::Clear() {
      clear(root_);
      root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    if(find(key,root_) != nullptr){
      return find(key,root_)->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    if (Find(key) != std::nullopt){
      return true;
    }
    return false;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    if(find_min(root_) != nullptr){
      return find_min(root_)->value;
    }
    return std::nullopt;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    if(find_max(root_) != nullptr){
      return find_max(root_)->value;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node == nullptr){
      node = new Node(key,value);
    }
    else if (node->key == key){
      node->value = value;
    }
    else if (node->key > key){
      insert(key,value,node->left);
    }
    else{
      insert(key,value,node->right);
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node == nullptr){
      return false;
    }
    else {
      if (node->key == key) {
        if (node->left != nullptr and node->right != nullptr) {
          Node* f_min = find_min(node->right);
          node->key = f_min->key;
          node->value = f_min->value;
          return remove(f_min->key, node->right);
        }
        else if (node->left != nullptr) {
          Node* new_node = node->left;
          delete node;
          node = new_node;
          return true;
        }
        else {
          Node* new_node = node->right;
          delete node;
          node = new_node;
          return true;
        }
      }
      else if (node->key > key) {
        return remove(key, node->left);
      }
      else if (node->key < key) {
        return remove(key, node->right);
      }
    }
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr){
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr){
      return nullptr;
    }
    else if (node->key == key){
      return node;
    }
    else if (node->key > key){
      return find(key,node->left);
    }
    else if (node->key < key){
      return find(key,node->right);
    }
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if(node != nullptr){
      Node* node_min = node;
      while (node_min->left != nullptr){
        node_min = node_min->left;
      }
      return node_min;
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if(node != nullptr){
      Node* node_max = node;
      while (node_max->right != nullptr){
        node_max = node_max->right;
      }
      return node_max;
    }
    return nullptr;
  }

}  // namespace assignment