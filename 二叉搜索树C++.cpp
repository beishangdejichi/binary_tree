#include <iostream>
using namespace std;

template<class T> class IndexedBSTree;

template<class T>
class TreeNode
{
public:
	friend IndexedBSTree<T>;
private:
	T data;
	TreeNode<T> *lchild,*rchild;
};

template<class T>
class IndexedBSTree
{
public:
	IndexedBSTree(){r=new TreeNode<T>*;*r=NULL;}
	~IndexedBSTree(){delete [] r;}
	TreeNode<T>* Search(T d);                       //查找值为d的元素，并返回该节点
	IndexedBSTree<T>& Insert(const T d);            //若树中没有值为d的元素，则将其插入树中 
	IndexedBSTree<T>& Delete(T d);                  //删除值为d的节点
	void Pre(TreeNode<T> *root);                    //前序遍历
	void StartPre();
private:
	TreeNode<T>* *r;                                //根节点指针
	
};

template<class T>
TreeNode<T>* IndexedBSTree<T>::Search(T d)
{
	if ((*r)!=NULL)
	{
		TreeNode<T> *p=*r;
		while(p)
		{
			if (p->data==d)
			{
				return p;
			}
			else if (p->data<d)
			{
				p=p->lchild;
			}
			else if (p->data>d)
			{
				p=p->rchild;
			}
		}
		return NULL;
	}
	return NULL;
}

template<class T>
IndexedBSTree<T>& IndexedBSTree<T>::Insert(const T d)
{
	if (!(*r))
	{
		TreeNode<T> *p=new TreeNode<T>;
		p->data=d;
		p->lchild=p->rchild=NULL;
		*r=p;
		
	}
	else
	{
		TreeNode<T> *p=*r;
		TreeNode<T> *pr=NULL;
		while(p)
		{
			if (p->data>d)
			{
				pr=p;
				p=p->lchild;
			}
			else if (p->data<d)
			{
				pr=p;
				p=p->rchild;
			}
			else
			{
				cout<<"已有该元素\n";
				exit(0);
			}
		}
		TreeNode<T> *q=new TreeNode<T>;
		q->data=d;
		q->lchild=q->rchild=NULL;
		if (d<pr->data)
		{
			pr->lchild=q;
		}
		else
		{
			pr->rchild=q;
		}
	}
	return *this;
}

template<class T>
IndexedBSTree<T>& IndexedBSTree<T>::Delete(T d)
{
	if (!(*r))
	{
		exit(0);
	}
	else
	{
		TreeNode<T> *p=*r;
		TreeNode<T> *pr=NULL;
		while(p)
		{
			
			if (p->data>d)
			{
				pr=p;
				p=p->lchild;
			}
			else if (p->data<d)
			{

				pr=p;
				p=p->rchild;
			}
			else
				break;
		}
		if (!p)
		{
			cout<<"无此节点\n";
			exit(0);
		}
		else                      //删除的节点仅有左孩子或右孩子或没有孩子
		{
			if (p->lchild==NULL)
			{
				if (p==*r)
				{
					*r=p->rchild;
				}
				else if(p==pr->lchild)
				{
					pr->lchild=p->rchild;
				}
				else
				{
					pr->rchild=p->rchild;
				}
				delete p;
			}
			else if (p->rchild==NULL)
			{
				if (p==*r)
				{
					*r=p->lchild;
				}
				else if(p==pr->lchild)
				{
					pr->lchild=p->lchild;
				}
				else
				{
					pr->rchild=p->lchild;
				}
				
			}
			else                                         //要删除的节点有左右子树
			{
				TreeNode<T> *q1=p->lchild;              //以左子树中的最右端节点进行替换
				TreeNode<T> *q2=p;
				while(q1->rchild)
				{
					q2=q1;
					q1=q1->rchild;
				}
				p->data=q1->data;
				if (q2==p)                            //要删除的节点的左子树再无右子树
				{
					q2->lchild=q1->lchild;
				}
				else
				{
					q2->rchild=q1->lchild;
				}
				delete q1;
			}
			
			return *this;
		}
	}
}

template<class T>
void IndexedBSTree<T>::Pre(TreeNode<T> *root)
{
	if (root)
	{
		
		Pre(root->lchild);
		
		Pre(root->rchild);
		cout<<root->data<<endl;
	}
}

template<class T>
void IndexedBSTree<T>::StartPre()
{
	if (!(*r))
	{
		cout<<"空树\n";
	}
	else
	{
		Pre(*r);
	}
}

void main()
{
	IndexedBSTree<int> BST;
	int a[]={51,56,49,50,48};
	for (int i=0;i<5;i++)
	{
		BST.Insert(a[i]);
	}
	//BST.StartPre();
	BST.Delete(51);
	BST.StartPre();
}