//#include <iostream>
//#include <stack>
//
//using namespace std;
//
//template<class T, class Compare = less<T>>
//class BinaryTree {
//public:
//	BinaryTree(const Compare& _cmp = Compare()) : root(nullptr), cmp(_cmp) {}
//	~BinaryTree();
//
//	void Add(const T& key);
//
//	bool Has(const T& key) const;
//
//	void Delete(const T& key);
//
//	void CheckIfValuesAreSame(const T& initialValue, bool& result) const;
//
//private:
//	struct Node {
//		T Key;
//		Node* Left;
//		Node* Right;
//		Node(const T& key) : Key(key), Left(nullptr), Right(nullptr) {}
//	};
//	Node* root;
//	Compare cmp;
//};
//
//template<class T, class Compare>
//BinaryTree<T, Compare>::~BinaryTree() {
//	if (root == nullptr)
//		return;
//
//	stack<Node*> nodeStack;
//	nodeStack.push(root);
//
//	while (!nodeStack.empty()) {
//		Node* currNode = nodeStack.top();
//		nodeStack.pop();
//		if (currNode->Left)
//			nodeStack.push(currNode->Left);
//		if (currNode->Right)
//			nodeStack.push(currNode->Right);
//		delete currNode;
//	}
//}
//
//template<class T, class Compare>
//void BinaryTree<T, Compare>::Add(const T& key) {
//	Node* newNode = new Node(key);
//	if (root == nullptr)
//		root = newNode;
//	else {
//		Node* currentNode = root;
//		Node* parent = nullptr;
//		while (currentNode) {
//			parent = currentNode;
//			if (cmp(key, currentNode->Key))
//				currentNode = currentNode->Left;
//			else
//				currentNode = currentNode->Right;
//		}
//		if (cmp(key, parent->Key))
//			parent->Left = newNode;
//		else
//			parent->Right = newNode;
//	}
//}
//
//template<class T, class Compare>
//bool BinaryTree<T, Compare>::Has(const T& key) const {
//	if (root == nullptr)
//		return false;
//	else {
//		Node* currentNode = root;
//		while (currentNode && currentNode->Key != key) {
//			if (cmp(key, currentNode->Key))
//				currentNode = currentNode->Left;
//			else
//				currentNode = currentNode->Right;
//		}
//		if (!currentNode)
//			return false;
//		return true;
//	}
//}
//
//template<class T, class Compare>
//void BinaryTree<T, Compare>::Delete(const T& key) {
//	Node* curr = root;
//	Node* prev = nullptr;
//	while (curr != nullptr && curr->Key != key) {
//		prev = curr;
//		if (cmp(key, curr->Key))
//			curr = curr->Left;
//		else
//			curr = curr->Right;
//	}
//
//	if (curr == nullptr)
//		return;
//	if (curr->Left == nullptr || curr->Right == nullptr) {
//		Node* newCurr;
//		if (curr->Left == nullptr)
//			newCurr = curr->Right;
//		else
//			newCurr = curr->Left;
//		if (prev == nullptr)
//			root = newCurr;
//		if (curr == prev->Left)
//			prev->Left = newCurr;
//		else
//			prev->Right = newCurr;
//	}
//
//	delete curr;
//}
//
//template<class T, class Compare>
//void BinaryTree<T, Compare>::CheckIfValuesAreSame(const T& initialValue, bool& result) const {
//	if (root == nullptr)
//		return;
//
//	stack<Node*> nodeStack;
//	nodeStack.push(root);
//
//	while (!nodeStack.empty()) {
//		Node* node = nodeStack.top();
//		if (node->Key != initialValue)
//			result = false;
//		nodeStack.pop();
//		if (node->Right)
//			nodeStack.push(node->Right);
//		if (node->Left)
//			nodeStack.push(node->Left);
//	}
//}
//
//void areValuesSame(const int& key, int& initialValue, bool& result) {
//	if (key != initialValue)
//		result = false;
//}
//
//int main() {
//	BinaryTree<int> tree;
//	int val;
//	while (cin >> val) {
//		tree.Add(val);
//	}
//	bool res = true;
//	tree.CheckIfValuesAreSame(val, res);
//	cout << res;
//	return 0;
//}
#include <iostream>
#include <unordered_map>

template<typename T1, typename T2>
struct Node
{
    T1 x;
    T2 y;

    // конструктор
    Node(T1 x, T2 y)
    {
        this->x = x;
        this->y = y;
    }

    // `operator==` требуется для сравнения ключей в случае коллизии хэшей
    bool operator==(const Node& p) const {
        return x == p.x && y == p.y;
    }
};

// Специализированная хеш-функция для ключей `unordered_map`
struct hash_fn
{
    template <class T1, class T2>
    std::size_t operator() (const Node<T1, T2>& node) const
    {
        std::size_t h1 = std::hash<T1>()(node.x);
        std::size_t h2 = std::hash<T2>()(node.y);

        return h1 ^ h2;
    }
};

int main()
{
    std::unordered_map<Node<std::string, std::string>, hash_fn> u_map =
    {
        {{"C", "C99"}, 1999},
        {{"C", "C11"}, 2011},
        {{"C++", "C++14"}, 2014},
        {{"C++", "C++17"}, 2017},
        {{"Java", "Java SE 8"}, 2014},
        {{"Java", "Java SE 9"}, 2017}
    };

    for (const auto& entry : u_map)
    {
        std::cout << "{" << entry.first.x << "," << entry.first.y << "}: "
            << entry.second << std::endl;
    }

    return 0;
}