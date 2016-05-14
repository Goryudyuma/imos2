// imos2.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#endif

//#include<bits/stdc++.h>
using namespace std;

class imos2
{
public:
	void addInc( long long int x, long long int y ) {
		inc.emplace_back( make_pair( x, y ) );
		incsortflag = false;
	}

	void addDec( long long int x, long long int y ) {
		dec.emplace_back( make_pair( x, y ) );
		decsortflag = false;
	}

	pair<long long int, long long int> ans( long long int R ) {
		pair<long long int, long long int>ret = make_pair( 0, 0 );
		if( !incsortflag ) {
			for( auto now : inc ) {
				incymax = max( incymax, now.second );
				incymin = min( incymin, now.second );
			}
			sort( inc.begin(), inc.end() );
			incsortflag = true;
		}
		if( !decsortflag ) {
			for( auto now : dec ) {
				decymax = max( decymax, now.second );
				decymin = min( decymin, now.second );
			}
			sort( dec.begin(), dec.end() );
			decsortflag = true;
		}
		long long int ymin = min( incymin, decymin ), ymax = max( incymax, decymax );
		vector<long long int>tmp1( ymax - ymin + 1 );
		vector<long long int>tmp2( ymax - ymin + 1 );
		long long int incidx = 0, decidx = 0;
		for( long long int i = inc[0].first; i <= dec[dec.size() - 1].first; i++ ) {
			while( incidx < inc.size() && inc[incidx].first == i&&inc[incidx].second <= ymax ) {
				tmp2[inc[incidx].second - ymin]++;
				incidx++;
			}
			while( decidx < dec.size() && dec[decidx].first == i&&dec[decidx].second <= ymax ) {
				tmp2[dec[decidx].second - ymin]--;
				decidx++;
			}
			for( long long int j = 0; j < ymax - ymin; j++ ) {
				tmp2[j + 1] += tmp2[j];
			}
			for( long long int j = 0; j < ymax - ymin + 1; j++ ) {
				tmp2[j] += tmp1[j];
				//cout << setw( 2 ) << tmp2[j];
				if( tmp2[j] ) {
					ret.first++;
				}
				if( R == 2 ) {
					if( (!tmp2[j]) != (!tmp1[j]) ) {
						ret.second++;
					}
					if( j > 0 && (!tmp2[j]) != (!tmp2[j - 1]) ) {
						ret.second++;
					}
				}
			}
			if( tmp2[0] ) {
				ret.second++;
			}
			tmp1 = tmp2;
			tmp2 = vector<long long int>( ymax - ymin + 1 );
		}
		return ret;
	}


	vector<pair<long long int, long long int>>inc;
	vector<pair<long long int, long long int>>dec;

	bool incsortflag;
	bool decsortflag;

	long long int incymax = LLONG_MIN, decymax = LLONG_MIN;
	long long int incymin = LLONG_MAX, decymin = LLONG_MAX;
};

int main() {
	long long int N, R;
	while( cin >> N >> R, N || R ) {
		imos2 imos;
		for( size_t i = 0; i < N; i++ ) {
			long long int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			imos.addInc( x1, y1 );
			imos.addInc( x2, y2 );
			imos.addDec( x1, y2 );
			imos.addDec( x2, y1 );
		}
		auto memo = imos.ans( R );
		if( R == 1 ) {
			cout << memo.first << endl;
		} else {
			cout << memo.first << endl << memo.second << endl;
		}

	}
	return 0;
}
