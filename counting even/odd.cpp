# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;

struct node
{
	int even = 0;
	int odd = 0;
};

void buildtree(int a[], node* tree, int start, int end, int tn)
{
	if (start == end)
	{
		if (a[start] % 2 == 0)
		{
			tree[tn].even += 1;
		}
		else
		{
			tree[tn].odd += 1;
		}
		return;
	}

	int mid = (start + end) / 2;
	buildtree(a, tree, start, mid, 2 * tn);
	buildtree(a, tree, mid + 1, end, 2 * tn + 1);
	//node left = tree[2 * tn];
	//node right = tree[2 * tn + 1];
	tree[tn].even = tree[2 * tn].even + tree[2 * tn + 1].even;
	tree[tn].odd = tree[2 * tn].odd + tree[2 * tn + 1].odd;
}

void update(int a[], node* tree, int start, int end, int tn, int idx , int value)
{
	if (start == end)
	{
		a[idx] = value;
		tree[tn].even = 0;
		tree[tn].odd = 0;
		if (value % 2 == 0)
		{
			tree[tn].even += 1;
		}
		else
		{
			tree[tn].odd += 1;
		}
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

	tree[tn].even = tree[2 * tn].even + tree[2 * tn + 1].even;
	tree[tn].odd = tree[2 * tn].odd + tree[2 * tn + 1].odd;


}

node query(node* tree, int start, int end, int tn, int left, int right)
{
	if (end<left or start>right)
	{
		node tr;
		tr.even = 0;
		tr.odd = 0;
		return tr;
	}
	if (start >= left and end <= right)
	{
		return tree[tn];
	}
	int mid = (start + end) / 2;
	node ans1 = query(tree, start, mid, 2 * tn, left, right);
	node ans2 = query(tree, mid + 1, end, 2 * tn + 1, left, right);
	node ans3;
	ans3.even = ans1.even + ans2.even;
	ans3.odd = ans1.odd + ans2.odd;
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

	int Query;
	cin >> Query;
	while (Query--)
	{
		int q, x, y;
		cin >> q >> x >> y;
		if (q == 1)
		{
			cout << query(tree, 0, n - 1, 1, x - 1, y - 1).even << endl;
		}
		else if (q == 2)
		{
			cout << query(tree, 0, n - 1, 1, x - 1, y - 1).odd << endl;
		}
		else
		{
			update(a, tree, 0, n - 1, 1, x - 1, y);
		}
	}
	/*for (int i = 1; i < 3 * n; ++i)
	{
		cout << tree[i].even << " , " << tree[i].odd  << endl;
	}
	cout << endl;
	update(a, tree, 0, n - 1, 1, 4, 4);

	for (int i = 1; i < 3 * n; ++i)
	{
		cout << tree[i].even << " , " << tree[i].odd  << endl;
	}

	cout << query(tree, 0, n - 1, 1, 0, 5).even;*/

}
