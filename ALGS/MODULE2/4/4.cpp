//#include <iostream>
//#include <stack>
//#include <cassert>
//
//using namespace std;
//
//template<class T, class Compare=greater<T>>
//class AVLTree {
//public:
//	AVLTree(const Compare& _cmp = Compare()) : root(nullptr), cmp(_cmp) {}
//	~AVLTree();
//
//	void Add(const T& key);
//
//	void Remove(const T& key);
//
//	void DfsInOrder(void (*visit)(const T& key)) const;
//
//	int FindStatNumber(const T& key) const;
//
//	T& FindKeyByStat(int stat) const;
//
//private:
//	struct Node // структура для представления узлов дерева
//	{
//		T Key;
//		int Height;
//		int Children;
//		Node* Left;
//		Node* Right;
//		Node(const T& k) : Key(k), Left(nullptr), Right(nullptr), Height(1), Children(1) {}
//	};
//
//	Node* root;
//	Compare cmp;
//
//	void dfsInOrder(void (*visit)(const T& key), Node* node) const;
//
//	int findStatNumber(const T& key, Node* node) const {
//		if (!node)
//			assert(false);
//		Node* currNode = node;
//		int stat = children(currNode->Left) + 1;
//		int parentStat = 0;
//		int currStat = stat;
//		while (currNode != nullptr) {
//			if (currNode->Key == key)
//				return stat;
//			if (cmp(key, currNode->Key)) {
//				//parentStat does not change
//				currNode = currNode->Left;
//				currStat = children(currNode->Left) + 1;
//				stat = parentStat + currStat;
//			} else {
//				parentStat += currStat;
//				currNode = currNode->Right;
//				currStat = children(currNode->Left) + 1;
//				stat = parentStat + currStat;
//			}
//		}
//		assert(false);
//	}
//
//	T& findKeyByStat(int stat, Node* node) const {
//		Node* currNode = node;
//		while (currNode != nullptr) {
//			int childrenL = children(currNode->Left);
//			if (childrenL == stat)
//				return currNode->Key;
//			currNode = childrenL > stat ? currNode->Left : currNode->Right;
//			if (childrenL < stat)
//				stat -= childrenL + 1;
//		}
//		assert(false);
//	}
//
//	Node* add(const T& k, Node* p) {
//		if (!p) return new Node(k);
//		if (cmp(k, p->Key))
//			p->Left = add(k, p->Left);
//		else
//			p->Right = add(k, p->Right);
//		balance(p);
//		return p;
//	}
//
//	Node* findMin(Node* p) const
//	{
//		return p->Left ? findMin(p->Left) : p;
//	}
//
//	Node* findAndRemoveMin(Node* p, Node*& min, Node* minParent=nullptr)
//	{
//		if (!p->Left) {
//			Node* right = p->Right;
//			p->Right = nullptr;
//			min = p;
//			return right;
//		}
//		p->Left = findAndRemoveMin(p->Left, min, p);
//		balance(p);
//		return p;
//	}
//
//	void remove(Node*& p, const int& k)
//	{
//		int leftCounts = children(p->Left);
//		if (leftCounts >= k)
//			remove(p->Left, k);
//		else if (leftCounts + 1 < k)
//			remove(p->Right, k - leftCounts - 1);
//		else
//		{
//			Node* q = p->Left;
//			Node* r = p->Right;
//			delete p;
//			if (!r) {
//				p = q;
//				return;
//			}
//			Node* min; 
//			findAndRemoveMin(r, min);
//			min->Right = r;
//			min->Left = q;
//			p = min;
//		}
//		balance(p);
//	}
//
//	/*Node* remove(const T& k, Node* p) {
//		if (!p) return nullptr;
//		if (cmp(k, p->Key))
//			p->Left = remove(k, p->Left);
//		else if (!cmp(k, p->Key) && k != p->Key)
//			p->Right = remove(k, p->Right);
//		else {
//			Node* q = p->Left;
//			Node* r = p->Right;
//			delete p;
//			if (!r) return q;
//			Node* min = r;
//			Node* minParent = nullptr;
//			while (min->Left) {
//				minParent = min;
//				min = min->Left;
//			}
//			if (minParent) {
//				minParent->Left = min->Right;
//				min->Right = balance(r);
//			}
//			min->Left = q;
//			return balance(min);
//		}
//		return balance(p);
//	}*/
//
//	int height(Node* p) const {
//		return p ? p->Height : 0;
//	}
//
//	int children(Node* p) const {
//		return p ? p->Children : 0;
//	}
//
//	int bFactor(Node* p) const {
//		return height(p->Right) - height(p->Left);
//	}
//
//	void fixHeightAndChildren(Node*& p) {
//		int hl = height(p->Left);
//		int hr = height(p->Right);
//		int childrenL = children(p->Left);
//		int childrenR = children(p->Right);
//		p->Height = (hl > hr ? hl : hr) + 1;
//		p->Children = childrenL + childrenR + 1;
//	}
//
//	Node* rotateRight(Node*& p) {
//		Node* q = p->Left;
//		p->Left = q->Right;
//		q->Right = p;
//		fixHeightAndChildren(p);
//		fixHeightAndChildren(q);
//		return q;
//	}
//
//	Node* rotateLeft(Node*& q) {
//		Node* p = q->Right;
//		q->Right = p->Left;
//		p->Left = q;
//		fixHeightAndChildren(q);
//		fixHeightAndChildren(p);
//		return p;
//	}
//
//	void balance(Node*& p) // балансировка узла p
//	{
//		fixHeightAndChildren(p);
//		if (bFactor(p) == 2)
//		{
//			if (bFactor(p->Right) < 0)
//				p->Right = rotateRight(p->Right);
//			return rotateLeft(p);
//		}
//		if (bFactor(p) == -2)
//		{
//			if (bFactor(p->Left) > 0)
//				p->Left = rotateLeft(p->Left);
//			return rotateRight(p);
//		}
//		// return p; // балансировка не нужна
//	}
//};
//
//template<class T, class Compare>
//AVLTree<T, Compare>::~AVLTree() {
	//if (root == nullptr)
	//	return;

	//stack<Node*> nodeStack;
	//nodeStack.push(root);

	//while (!nodeStack.empty()) {
	//	Node* currNode = nodeStack.top();
	//	nodeStack.pop();
	//	if (currNode->Left)
	//		nodeStack.push(currNode->Left);
	//	if (currNode->Right)
	//		nodeStack.push(currNode->Right);
	//	delete currNode;
	//}
