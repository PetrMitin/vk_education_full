#include <iostream>
#include <stack>

using namespace std;

template<class T, class Compare = less<T>>
class BinaryTree {
public:
	BinaryTree(const Compare& _cmp = Compare()) : root(nullptr), cmp(_cmp) {}
	~BinaryTree();

	void Add(const T& key);

	bool Has(const T& key) const;

	void Delete(const T& key);

	void DfsPreOrder(void (*visit)(const T& key)) const;

	int ShortestDistanceToNode() const;

private:
	struct Node {
		T Key;
		Node* Left;
		Node* Right;
		Node(const T& key) : Key(key), Left(nullptr), Right(nullptr) {}
	};
	Node* root;
	Compare cmp;

	int shortestDistanceToNode(Node* node) const {
		if (!node->Right && !node->Left)
			return 1;

		if ()
		return std::min(shortestDistanceToNode(node->Left), shortestDistanceToNode(node->Right)) + 1;
	}
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
	if (root == nullptr)
		return;

	stack<Node*> nodeStack;
	nodeStack.push(root);

	while (!nodeStack.empty()) {
		Node* currNode = nodeStack.top();
		nodeStack.pop();
		if (currNode->Left)
			nodeStack.push(currNode->Left);
		if (currNode->Right)
			nodeStack.push(currNode->Right);
		delete currNode;
	}
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T& key) {
	Node* newNode = new Node(key);
	if (root == nullptr)
		root = newNode;
	else {
		Node* currentNode = root;
		Node* parent = nullptr;
		while (currentNode) {
			parent = currentNode;
			if (cmp(key, currentNode->Key))
				currentNode = currentNode->Left;
			else
				currentNode = currentNode->Right;
		}
		if (cmp(key, parent->Key))
			parent->Left = newNode;
		else
			parent->Right = newNode;
	}
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T& key) const {
	if (root == nullptr)
		return false;
	else {
		Node* currentNode = root;
		while (currentNode && currentNode->Key != key) {
			if (cmp(key, currentNode->Key))
				currentNode = currentNode->Left;
			else
				currentNode = currentNode->Right;
		}
		if (!currentNode)
			return false;
		return true;
	}
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Delete(const T& key) {
	Node* curr = root;
	Node* prev = nullptr;
	while (curr != nullptr && curr->Key != key) {
		prev = curr;
		if (cmp(key, curr->Key))
			curr = curr->Left;
		else
			curr = curr->Right;
	}

	if (curr == nullptr)
		return;
	if (curr->Left == nullptr || curr->Right == nullptr) {
		Node* newCurr;
		if (curr->Left == nullptr)
			newCurr = curr->Right;
		else
			newCurr = curr->Left;
		if (prev == nullptr)
			root = newCurr;
		if (curr == prev->Left)
			prev->Left = newCurr;
		else
			prev->Right = newCurr;
	}

	delete curr;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::DfsPreOrder(void (*visit)(const T& key)) const {
	if (root == nullptr)
		return;

	stack<Node*> nodeStack;
	nodeStack.push(root);

	while (!nodeStack.empty()) {
		Node* node = nodeStack.top();
		visit(node->Key);
		nodeStack.pop();
		if (node->Right)
			nodeStack.push(node->Right);
		if (node->Left)
			nodeStack.push(node->Left);
	}
}

template<class T, class Compare>
int BinaryTree<T, Compare>::ShortestDistanceToNode() const {
	return shortestDistanceToNode(root);
}

int main() {
	BinaryTree<int> tree;
	int val = 0;
	while (cin >> val) {
		tree.Add(val);
	}
	cout << tree.ShortestDistanceToNode();
	return 0;
}