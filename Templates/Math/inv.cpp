struct Inversion { 
	static constexpr int B = (1 << 10), T = (1 << 20);

	int f[T + 5], p[T + 5], buf[T * 3 + 5];
	int *I = buf + T;
	int mod;

	Inversion(int mod_) {
		init(mod_);
	}

	void init(int mod_) {
		mod = mod_;
		for (int u = 1; u <= B; u++) {
			int s = 0, d = (u << 10);
			for (int a = 1; a <= T; a++) {
				if ((s += d) >= mod) s -= mod;
				if (s <= T) {
					if (!f[a]) f[a] = u, p[a] = s;
			        continue;
				} 
			    if (s >= mod - T) {
			        if (!f[a]) f[a] = u, p[a] = s - mod;
			        continue;
				} 
			    int t = (mod - T - s - 1) / d;
			    s += t * d, a += t;
			}
		}

		I[1] = f[0] = 1;
		for (int i = 2; i <= (T << 1); i++) I[i] = 1ll * (mod - mod / i) * I[mod % i] % mod;
		for (int i = -1; i >= -T; i--) I[i] = mod - I[-i];
	}

	int inv(int x) { return 1ll * I[p[x >> 10] + (x & 1023) * f[x >> 10]] * f[x >> 10] % mod; }
};

Inversion inver(998244353);
