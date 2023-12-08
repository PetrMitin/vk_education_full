/*
В одной военной части решили построить в одну шеренгу по росту.
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и
вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в
процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые
высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который
заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит
в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого
приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Требуемая скорость выполнения команды - O(log n).
*/

#include <iostream>
#include <cassert>
#include <string>
#include <stack>

template<class T, class Compare=std::greater<T>>
class AVLTree {

public:
	AVLTree(const Compare& _cmp=Compare());
	~AVLTree();

	int Insert(const T& key);
	void Remove(const T& key);

private:

	struct Node {
		T Key;
		unsigned int Height;
		unsigned int Counts;
		Node* Left;
		Node* Right;
		Node(T k) : Key(k), Left(nullptr), Right(nullptr), Height(1), Counts(1) {}
	};

	Compare cmp;
	Node* root;

	unsigned int counts(Node* p) const;
	int bfactor(Node* p) const;
	void fixHeight(Node*& p);
	void fixCounts(Node*& p);

	void rotateRight(Node*& p) {
		Node* q = p->Left;
		p->Left = q->Right;
		q->Right = p;
		fixHeight(p);
		fixHeight(q);
		fixCounts(p);
		fixCounts(q);
		p = q;
	}

	void rotateLeft(Node*& q) {
		Node* p = q->Right;
		q->Right = p->Left;
		p->Left = q;
		fixHeight(q);
		fixHeight(p);
		fixCounts(q);
		fixCounts(p);
		q = p;
	}

	void balance(Node*& p) {
		fixHeight(p);
		fixCounts(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->Right) < 0)
				rotateRight(p->Right);
			return rotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->Left) > 0)
				rotateLeft(p->Left);
			return rotateRight(p);
		}
	}

	int insert(Node*& p, const T& k, const int& s) {
		if (!p) {
			p = new Node(k);
			return s;
		}
		int ind;
		if (cmp(k, p->Key))
			ind = insert(p->Left, k, s);
		else
			ind = insert(p->Right, k, s + p->Counts - counts(p->Right));
		balance(p);
		return ind;
	}

	Node* findAndRemoveMin(Node* p, Node*& min) {
		if (p->Left == 0) {
			Node* right = p->Right;
			min = p;
			return right;
		}
		p->Left = findAndRemoveMin(p->Left, min);
		balance(p);
		return p;
	}

	void remove(Node*& p, const int& k) {
		int leftCounts = counts(p->Left);
		if (leftCounts >= k)
			remove(p->Left, k);
		else if (leftCounts + 1 < k)
			remove(p->Right, k - leftCounts - 1);
		else
		{
			Node* q = p->Left;
			Node* r = p->Right;
			delete p;
			if (!r) {
				p = q;
				return;
			}
			Node* min;
			min->Right = findAndRemoveMin(r, min);
			min->Left = q;
			p = min;
		}
		balance(p);
	}

	void deleteNode(Node*& p) {
		if (!p) {
			return;
		}
		deleteNode(p->Left);
		deleteNode(p->Right);
		delete p;
	}

	unsigned int height(Node* p) const {
		return p ? p->Height : 0;
	}
};

template<class T, class Compare>
AVLTree<T, Compare>::AVLTree(const Compare& _cmp) : root(nullptr), cmp(_cmp) {}

template<class T, class Compare>
AVLTree<T, Compare>::~AVLTree() {
	if (root == nullptr)
		return;

	std::stack<Node*> nodeStack;
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
unsigned int AVLTree<T, Compare>::counts(Node* p) const {
	return p ? p->Counts : 0;
}

template<class T, class Compare>
int AVLTree<T, Compare>::bfactor(Node* p) const
{
	return height(p->Right) - height(p->Left);
}

template<class T, class Compare>
void AVLTree<T, Compare>::fixHeight(Node*& p)
{
	unsigned int hl = height(p->Left);
	unsigned int hr = height(p->Right);
	p->Height = (hl > hr ? hl : hr) + 1;
}

template<class T, class Compare>
void AVLTree<T, Compare>::fixCounts(Node*& p) {
	p->Counts = counts(p->Left) + counts(p->Right) + 1;
}

template<class T, class Compare>
int AVLTree<T, Compare>::Insert(const T& key) {
	return insert(root, key, 0);
}

template<class T, class Compare>
void AVLTree<T, Compare>::Remove(const T& key) {
	remove(root, key);
}

int main() {
	AVLTree<int> tree;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int operation, a;
		std::cin >> operation >> a;
		switch (operation) {
		case 1:
			std::cout << tree.Insert(a) << '\n';
			break;
		case 2:
			tree.Remove(a + 1);
			break;
		default:
			assert(false);
		}
	}
}