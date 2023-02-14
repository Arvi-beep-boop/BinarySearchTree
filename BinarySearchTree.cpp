#include <iostream>
#include "unit_test.h"
#include <vector>
#include <stack>
#define OPT_IMPL 1


class Node {
public:
	int number;
	Node* higher = NULL;
	Node* lower = NULL;

	Node(int value) : number(value)
	{
	}
};

class Tree
{
public:

	Node* core = NULL;
	std::vector<Node*> adj;
	void AppendNumber(int num)
	{

		AppendNumber(num, core);
	}

	int GetDepthOfElement(int num)
	{
#if OPT_IMPL == 0
		return GetDepth(num, core, 0);
#elif OPT_IMPL == 1
		return GetDepthWhile(num);
#endif
	}

	Node* FindTheDeepest(Node* temp)
	{
		if (temp->higher != NULL)
			return FindTheDeepest(temp->higher);
		if (temp->lower != NULL)
			return FindTheDeepest(temp->lower);
		else
			return temp;
	}

	void IterateAllForDelete()
	{
		OnIterateAllForDelete(core);
		core = NULL;
	}

	void DFS()
	{
		DFS(core);
	}

	int GetMaxDepth()
	{
		int maxDepth = 0;
		DepthFirstSearch(core, 0, maxDepth);
		return maxDepth;
	}

private:
	void AppendNumber(int num, Node* temp)
	{
		if (core == NULL)
		{
			core = new Node(num);
		}
		else
		{

			if (num < temp->number)
			{
				if (!temp->lower)
				{
					temp->lower = new Node(num);
				}
				else
				{
					temp = temp->lower;
					AppendNumber(num, temp);
				}
			}
			else
			{
				if (!temp->higher)
				{
					temp->higher = new Node(num);
				}
				else
				{
					temp = temp->higher;
					AppendNumber(num, temp);
				}
			}
		}
	}

	void OnIterateAllForDelete(Node* node)
	{
		if (node->higher != NULL)
		{
			OnIterateAllForDelete(node->higher);
			node->higher = NULL;
		}

		if (node->lower != NULL)
		{
			OnIterateAllForDelete(node->lower);
			node->lower = NULL;
		}

		delete node;
	}

	int GetDepth(int num, Node* temp, int currentDepth) const
	{
		if (temp == NULL)
			return -1;
		if (num == temp->number)
			return currentDepth;
		if (num < temp->number)
			return GetDepth(num, temp->lower, currentDepth + 1);
		else
		{
			return GetDepth(num, temp->higher, currentDepth + 1);
		}

	}
	int GetDepthWhile(int num)
	{
		Node* temp = core;
		int depth = 0;
		while (num != temp->number)
		{
			if (num < temp->number)
			{
				temp = temp->lower;
			}
			else
			{
				temp = temp->higher;
			}
			if (temp == NULL)
				return -1;
			depth++;
		}
		return depth;
	}

	void DFS(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		adj.push_back(node);
		DFS(node->higher);
		DFS(node->lower);
	}

	void DepthFirstSearch(Node* node, int depth, int& maxDepth)
	{
		if (depth > maxDepth)
		{
			maxDepth = depth;
		}
		if (node->higher)
			DepthFirstSearch(node->higher, depth + 1, maxDepth);
		if (node->lower)
			DepthFirstSearch(node->lower, depth + 1, maxDepth);
	}
};

int main()
{
	Tree myTree;
	myTree.AppendNumber(7);
	myTree.AppendNumber(10);
	myTree.AppendNumber(4);
	myTree.AppendNumber(2);
	myTree.AppendNumber(5);
	myTree.AppendNumber(6);
	myTree.DFS();
	for (int i = 0; i < myTree.adj.size(); i++)
	{
		std::cout << "number: " << myTree.adj[i]->number << " with a order number of: " << myTree.GetDepthOfElement(myTree.adj[i]->number) << "\n";
	}
	std::cout << "maxDepth is equal to: " << myTree.GetMaxDepth() << "\n";
	RunAllTests();
	return 0;
}

UNIT_TEST(Tree, add_element)
{
	Tree myTree;
	myTree.AppendNumber(5);
	Assert(myTree.core->number == 5, "core number is different than declared");
}
UNIT_TEST(Tree, add_core_lower_and_higher)
{
	Tree myTree;
	myTree.AppendNumber(3);
	myTree.AppendNumber(1);
	myTree.AppendNumber(5);
	Assert(myTree.core->number == 3, "core number is different than declared");
	Assert(myTree.core->lower->number == 1, "lower number is different than declared");
	Assert(myTree.core->higher->number == 5, "higher number is different than declared");

}

