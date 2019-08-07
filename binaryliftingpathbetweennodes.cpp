void pre(){
	ll out = 0;
	for(auto x : lcaQueries) {
    	int d, d1 = x.F.F, d2 = x.F.S, l = x.S;
    	bool x = d1 < l, y = l < d2;
    	if(d1 != l && d2 != l && p == x && q == y) ust.insert(l);
    	if(d1 != l) {
        	d = up[d1][0];
        	while(d != l) {
            x = d1 < d, y = d < d2;
            if(p == x && q == y) ust.insert(d);
            d = up[d][0];
        	}
    	}
    	if(d2 != l) {
        d = up[node2][0];
        while(d != l) {
            x = d1 < d, y = d < d2;
            if(p == x && q == y) ust.insert(d);
            d = up[d][0];
        }
    }
    out += ust.size();
    ust.clear();
    }
}
