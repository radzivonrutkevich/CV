#include <fstream>
#include <string>
using namespace std;

fstream fin("input.txt");
ofstream fout("output.txt");

class Vertex_Tree {
public:
	int Key;
	Vertex_Tree* Left;
	Vertex_Tree* Right;
	Vertex_Tree(int value_Key) {
		Key = value_Key;
		Left = nullptr;
		Right = nullptr;
	}
};

class Bst {
public:
	Vertex_Tree* Root;
	Bst()
		:Root(0)
	{
	}

	void Insert(int value) {
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

	Vertex_Tree Delete(Vertex_Tree* temp_obj, int key_value) {
		if (temp_obj == NULL) {
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
};

int main() {
	int delete_key = 0;
	int temp_counter = 0; 
	string s;
	Bst my_tree;
	getline(fin, s);
	delete_key = atoi(s.c_str());
	getline(fin, s);
	while (getline(fin, s)) {
		my_tree.Insert(atoi(s.c_str()));
		if (delete_key == atoi(s.c_str())) {
			temp_counter++;
		}
	}
	if (temp_counter != 0) {
		*my_tree.Root = my_tree.Delete(my_tree.Root, delete_key);
		my_tree.Show_Bst(my_tree.Root);
	}
	else {
		my_tree.Show_Bst(my_tree.Root);
	}

	

}
