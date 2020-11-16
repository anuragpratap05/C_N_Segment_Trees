# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;

struct node {
	int max;
	int smax;
	int sum;
};

void buildtree(int a[], node* tree, int start, int end, int tn)
{
	if (start == end)
	{
		tree[tn].max = a[start];
		tree[tn].smax = 0;
		tree[tn].sum = tree[tn].max + tree[tn].smax;
		return;
	}

	int mid = (start + end) / 2;
	buildtree(a, tree, start, mid, 2 * tn);
	buildtree(a, tree, mid + 1, end, 2 * tn + 1);
	node left = tree[2 * tn];
	node right = tree[2 * tn + 1];
	tree[tn].max = max(left.max, right.max);
	tree[tn].smax = min(max(left.max, right.smax), max(right.max, left.smax));
	tree[tn].sum = tree[tn].max + tree[tn].smax;
}

void update(int a[], node* tree, int start, int end, int tn, int idx, int value)
{
	if (start == end)
	{
		a[start] = value;
		tree[tn].max = value;
		tree[tn].smax = 0;
		tree[tn].sum = tree[tn].max + tree[tn].smax;
		return;
	}
	int mid = (start + end) / 2;
	if (idx > mid)
	{
		update(a, tree, mid + 1, end, 2 * tn + 1, idx, value);
	}
	else
	{
		update(a, tree, start, mid, 2 * tn, idx, value);
	}

	node left = tree[2 * tn];
	node right = tree[2 * tn + 1];
	tree[tn].max = max(left.max, right.max);
	tree[tn].smax = min(max(left.max, right.smax), max(right.max, left.smax));
	tree[tn].sum = tree[tn].max + tree[tn].smax;
}

node query(node* tree, int start, int end, int tn, int left , int right)
{
	if (end< left or start > right)
	{
		//cout<<"end="<<end<<" ";
		node tr;
		tr.max = 0;
		tr.smax = 0;
		tr.sum = 0;
		return tr;
		//cout<<"start="<<start<<endl;
	}
	if (start >= left and end <= right )
	{
		return tree[tn];
	}
	int mid = (start + end) / 2;

	node ans1 = query(tree, start, mid, 2 * tn, left, right);
	node ans2 = query(tree, mid + 1, end, 2 * tn + 1, left, right);
	node ans3;
	//int ca = ans1 + ans2;
	ans3.max = max(ans1.max, ans2.max);
	ans3.smax = min(max(ans1.max, ans2.smax), max(ans2.max, ans1.smax));
	ans3.sum = ans3.max + ans3.smax;
	return ans3;



}

int main()
{

	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		/* code */cin >> a[i];
	}

	node* tree = new node[3 * n];

	buildtree(a, tree, 0, n - 1, 1);

	int q;
	cin >> q;

	while (q--)
	{
		char ch;
		cin >> ch;
		int x, y;
		cin >> x >> y;
		if (ch == 'U')
		{
			//cout << "U me aya" << endl;
			update(a, tree, 0, n - 1, 1, x - 1, y);
		}
		else
		{
			cout << query(tree, 0, n - 1, 1, x - 1, y - 1).sum << endl;
		}
	}

	//node* tree = new node[3 * n];

	//buildtree(a, tree, 0, n - 1, 1);

	/*for (int i = 0; i < 3 * n; ++i)
	{
		cout << tree[i].max << " , " << tree[i].smax << " , " << tree[i].sum << endl;
	}

	update(a, tree, 0, n - 1, 1, 2, 8);

	cout << endl;
	for (int i = 0; i < 3 * n; ++i)
	{
		cout << tree[i].max << " , " << tree[i].smax << " , " << tree[i].sum << endl;
	}
	cout << endl;
	cout << query(tree, 0, n - 1, 1, 3, 4).sum;*/


}
