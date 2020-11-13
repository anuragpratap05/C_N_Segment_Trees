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

	tree[tn] = min(tree[2 * tn] , tree[2 * tn + 1 ]);
}

void update(int a[], int tree[], int start, int end, int tn, int idx, int value)
{
	if (start == end)
	{
		a[idx] = value;
		tree[tn] = value;
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
	tree[tn] = min(tree[2 * tn + 1] , tree[2 * tn]);
}

int query(int tree[], int s, int e, int tn, int left, int right)
{
	if (e<left or s>right)
	{
		return INT_MAX;
	}
	if (s >= left and e <= right)
	{
		return tree[tn];
	}
	int mid = (s + e) / 2;
	int ans1 = query(tree, s, mid, 2 * tn, left, right);
	int ans2 = query(tree, mid + 1, e, 2 * tn + 1, left, right);
	//cout << ans1 << " " << ans2 << endl;
	return min(ans1 , ans2);
}

int main()
{

	int n, q;
	cin >> n >> q;
	int a[n];
	for (int i = 0; i < n; i ++ )
	{
		cin >> a[i];
	}

	int tree[4*n];

	buildtree(a, tree, 0, n - 1, 1);
	/*for (int i = 1; i < 2 * n ; ++i)
	{
		cout << tree[i] << " ";
	}
	cout << endl;*/

	char c;
	int x, y;
	for (int i = 0; i < q; i++)
	{
		cin >> c >> x >> y;
		//cout << ;
		if (c == 'q')
		{
			int ans = query(tree, 0, n - 1, 1, x - 1, y - 1);
			cout << ans << endl;
		}
		else
		{
			update(a, tree, 0, n - 1, 1, x - 1, y);
		}
	}

	//int tree[n * 2];

	/*buildtree(a, tree, 0, n - 1, 1);
	for (int i = 1; i < 2 * n ; ++i)
	{
		cout << tree[i] << " ";
	}
	cout << endl;*/

	//update(a, tree, 0, n - 1, 1, 2, 6);

	/*for (int i = 1; i < 2 * n ; ++i)
	{
		cout << tree[i] << " ";
	}
	cout << endl;*/

	/*int ans = query(tree, 0, n - 1, 1, 0, 4);
	cout << ans;*/


}
