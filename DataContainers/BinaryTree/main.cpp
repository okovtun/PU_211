#include<iostream>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------\n"

//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}
	~Tree()
	{
		clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void print(int depth)const
	{
		print(Root, depth);
		cout << endl;
	}
	void true_print()const
	{
		true_print(Root, depth());
		cout << endl;
	}

private:
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf()/*Root->pLeft == Root->pRight*/)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	//					Methods:
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
		//return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}

	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
		/*else return
			depth(Root->pLeft) > depth(Root->pRight) ?
			depth(Root->pLeft) + 1 :
			depth(Root->pRight) + 1;*/
			//if (depth(Root->pLeft) > depth(Root->pRight))return depth(Root->pLeft) + 1;
			//else return depth(Root->pRight) + 1;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
	void print(Element* Root, int depth)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft, depth - 1);
		if (depth == 0)cout << Root->Data << tab;
		print(Root->pRight, depth - 1);
	}
	void true_print(Element* Root, int depth)const
	{
		if (depth == -1)return;
		true_print(Root, depth - 1);
		print(Root, depth);
		cout << endl;
		cout << endl;
		cout << endl;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template<typename T>
void measure(const char description[], const Tree& tree, T(Tree::*member_function)()const)
{
	cout << description;
	clock_t t_start = clock();
	cout << (tree.*member_function)();
	clock_t t_end = clock();
	cout << " ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ������.\n";
}

//#define BASE_CHECK
#define DEPTH_CHECK
//#define PREFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "����� ��������� � ������: " << tree.sum() << endl;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "����������� �������� � ������: " << tree.minValue() << endl;
	cout << "������������ �������� � ������:" << tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << tree.count() << endl;
	cout << "����� ��������� � ������: " << tree.sum() << endl;
	cout << "������� ������: " << tree.depth() << endl;

	int value;
	cout << "������� ��������� ��������: "; cin >> value;
	tree.erase(value);
	tree.print();

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������:" << u_tree.maxValue() << endl;
	cout << "���������� ��������� � ������: " << u_tree.count() << endl;
	cout << "����� ��������� � ������: " << u_tree.sum() << endl;
	cout << "������� ������: " << u_tree.depth() << endl;
#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 80 };
	//tree.~Tree();
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;

	//tree.print(3);
	tree.true_print();

	//int value;
	//cout << "������� ��������� ��������: "; cin >> value;
	//tree.erase(value);
	//tree.print();
#endif // DEPTH_CHECK

#ifdef PREFORMANCE_CHECK
	clock_t t_start, t_end;
	int n;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	t_start = clock();	//������� 'clock()' ���������� ���������� ������ CPU
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	t_end = clock();
	cout << "������ ��������� �� " << double(t_end - t_start) / CLOCKS_PER_SEC << " ���.\n";
	//tree.print();

	measure("����������� �������� � ������:\t", tree, &Tree::minValue);
	measure("������������ �������� � ������:\t", tree, &Tree::maxValue);
	measure("����� ��������� ������:\t\t", tree, &Tree::sum);
	measure("���������� ��������� ������:\t", tree, &Tree::count);
	measure("�������-�������������� ��������� ������:\t", tree, &Tree::avg);
	measure("������� ������:\t\t\t", tree, &Tree::depth);

	/*t_start = clock();
	cout << "����������� �������� � ������: " << tree.minValue() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;

	t_start = clock();
	cout << "������������ �������� � ������:" << tree.maxValue() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;

	t_start = clock();
	cout << "���������� ��������� � ������: " << tree.count() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;

	t_start = clock();
	cout << "����� ��������� � ������:\t" << tree.sum() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;

	t_start = clock();
	cout << "�������-�������������� ��������� � ������: " << tree.avg() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;

	t_start = clock();
	cout << "������� ������: " << tree.depth() << tab;
	t_end = clock();
	cout << double(t_end - t_start) / CLOCKS_PER_SEC << " ���." << endl;*/
#endif // PREFORMANCE_CHECK

}