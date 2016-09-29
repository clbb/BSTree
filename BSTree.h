#include<iostream>
using namespace std;
//cldeh
template<class K,class V>
struct BSTreeNode
{
	K _key;
	V _value;
	BSTreeNode<K,V>* _left;
	BSTreeNode<K,V>* _right;
	BSTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K,V> Node; 
public:
	BSTree()
		:_root(NULL)
	{}
	Node* Find(const K& key)
	{
		if(_root == NULL)
			return NULL;

		Node* cur = _root;
		while (cur)
		{
			if(cur->_key < key)
				cur = cur->_right;
			else if(cur->_key > key)
				cur = cur->_left;
			else
				return cur;
		}
		return NULL;
	}

	Node* FindR(const K& key)
	{
		return _FindR(_root,key);
	}
	Node* _FindR(Node* root,const K& key)
	{
		if(root == NULL)
			return NULL;

		//Node*  = root;
		if(root->_key > key)
			_FindR(root->_left,key);
		else if(root->_key < key)
			_FindR(root->_right,key);
		else 
			return root;
	}
	bool Insert(const K& key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
		}
		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		
		cur = new Node(key,value);
		if(parent->_key > key)
		{
			parent->_left = cur;
		}
		else if(parent->_key < key)
		{
			parent->_right = cur;
		}
		
		else 
			return false;
		
		return false;

	}
	bool InsertR(const K& key,const V& value)
	{
		return _InsertR(_root,key,value);
	}
	
	void Inorder()
	{
		_Inorder(_root);
		cout<<endl;
	}
	bool Remove(const K& key)
	{
		if(isEmpty(_root))
		{
			return false;
		}
		if(_root->_left == NULL && _root->_right == NULL)
		{
			delete _root;
			_root = NULL;
			return true;
		}
		Node* del = _root;
		Node* parent = _root;
		while(del)
		{
			if(del->_key < key)
			{
				parent = del;
				del = del->_right;
			}
			else if(del->_key > key)
			{
				parent = del;
				del = del->_left;
			}
			else
			{
				//break;
				//	return false;//Remove shiyong tihuan silu  eg:5-> 6 
				if(del == NULL)
				{
					return false;
				}
				if(del->_left == NULL)
				{
					if(parent->_left == del)
						parent->_left = del->_right;
					else if(parent->_right == del)
						parent->_right = del->_right;
				}
				else if(del->_right == NULL)
				{
					if(parent->_left == del)
						parent->_left = del->_left;
					else if(parent->_right == del)
						parent->_right = del->_left;
				}
				else
				{
					Node* sub = del;
					Node* first = del->_right;
					while(first->_left)
					{
						sub = first;
						first = first->_left;
					}
					swap(del->_key,first->_key);
					swap(del->_value,first->_value);
					del = first;
					parent = sub;
					if(del->_left == NULL)
					{
						if(parent->_left == del)
							parent->_left = del->_right;
						else if(parent->_right == del)
							parent->_right = del->_right;

					}
					else if(del->_right == NULL)
					{
						if(parent->_left == del)
							parent->_left = del->_left;
						else if(parent->_right == del)
							parent->_right = del->_left;
					}
				}
				delete del;
				del = NULL;
				return true;
			}
		}
		return false;
	}
protected:
	void _Inorder(Node* root)
	{
		if(root ==NULL)
		{
			return;
		}
		_Inorder(root->_left);
		cout<<root->_key<<" ";
		_Inorder(root->_right);
	}
	bool _InsertR(Node*& root,const K& key,const V& value)
	{
		if(root == NULL)
		{
			root = new Node(key,value);
			return true;
		}

		if(root->_key < key)
		{
			return _InsertR(root->_right,key,value);
		}
		else if(root->_key > key)
		{
			return _InsertR(root->_left,key,value);
		}
		else
		{
			return false;//Remove shiyong tihuan silu  eg:5-> 6 
		}
		return false;
	}
	bool isEmpty(Node* root)
	{
		return (_root == NULL) ? 1:0;
	}
	
protected:
	Node* _root; 

};

void Test1()
{
	BSTree<int,int> s;
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	for(int i = 0;i<10;++i)
	{
		s.Insert(a[i],i);
	}
	
	/*BSTreeNode<int,int>* cur = s.FindR(10);
	if(cur == NULL)
	{
	return -1;
	}
	cout<<cur->_key<<endl;*/
	s.Inorder();
	//s.Remove(0);
	//s.Remove(4);
	//s.Remove(4);
	//s.Remove(0);
	s.Remove(5);

	s.Inorder();

	/*s.Remove(1);
	s.Remove(1);
	s.Remove(1);
	s.Remove(1);*/

}
