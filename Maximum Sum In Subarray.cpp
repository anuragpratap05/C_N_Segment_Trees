# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int mps;
	int mss;
	int ts;
	int max_subarray_sum;

	node()
	{
		 mss=INT_MIN;
        mps=  ts =0 ;
             max_subarray_sum = INT_MIN;
	}
};

node merge(node left, node right)
{
	node parentnode;

	parentnode.mps = max(left.mps, left.ts + right.mps);

	parentnode.mss = max(right.mss, right.ts + left.mss);

	parentnode.ts = left.ts + right.ts;

	parentnode.max_subarray_sum = max(max(left.max_subarray_sum, right.max_subarray_sum), left.mss + right.mps);
	return parentnode;
}

void buildtree(int a[], node* tree, int start, int end, int tn)
{
	if (start == end)
	{
		tree[tn].ts = a[start];
		tree[tn].mps = a[start];
		tree[tn].mss = a[start];
		tree[tn].max_subarray_sum = a[start];
		return;
	}
	int mid = (start + end) / 2;
	buildtree(a, tree, start, mid, 2 * tn);
	buildtree(a, tree, mid + 1, end, 2 * tn + 1);
	tree[tn] = merge(tree[2 * tn], tree[2 * tn + 1]);
}

node query(node* tree, int start, int end, int tn, int left, int right)
{
	if (end<left or start>right)
	{
		node nullnode;
		return nullnode;
	}
	if (start >= left and end <= right)
	{
		return tree[tn];
	}
	int mid = (start + end) / 2;
	node ans1 = query(tree, start, mid, 2 * tn, left, right);
	node ans2 = query(tree, mid + 1, end, 2 * tn + 1, left, right);
	node res = merge(ans1, ans2);
	return res;
}

int32_t main()
{

	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i)
	{
		/* code */cin >> a[i];
	}

	node* tree = new node[4 * n];

	buildtree(a, tree, 0, n - 1, 1);

	/*for (int i = 0; i < 3 * n; ++i)
	{
		cout << tree[i].mps << " , " << tree[i].mss << " , " << tree[i].ts << " , " << tree[i].max_subarray_sum << endl;
	}
	cout << endl;*/

	int q;
	cin >> q;
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		cout << query(tree, 0, n - 1, 1, x - 1, y - 1).max_subarray_sum << endl;
	}
	//cout << query(tree, 0, n - 1, 1, 0, 2).max_subarray_sum;




}
