// Copyright 2008, 2009 Brady J. Garvin

// This file is part of Covering Arrays by Simulated Annealing (CASA).

// CASA is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// CASA is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with CASA.  If not, see <http://www.gnu.org/licenses/>.

#include "Combinadic.h"
#include <cassert>

std::vector<unsigned> Combinadic::begin(const unsigned size) const {
  std::vector<unsigned> vec(size);
  for (unsigned i = 0; i < size; ++i) {
    vec[i] = i;
  }
  return vec;
}

void Combinadic::next(std::vector<unsigned> &sortedSubset) const {
  assert(sortedSubset.size());
  unsigned limit = sortedSubset.size() - 1, ceiling = sortedSubset[0];
  for (unsigned i = 0; i < limit; ++i) {
    unsigned entry = ceiling + 1;
    ceiling = sortedSubset[i + 1];
    if (entry < ceiling) {
      sortedSubset[i] = entry;
      return;
    }
    sortedSubset[i] = i;
  }
  ++sortedSubset[limit];
}

// [low, high)
unsigned first_leq(unsigned low, unsigned high, unsigned combination,
                   unsigned &k) {
  unsigned mid = (low + high) / 2;
  unsigned cur = pascalTriangle.nCr(mid, combination);
  if (k < cur) { // [low, mid)
    if (mid - low <= 1) {
      k -= pascalTriangle.nCr(low, combination);
      return low;
    }
    return first_leq(low, mid, combination, k);
  } else { // [mid, high)
    if (high - mid <= 1) {
      k -= cur;
      return mid;
    }
    return first_leq(mid, high, combination, k);
  }
}

void Combinadic::columns(std::vector<unsigned> &sortedSubset,
                         unsigned upper_bound, unsigned k) const {
  unsigned sz = sortedSubset.size();
  assert(sz >= 1);

  sortedSubset[sz - 1] = first_leq(sz - 1, upper_bound, sz, k);

  for (unsigned i = sz - 1; i-- > 0;) {
    sortedSubset[i] = first_leq(i, sortedSubset[i + 1], i + 1, k);
  }
}

// void Combinadic::columns(std::vector<unsigned> &sortedSubset,
//                          unsigned k) const {
//   unsigned j = *sortedSubset.rbegin();
//   for (unsigned i = sortedSubset.size(); i-- > 0; j = i) {
//     unsigned last = pascalTriangle.nCr(j, i + 1);
//     do {
//       ++j;
//       unsigned cur = pascalTriangle.nCr(j, i + 1);
//       if (cur > k) {
//         sortedSubset[i] = j - 1;
//         k -= last;
//         break;
//       }
//       last = cur;
//     } while (true);
//   }
// }

void Combinadic::previous(std::vector<unsigned> &sortedSubset) const {
  assert(sortedSubset.size());
  unsigned limit = sortedSubset.size();
  for (unsigned i = 0; i < limit; ++i) {
    unsigned entry = sortedSubset[i];
    if (entry > i) {
      do {
        sortedSubset[i] = --entry;
      } while (i-- > 0);
      return;
    }
  }
}

// unsigned Combinadic::encode(const std::vector<unsigned> &sortedSubset) const
// {
//	unsigned result = 0;
//	for (unsigned i = 0; i < sortedSubset.size(); ++i) {
//		result += pascalTriangle.nCr(sortedSubset[i], i+1);
//	}
//	return result;
//}

// unsigned Combinadic::encode(const std::vector<unsigned> &sortedSubset) const
// {
//	unsigned result = 0;
//	result += sortedSubset[0];
//	result += sortedSubset[1] * (sortedSubset[1] - 1) / 2;
//	result += sortedSubset[2] * (sortedSubset[2] - 1) * (sortedSubset[2] -
// 2) / 6;
//	return result;
//}

// unsigned Combinadic::encode(const std::vector<unsigned> &sortedSubset) const
// {
//	unsigned result = 0;
//	for (unsigned i = 0; i < sortedSubset.size(); ++i) {
//		unsigned nCr = 1;
//		for (unsigned j = 0; j <= i; ++j) {
//			nCr *= sortedSubset[i] - j;
//		}
//		for (unsigned j = 2; j <= i + 1; ++j) {
//			nCr /= j;
//		}
//		result += nCr;
//	}
//	return result;
//}

unsigned Combinadic::encode(const std::vector<unsigned> &sortedSubset) const {
  switch (sortedSubset.size()) {
  case 2:
    return encode_2way(sortedSubset);
  case 3:
    return encode_3way(sortedSubset);
  default:
    return encode_anyway(sortedSubset);
  }
}

Combinadic combinadic;