UNIT_TEST(Tree, add_core_lower_and_2_higher)
{
	Tree myTree;
	myTree.AppendNumber(3);
	myTree.AppendNumber(1);
	myTree.AppendNumber(5);
	myTree.AppendNumber(8);
	Assert(myTree.core->number == 3, "core number is different than declared");
	Assert(myTree.core->lower->number == 1, "lower number is different than declared");
	Assert(myTree.core->higher->number == 5, "higher number is different than declared");
	Assert(myTree.core->higher->higher->number == 8, "the highest number is different");

}

UNIT_TEST(Tree, check_depth_core)
{
	Tree myTree;
	myTree.AppendNumber(3);
	Assert(myTree.GetDepthOfElement(3) == 0, "Depth of core is different than 0");
}

UNIT_TEST(Tree, check_depth)
{
	Tree myTree;
	myTree.AppendNumber(8);
	myTree.AppendNumber(3);
	myTree.AppendNumber(20);
	myTree.AppendNumber(2);
	myTree.AppendNumber(5);
	myTree.AppendNumber(9);
	myTree.AppendNumber(30);
	Assert(myTree.GetDepthOfElement(3) == 1, "Depth of 3 is different than 1");
	Assert(myTree.GetDepthOfElement(30) == 2, "Depth of 30 is different than 2");
}
UNIT_TEST(Tree, check_depth_nonexisting_element)
{
	Tree myTree;
	myTree.AppendNumber(8);
	myTree.AppendNumber(3);
	myTree.AppendNumber(20);
	myTree.AppendNumber(2);
	Assert(myTree.GetDepthOfElement(7) == -1, "Depth of non-existing element is different than -1");

}

UNIT_TEST(Tree, find_the_deepest)
{
	Tree myTree;
	myTree.AppendNumber(8);
	myTree.AppendNumber(3);
	myTree.AppendNumber(20);
	myTree.AppendNumber(2);
	myTree.AppendNumber(5);
	myTree.AppendNumber(9);
	myTree.AppendNumber(30);
	Assert(myTree.FindTheDeepest(myTree.core)->number == 30, "Deepest element is different");
}

UNIT_TEST(Tree, doest_delete_work)
{
	Tree myTree;
	myTree.AppendNumber(8);
	myTree.AppendNumber(3);
	myTree.AppendNumber(20);
	myTree.AppendNumber(2);
	myTree.IterateAllForDelete();
	Assert(myTree.core == NULL, "Core is not empty");
}


// ========================================================================
// ========== BELOW CODE IS UNDERSTANDING POINTERS EXERCISE ===============
// ========================================================================


// unique_ptr::unique_ptr(const unique_ptr&)

template<typename T>
class SmartPtr
{
public:
	SmartPtr(T* rawPtr) :m_rawPtr(rawPtr) {}

	/*SmartPtr(const SmartPtr& other)
	{
		m_rawPtr = other.m_rawPtr;
	}*/

	SmartPtr(const SmartPtr& other) = delete;
	SmartPtr(SmartPtr&& other)
	{
		m_rawPtr = other.m_rawPtr;
		other.m_rawPtr = nullptr;
	}

	~SmartPtr()
	{
		if (m_rawPtr != nullptr)
		{
			delete m_rawPtr;
			m_rawPtr = nullptr;
		}
	}

private:
	T* m_rawPtr = nullptr;
};

class MyClass
{
public:
	MyClass(int _v) : m_value(_v) {}
	~MyClass() {}

	int m_value;
};

void DoMagic(std::unique_ptr<MyClass> ptr)
{
	ptr->m_value = 42;
}

UNIT_TEST(TestPointers, new_delete_null)
{
	{
		MyClass* ptr = nullptr;
		Assert(ptr == nullptr, "not null!");

		ptr = new MyClass(5);
		Assert(ptr != nullptr, "is null!");

		delete ptr;
		// from that point, ptr is dangling pointer
		Assert(ptr != nullptr, "is null!");

		ptr = nullptr;
		Assert(ptr == nullptr, "not null!");
	}

	// ================
	// Equivalent in C:

	{
		// MyClass* ptr = nullptr;
		MyClass* ptr = NULL;

		// ptr = new MyClass(5);
		ptr = (MyClass*)malloc(sizeof(MyClass));
		new (ptr) MyClass(5);	// in-place new

		// delete ptr;
		ptr->~MyClass();
		free(ptr);

		//ptr = nullptr;
		ptr = NULL;
	}

	{
		int* ptr = new int(5);
		delete ptr;
		//delete ptr;
	}


	// smart pointers
	{
		std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>(5);

		DoMagic(std::move(ptr));

		//std::unique_ptr<MyClass> ptr2 = ptr;
	}

	{
		std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>(5);

		std::shared_ptr<MyClass> ptr2 = ptr;
	}

	{
		SmartPtr<MyClass> ptr = SmartPtr<MyClass>(new MyClass(5));
	}
}
