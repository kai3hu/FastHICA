#ifndef LINEVARTUPLESET_H_MBOTX5KJ
#define LINEVARTUPLESET_H_MBOTX5KJ

#include <vector>

#include "Combinadic.h"
#include "Coverage.h"
#include "SpecificationFile.h"
using namespace std;
struct ECEntry {
public:
  unsigned encode;
  size_t column_index;
};
struct Mapt {
public:
int row_index;
size_t column_index;
};


class LineVarTupleSet {
public:
  LineVarTupleSet(){};
  void initialize(const SpecificationFile &specificationFile,
                  const unsigned array_size);
  void pop(const unsigned encode, const unsigned lineIndex,
           const std::vector<unsigned> &tuple);
  void push(const unsigned encode, const unsigned lineIndex,
            const std::vector<unsigned> &tuple, const unsigned pushtimes);

  void pushNCoveredTuple(const Coverage &coverage,
                           const std::vector<std::vector<int>> &coverByLineindex, const unsigned index);

  void exchange_row(unsigned lineIndex1, unsigned lineIndex2) {
    lineVarTupleSet[lineIndex1].swap(lineVarTupleSet[lineIndex2]);
    std::swap(lineNCoveredCount[lineIndex1], lineNCoveredCount[lineIndex2]);
  }
  void pop_back_row() {
    lineVarTupleSet.pop_back();
    lineNCoveredCount.pop_back();
  }

  const std::vector<ECEntry> &getECbyLineVar(unsigned lineIndex, unsigned var) {
    return lineVarTupleSet[lineIndex][var];
  }

  unsigned NCoveredCount(unsigned lineIndex) {
    return lineNCoveredCount[lineIndex];
  }

private:
  std::vector<size_t> lineNCoveredCount;

  std::vector<std::vector<std::vector<ECEntry>>> lineVarTupleSet;
  std::vector<vector<vector<Mapt>>> varMapping; //
};

#endif /* end of include guard: LINEVARTUPLESET_H_MBOTX5KJ */