//}
//
//template<class T, class Compare>
//void AVLTree<T, Compare>::Add(const T& key) {
//	root = add(key, root);
//}
//
//template<class T, class Compare>
//void AVLTree<T, Compare>::Remove(const T& key) {
//	if (root == nullptr)
//		assert(false);
//	remove(root, key);
//}
//
//template<class T, class Compare>
//int AVLTree<T, Compare>::FindStatNumber(const T& key) const {
//	if (root == nullptr)
//		assert(false);
//	return findStatNumber(key, root);
//}
//
//template<class T, class Compare>
//void AVLTree<T, Compare>::DfsInOrder(void (*visit)(const T& key)) const {
//	if (root == nullptr)
//		return;
//	dfsInOrder(visit, root);
//}
//
//template<class T, class Compare>
//void AVLTree<T, Compare>::dfsInOrder(void (*visit)(const T& key), Node* node) const {
//	if (node == nullptr)
//		return;
//	dfsInOrder(visit, node->Left);
//	visit(node->Key);
//	int statNumber = FindStatNumber(node->Key) - 1;
//	cout << statNumber << ' ' << FindKeyByStat(statNumber) << endl;
//	dfsInOrder(visit, node->Right);
//}
//
//template<class T, class Compare>
//T& AVLTree<T, Compare>::FindKeyByStat(int stat) const {
//	if (root == nullptr)
//		assert(false);
//	return findKeyByStat(stat, root);
//}
//
//int main() {
//	int n;
//	cin >> n;
//	AVLTree<int> tree;
//	for (int i = 0; i < n; ++i) {
//		int val, move;
//		cin >> move >> val;
//		switch (move) {
//			case 1:
//				tree.Add(val);
//				cout << tree.FindStatNumber(val) - 1 << endl;
//				break;
//			case 2:
//				tree.Remove(val + 1);
//				break;
//			default:
//				break;
//		}
//		//tree.DfsInOrder([](const int& key) { std::cout << key << " "; });
//	}
//	return 0;
//}
//
////12
////1 6
////1 5
////1 4
////2 2
////1 3
////1 2
////2 1
////1 1
////2 3
////2 1
////2 1
////2 0
//
//11
//1 20
//1 8
//1 6
//1 19
//1 7
//1 40
//1 30
//1 45
//1 60
//2 8
//1 30
//
//
////14
////1 8
////1 20
////1 40
////1 19
////1 30
////1 6
////1 7
////2 6
////2 3
////2 4
////2 1
////2 0
////2 1
////2 0