#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define st first
#define nd second

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct Node {
	ll val = 0;
	ll lazy = 0;
};

struct SegmentTree {
	int size;
	vector <Node> Tree;

	void init(int n) {
		Tree.resize(4 * n);
	}

	void build(int id, int lx, int rx, vector <ll> &a) {
		if (lx == rx) {
			Tree[id].val = a[lx];
			return;
		}

		int mx = (lx + rx) >> 1;
		build(2 * id, lx, mx, a);
		build(2 * id + 1, mx + 1, rx, a);

		Tree[id].val = Tree[2 * id].val + Tree[2 * id + 1].val;
	}

	void apply(int id) {
		ll add = Tree[id].lazy;
		Tree[2 * id].val += add;
		Tree[2 * id].lazy += add;

		Tree[2 * id + 1].val += add;
		Tree[2 * id + 1].lazy += add;

		Tree[id].lazy = 0;
	}

	void update(int id, int lx, int rx, int u, int v, ll k) {
		if (lx > v || rx < u) return;
		if (lx >= u && rx <= v) {
			Tree[id].val += k;
			Tree[id].lazy += k;
			return;
		}

		int mx = (lx + rx) >> 1;
		apply(id);
		update(2 * id, lx, mx, u, v, k);
		update(2 * id + 1, mx + 1, rx, u, v, k);

		Tree[id].val = Tree[2 * id].val + Tree[2 * id + 1].val;
	}

	ll query(int id, int lx, int rx, int i) {
		if (lx > i || rx < i) return 0;
		if (lx == rx) return Tree[id].val;

		int mx = (lx + rx) >> 1;
		ll x = query(2 * id, lx, mx, i);
		ll y = query(2 * id + 1, mx + 1, rx, i);

		return x + y + Tree[id].lazy;
	}

	void build(vector <ll> &a) {
		build(1, 1, size, a);
	}

	void update(int u, int v, ll k) {
		update(1, 1, size, u + 1, v, k);
	}

	ll query(int i) {
		return query(1, 1, size, i + 1);
	}
};

void solve() {
	int n, q;
	cin >> n >> q;
	vector <ll> a(n + 1, 0);

	SegmentTree St;
	St.size = n;
	St.init(n);
	St.build(a);

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			ll l, r, v;
			cin >> l >> r >> v;
			St.update(l, r, v);
		}
		else {
			int i;
			cin >> i;
			cout << St.query(i) << '\n';
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t = 1;
	while (t--) {
		solve();
	}

	return 0;
}
