# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;

void buildtree(int a[], int tree[], int s, int e, int tn)
{

	if (s == e)
	{
		tree[tn] = a[s];
		return;

	}
	int mid = (s + e) / 2;
	buildtree(a, tree, s, mid, 2 * tn);
	buildtree(a, tree, mid + 1, e, 2 * tn + 1);

	tree[tn] = tree[2 * tn] + tree[2 * tn + 1 ];
}

void upadate_tree(int a[], int tree[], int s, int e, int tn, int idx, int value)
{
	if (s == e)
	{
		a[idx] = value;
		tree[tn] = value;
		return;
	}

	int mid = (s + e) / 2;
	if (idx > mid)
	{
		upadate_tree(a, tree, mid + 1, e, 2 * tn + 1, idx, value);
	}
	else
	{
		upadate_tree(a, tree, s, mid, 2 * tn, idx, value);
	}
	tree[tn] = tree[2 * tn + 1] + tree[2 * tn];
}


int main()
{
#ifndef ONLINE_jUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	int tree[2 * n];

	buildtree(a, tree, 0, n - 1, 1);

	for (int i = 1; i < 2 * n; i++)
	{
		/* code */cout << tree[i] << " ";
	}
	cout << endl;

	upadate_tree(a, tree, 0, n - 1, 1, 2, 10);

	for (int i = 1; i < 2 * n; i++)
	{
		/* code */cout << tree[i] << " ";
	}

}

