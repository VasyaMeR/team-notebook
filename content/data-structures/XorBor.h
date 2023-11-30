struct Node {
	array<Node*, 2> mp = {nullptr, nullptr};

	void add(int mask, int k = 30) {
		if (k == -1)
			return;
		int bit = (mask>>k)&1;
		// cerr << this->mp.size() << " " << bit << endl;
		if (!this->mp[bit])
			this->mp[bit] = new Node();
		this->mp[bit]->add(mask, k - 1);
	}

	int get(int mask, int k = 30) {
		if (k == -1)
			return 0;
		int bit = (mask>>k)&1;
		int cur= bit;
		if (mp[!bit])
			cur = !bit;
		return ((cur^bit) << k) | mp[cur]->get(mask, k - 1);
	}
};
