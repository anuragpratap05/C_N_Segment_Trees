# C_N_Segment_Trees
#include<bits/stdc++.h>
using namespace std;


class node

{
public:
	int sumofs, sum;
	node()
	{
		sumofs = 0;
		sum = 0;
	}
};

class type
{
public:
	int value, identity;
	type()
	{
		value = 0;
		identity = 0;
	}
};

void build_tree(int * a, node * tree, int s, int e, int tn)
{


	if (s == e)
	{
		tree[tn].sumofs = a[s] * a[s];
		tree[tn].sum = a[s];
		return;
	}


	int mid = (s + e) / 2;
	build_tree(a, tree, s, mid, 2 * tn);
	build_tree(a, tree, mid + 1, e, 2 * tn + 1);

	tree[tn].sumofs = tree[2 * tn].sumofs + tree[2 * tn + 1].sumofs;
	tree[tn].sum = tree[2 * tn].sum + tree[2 * tn + 1].sum;

}

void upadte(int* a, node* tree, type* lazy , int s, int e, int tn, int left, int right, int inc, int disting)
{

	if (s > e)
	{
		return;
	}

	if (lazy[tn].identity != 0)
	{
		if (lazy[tn].identity == 1)
		{
			tree[tn].sumofs = tree[tn].sumofs + (e - s + 1) * (lazy[tn].value * lazy[tn].value) + (2 * lazy[tn].value * tree[tn].sum);
			tree[tn].sum += lazy[tn].value * (e - s + 1);
			if (s != e)
			{
				lazy[2 * tn].value +=  lazy[tn].value;
				lazy[2 * tn + 1].value +=  lazy[tn].value;
			}
		}
		else if (lazy[tn].identity == 5)
		{
			tree[tn].sumofs = (e - s + 1) * (lazy[tn].value * lazy[tn].value);
			tree[tn].sum = (e - s + 1) * lazy[tn].value;
			if (s != e)
			{
				lazy[2 * tn].value = lazy[tn].value;
				lazy[2 * tn].identity = 5;
				lazy[2 * tn + 1].value = lazy[tn].value;;
				lazy[2 * tn + 1].identity = 5;


			}
		}
		lazy[tn].identity = 0;
	}

	if (e<left or s>right)
	{
		return;
	}

	if (s >= left and e <= right)
	{
		if (disting == 1)
		{
			tree[tn].sumofs = tree[tn].sumofs + (e - s + 1) * (inc * inc) + (2 * inc * tree[tn].sum);
			tree[tn].sum += (e - s + 1) * inc;
			if (s != e)
			{
				lazy[2 * tn].value += inc;
				lazy[2 * tn].identity = 1;
				lazy[2 * tn + 1].value += inc;
				lazy[2 * tn + 1].identity = 1;


			}
		}

		else if (disting == 0)
		{
			tree[tn].sumofs = (e - s + 1) * (inc * inc);
			tree[tn].sum = (e - s + 1) * inc;
			if (s != e)
			{
				lazy[2 * tn].value = inc;
				lazy[2 * tn].identity = 5;
				lazy[2 * tn + 1].value = inc;
				lazy[2 * tn + 1].identity = 5;


			}
		}

		return;
	}

	int mid = (s + e) / 2;

	upadte( a,  tree, lazy , s, mid,  2 * tn,  left,  right, inc, disting);
	upadte( a,  tree, lazy , mid + 1, e,  2 * tn + 1,  left,  right, inc, disting);



	tree[tn].sumofs = tree[2 * tn].sumofs + tree[2 * tn + 1].sumofs;
	tree[tn].sum = tree[2 * tn].sum + tree[2 * tn + 1].sum;
}


int query(node* tree, type* lazy, int s, int e, int tn, int left , int right)
{



	if (lazy[tn].identity != 0)
	{
		if (lazy[tn].identity == 1)
		{
			tree[tn].sumofs = tree[tn].sumofs + (e - s + 1) * (lazy[tn].value  * lazy[tn].value) + (2 * lazy[tn].value * tree[tn].sum);
			tree[tn].sum += lazy[tn].value * (e - s + 1);
			if (s != e)
			{
				lazy[2 * tn].value +=  lazy[tn].value;
				lazy[2 * tn + 1].value +=  lazy[tn].value;
			}
		}
		else if (lazy[tn].identity == 5)
		{
			tree[tn].sumofs = (e - s + 1) * (lazy[tn].value * lazy[tn].value);
			tree[tn].sum = (e - s + 1) * lazy[tn].value;
			if (s != e)
			{
				lazy[2 * tn].value = lazy[tn].value;
				lazy[2 * tn].identity = 5;
				lazy[2 * tn + 1].value = lazy[tn].value;;
				lazy[2 * tn + 1].identity = 5;


			}
		}
		lazy[tn].identity = 0;
	}


	if (e<left or s>right )
	{
		return 0;
	}

	if (s >= left and e <= right)
	{
		//cout << s << " " << e << " " << tree[tn] << endl;

		//return;
		return tree[tn].sumofs;
	}


	int mid = (s + e) / 2;
	int ans1 = 0;
	int ans2 = 0;

	ans2 = query(tree, lazy, s, mid, 2 * tn, left, right);

	ans1 = query(tree, lazy, mid + 1, e, 2 * tn + 1, left, right);



	return (ans1 + ans2);



}

int main()
{



	int t;
	cin >> t;
	int cnt = 0;
	for (int i = 1; i <= t; i++)
	{
		cout << "Case " << i << ":" << endl;




		int n, q;
		cin >> n;
		cin >> q;
		int* a = new int[n];

		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
		}

		node* tree = new node[4 * n];

		type * lazy = new type[4 * n]();

		build_tree(a, tree, 0, n - 1, 1);

		/*for (int i = 1; i < 3 * n; i++)
		{
			cout << tree[i].sumofs << " " << tree[i].sum << endl;
		}
		cout << endl;*/


		for (int i = 0; i < q; i++)
		{
			int x, b, c, d;
			cin >> x;
			if (x == 2)
			{
				cin >> b >> c;
				cout << query(tree, lazy, 0, n - 1, 1, b - 1, c - 1) << endl;

			}
			else
			{
				cin >> b >> c >> d;
				upadte(a, tree, lazy, 0, n - 1, 1, b - 1, c - 1, d, x) ;

			}
		}
	}



	/*for (int i = 1; i < 3 * n; i++)
	{
		cout << tree[i].sumofs << " " << tree[i].sum << endl;
	}

	upadte(a, tree, lazy, 0, n - 1, 1, 0, 4, 2, 0) ;
	cout << endl;

	for (int i = 1; i < 3 * n; i++)
	{
		cout << tree[i].sumofs << " " << tree[i].sum << endl;
	}
	cout << endl;
	cout << query(tree, lazy, 0, n - 1, 1, 0, 2) << endl;*/


}
