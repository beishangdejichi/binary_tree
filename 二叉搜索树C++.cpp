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
	TreeNode<T>* Search(T d);                       //����ֵΪd��Ԫ�أ������ظýڵ�
	IndexedBSTree<T>& Insert(const T d);            //������û��ֵΪd��Ԫ�أ������������ 
	IndexedBSTree<T>& Delete(T d);                  //ɾ��ֵΪd�Ľڵ�
	void Pre(TreeNode<T> *root);                    //ǰ�����
	void StartPre();
private:
	TreeNode<T>* *r;                                //���ڵ�ָ��
	
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
				cout<<"���и�Ԫ��\n";
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
			cout<<"�޴˽ڵ�\n";
			exit(0);
		}
		else                      //ɾ���Ľڵ�������ӻ��Һ��ӻ�û�к���
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
			else                                         //Ҫɾ���Ľڵ�����������
			{
				TreeNode<T> *q1=p->lchild;              //���������е����Ҷ˽ڵ�����滻
				TreeNode<T> *q2=p;
				while(q1->rchild)
				{
					q2=q1;
					q1=q1->rchild;
				}
				p->data=q1->data;
				if (q2==p)                            //Ҫɾ���Ľڵ������������������
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
		cout<<"����\n";
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