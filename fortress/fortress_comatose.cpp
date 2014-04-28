#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

class Wall{
public:
    int x, y, r, d;
    vector<Wall*> subs;
    bool covers(const Wall& w){
	return r > w.r && (pow(x - w.x, 2) + pow(y - w.y, 2)) < pow(r - w.r, 2);
    }
};

void build(Wall& r, Wall& n){
    if(!r.covers(n))
	return;

    for(auto &c: r.subs){
	if(c->covers(n)){
	    build(*c, n);
	    return;
	}
    }

    auto p = partition(r.subs.begin(), r.subs.end(), [&](Wall* c){
	    return !n.covers(*c);
	});

    n.subs.insert(n.subs.end(), p, r.subs.end());
    r.subs.erase(p, r.subs.end());
    r.subs.push_back(&n);
}

int depth(Wall& w){
    int &d = w.d;
    if(d == 0){
	for(auto &c: w.subs)
	    d = max(d, depth(*c));
	d++;
    }
    return d;
}

int diff(const Wall& w){
    int m1 = 0, m2 = 0;
    for(auto &c: w.subs){
	m2 = max(m2, depth(*c));
	if(m2 > m1)
	    swap(m1, m2);
    }
    return m1 + m2;
}

int maxdiff(int m, const Wall& w){
    m = max(m, diff(w));
    for(auto &c: w.subs)
	m = maxdiff(m, *c);
    return m;
}

int main(){
    int c, n;
    scanf("%d", &c);
    while(c--){
	scanf("%d", &n);
	vector<Wall> cas(n);
	for(auto &e: cas)
	    scanf("%d %d %d", &e.x, &e.y, &e.r);

	for(auto &e: cas)
	    build(cas.front(), e);

	printf("%d\n", maxdiff(0, cas.front()));
    }
    return 0;
}
