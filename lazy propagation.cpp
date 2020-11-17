# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;

void buildtree(int a[], int* tree, int start, int end, int tn)
{
	if (start == end)
	{
		tree[tn] = a[start];
		return;
	}

	int mid = (start + end) / 2;

	buildtree(a, tree, start, mid, 2 * tn);
	buildtree(a, tree, mid + 1, end, 2 * tn + 1);
	tree[tn] = min(tree[2 * tn], tree[2 * tn + 1]);
}

void updatelazy(int* tree, int* lazy, int start, int end, int tn, int left, int right, int inc)
{
	if (start > end)
	{
		return;
	}

	if (lazy[tn] != 0)
	{
		tree[tn] += lazy[tn];
		if (start != end)
		{
			lazy[2 * tn] += lazy[tn];
			lazy[2 * tn + 1] += lazy[tn];
		}
		lazy[tn] = 0;
	}

	if (end<left or start>right)
	{
		return;
	}
	if (start >= left and end <= right)
	{
		tree[tn] += inc;
		lazy[2 * tn] += inc;
		lazy[2 * tn + 1] += inc;
		return;
	}

	int mid = (start + end) / 2;
	updatelazy(tree, lazy, start, mid, 2 * tn, left, right, inc);
	updatelazy(tree, lazy, mid + 1, end, 2 * tn + 1, left, right, inc);
	tree[tn] = min(tree[2 * tn], tree[2 * tn + 1]);
}

int main()
{
#ifndef ONLINE_jUDGE
	freopen("input2.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
#endif
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		/* code */cin >> a[i];
	}

	int* tree = new int[3 * n];
	int*lazy = new int[3 * n];
	buildtree(a, tree, 0, n - 1, 1);
	for (int i = 0; i < 3 * n; ++i)
	{
		/* code */cout << tree[i] << endl;
	}

	updatelazy(tree, lazy, 0, n - 1, 1, 0, 3, 3);
	updatelazy(tree, lazy, 0, n - 1, 1, 0, 1, 2);
	cout << "segment tree" << endl;
	for (int i = 1; i < 3 * n; ++i)
	{
		/* code */cout << tree[i] << endl;
	}
	cout << "lazy tree" << endl;
	for (int i = 1; i < 3 * n; ++i)
	{
		/* code */cout << lazy[i] << endl;
	}
}
