#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

//#define LOCAL
#define DEBUG 0
#define NMAX 2001
#define AMAX 5
#define OPMAX 201
#define ONE_DAY 86400
#define ONE_HOUR 3600
#define NINE_HOURS 32400
#define TEN_MINUTES 600
#define BASE_PENALTY 300000
#define MISS_PENALTY 1500000
#define MOVE_OP 0
#define PICKUP1_OP 1
#define PICKUP2_OP 2
#define DROPOFF1_OP 3
#define DROPOFF2_OP 4
#define TIME_LIMIT 29.0

inline double GetTime() {
	timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec * 1e-6;
}

class MersenneTwister {
private:
	// Period parameters
	static const int N = 624;
	static const int M = 397;
	static const unsigned int MATRIX_A = 0x9908b0dfU;   //    private static final * constant vector a
	static const unsigned int UPPER_MASK = 0x80000000U; // most significant w-r bits
	static const unsigned int LOWER_MASK = 0x7fffffffU; // least significant r bits
 
	// Tempering parameters
    static const unsigned int TEMPERING_MASK_B = 0x9d2c5680;
    static const unsigned int TEMPERING_MASK_C = 0xefc60000;
    
    unsigned int* mt; // the array for the state vector
    unsigned int mti; // mti==N+1 means mt[N] is not initialized
    unsigned int* mag01;
    
public: 
	MersenneTwister(unsigned int seed) {
		mt = mag01 = NULL;
		setSeed(seed);
	}
    
