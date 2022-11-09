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

    void exchange_row(unsigned lineIndex1, unsigned lineIndex2, unsigned strength, const Options options, std::vector<std::vector<unsigned>> array, Coverage coverage, unsigned index) {
    lineVarTupleSet[lineIndex1].swap(lineVarTupleSet[lineIndex2]);
    std::swap(lineNCoveredCount[lineIndex1], lineNCoveredCount[lineIndex2]);
    std::vector<unsigned> tmpTuple(strength);
    for (std::vector<unsigned> columns = combinadic.begin(strength);
    columns[strength - 1] < options.size(); combinadic.next(columns)) {
    for (unsigned j = 0; j < strength; ++j) {
        tmpTuple[j] = array[lineIndex1][columns[j]];
    }
    unsigned encode = coverage.encode(columns, tmpTuple);
    unsigned coverCount = coverage.coverCount(encode);
        if (coverCount == index){
            for (unsigned n = 0; n < strength; ++n){
                for (unsigned m = 0; m< index; ++m){
             if (varMapping[encode][n][m].row_index == lineIndex2)
                 varMapping[encode][n][m].row_index = lineIndex1;
                }
            }
        }
    }
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
