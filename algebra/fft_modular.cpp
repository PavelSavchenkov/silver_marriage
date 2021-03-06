const int MAXK = 16;
const int MAXN = 1 << MAXK;				   
const int MOD = 786433;
const ll ROOT = 10;		 

typedef vector<int> polynom;

ll binpow(ll n, int k) {
	ll res = 1;
	while (k > 0) {
		if (k & 1)
			res = (res * n) % MOD;
		n = (n * n) % MOD;
		k >>= 1;
	}
	return res;
}

int inv(int n) {
	int res = 0;
	forn(i, MAXK)
		res |= ((n >> (MAXK - i - 1)) & 1) << i;
	return res;
}

void fft(polynom &a, bool invert) {
	int n = a.size();
	if (n == 1)
		return;
			
	forn(i, n)
		if (i < inv(i))	
			swap(a[i], a[inv(i)]);
	
	for (int len = 2; len <= n; len <<= 1) {
		int st = (MOD - 1) / len;
		if (invert)
			st = (MOD - 1 - st);
		ll w, wn = binpow(ROOT, st);
	
		for (int i = 0; i < n; i += len) {
			w = 1;
			for (int j = 0; j < len / 2; j++) {
				ll a0 = a[i + j], a1 = a[i + j + len / 2];
				a[i + j] = (a0 + w * a1) % MOD;
				a[i + j + len / 2] = (1ll * MOD * MOD + a0 - w * a1) % MOD;
				
				w = (w * wn) % MOD;
			}
		}	
			
	}
	
	if (invert) {
		ll nn = binpow(n, MOD - 2);
		forn(i, n)
			a[i] = (1ll * a[i] * nn) % MOD;
	}
}

vi multiply(vi a, vi b) {
	polynom fa(a.size()), fb(b.size()), fc(a.size());
	forn(i, a.size())
		fa[i] = a[i];
	forn(i, b.size())
		fb[i] = b[i];

	fft(fa, 0);
	fft(fb, 0);
	forn(i, fc.size())
		fc[i] = (1ll * fa[i] * fb[i]) % MOD;
	
	fft(fc, 1); 
		
	vi res(fc.size());
	forn(i, fc.size())
		res[i] = fc[i];		
	
	return res;
}