	void setSeed(unsigned int seed) {
	        if (mt == NULL) mt = new unsigned int[N];
	        if (mag01 == NULL) mag01 = new unsigned int[2];
	        mag01[0] = 0x0;
	        mag01[1] = MATRIX_A;
 
	        mt[0] = seed;
		for (mti=1; mti<N; mti++)  {
			mt[mti] = 
				(1812433253U * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
		}
	}
 
	int next(int bits) {
		unsigned int y;
		if (mti >= N) {
			int kk;
			unsigned int* mt = this->mt;
			unsigned int* mag01 = this->mag01;
			for (kk = 0; kk < N - M; kk++) {
	                	y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
                		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
			}
			for (; kk < N-1; kk++) {
                		y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
        		        mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
			}
			y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
			mti = 0;
		}
  
        y = mt[mti++]; 
		y ^= y >> 11;
		y ^= (y << 7) & TEMPERING_MASK_B; 
		y ^= (y << 15) & TEMPERING_MASK_C;
		y ^= y >> 18;
		int ret = y >> (32 - bits);
		return ret;
	}
 
    int NextInt() {
		return next(31);
    }
 
	int x, y;
	double NextDouble() {
		x = next(26); y = next(27);
        double d = (((long long)x << 27) + y)
				/ (double)(1LL << 53);
		return d;
	}
};
 
MersenneTwister mt(0);

struct Order {
	int from, to, moment;
};

struct Driver {
	int garage, start, finish;
};

int x[NMAX], y[NMAX], d[NMAX][NMAX], t[NMAX][NMAX];
struct Order order[NMAX];
struct Driver driver[NMAX];
int A, G, Q, D, N;
unsigned int SEED;

void ReadInput() {
	scanf("%u %d %d %d %d", &SEED, &A, &G, &Q, &D);
	N = A + G + Q;
	for (int i = 0; i < N; i++)
		scanf("%d %d", &x[i], &y[i]);
	for (int i = 0; i < Q; i++)
		scanf("%d %d %d", &order[i].from, &order[i].to, &order[i].moment);
	for (int i = 0; i < D; i++) {
		scanf("%d %d %d", &driver[i].garage, &driver[i].start, &driver[i].finish);
		assert(A <= driver[i].garage && driver[i].garage < A + G);
		assert (0 <= driver[i].start && driver[i].start <= 12 * ONE_HOUR);
		assert((driver[i].start % ONE_HOUR) == 0);
		assert(driver[i].finish == driver[i].start + 12 * ONE_HOUR);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &d[i][j]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &t[i][j]);
}

double TSTART, TEND, TCRITICAL;

struct DriverInstructions {
	int ops[OPMAX][4], nops;	
} bsol[NMAX], csol[NMAX];

long long bgscore, cgscore;

void InitSol(struct DriverInstructions sol[NMAX], long long& gscore) {
	gscore = (long long) MISS_PENALTY * (long long) Q;
	for (int i = 0; i < D; i++) sol[i].nops = 0;
}

void UpdateSol() {
	if (bgscore < 0 || cgscore < bgscore) {
		bgscore = cgscore;
#ifdef LOCAL
		fprintf(stderr, "new bgscore=%I64d\n", bgscore);
#endif
		for (int i = 0; i < D; i++) {
			bsol[i].nops = csol[i].nops;
			memcpy(&bsol[i].ops[0], &csol[i].ops[0], bsol[i].nops * sizeof(bsol[i].ops[0]));
		}
	}
}

void AddMoveOp(int moment, int v, int ops[][4], int& nops) {
	ops[nops][0] = MOVE_OP;
	ops[nops][1] = moment;
	ops[nops][2] = v;
	nops++;
}

void AddPickup1Op(int moment, int oid, int ops[][4], int& nops) {
	ops[nops][0] = PICKUP1_OP;
	ops[nops][1] = moment;
	ops[nops][2] = oid;
	nops++;
}

void AddPickup2Op(int moment, int oid1, int oid2, int ops[][4], int& nops) {
	ops[nops][0] = PICKUP2_OP;
	ops[nops][1] = moment;
	ops[nops][2] = oid1;
	ops[nops][3] = oid2;
	nops++;
}

void AddDropoff1Op(int moment, int oid, int ops[][4], int& nops) {
	ops[nops][0] = DROPOFF1_OP;
	ops[nops][1] = moment;
	ops[nops][2] = oid;
	nops++;
}

void AddDropoff2Op(int moment, int o1, int o2, int ops[][4], int& nops) {
	ops[nops][0] = DROPOFF2_OP;
	ops[nops][1] = moment;
	ops[nops][2] = o1;
	ops[nops][3] = o2;
	nops++;
}

namespace TPN {

#define WAIT_STEP 3600
int SCALE_FACTOR;
#define PACK(time, place) ((time + SCALE_FACTOR - 1) / SCALE_FACTOR * N + place)
#define UNPACK(time_place, time, place) (time = (time_place / N) * SCALE_FACTOR, place = time_place % N);
#define MAX_EDGES 19000000

int MAX_PAIRS;
vector<pair<int, int> > pickup_from[AMAX];
vector<int> dropoff_at[AMAX];

set<int> tps;

struct Edge {
	short int o1, o2;
	int tdrive, dist, tpdest;
};

struct Edge etmp;
struct Edge tpve[MAX_EDGES];
vector<pair<int, int> > tpve_pickup_from_airport[AMAX], tpve_dropoff_at_airport_tstart[AMAX];
vector<pair<pair<int, int>, pair<int, int> > > tpve_dropoff_at_airport_tlinear[AMAX];

#define MAXTPVAL 6000000
int tpidx[MAXTPVAL], ntp;
char intps[MAXTPVAL];

#define MAXTPCNT 35000
vector<int> tpmeout[MAXTPCNT];

inline int GetNode(int tp) {
	if (tpidx[tp] < 0) {
		tpidx[tp] = ntp;
		tpmeout[ntp].clear();
		ntp++;
	}
	return tpidx[tp];
}

inline void AddEdge(int tp1, int tp2, int eidx) {
	int n1 = GetNode(tp1), n2 = GetNode(tp2);
	tpmeout[n1].push_back(eidx);
}

int nedges, maxtpval;
vector<pair<int, pair<int, int> > > new_sorted_edges;
vector<pair<int, pair<int, pair<int, pair<int, pair<int, int> > > > > > new_sorted_edges2;
vector<pair<double, int> > we;

void Init() {
	for (int i = 0; i < A; i++) {
		pickup_from[i].clear();
		dropoff_at[i].clear();
		tpve_pickup_from_airport[i].clear();
		tpve_dropoff_at_airport_tstart[i].clear();
		tpve_dropoff_at_airport_tlinear[i].clear();
	}
	for (int i = 0; i < Q; i++) {
		if (order[i].from < A) pickup_from[order[i].from].push_back(make_pair(order[i].moment, i));
		else dropoff_at[order[i].to].push_back(i);
	}
	nedges = ntp = 0;

	SCALE_FACTOR = 30;
	MAX_PAIRS = 9;

	maxtpval = (ONE_DAY / SCALE_FACTOR) * N + N - 1;
	for (int i = 0; i < maxtpval; i++) {
		tpidx[i] = -1;
		intps[i] = 0;
	}

	for (int a = 0; a < A; a++) {
		// Pickup from airport a.
		sort(pickup_from[a].begin(), pickup_from[a].end());
		int gstart = 0;
		for (int i = 0; i < pickup_from[a].size(); i++) {
			if (pickup_from[a][i].first != pickup_from[a][gstart].first) gstart = i;
			int oid = pickup_from[a][i].second;
			// Single order move.
			etmp.o1 = oid; etmp.o2 = -1;
			etmp.tdrive = t[a][order[oid].to];
			etmp.dist = d[a][order[oid].to];
			int tstart = order[oid].moment; int tend = order[oid].moment + t[a][order[oid].to] + 2 * TEN_MINUTES;
			etmp.tpdest = PACK(tend, order[oid].to);
			tpve[nedges] = etmp;
			tpve_pickup_from_airport[a].push_back(make_pair(tstart, nedges));
			int tpsrc = PACK(tstart, a);
			AddEdge(tpsrc, etmp.tpdest, nedges);
			nedges++;
		
			for (int j = gstart; j < pickup_from[a].size() && pickup_from[a][j].first == pickup_from[a][gstart].first; j++) {
				if (i == j) continue;
				// Two orders move.
				int oid2 = pickup_from[a][j].second;
				int tend = order[oid].moment + t[a][order[oid].to] + t[order[oid].to][order[oid2].to] + 3 * TEN_MINUTES;
				if (tend > order[oid2].moment + t[a][order[oid2].to] + 2 * TEN_MINUTES + ONE_HOUR) continue;
				etmp.o1 = oid; etmp.o2 = oid2;
				etmp.tdrive = t[a][order[oid].to] + t[order[oid].to][order[oid2].to];
				etmp.dist = d[a][order[oid].to] + d[order[oid].to][order[oid2].to];
				tstart = order[oid].moment;
				etmp.tpdest = PACK(tend, order[oid2].to);
				tpve[nedges] = etmp;
				int escore = etmp.dist - d[a][order[oid].to] - d[a][order[oid2].to];
				new_sorted_edges.push_back(make_pair(escore, make_pair(nedges, tstart)));
				nedges++;
			}
			sort(new_sorted_edges.begin(), new_sorted_edges.end());
			for (int j = 0; j < new_sorted_edges.size() && j < MAX_PAIRS; j++) {
				int eidx = new_sorted_edges[j].second.first;
				int tstart = new_sorted_edges[j].second.second;
				const auto& edge = tpve[eidx];
				tpve_pickup_from_airport[a].push_back(make_pair(tstart, eidx));
				AddEdge(tpsrc, edge.tpdest, eidx);
			}
			new_sorted_edges.clear();
		}
		sort(tpve_pickup_from_airport[a].begin(), tpve_pickup_from_airport[a].end());

		// Drop off at airport a.
		sort(dropoff_at[a].begin(), dropoff_at[a].end());
		for (int i = 0; i < dropoff_at[a].size(); i++) {
			int oid = dropoff_at[a][i];
			// Single order move.
			etmp.o1 = oid; etmp.o2 = -1;
			etmp.tdrive = t[order[oid].from][a];
			etmp.dist = d[order[oid].from][a];
			int tstart = order[oid].moment - t[order[oid].from][a] - 2 * TEN_MINUTES - ONE_HOUR;
			if (tstart >= 0) {
				int tend = tstart + t[order[oid].from][a] + 2 * TEN_MINUTES;
				etmp.tpdest = PACK(tend, a);
				tpve[nedges] = etmp;
				tpve_dropoff_at_airport_tstart[a].push_back(make_pair(tstart, nedges));
				tpve_dropoff_at_airport_tlinear[a].push_back(make_pair(make_pair(tstart + ONE_HOUR, tstart), make_pair(nedges, tend)));
				int tpsrc = PACK(tstart, order[oid].from);
				AddEdge(tpsrc, etmp.tpdest, nedges);
				nedges++;
			}

			for (int j = 0; j < dropoff_at[a].size(); j++) {
				if (i == j) continue;
				// Two orders move.
				int oid2 = dropoff_at[a][j];
				int tstart, tlinear, tmax_reach_oid2 = order[oid2].moment - t[order[oid2].from][a] - 2 * TEN_MINUTES;
				tstart = order[oid].moment - t[order[oid].from][a] - 2 * TEN_MINUTES - ONE_HOUR;
				tlinear = tstart + ONE_HOUR;
				int treach_oid2 = tstart + TEN_MINUTES + t[order[oid].from][order[oid2].from];
				if (treach_oid2 > tmax_reach_oid2) continue;
				if (treach_oid2 < tmax_reach_oid2 - ONE_HOUR) {
					tstart += (tmax_reach_oid2 - ONE_HOUR - treach_oid2);
					treach_oid2 = tmax_reach_oid2 - ONE_HOUR;
					if (tstart > tlinear) tstart = tlinear;
				} else {
					tlinear = tstart + (tmax_reach_oid2 - treach_oid2);
				}
				int tend = treach_oid2 + t[order[oid2].from][a] + 2 * TEN_MINUTES;
				if (tend > order[oid].moment || tend > order[oid2].moment) continue;
				
				int tlinear_end = tend + (tlinear - tstart);
				if (tlinear_end > order[oid].moment) {
					tlinear -= (tlinear_end - order[oid].moment);
					tlinear_end = order[oid].moment;
				}
				if (tlinear_end > order[oid2].moment) {
					tlinear -= (tlinear_end - order[oid2].moment);
					tlinear_end = order[oid2].moment;
				}
				etmp.o1 = oid; etmp.o2 = oid2;
				etmp.tdrive = t[order[oid].from][order[oid2].from] + t[order[oid2].from][a];
				etmp.dist = d[order[oid].from][order[oid2].from] + d[order[oid2].from][a];
				etmp.tpdest = PACK(tend, a);
				int tpsrc = PACK(tstart, order[oid].from);
				tpve[nedges] = etmp;
				int escore = etmp.dist - d[order[oid].from][a] - d[order[oid2].from][a];
				new_sorted_edges2.push_back(make_pair(escore, make_pair(nedges, make_pair(tlinear, make_pair(tend, make_pair(tstart, tpsrc))))));
				nedges++;
			}
			sort(new_sorted_edges2.begin(), new_sorted_edges2.end());
			for (int j = 0; j < new_sorted_edges2.size() && j < MAX_PAIRS; j++) {
				int eidx = new_sorted_edges2[j].second.first;
				int tstart = new_sorted_edges2[j].second.second.second.second.first; 
				const auto& edge = tpve[eidx];
				if (tstart >= 0) {
					tpve_dropoff_at_airport_tstart[a].push_back(make_pair(tstart, eidx));
					int tpsrc = new_sorted_edges2[j].second.second.second.second.second; 
					AddEdge(tpsrc, edge.tpdest, eidx);
				}
				int tlinear = new_sorted_edges2[j].second.second.first;
				int tend = new_sorted_edges2[j].second.second.second.first;
				if (tstart < tlinear && tlinear >= 0) tpve_dropoff_at_airport_tlinear[a].push_back(make_pair(make_pair(tlinear, tstart), make_pair(eidx, tend)));
			}
			new_sorted_edges2.clear();
		}
		sort(tpve_dropoff_at_airport_tstart[a].begin(), tpve_dropoff_at_airport_tstart[a].end());
		sort(tpve_dropoff_at_airport_tlinear[a].begin(), tpve_dropoff_at_airport_tlinear[a].end());
	}

	tps.clear();
	for (int i = 0; i < D; i++) {
		int tp = PACK(driver[i].start, driver[i].garage);
		int node = GetNode(tp);
		if (!intps[tp]) {
			tps.insert(tp);
			intps[tp] = 1;
		}
	}

	while (tps.size() > 0 && nedges < MAX_EDGES) {
		const auto& tpsit = tps.begin();
		int time_place = *tpsit, time, place;
		UNPACK(*tpsit, time, place);
		tps.erase(tpsit);
		int time_next = time + WAIT_STEP;
		time_next -= (time_next % WAIT_STEP);
		if (time_next < ONE_DAY) {
			etmp.o1 = etmp.o2 = -1;
			etmp.tdrive = etmp.dist = 0;
			etmp.tpdest = PACK(time_next, place);
			tpve[nedges] = etmp;
			AddEdge(time_place, etmp.tpdest, nedges);
			nedges++;
			if (!intps[etmp.tpdest]) {
				tps.insert(etmp.tpdest);
				intps[etmp.tpdest] = 1;
			}
		}

		for (int a = 0; a < A; a++) {
			// Pickup from airport a.
			int ta = time + t[place][a];
			int ta_next = ta + time_next - time;
			int li = 0, ls = tpve_pickup_from_airport[a].size() - 1, mid;
			int startidx = ls + 1;
			while (li <= ls) {
				mid = (li + ls) >> 1;
				if (tpve_pickup_from_airport[a][mid].first < ta) li = mid + 1;
				else {
					startidx = mid;
					ls = mid - 1;
				}
			}
			for (int i = startidx; i < tpve_pickup_from_airport[a].size() && nedges < MAX_EDGES; i++) {
				const auto& edge = tpve[tpve_pickup_from_airport[a][i].second];
				int etstart = tpve_pickup_from_airport[a][i].first;
				if (etstart == time || etstart >= ta_next) break;
				etmp.o1 = etmp.o2 = -1;
				etmp.tdrive = t[place][a];
				etmp.dist = d[place][a];
				etmp.tpdest = PACK(etstart, a);
				tpve[nedges] = etmp;
				AddEdge(time_place, etmp.tpdest, nedges);
				nedges++;
				if (!intps[edge.tpdest]) {
					tps.insert(edge.tpdest);
					intps[edge.tpdest] = 1;
				}
			}

			// Drop off at airport a (tstart).
			li = 0; ls = tpve_dropoff_at_airport_tstart[a].size() - 1, mid;
			startidx = ls + 1;
			while (li <= ls) {
				mid = (li + ls) >> 1;
				if (tpve_dropoff_at_airport_tstart[a][mid].first <= time) li = mid + 1;
				else {
					startidx = mid;
					ls = mid - 1;
				}
			}
			for (int i = startidx; i < tpve_dropoff_at_airport_tstart[a].size() && nedges < MAX_EDGES; i++) {
				const auto& edge = tpve[tpve_dropoff_at_airport_tstart[a][i].second];
				int etstart = tpve_dropoff_at_airport_tstart[a][i].first;
				if (place == order[edge.o1].from && time == etstart) continue;
				ta = time + t[place][order[edge.o1].from];
				if (etstart < ta) continue;
				ta_next = ta + time_next - time;
				if (etstart >= ta_next) continue;
				etmp.o1 = etmp.o2 = -1;
				etmp.tdrive = t[place][order[edge.o1].from];
				etmp.dist = d[place][order[edge.o1].from];
				etmp.tpdest = PACK(etstart, order[edge.o1].from);
				tpve[nedges] = etmp;
				AddEdge(time_place, etmp.tpdest, nedges);
				nedges++;
				if (!intps[edge.tpdest]) {
					tps.insert(edge.tpdest);
					intps[edge.tpdest] = 1;
				}
			}

			// Drop off at airport a (tlinear).
			li = 0; ls = tpve_dropoff_at_airport_tlinear[a].size() - 1, mid;
			startidx = ls + 1;
			while (li <= ls) {
				mid = (li + ls) >> 1;
				if (tpve_dropoff_at_airport_tlinear[a][mid].first.first <= time) li = mid + 1;
				else {
					startidx = mid;
					ls = mid - 1;
				}
			}
			for (int i = startidx; i < tpve_dropoff_at_airport_tlinear[a].size() && nedges < MAX_EDGES; i++) {
				const auto& edge = tpve[tpve_dropoff_at_airport_tlinear[a][i].second.first];
				int tmin = tpve_dropoff_at_airport_tlinear[a][i].first.second;
				int tmax = tpve_dropoff_at_airport_tlinear[a][i].first.first;
				int tend = tpve_dropoff_at_airport_tlinear[a][i].second.second;
				ta = time + t[place][order[edge.o1].from];
				if (ta <= tmin || ta > tmax) continue;
				etmp = edge;
				tend += (ta - tmin);
				etmp.tdrive += t[place][order[edge.o1].from];
				etmp.dist += d[place][order[edge.o1].from];
				etmp.tpdest = PACK(tend, a);
				tpve[nedges] = etmp;
				AddEdge(time_place, etmp.tpdest, nedges);
				nedges++;
				if (!intps[etmp.tpdest]) {
					tps.insert(etmp.tpdest);
					intps[etmp.tpdest] = 1;
				}
			}
		}
	}
	for (int i = 0; i < ntp; i++) {
		we.resize(tpmeout[i].size());
		for (int j = 0; j < tpmeout[i].size(); j++) {
			we[j].first = 1e30;
			int eidx = tpmeout[i][j], no = 0;
			if (tpve[eidx].o1 >= 0) no++;
			if (tpve[eidx].o2 >= 0) no++;
			if (no > 0) we[j].first = (double) tpve[eidx].dist / (double) no;
			//else if (tpve[eidx].tdrive == 0) we[j].first -= 1e10;
			we[j].second = eidx;
		}
		sort(we.begin(), we.end());
		for (int j = 0; j < we.size(); j++)
			tpmeout[i][j] = we[j].second;
	}
#ifdef LOCAL
	fprintf(stderr, "ntp=%d ne=%d\n", ntp, nedges);
#endif
}

int order_taken[NMAX];

struct ScoreInfo {
	int tdrive, next_eidx, computed;
	short int garage_mask;
	int norders, penalty;
	double score;
};

int computed_idx;

#define HMAX 13
#define GMAX 10
unordered_set<int> avail_drivers[HMAX][GMAX];

int TFINISH, h, GMASK;
struct ScoreInfo mscore[MAXTPCNT];

vector<int> good_eidx;

int MAX_NEXT_EDGES, MIN_NORDERS = 0;

void DFS(int time_place) {
	int node = tpidx[time_place];
	if (mscore[node].computed == computed_idx) return;	
	int time, place;
	UNPACK(time_place, time, place);
	struct ScoreInfo& sinfo = mscore[node];
	sinfo.tdrive = sinfo.norders = 0;
	sinfo.penalty = 0;//1000000000;
	sinfo.score = 1e30;
	sinfo.next_eidx = -1;
	sinfo.garage_mask = 0;
	if (time > TFINISH) return;
	
	for (int g = 0; g < G; g++) {
		if (avail_drivers[h][g].empty() || (GMASK & (1 << g)) == 0) continue;
		if (time + t[place][A + g] <= TFINISH && t[place][A + g] <= NINE_HOURS) {
			sinfo.garage_mask |= (1 << g);
			if (d[place][A + g] < sinfo.penalty) {
				sinfo.tdrive = t[place][A + g];
				sinfo.penalty = d[place][A + g];
			}
		}
	}

	sinfo.penalty += BASE_PENALTY;
	sinfo.score = 1e10 + sinfo.penalty;

	int num_order_edges = 0;
	int nbad = 0;

	for (const auto& eidx : tpmeout[node]) {
		const auto& edge = tpve[eidx];
		if (edge.o1 >= 0 && order_taken[edge.o1]) {
			nbad++;
			continue;
		}
		if (edge.o2 >= 0 && order_taken[edge.o2]) {
			nbad++;
			continue;
		}
		
		if (edge.o1 >= 0) {
			//fprintf(stderr, "level=%d: noe=%d %lf dist=%d o1=%d o2=%d\n", level, num_order_edges, w_eidx.first, edge.dist, edge.o1, edge.o2);
			num_order_edges++;
			if (num_order_edges > MAX_NEXT_EDGES) break;
		} //else if (edge.tdrive == 0 && sinfo.norders > 0) continue;
		
		DFS(edge.tpdest);
		
		const ScoreInfo& esinfo = mscore[tpidx[edge.tpdest]];
		if (esinfo.garage_mask == 0 || esinfo.score > 1e20) continue;
		if (edge.o1 < 0 && esinfo.norders == 0) continue;
		
		int new_tdrive = edge.tdrive + esinfo.tdrive;
		if (new_tdrive > NINE_HOURS) continue;
		int new_penalty = esinfo.penalty + edge.dist;
		int new_norders = esinfo.norders;
		if (edge.o1 >= 0) new_norders++;
		if (edge.o2 >= 0) new_norders++;

		double new_score;
		if (new_norders > 0) new_score = (double) new_penalty / (double) new_norders;
		else new_score = 1e10 + new_penalty;
		
		if ((new_norders == 0 && 1e10 + new_penalty < sinfo.score) ||
			(sinfo.norders < MIN_NORDERS && new_norders > sinfo.norders) ||
			((new_norders >= sinfo.norders || new_norders >= MIN_NORDERS) && new_score < sinfo.score)) {
			int eidx2 = esinfo.next_eidx;
			if (edge.o1 < 0 && eidx2 >= 0) {
				if (tpve[eidx2].o1 < 0 && edge.tdrive > 0) continue;
				if (edge.tdrive > 0 && eidx2 >= 0 && tpve[eidx2].o1 >= 0) {
					int time_next, place_next;
					UNPACK(edge.tpdest, time_next, place_next);
					if (place_next != order[tpve[eidx2].o1].from) continue;
				}
			} else if (eidx2 >= 0) {
				int good = 1;
				for (int cnt = 0; eidx2 >= 0 && cnt < 5; eidx2 = mscore[tpidx[tpve[eidx2].tpdest]].next_eidx, cnt++) {
					if (edge.o1 >= 0 && (edge.o1 == tpve[eidx2].o1 || edge.o1 == tpve[eidx2].o2)) {
						good = 0; break;
					}
					if (edge.o2 >= 0 && (edge.o2 == tpve[eidx2].o1 || edge.o2 == tpve[eidx2].o2)) {
						good = 0; break;
					}
				}
				if (!good) continue;
			}
			sinfo.score = new_score;
			sinfo.tdrive = new_tdrive;
			sinfo.penalty = new_penalty;
			sinfo.norders = new_norders;
			sinfo.garage_mask = esinfo.garage_mask;
			sinfo.next_eidx = eidx;
		}
	}

	if (nbad > 10) { //&& nbad > (tpmeout[node].size() >> 3)) {
		good_eidx.clear();
		for (const auto& eidx : tpmeout[node]) {
			const auto& edge = tpve[eidx];
			if (edge.o1 >= 0 && order_taken[edge.o1]) continue;
			if (edge.o2 >= 0 && order_taken[edge.o2]) continue;
			good_eidx.push_back(eidx);
		}
		tpmeout[node] = good_eidx;
	}

	mscore[node].computed = computed_idx;
}

struct BestPath {
	int ops[OPMAX][4], nops, o[OPMAX], no, tdrive, dist, tfin;
	double score;
} bpath[HMAX][GMAX];

int order_taken_this_move[NMAX], order_taken_this_move_idx;

struct State {
	int nops, no, tdrive, dist, tfin, cplace;
	double score;
} state;

void SaveState(int cplace, const struct BestPath& bpath) {
	state.nops = bpath.nops;
	state.no = bpath.no;
	state.tdrive = bpath.tdrive;
	state.dist = bpath.dist;
	state.tfin = bpath.tfin;
	state.score = bpath.score;
	state.cplace = cplace;
}

void RestoreState(int &cplace, struct BestPath& bpath) {
	bpath.nops = state.nops;
	bpath.no = state.no;
	bpath.tdrive = state.tdrive;
	bpath.dist = state.dist;
	bpath.tfin = state.tfin;
	bpath.score = state.score;
	cplace = state.cplace;
}

void HandleMoveNow(int dest, int& cplace, struct BestPath& bpath) {
	if (cplace != dest) {
		AddMoveOp(bpath.tfin, dest, bpath.ops, bpath.nops);
		bpath.tfin += t[cplace][dest];
		bpath.tdrive += t[cplace][dest];
		bpath.dist += d[cplace][dest];
		bpath.score -= d[cplace][dest];
		cplace = dest;
	}
}

int HandleSingleOrder(int oid, int& cplace, struct BestPath& bpath) {
	if (order[oid].from < A && bpath.tfin + t[cplace][order[oid].from] > order[oid].moment) return 0;
	if (order[oid].from >= A && bpath.tfin + t[cplace][order[oid].from] > order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES) return 0;
	if (order[oid].from != cplace && bpath.nops > 0 && bpath.ops[bpath.nops - 1][0] == MOVE_OP) RestoreState(cplace, bpath);
	HandleMoveNow(order[oid].from, cplace, bpath);
	if (order[oid].from < A)
		bpath.tfin = order[oid].moment;
	else if (bpath.tfin < order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES - ONE_HOUR)
		bpath.tfin = order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES - ONE_HOUR;
	AddPickup1Op(bpath.tfin, oid, bpath.ops, bpath.nops);
	bpath.tfin += TEN_MINUTES;
	HandleMoveNow(order[oid].to, cplace, bpath);	
	AddDropoff1Op(bpath.tfin, oid, bpath.ops, bpath.nops);
	bpath.tfin += TEN_MINUTES;
	if (order[oid].from >= A && bpath.tfin > order[oid].moment) return 0;
	bpath.o[bpath.no++] = oid;
	order_taken_this_move[oid] = order_taken_this_move_idx;
	bpath.score += MISS_PENALTY;
	return 1;
}

int HandleTwoOrders(int o1, int o2, int& cplace, struct BestPath& bpath) {
	if (order[o1].from < A && bpath.tfin + t[cplace][order[o1].from] > order[o1].moment) return 0;
	if (order[o1].from >= A && bpath.tfin + t[cplace][order[o1].from] > order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES) return 0;
	if (order[o1].from != cplace && bpath.nops > 0 && bpath.ops[bpath.nops - 1][0] == MOVE_OP) RestoreState(cplace, bpath);
	HandleMoveNow(order[o1].from, cplace, bpath);
	if (order[o1].from == order[o2].from) {
		bpath.tfin = order[o1].moment;
		AddPickup2Op(order[o1].moment, o1, o2, bpath.ops, bpath.nops);
		bpath.tfin += TEN_MINUTES;
		HandleMoveNow(order[o1].to, cplace, bpath);
		AddDropoff1Op(bpath.tfin, o1, bpath.ops, bpath.nops);
		bpath.tfin += TEN_MINUTES;
		HandleMoveNow(order[o2].to, cplace, bpath);
		AddDropoff1Op(bpath.tfin, o2, bpath.ops, bpath.nops);		
		bpath.tfin += TEN_MINUTES;
	} else {
		if (bpath.tfin < order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR)		
			bpath.tfin = order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR;
		AddPickup1Op(bpath.tfin, o1, bpath.ops, bpath.nops);
		bpath.tfin += TEN_MINUTES;
		if (bpath.tfin + t[cplace][order[o2].from] > order[o2].moment - t[order[o2].from][order[o2].to] - 2 * TEN_MINUTES) {
			o2 = -1;
		} else {
			HandleMoveNow(order[o2].from, cplace, bpath);
			if (bpath.tfin < order[o2].moment - t[order[o2].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR)		
				bpath.tfin = order[o2].moment - t[order[o2].from][order[o2].to] - 2 * TEN_MINUTES - ONE_HOUR;
			AddPickup1Op(bpath.tfin, o2, bpath.ops, bpath.nops);
			bpath.tfin += TEN_MINUTES;
		}
		HandleMoveNow(order[o1].to, cplace, bpath);
		if (o2 >= 0) AddDropoff2Op(bpath.tfin, o1, o2, bpath.ops, bpath.nops);
		else AddDropoff1Op(bpath.tfin, o1, bpath.ops, bpath.nops);
		bpath.tfin += TEN_MINUTES;
		if (bpath.tfin > order[o1].moment) return 0;
		if (o2 >= 0 && bpath.tfin > order[o2].moment) return 0;
	}
	order_taken_this_move[o1] = order_taken_this_move_idx;
	bpath.score += MISS_PENALTY;
	bpath.o[bpath.no++] = o1;
	if (o2 >= 0) {
		order_taken_this_move[o2] = order_taken_this_move_idx;
		bpath.score += MISS_PENALTY;
		bpath.o[bpath.no++] = o2;
	}
	return 1;
}

void GetSequenceOfMoves(int time_place, struct BestPath& bpath) {
	bpath.score = 0;
	bpath.tdrive = 0;
	bpath.dist = 0;
	bpath.no = bpath.nops = 0;
	int time, place, cplace, time_next, place_next;
	UNPACK(time_place, time, place);
	bpath.tfin = time; cplace = place;
	order_taken_this_move_idx++;
	SaveState(cplace, bpath);
	while (1) {
		int eidx = mscore[tpidx[time_place]].next_eidx;
		if (eidx < 0) break;
		const auto& edge = tpve[eidx];
		UNPACK(edge.tpdest, time_next, place_next);
		char handled_order = 0, restore_state = 0;
		if (edge.o1 < 0) {
			if (place_next != cplace && bpath.nops > 0 && bpath.ops[bpath.nops - 1][0] == MOVE_OP) {
				RestoreState(cplace, bpath);
			}
			HandleMoveNow(place_next, cplace, bpath);
		} else if (edge.o1 >= 0 && edge.o2 < 0) {
			if (order_taken_this_move[edge.o1] != order_taken_this_move_idx)
				handled_order = HandleSingleOrder(edge.o1, cplace, bpath);
			if (!handled_order) restore_state = 1;
		} else {
			if (order_taken_this_move[edge.o1] != order_taken_this_move_idx &&
				order_taken_this_move[edge.o2] != order_taken_this_move_idx)
				handled_order = HandleTwoOrders(edge.o1, edge.o2, cplace, bpath);
			else if (order_taken_this_move[edge.o1] != order_taken_this_move_idx)
				handled_order = HandleSingleOrder(edge.o1, cplace, bpath);
			else if (order_taken_this_move[edge.o2] != order_taken_this_move_idx)
				handled_order = HandleSingleOrder(edge.o2, cplace, bpath);
			if (!handled_order) restore_state = 1;
		}
		if (restore_state || bpath.tfin + t[cplace][place] > time + 12 * ONE_HOUR) RestoreState(cplace, bpath);
		else if (handled_order && bpath.tdrive + t[cplace][place] <= NINE_HOURS) SaveState(cplace, bpath);
		time_place = edge.tpdest;
	}
	RestoreState(cplace, bpath);
	//assert(bpath.tfin <= time + 12 * ONE_HOUR);
	HandleMoveNow(place, cplace, bpath);
	//assert(bpath.tdrive <= NINE_HOURS);
	//assert(bpath.tfin <= time + 12 * ONE_HOUR);
	if (bpath.no == 0) bpath.score = 1e30;
	else bpath.score = (BASE_PENALTY + bpath.dist) / bpath.no;
}

int order_tried_as_first[NMAX], bgarage[HMAX];

int Greedy() {
	int tle = 0, critical = 0;
	for (int i = 0; i < HMAX; i++) {
		for (int j = 0; j < G; j++) {
			avail_drivers[i][j].clear();
			bpath[i][j].nops = 0;
			bpath[i][j].no = -1;
		}
		bgarage[i] = -1;
	}
	for (int i = 0; i < D; i++)
		avail_drivers[driver[i].start / ONE_HOUR][driver[i].garage - A].insert(i);
	for (int i = 0; i < Q; i++) {
		order_taken[i] = order_taken_this_move[i] = order_tried_as_first[i] = 0;
	}
	for (int i = 0; i < ntp; i++) mscore[i].computed = 0;
	computed_idx = 0;
	order_taken_this_move_idx = 0;
	int num_used_drivers = 0, num_taken_orders = 0;
	InitSol(csol, cgscore);
	cgscore = 0;
	MAX_NEXT_EDGES = 100;

	while (!tle) {
		// Select the schedule for one more driver.
		double best_score = 1e9;
		int best_hour = -1, best_garage = -1, hmin = 0, hmax = HMAX - 1;
		for (h = hmax; h >= hmin; h--) {
			int needs_update;
			if (bgarage[h] < 0) needs_update = 1;
			else {
				needs_update = 0;
				for (int i = 0; i < bpath[h][bgarage[h]].no; i++)
					if (order_taken[bpath[h][bgarage[h]].o[i]]) {
						needs_update = 1;
						break;
					}
			}
			if (needs_update) {
				bgarage[h] = -1;			
				computed_idx++;
				GMASK = (1 << G) - 1;
				for (int g = 0; g < G; g++) {
					if (avail_drivers[h][g].empty() || (GMASK & (1 << g)) == 0) continue;
					int time_place = PACK(h * ONE_HOUR, A + g), updated = 0;
					int node = tpidx[time_place];
					TFINISH = (h + 12) * ONE_HOUR;
					DFS(time_place);
					if (DEBUG >= 2) fprintf(stderr, "  num_used_drivers=%d: h=%d g=%d: navail=%d estsc=%.3lf gmask=%d/%d", num_used_drivers, h, g, avail_drivers[h][g].size(), mscore[node].score, mscore[node].garage_mask, GMASK);
					bpath[h][g].score = 0; bpath[h][g].no = 0;
					//GMASK = mscore[node].garage_mask;
					if ((mscore[node].garage_mask & (1 << g)) > 0 && mscore[node].norders > 0) {
						GetSequenceOfMoves(time_place, bpath[h][g]);
						if (DEBUG >= 2) fprintf(stderr, " rsc=%.3lf no=%d dist=%d tdrive=%d tfin=%d", bpath[h][g].score, bpath[h][g].no, bpath[h][g].dist, bpath[h][g].tdrive, bpath[h][g].tfin);
						if (bgarage[h] < 0 || bpath[h][g].score < bpath[h][bgarage[h]].score) bgarage[h] = g;
					}
				}
				int tnow = GetTime();
				if (tnow > TCRITICAL) critical = 1;
				if (tnow > TEND) {
					tle = 1; break;
				}
			}		
			if (bgarage[h] >= 0 && bpath[h][bgarage[h]].score < best_score) {
				best_score = bpath[h][bgarage[h]].score;
				best_hour = h;
				best_garage = bgarage[h];
				if (critical) break;
			}
		}
		if (best_hour < 0) break;
		int did = *avail_drivers[best_hour][best_garage].begin();
		avail_drivers[best_hour][best_garage].erase(did);
		num_used_drivers++;

		csol[did].nops = bpath[best_hour][best_garage].nops;
		memcpy(&csol[did].ops[0], &bpath[best_hour][best_garage].ops[0], csol[did].nops * sizeof(csol[did].ops[0]));

		for (int i = 0; i < bpath[best_hour][best_garage].no; i++) {
			int oid = bpath[best_hour][best_garage].o[i];
			assert(!order_taken[oid]);
			order_taken[oid] = 1;
			num_taken_orders++;
		}

		bgarage[best_hour] = -1;

		cgscore += bpath[best_hour][best_garage].dist + BASE_PENALTY;

		if (DEBUG >= 1) fprintf(stderr, "%d: best_score=%.3lf bh=%d bg=%d: cgscore=%d nct=%d nto=%d/%d\n", num_used_drivers, best_score, best_hour, best_garage, cgscore, bpath[best_hour][best_garage].no, num_taken_orders, Q);
	}
	int num_missed_orders = 0;
	for (int i = 0; i < Q; i++)
		if (!order_taken[i]) {
			num_missed_orders++;
			cgscore += MISS_PENALTY;
		}
#ifdef LOCAL
	fprintf(stderr, "cgscore=%d num_used_drivers=%d num_missed_orders=%d\n", cgscore, num_used_drivers, num_missed_orders);
#endif
	UpdateSol();
	return tle;
}

int Solve() {
	Init();
#ifdef LOCAL
	fprintf(stderr, "Init took %.3lf sec\n", GetTime() - TSTART);
#endif
	return Greedy();
}
}

namespace IMPROV {

#define MAX_EDGES_IMPROV 200000
#define MAX_STEPS 100000

vector<pair<int, int> > pickup_from[AMAX];
vector<int> dropoff_at[AMAX];

struct Edge {
	short int o1, o2;
	int tdrive, dist, tstart, tlinear, tend;
};

struct Edge tpve[MAX_EDGES_IMPROV], etmp;
int nedges;

struct Step {
	int tend, pstart, pend;
	int eidx, next_step;
};

struct Step step_pool[MAX_STEPS];
unordered_set<int> avail_steps;
int nsteps;

int NewStep() {
	if (nsteps < MAX_STEPS) return nsteps++;
	if (!avail_steps.empty()) {
		int new_step = *avail_steps.begin();
		avail_steps.erase(new_step);
		return new_step;
	}
	fprintf(stderr, "Too many steps!\n");
	exit(1);
}

void ReleaseStep(int sid) {
	avail_steps.insert(sid);
}

void ReleaseStepSequence(int first_step) {
	for (int step = first_step; step >= 0; step = step_pool[step].next_step)
		avail_steps.insert(step);
}

int CopyStepSequence(int first_step) {
	int new_first_step = NewStep();
	step_pool[new_first_step] = step_pool[first_step];
	int new_prev_step = new_first_step;
	for (int step = step_pool[first_step].next_step; step >= 0; step = step_pool[step].next_step) {
		int new_step = NewStep();
		step_pool[new_step] = step_pool[step];
		step_pool[new_prev_step].next_step = new_step;
		new_prev_step = new_step;
	}
	return new_first_step;
}

void Init() {
	for (int i = A; i < A + G; i++)
		for (int j = 0; j < N; j++)
			if (i != j) d[j][i] += BASE_PENALTY;

	for (int a = 0; a < A; a++) {
		pickup_from[a].clear();
		dropoff_at[a].clear();
	}
	for (int i = 0; i < Q; i++) {
		if (order[i].from < A) pickup_from[order[i].from].push_back(make_pair(order[i].moment, i));
		else dropoff_at[order[i].to].push_back(i);
	}
	nedges = 0;

	for (int a = 0; a < A; a++) {
		// Pickup from airport a.
		sort(pickup_from[a].begin(), pickup_from[a].end());
		int gstart = 0;
		for (int i = 0; i < pickup_from[a].size(); i++) {
			if (pickup_from[a][i].first != pickup_from[a][gstart].first) gstart = i;
			int oid = pickup_from[a][i].second;
			// Single order move.
			etmp.o1 = oid; etmp.o2 = -1;
			etmp.tdrive = t[a][order[oid].to];
			etmp.dist = d[a][order[oid].to];
			etmp.tstart = etmp.tlinear = order[oid].moment; etmp.tend = order[oid].moment + t[a][order[oid].to] + 2 * TEN_MINUTES;
			tpve[nedges] = etmp;
			nedges++;
			for (int j = gstart; j < pickup_from[a].size() && pickup_from[a][j].first == pickup_from[a][gstart].first; j++) {
				if (i == j) continue;
				// Two orders move.
				int oid2 = pickup_from[a][j].second;
				etmp.tend = order[oid].moment + t[a][order[oid].to] + t[order[oid].to][order[oid2].to] + 3 * TEN_MINUTES;
				if (etmp.tend > order[oid2].moment + t[a][order[oid2].to] + 2 * TEN_MINUTES + ONE_HOUR) continue;
				etmp.o1 = oid; etmp.o2 = oid2;
				etmp.tdrive = t[a][order[oid].to] + t[order[oid].to][order[oid2].to];
				etmp.dist = d[a][order[oid].to] + d[order[oid].to][order[oid2].to];
				etmp.tstart = etmp.tlinear = order[oid].moment;
				tpve[nedges] = etmp;
				nedges++;
			}
		}

		// Drop off at airport a.
		sort(dropoff_at[a].begin(), dropoff_at[a].end());
		for (int i = 0; i < dropoff_at[a].size(); i++) {
			int oid = dropoff_at[a][i];
			// Single order move.
			etmp.o1 = oid; etmp.o2 = -1;
			etmp.tdrive = t[order[oid].from][a];
			etmp.dist = d[order[oid].from][a];
			etmp.tstart = order[oid].moment - t[order[oid].from][a] - 2 * TEN_MINUTES - ONE_HOUR;
			etmp.tlinear = etmp.tstart + ONE_HOUR;
			if (etmp.tstart >= 0) {
				etmp.tend = etmp.tstart + t[order[oid].from][a] + 2 * TEN_MINUTES;
				tpve[nedges] = etmp;
				nedges++;
			}

			for (int j = 0; j < dropoff_at[a].size(); j++) {
				if (i == j) continue;
				// Two orders move.
				int oid2 = dropoff_at[a][j];
				int tmax_reach_oid2 = order[oid2].moment - t[order[oid2].from][a] - 2 * TEN_MINUTES;
				etmp.tstart = order[oid].moment - t[order[oid].from][a] - 2 * TEN_MINUTES - ONE_HOUR;
				etmp.tlinear = etmp.tstart + ONE_HOUR;
				int treach_oid2 = etmp.tstart + TEN_MINUTES + t[order[oid].from][order[oid2].from];
				if (treach_oid2 > tmax_reach_oid2) continue;
				if (treach_oid2 < tmax_reach_oid2 - ONE_HOUR) {
					etmp.tstart += (tmax_reach_oid2 - ONE_HOUR - treach_oid2);
					treach_oid2 = tmax_reach_oid2 - ONE_HOUR;
					if (etmp.tstart > etmp.tlinear) etmp.tstart = etmp.tlinear;
				} else {
					etmp.tlinear = etmp.tstart + (tmax_reach_oid2 - treach_oid2);
				}
				etmp.tend = treach_oid2 + t[order[oid2].from][a] + 2 * TEN_MINUTES;
				if (etmp.tend > order[oid].moment || etmp.tend > order[oid2].moment) continue;
				
				int tlinear_end = etmp.tend + (etmp.tlinear - etmp.tstart);
				if (tlinear_end > order[oid].moment) {
					etmp.tlinear -= (tlinear_end - order[oid].moment);
					tlinear_end = order[oid].moment;
				}
				if (tlinear_end > order[oid2].moment) {
					etmp.tlinear -= (tlinear_end - order[oid2].moment);
					tlinear_end = order[oid2].moment;
				}
				etmp.o1 = oid; etmp.o2 = oid2;
				etmp.tdrive = t[order[oid].from][order[oid2].from] + t[order[oid2].from][a];
				etmp.dist = d[order[oid].from][order[oid2].from] + d[order[oid2].from][a];
				tpve[nedges] = etmp;
				nedges++;
			}
		}
	}
#ifdef LOCAL
	fprintf(stderr, "nedges=%d\n", nedges);
#endif
}

struct DriverInfo {
	int first_step, tdrive, dist;
} dinfo[NMAX], tmpdinfo[NMAX];

int order_taken[NMAX], num_taken_orders;

int order_taken_this_move[NMAX], order_taken_this_move_idx;

struct State {
	int nops, no, tdrive, dist, tfin, cplace;
} state;

void HandleMoveNow(int dest, struct State& state, int did) {
	if (state.cplace != dest) {
		AddMoveOp(state.tfin, dest, csol[did].ops, csol[did].nops);
		state.tfin += t[state.cplace][dest];
		state.tdrive += t[state.cplace][dest];
		state.dist += d[state.cplace][dest];
		state.cplace = dest;
	}
}

void HandleSingleOrder(int oid, struct State& state, int did) {
	if (order[oid].from < A && state.tfin + t[state.cplace][order[oid].from] > order[oid].moment) exit(1);
	if (order[oid].from >= A && state.tfin + t[state.cplace][order[oid].from] > order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES) exit(2);
	HandleMoveNow(order[oid].from, state, did);
	if (order[oid].from < A)
		state.tfin = order[oid].moment;
	else if (state.tfin < order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES - ONE_HOUR)
		state.tfin = order[oid].moment - t[order[oid].from][order[oid].to] - 2 * TEN_MINUTES - ONE_HOUR;
	AddPickup1Op(state.tfin, oid, csol[did].ops, csol[did].nops);
	state.tfin += TEN_MINUTES;
	HandleMoveNow(order[oid].to, state, did);
	AddDropoff1Op(state.tfin, oid, csol[did].ops, csol[did].nops);
	state.tfin += TEN_MINUTES;
	if (order[oid].from >= A && state.tfin > order[oid].moment) exit(3);
}

void HandleTwoOrders(int o1, int o2, struct State& state, int did) {
	if (order[o1].from < A && state.tfin + t[state.cplace][order[o1].from] > order[o1].moment) exit(4);
	if (order[o1].from >= A && state.tfin + t[state.cplace][order[o1].from] > order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES) exit(5);
	HandleMoveNow(order[o1].from, state, did);
	if (order[o1].from == order[o2].from) {
		state.tfin = order[o1].moment;
		AddPickup2Op(order[o1].moment, o1, o2, csol[did].ops, csol[did].nops);
		state.tfin += TEN_MINUTES;
		HandleMoveNow(order[o1].to, state, did);
		AddDropoff1Op(state.tfin, o1, csol[did].ops, csol[did].nops);
		state.tfin += TEN_MINUTES;
		HandleMoveNow(order[o2].to, state, did);
		AddDropoff1Op(state.tfin, o2, csol[did].ops, csol[did].nops);		
		state.tfin += TEN_MINUTES;
	} else {
		if (state.tfin < order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR)
			state.tfin = order[o1].moment - t[order[o1].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR;
		AddPickup1Op(state.tfin, o1, csol[did].ops, csol[did].nops);
		state.tfin += TEN_MINUTES;
		if (state.tfin + t[state.cplace][order[o2].from] > order[o2].moment - t[order[o2].from][order[o2].to] - 2 * TEN_MINUTES) exit(6);
		HandleMoveNow(order[o2].from, state, did);
		if (state.tfin < order[o2].moment - t[order[o2].from][order[o1].to] - 2 * TEN_MINUTES - ONE_HOUR)		
			state.tfin = order[o2].moment - t[order[o2].from][order[o2].to] - 2 * TEN_MINUTES - ONE_HOUR;
		AddPickup1Op(state.tfin, o2, csol[did].ops, csol[did].nops);
		state.tfin += TEN_MINUTES;
		HandleMoveNow(order[o1].to, state, did);
		AddDropoff2Op(state.tfin, o1, o2, csol[did].ops, csol[did].nops);
		state.tfin += TEN_MINUTES;
		if (state.tfin > order[o1].moment) exit(7);
		if (state.tfin > order[o2].moment) exit(8);
	}
}

void GetSequenceOfMoves(int did) {
	state.tdrive = 0;
	state.dist = 0;
	state.tfin = driver[did].start;
	state.cplace = driver[did].garage;
	int cstep = dinfo[did].first_step;
	while (cstep >= 0) {
		HandleMoveNow(step_pool[cstep].pstart, state, did);
		int eidx = step_pool[cstep].eidx;
		if (eidx >= 0) {
			const auto& edge = tpve[eidx];
			if (edge.o1 >= 0 && edge.o2 < 0) {
				HandleSingleOrder(edge.o1, state, did);
			} else {
				HandleTwoOrders(edge.o1, edge.o2, state, did);
			}
		}
		cstep = step_pool[cstep].next_step;
	}
}

int InsertEdge(int pstep, int nstep, int eidx, int estart, int eend, int do_insert) {
	const struct Edge& edge = tpve[eidx];
	int tcurr = step_pool[pstep].tend;
	tcurr += t[step_pool[pstep].pend][estart];
	if (tcurr <= edge.tstart) tcurr = edge.tend;
	else if (tcurr <= edge.tlinear) tcurr = edge.tend + (tcurr - edge.tstart);
	else return 0;
	if (do_insert) {
		int new_step = NewStep();
		step_pool[pstep].next_step = new_step;
		step_pool[new_step].next_step = nstep;
		step_pool[new_step].eidx = eidx;
		step_pool[new_step].tend = tcurr;
		step_pool[new_step].pstart = estart; step_pool[new_step].pend = eend;
	}
	int cstep = nstep, cplace = eend;
	while (cstep >= 0) {
		tcurr += t[cplace][step_pool[cstep].pstart];
		if (step_pool[cstep].eidx < 0) {
			if (tcurr > step_pool[cstep].tend) return 0;
		} else {
			const struct Edge& edge2 = tpve[step_pool[cstep].eidx];
			if (tcurr <= edge2.tstart) return 1;
			if (tcurr > edge2.tlinear) return 0;
			tcurr = edge2.tend + (tcurr - edge2.tstart);
			if (do_insert) step_pool[cstep].tend = tcurr;
			cplace = step_pool[cstep].pend;
		}
		cstep = step_pool[cstep].next_step;
	}
	return 1;
}

vector<pair<double, int> > wedges;
char dused[NMAX];
int used_drivers[NMAX];

void FindBestDriver(int eidx, int estart, int eend, int can_use_new_driver, double& best_score, int& best_distdif, int& best_pstep, int& best_nstep, int& best_driver, int& best_eidx) {
	const struct Edge& edge = tpve[eidx];
	int no = 1; if (edge.o2 >= 0) no++;
	for (int i = 0; i < D; i++) {
		if (!can_use_new_driver && !dused[i]) continue;
		for (int pstep = dinfo[i].first_step, nstep = step_pool[dinfo[i].first_step].next_step; nstep >= 0; pstep = step_pool[pstep].next_step, nstep = step_pool[nstep].next_step) {
			// Try to insert the edge between pstep and nstep.
			int new_tdrive = dinfo[i].tdrive + t[step_pool[pstep].pend][estart] + edge.tdrive + t[eend][step_pool[nstep].pstart] - t[step_pool[pstep].pend][step_pool[nstep].pstart];
			if (new_tdrive > NINE_HOURS) continue;
			int distdif = d[step_pool[pstep].pend][estart] + edge.dist + d[eend][step_pool[nstep].pstart] - d[step_pool[pstep].pend][step_pool[nstep].pstart];
			double score = (double) distdif / (double) no;
			if (score < best_score && InsertEdge(pstep, nstep, eidx, estart, eend, 0)) {
				best_score = score;
				best_distdif = distdif;
				best_pstep = pstep;
				best_nstep = nstep;
				best_driver = i;
				best_eidx = eidx;
			}
		}
	}
}

void InitDriver(int i) {
	dused[i] = 0;
	dinfo[i].tdrive = dinfo[i].dist = 0;
	dinfo[i].first_step = NewStep();
	step_pool[dinfo[i].first_step].eidx = -1;
	step_pool[dinfo[i].first_step].tend = driver[i].start;
	step_pool[dinfo[i].first_step].pstart = step_pool[dinfo[i].first_step].pend = driver[i].garage;
	int last_step = step_pool[dinfo[i].first_step].next_step = NewStep();
	step_pool[last_step].eidx = -1;
	step_pool[last_step].tend = driver[i].finish;
	step_pool[last_step].pstart = step_pool[last_step].pend = driver[i].garage;
	step_pool[last_step].next_step = -1;
}

char is_tmp_driver[NMAX];
int tmp_drivers[NMAX], num_tmp_drivers;

void AddOrders(int driver, int& pstep, int o1, int o2) {
	int eidx;
	for (eidx = 0; eidx < nedges; eidx++)
		if (tpve[eidx].o1 == o1 && tpve[eidx].o2 == o2) break;
	assert(eidx < nedges);
	const auto& edge = tpve[eidx];
	int estart = order[edge.o1].from;
	int eend;
	if (edge.o2 >= 0) eend = order[edge.o2].to;
	else eend = order[edge.o1].to;

	int nstep = step_pool[pstep].next_step;
	int ddif = d[step_pool[pstep].pend][estart] + edge.dist + d[eend][step_pool[nstep].pstart] - d[step_pool[pstep].pend][step_pool[nstep].pstart];
	cgscore += ddif;
	dinfo[driver].tdrive += (t[step_pool[pstep].pend][estart] + edge.tdrive + t[eend][step_pool[nstep].pstart] - t[step_pool[pstep].pend][step_pool[nstep].pstart]);
	dinfo[driver].dist += ddif;
	assert(InsertEdge(pstep, nstep, eidx, estart, eend, 1));
	order_taken[edge.o1] = 1;
	num_taken_orders++;
	if (edge.o2 >= 0) {
		order_taken[edge.o2] = 1;
		num_taken_orders++;
	}
	pstep = step_pool[pstep].next_step;
}

int Greedy() {
	int tle = 0, critical = 0;
	nsteps = 0;
	avail_steps.clear();
	for (int i = 0; i < D; i++) InitDriver(i);
	for (int i = 0; i < Q; i++) order_taken[i] = 0;
	num_taken_orders = 0;
	InitSol(csol, cgscore);
	cgscore = 0;
	int ntested	= 0, num_used_drivers = 0;
	wedges.clear();
	for (int i = 0; i < nedges; i++) {
		const struct Edge& edge = tpve[i];
		double w = edge.dist;
		int no = 1;
		if (edge.o2 >= 0) no++;
		if (no == 1) w += 1e5;
		//w /= no;
		wedges.push_back(make_pair(w, i));
	}
	sort(wedges.begin(), wedges.end());

	// Initialize the drivers using the best solution found so far.
	for (int driver = 0; driver < D; driver++) {
		if (bsol[driver].nops == 0) continue;
		dused[driver] = 1;
		used_drivers[num_used_drivers++] = driver;
		int o1 = -1, o2 = -1, cstep = dinfo[driver].first_step;
		for (int op = 0; op < bsol[driver].nops; op++) {
			if (bsol[driver].ops[op][0] == PICKUP1_OP) {
				if (o1 < 0) o1 = bsol[driver].ops[op][2];
				else o2 = bsol[driver].ops[op][2];
			} else if (bsol[driver].ops[op][0] == PICKUP2_OP) {
				o1 = bsol[driver].ops[op][2];
				o2 = bsol[driver].ops[op][3];
				AddOrders(driver, cstep, o1, o2);
				o1 = o2 = -1;
			} else if (bsol[driver].ops[op][0] == DROPOFF1_OP) {
				if (o1 >= 0) {
					AddOrders(driver, cstep, o1, o2);
					o1 = o2 = -1;
				}
			} else if (bsol[driver].ops[op][0] == DROPOFF2_OP) {
				if (o1 >= 0) {
					AddOrders(driver, cstep, o1, o2);
					o1 = o2 = -1;
				}
			}
		}
	}
	
	if (cgscore < bgscore) {
		for (int i = 0; i < D; i++) {
			int step2 = step_pool[dinfo[i].first_step].next_step;
			if (step_pool[step2].eidx >= 0) {
				GetSequenceOfMoves(i);
			}
		}
		cgscore += (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
		UpdateSol();
		cgscore -= (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
	}

/*
	int eeidx = 0;
	while (num_taken_orders < Q && eeidx < nedges) {
		double best_score = 1e30;
		int best_distdif, best_pstep, best_nstep, best_driver, best_eidx = -1;
		{
			int eidx = wedges[eeidx].second;
			const auto& edge = tpve[eidx];
			if (order_taken[edge.o1] || (edge.o2 >= 0 && order_taken[edge.o2])) {
				eeidx++;
				continue;
			}
			int estart = order[edge.o1].from;
			int eend;
			if (edge.o2 >= 0) eend = order[edge.o2].to;
			else eend = order[edge.o1].to;
			// Try to insert the edge eidx in the best place in the schedule of some driver.
			FindBestDriver(eidx, estart, eend, 1, best_score, best_distdif, best_pstep, best_nstep, best_driver, best_eidx);
			eeidx++;
		}
		if (best_eidx < 0) continue;
		cgscore += best_distdif;
		const auto& edge = tpve[best_eidx];
		int estart = order[edge.o1].from;
		int eend;
		if (edge.o2 >= 0) eend = order[edge.o2].to;
		else eend = order[edge.o1].to;
		dinfo[best_driver].tdrive += (t[step_pool[best_pstep].pend][estart] + edge.tdrive + t[eend][step_pool[best_nstep].pstart] - t[step_pool[best_pstep].pend][step_pool[best_nstep].pstart]);
		dinfo[best_driver].dist += best_distdif;
		int step2 = step_pool[dinfo[best_driver].first_step].next_step;
		if (step_pool[step2].eidx < 0) {
			dused[best_driver] = 1;
			used_drivers[num_used_drivers++] = best_driver;
		}
		InsertEdge(best_pstep, best_nstep, best_eidx, estart, eend, 1);
		order_taken[edge.o1] = 1;
		num_taken_orders++;
		if (edge.o2 >= 0) {
			order_taken[edge.o2] = 1;
			num_taken_orders++;
		}
	}
	for (int i = 0; i < D; i++) {
		int step2 = step_pool[dinfo[i].first_step].next_step;
		if (step_pool[step2].eidx >= 0) {
			GetSequenceOfMoves(i);
		}
	}
	cgscore += (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
	UpdateSol();
	cgscore -= (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
*/

	mt.setSeed(1721881721);
	int num_iters_since_last_improvement = 0;
	while (GetTime() < TEND) {
		for (int i = 0; i < D; i++) is_tmp_driver[i] = 0;
		int max_num_taken_orders = (int) (0.95 * num_taken_orders);
		int max_num_used_drivers = (int) (0.9 * num_used_drivers);
		num_tmp_drivers = 0;
		while (num_taken_orders > max_num_taken_orders || num_used_drivers > max_num_used_drivers) {
			int did_idx = mt.NextInt() % num_used_drivers;
			int did = used_drivers[did_idx];
			used_drivers[did_idx] = used_drivers[num_used_drivers - 1];
			num_used_drivers--;
			cgscore -= dinfo[did].dist;
			is_tmp_driver[did] = 1;
			tmp_drivers[num_tmp_drivers++] = did;
			tmpdinfo[did] = dinfo[did];
			for (int step = dinfo[did].first_step; step >= 0; step = step_pool[step].next_step) {
				if (step_pool[step].eidx < 0) continue;
				const struct Edge& edge = tpve[step_pool[step].eidx];
				order_taken[edge.o1] = 0;
				num_taken_orders--;
				if (edge.o2 >= 0) {
					order_taken[edge.o2] = 0;
					num_taken_orders--;
				}
			}
			InitDriver(did);
		}
		int eeidx = 0;
		while (num_taken_orders < Q && eeidx < nedges) {
			double best_score = 1e30;
			int best_distdif, best_pstep, best_nstep, best_driver, best_eidx = -1;
			//for (int eidx = 0; eidx < nedges; eidx++) {
			{
				int eidx = wedges[eeidx].second;
				const auto& edge = tpve[eidx];
				if (order_taken[edge.o1] || (edge.o2 >= 0 && order_taken[edge.o2])) {
					eeidx++;
					continue;
				}
				int estart = order[edge.o1].from;
				int eend;
				if (edge.o2 >= 0) eend = order[edge.o2].to;
				else eend = order[edge.o1].to;
				// Try to insert the edge eidx in the best place in the schedule of some driver.
				FindBestDriver(eidx, estart, eend, 1, best_score, best_distdif, best_pstep, best_nstep, best_driver, best_eidx);
				//if (best_eidx < 0) FindBestDriver(eidx, estart, eend, 1, best_score, best_distdif, best_pstep, best_nstep, best_driver, best_eidx);
				eeidx++;
			}
			if (best_eidx < 0) break;
			cgscore += best_distdif;
			if (cgscore >= bgscore) break;
			const auto& edge = tpve[best_eidx];
			int estart = order[edge.o1].from;
			int eend;
			if (edge.o2 >= 0) eend = order[edge.o2].to;
			else eend = order[edge.o1].to;
			if (!is_tmp_driver[best_driver]) {
				is_tmp_driver[best_driver] = 1;
				tmp_drivers[num_tmp_drivers++] = best_driver;
				tmpdinfo[best_driver] = dinfo[best_driver];
				tmpdinfo[best_driver].first_step = CopyStepSequence(dinfo[best_driver].first_step);
			}
			dinfo[best_driver].tdrive += (t[step_pool[best_pstep].pend][estart] + edge.tdrive + t[eend][step_pool[best_nstep].pstart] - t[step_pool[best_pstep].pend][step_pool[best_nstep].pstart]);
			dinfo[best_driver].dist += best_distdif;
			int step2 = step_pool[dinfo[best_driver].first_step].next_step;
			if (step_pool[step2].eidx < 0) {
				dused[best_driver] = 1;
				used_drivers[num_used_drivers++] = best_driver;
			}
			InsertEdge(best_pstep, best_nstep, best_eidx, estart, eend, 1);
			order_taken[edge.o1] = 1;
			num_taken_orders++;
			if (edge.o2 >= 0) {
				order_taken[edge.o2] = 1;
				num_taken_orders++;
			}
		}
		cgscore += (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
		if (cgscore < bgscore || num_iters_since_last_improvement > 10000000) {
			long long dummy;
			InitSol(csol, dummy);
			for (int i = 0; i < D; i++) {
				int step2 = step_pool[dinfo[i].first_step].next_step;
				if (step_pool[step2].eidx >= 0) {
					GetSequenceOfMoves(i);
				}
			}
			UpdateSol();
			cgscore -= (long long) (Q - num_taken_orders) * (long long) MISS_PENALTY;
			for (int i = 0; i < num_tmp_drivers; i++) {
				int did = tmp_drivers[i];
				ReleaseStepSequence(tmpdinfo[did].first_step);
			}
			num_iters_since_last_improvement = 0;
		} else {
			for (int i = 0; i < num_tmp_drivers; i++) {
				int did = tmp_drivers[i];
				ReleaseStepSequence(dinfo[did].first_step);
				dinfo[did] = tmpdinfo[did];
			}
			num_used_drivers = num_taken_orders = 0;
			cgscore = 0;
			for (int i = 0; i < Q; i++) order_taken[i] = 0;
			for (int i = 0; i < D; i++) {
				int step2 = step_pool[dinfo[i].first_step].next_step;
				if (step_pool[step2].eidx >= 0) {
					dused[i] = 1;
					used_drivers[num_used_drivers++] = i;
					cgscore += dinfo[i].dist;
					for (int j = step2; j >= 0; j = step_pool[j].next_step) {
						if (step_pool[j].eidx < 0) continue;
						const struct Edge& edge = tpve[step_pool[j].eidx];
						order_taken[edge.o1] = 1;
						num_taken_orders++;
						if (edge.o2 >= 0) {
							order_taken[edge.o2] = 1;
							num_taken_orders++;
						}
					}
				}
			}
			num_iters_since_last_improvement++;
			if (num_iters_since_last_improvement >= 50&&0) {
				for (int k = 0; k < nedges; k++) wedges[k].first *= (0.99 * (mt.NextInt() % 3) * 0.01);
				sort(wedges.begin(), wedges.end());
			}
		}
	}

	for (int i = A; i < A + G; i++)
		for (int j = 0; j < N; j++)
			if (i != j) d[j][i] -= BASE_PENALTY;

	return tle;
}

void Solve() {
	Init();
#ifdef LOCAL
	fprintf(stderr, "Init took %.3lf sec\n", GetTime() - TSTART);
#endif
	Greedy();
}
}

void Solve() {
	InitSol(bsol, bgscore);
	if (!TPN::Solve()) IMPROV::Solve();
}

void WriteOutput() {
	printf("%u\n", SEED);
	for (int i = 0; i < D; i++) {
		printf("driver %d: ", i);
		if (bsol[i].nops == 0) {
			printf("no\n");
			continue;
		}
		printf("yes\n");
		for (int j = 0; j < bsol[i].nops; j++) {
			if (bsol[i].ops[j][0] == MOVE_OP) {
				printf("move %d %d\n", bsol[i].ops[j][1], bsol[i].ops[j][2]);
			} else if (bsol[i].ops[j][0] == PICKUP1_OP) {
				printf("pick1 %d %d\n", bsol[i].ops[j][1], bsol[i].ops[j][2]);
			} else if (bsol[i].ops[j][0] == DROPOFF1_OP) {
				printf("drop1 %d %d\n", bsol[i].ops[j][1], bsol[i].ops[j][2]);
			} else if (bsol[i].ops[j][0] == PICKUP2_OP) {
				printf("pick2 %d %d %d\n", bsol[i].ops[j][1], bsol[i].ops[j][2], bsol[i].ops[j][3]);
			} else if (bsol[i].ops[j][0] == DROPOFF2_OP) {
				printf("drop2 %d %d %d\n", bsol[i].ops[j][1], bsol[i].ops[j][2], bsol[i].ops[j][3]);
			}
		}
		printf("end\n");
	}
}

namespace CHECKSOL {

int ostate[NMAX], tpickup[NMAX], dcnode, dtcurr, dtdrive;
int passengers[2], npassengers;

void CheckSolution() {
	long long score = 0;
	int i, j;
	for (i = 0; i < Q; i++) ostate[i] = 0;
	for (i = 0; i < D; i++) {
		if (bsol[i].nops == 0) continue;
		score += BASE_PENALTY;
		dtcurr = driver[i].start;
		dtdrive = npassengers = 0;
		dcnode = driver[i].garage;
		for (j = 0; j < bsol[i].nops; j++) {
			if (bsol[i].ops[j][0] == MOVE_OP) {
				if (j > 0 && bsol[i].ops[j - 1][0] == MOVE_OP) {
					fprintf(stderr, "Two consecutive move ops!\n");
					exit(1);
				}
				if (bsol[i].ops[j][1] < dtcurr) {
					fprintf(stderr, "Move time is in the past!\n");
					exit(1);
				}
				dtcurr = bsol[i].ops[j][1];
				dtcurr += t[dcnode][bsol[i].ops[j][2]];
				dtdrive += t[dcnode][bsol[i].ops[j][2]];
				score += d[dcnode][bsol[i].ops[j][2]];
				dcnode = bsol[i].ops[j][2];
			} else if (bsol[i].ops[j][0] == PICKUP1_OP) {
				if (bsol[i].ops[j][1] < dtcurr) {
					fprintf(stderr, "Pickup1 time is in the past!\n");
					exit(1);
				}
				dtcurr = bsol[i].ops[j][1];
				int oid = bsol[i].ops[j][2];
				if (dcnode != order[oid].from) {
					fprintf(stderr, "Pickup1 from wrong location for oid=%d! expected location=%d actual location=%d\n", oid, order[oid].from, dcnode);
					exit(1);
				}
				if (ostate[oid] != 0) {
					fprintf(stderr, "Pickup1 for already picked up client!\n");
					exit(1);
				}
				if (order[oid].from < A && dtcurr != order[oid].moment) {
					fprintf(stderr, "Pickup1 for client form airport at wrong time!\n");
					exit(1);
				}
				ostate[oid] = 1;
				tpickup[oid] = bsol[i].ops[j][1];
				dtcurr += TEN_MINUTES;
				if (npassengers >= 2) {
					fprintf(stderr, "More than two passegners in the car!\n");
					exit(1);
				}
				passengers[npassengers++] = oid;
			} else if (bsol[i].ops[j][0] == DROPOFF1_OP) {
				if (bsol[i].ops[j][1] < dtcurr) {
					fprintf(stderr, "Dropoff1 time is in the past!\n");
					exit(1);
				}
				dtcurr = bsol[i].ops[j][1];
				int oid = bsol[i].ops[j][2];
				if (dcnode != order[oid].to) {
					fprintf(stderr, "Dropoff1 to wrong location!\n");
					exit(1);
				}
				if (ostate[oid] != 1) {
					fprintf(stderr, "Dropoff1 for not picked up client!\n");
					exit(1);
				}
				dtcurr += TEN_MINUTES;
				if (order[oid].from >= A && dtcurr > order[oid].moment) {
					fprintf(stderr, "Dropoff1 for client at airport too late!\n");
					exit(1);
				}
				ostate[oid] = 2;
				npassengers--;
				if (order[oid].from < A) {
					if (dtcurr - tpickup[oid] > t[order[oid].from][order[oid].to] + 2 * TEN_MINUTES + ONE_HOUR) {
						fprintf(stderr, "Transfer time is more than hour above the optimum!\n");
						exit(1);
					}
				} else {
					if (order[oid].moment - tpickup[oid] > t[order[oid].from][order[oid].to] + 2 * TEN_MINUTES + ONE_HOUR) {
						fprintf(stderr, "Transfer time is more than hour above the optimum!\n");
						exit(1);
					}
				}
			} else if (bsol[i].ops[j][0] == PICKUP2_OP) {
				if (bsol[i].ops[j][1] < dtcurr) {
					fprintf(stderr, "Pickup2 time is in the past!\n");
					exit(1);
				}
				dtcurr = bsol[i].ops[j][1];
				int o1 = bsol[i].ops[j][2], o2 = bsol[i].ops[j][3];
				if (dcnode != order[o1].from) {
					fprintf(stderr, "Pickup2 from wrong location!\n");
					exit(1);
				}
				if (order[o1].from != order[o2].from || order[o1].moment != order[o2].moment) {
					fprintf(stderr, "Pickup2 combined two incompatible passengers!\n");
					exit(1);
				}
				if (ostate[o1] != 0 || ostate[o2] != 0) {
					fprintf(stderr, "Pickup2 for already picked up client(s)!\n");
					exit(1);
				}
				if (order[o1].from < A && dtcurr != order[o1].moment) {
					fprintf(stderr, "Pickup2 for clients form airport at wrong time!\n");
					exit(1);
				}
				ostate[o1] = ostate[o2] = 1;
				tpickup[o1] = tpickup[o2] = bsol[i].ops[j][1];
				dtcurr += TEN_MINUTES;
				if (npassengers >= 1) {
					fprintf(stderr, "More than two passegners in the car!\n");
					exit(1);
				}
				passengers[npassengers++] = o1;
				passengers[npassengers++] = o2;
			} else if (bsol[i].ops[j][0] == DROPOFF2_OP) {
				if (bsol[i].ops[j][1] < dtcurr) {
					fprintf(stderr, "Dropoff2 time is in the past!\n");
					exit(1);
				}
				dtcurr = bsol[i].ops[j][1];
				int o1 = bsol[i].ops[j][2], o2 = bsol[i].ops[j][3];
				if (dcnode != order[o1].to) {
					fprintf(stderr, "Dropoff2 to wrong location!\n");
					exit(1);
				}
				if (order[o1].to != order[o2].to) {
					fprintf(stderr, "Dropoff2 combined incompatible passengers!\n");
					exit(1);
				}
				if (ostate[o1] != 1 || ostate[o2] != 1) {
					fprintf(stderr, "Dropoff2 for not picked up client(s)!\n");
					exit(1);
				}
				dtcurr += TEN_MINUTES;
				if (order[o1].to < A && (dtcurr > order[o1].moment || dtcurr > order[o2].moment)) {
					fprintf(stderr, "Dropoff2 for client(s) at airport too late!\n");
					exit(1);
				}
				ostate[o1] = ostate[o2] = 2;
				npassengers -= 2;
				if (order[o1].to < A) {
					if (order[o1].moment - tpickup[o1] > t[order[o1].from][order[o1].to] + 2 * TEN_MINUTES + ONE_HOUR ||
					    order[o2].moment - tpickup[o2] > t[order[o2].from][order[o2].to] + 2 * TEN_MINUTES + ONE_HOUR) {
						fprintf(stderr, "Transfer time is more than hour above the optimum!\n");
						exit(1);
					}
				}
			}
		}
		for (j = 0; j < Q; j++)
			if (ostate[j] == 1) {
				fprintf(stderr, "Client picked up and not dropped off!\n");
				exit(1);				
			}
		if (dtcurr > driver[i].finish) {
			fprintf(stderr, "Driver worked more than allotted time! %d / %d\n", dtcurr, driver[i].finish);
			exit(1);
		}
		if (dtdrive > NINE_HOURS) {
			fprintf(stderr, "Driver drove more than 9 hours!\n");
			exit(1);
		}
		if (dcnode != driver[i].garage) {
			fprintf(stderr, "Driver did not finish the day in the garage!\n");
			exit(1);
		}
	}
	int num_missed_orders = 0;
	for (i = 0; i < Q; i++)
		if (ostate[i] == 0) num_missed_orders++;
	fprintf(stderr, "nmo=%d\n", num_missed_orders);
	score += (long long) num_missed_orders * (long long) MISS_PENALTY;
	if (score != bgscore) {
		fprintf(stderr, "expected score=%I64d actual score=%I64d\n", bgscore, score);
		exit(1);
	}
}
}

double ComputeScore(long long score) {
	long long optscore = 0, opttime = 0;
	for (int i = 0; i < Q; i++) {
		optscore += d[order[i].from][order[i].to];
		opttime += t[order[i].from][order[i].to];
	}
	long long optdrivers = 0;
	for (optdrivers = 0; optdrivers * NINE_HOURS < opttime; optdrivers++);
	optscore += optdrivers * BASE_PENALTY;
	return (double) (1000LL * optscore) / (double) score;
}

#define MAX_TESTS 249
long long best_score[MAX_TESTS];

char fname[128];

int main() {
//	freopen("x.txt", "w", stderr);
#ifdef LOCAL
	freopen("scores.txt", "r", stdin);
	for (int seed = 1; seed <= MAX_TESTS; seed++) scanf("%I64d", &best_score[seed - 1]);
	freopen("tmp-scores.txt", "w", stdout);
	double total_score = 0.0;
	int seed_min = 6, seed_max = 10;
	for (int seed = seed_min; seed <= seed_max; seed++) {
		sprintf(fname, "veeroute-%d.txt", seed);
		freopen(fname, "r", stdin);
		TSTART = GetTime(); TEND = TSTART + TIME_LIMIT;
		TCRITICAL = TSTART + 0.92 * TIME_LIMIT;
		ReadInput();
		fprintf(stderr, "read took %.3lf sec\n", (double) (GetTime() - TSTART));
		Solve();
		double TSTOP = GetTime();
		CHECKSOL::CheckSolution();
		double score = ComputeScore(bgscore);
		total_score += score;
		fprintf(stderr, "### seed=%d A=%d G=%d Q=%d D=%d time=%.2lf bgsc=%d sc=%.3lf rsc=%.3lf tsc=%.3lf\n", seed, A, G, Q, D, TSTOP - TSTART, bgscore, score, (double) best_score[seed - 1] / (double) bgscore, total_score);
		fflush(stderr);
		printf("%d\n", bgscore);
		fflush(stdout);
	}
#else
	TSTART = GetTime(); TEND = (int) (TSTART + TIME_LIMIT);
	TCRITICAL = (int) (TSTART + 0.9 * TIME_LIMIT);
	ReadInput();
	Solve();
	CHECKSOL::CheckSolution();
	WriteOutput();
#endif
	return 0;
}
