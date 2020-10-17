#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

fstream fin("tst.in");
ofstream fout("tst.out");

class Vertex_Tree {
public:
	long long Key;
	Vertex_Tree* Left;
	Vertex_Tree* Right;
	Vertex_Tree* Parent;
	long long Height;
	long long Number_of_leaves;
	long long MSL_Vertex;
	long long b_v;
	long long a_v;
	Vertex_Tree(long long value_Key) {
		Key = value_Key;
		Parent = nullptr;
		Left = nullptr;
		Right = nullptr;
		Height = 0;
		Number_of_leaves = 1;
		MSL_Vertex = 0;
		b_v = 0;
		a_v = 0;
	}
};

long long max_vertexMST = 0;

class Bst {
public:
	Vertex_Tree* Root;
	Bst()
		:Root(0)
	{
	}

	void Insert(long long value) {
		Vertex_Tree** cur = &Root;
		while (*cur) {
			Vertex_Tree& node = **cur;
			if (value < node.Key) {
				cur = &node.Left;
			}
			else if (value > node.Key) {
				cur = &node.Right;
			}
			else {
				return;
			}
		}
		*cur = new Vertex_Tree(value);
	}

	Vertex_Tree FindMin(Vertex_Tree x) {
		if (x.Left != nullptr) {
			return FindMin(*x.Left);
		}
		else {
			return x;
		}
	}

	Vertex_Tree Delete(Vertex_Tree* temp_obj, long long key_value) {
		if (!temp_obj) {
			return NULL;
		}
		if (key_value < temp_obj->Key) {
			*temp_obj->Left = Delete(temp_obj->Left, key_value);
			return *temp_obj;
		}
		else if (key_value > temp_obj->Key) {
			*temp_obj->Right = Delete(temp_obj->Right, key_value);
			return *temp_obj;
		}

		if (temp_obj->Left == NULL && temp_obj->Right == NULL) {
			return NULL;
		}

		if (temp_obj->Left == NULL) {
			return *temp_obj->Right;
		}
		else if (temp_obj->Right == NULL) {
			return *temp_obj->Left;
		}

		else {
			int min_key = FindMin(*temp_obj->Right).Key;
			temp_obj->Key = min_key;
			*temp_obj->Right = Delete(temp_obj->Right, min_key);
			return *temp_obj;
		}
	}

	void Show_Bst(Vertex_Tree* Root) {
		if (Root) {
			if (Root->Key != 0) {
				fout << Root->Key << endl;
			}
			Show_Bst(Root->Left);
			Show_Bst(Root->Right);
		}
	}

	void Set_HeightNLeaves(Vertex_Tree* Root) {
		if (Root) {
			Set_HeightNLeaves(Root->Right);
			Set_HeightNLeaves(Root->Left);
			int count_MSL = 0;
			if (Root->Left == NULL && Root->Right == NULL) {
				Root->Height = 0;
				Root->Number_of_leaves = 1;
				count_MSL = 0;
			}
			if (Root->Left == NULL && Root->Right != NULL) {
				Root->Height = Root->Right->Height + 1;
				Root->Number_of_leaves = Root->Right->Number_of_leaves;
				count_MSL = Root->Right->Height + 1;
			}
			if (Root->Left != NULL && Root->Right == NULL) {
				Root->Height = Root->Left->Height + 1;
				Root->Number_of_leaves = Root->Left->Number_of_leaves;
				count_MSL = Root->Left->Height + 1;
			}
			if (Root->Left != NULL && Root->Right != NULL) {
				Root->Height = max(Root->Left->Height, Root->Right->Height) + 1;
				count_MSL = Root->Left->Height + Root->Right->Height + 2;
				if (Root->Left->Height == Root->Right->Height) {
					Root->Number_of_leaves = Root->Left->Number_of_leaves + Root->Right->Number_of_leaves;
				}
				if (Root->Left->Height > Root->Right->Height) {
					Root->Number_of_leaves = Root->Left->Number_of_leaves;
				}
				if(Root->Right->Height > Root->Left->Height) {
					Root->Number_of_leaves = Root->Right->Number_of_leaves;
				}
			}
			Root->MSL_Vertex = count_MSL;
			if (max_vertexMST < count_MSL) {
				max_vertexMST = count_MSL;
			}
		}
	}

	
	void Different_path_vertex(Vertex_Tree* Root, Bst* mytree, set <long long>& arr) {
		if (Root) {
			if (Root->MSL_Vertex != max_vertexMST) {
				Root->b_v = 0;
			}
			else {
				if (Root->Left != NULL && Root->Right != NULL) {
					Root->b_v = Root->Left->Number_of_leaves * Root->Right->Number_of_leaves;
				}
				if (Root->Left == NULL && Root->Right != NULL) {
					Root->b_v = Root->Right->Number_of_leaves;
				}
				if (Root->Left != NULL && Root->Right == NULL) {
					Root->b_v = Root->Left->Number_of_leaves;
				}
			}
			if (Root->Key == mytree->Root->Key) {
				Root->a_v = 0;
			}
			if (Root->Left != NULL && Root->Right == NULL) {
				Root->Left->a_v = Root->a_v + Root->b_v;
			}
			if (Root->Left == NULL && Root->Right != NULL) {
				Root->Right->a_v = Root->a_v + Root->b_v;
			}
			if (Root->Left != NULL && Root->Right != NULL) {
				if (Root->Left->Height > Root->Right->Height) {
					Root->Left->a_v = Root->a_v + Root->b_v;
					Root->Right->a_v = Root->b_v;
				}
				if (Root->Right->Height > Root->Left->Height) {
					Root->Right->a_v = Root->a_v + Root->b_v;
					Root->Left->a_v = Root->b_v;
				}
				if (Root->Left->Height == Root->Right->Height) {
					Root->Left->a_v = Root->b_v + Root->Left->Number_of_leaves * (Root->a_v / Root->Number_of_leaves);
					Root->Right->a_v = Root->b_v + Root->Right->Number_of_leaves * (Root->a_v / Root->Number_of_leaves);
				}
			}
			int temp = Root->a_v + Root->b_v;
			if (temp % 2 != 0) {
				arr.insert(Root->Key);
			}
			Different_path_vertex(Root->Left, mytree, arr);
			Different_path_vertex(Root->Right, mytree, arr);
		}
	}
};

int main() {
	string s;
	Bst my_tree;
	long long max = LLONG_MIN;
	set <long long> cont;
	set <long long> iterator;
	while (getline(fin, s)) {
		my_tree.Insert(atoi(s.c_str()));
	}
	my_tree.Set_HeightNLeaves(my_tree.Root);
	my_tree.Different_path_vertex(my_tree.Root, &my_tree, cont);
	if (cont.size() != 0) {
		for (auto i : cont) {
			if (i > max) {
				max = i;
			}
		}
		*my_tree.Root = my_tree.Delete(my_tree.Root, max);
	}
	my_tree.Show_Bst(my_tree.Root);
}
