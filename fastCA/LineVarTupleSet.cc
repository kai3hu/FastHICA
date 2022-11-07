#include "LineVarTupleSet.h"

void LineVarTupleSet::initialize(const SpecificationFile &specificationFile,
                                 const unsigned array_size) {

  const Options &options = specificationFile.getOptions();
  unsigned strength = specificationFile.getStrenth();
  unsigned index = specificationFile.getIndex();

  unsigned MaxSize = 0;
  for (std::vector<unsigned> tuple = combinadic.begin(strength);
       tuple[strength - 1] < options.size(); combinadic.next(tuple)) {
    unsigned blockSize = 1;
    for (unsigned i = 0; i < strength; ++i) {
      blockSize *= options.symbolCount(tuple[i]);
    }
    MaxSize += blockSize;
  }
  varMapping.resize(MaxSize);
      for (unsigned i = 0; i < MaxSize; ++i) {
          varMapping[i].resize(strength);
          for (unsigned j = 0; j < strength; ++j)
          {
             varMapping[i][j].resize(index);
          }
      }

  lineVarTupleSet.resize(array_size);
  for (unsigned i = 0; i < array_size; ++i) {
    lineVarTupleSet[i].resize(options.allSymbolCount());
  }

  lineNCoveredCount.resize(array_size, 0);
}

void LineVarTupleSet::pushNCoveredTuple(
    const Coverage &coverage, const std::vector<std::vector<int>> &coverByLineindex, const unsigned index) {
  for (unsigned encode = 0; encode < coverage.tupleCount(); ++encode) {
    if (coverage.coverCount(encode) == index) {
        for (unsigned i = 0; i < index ; i++)
        {
      push(encode, coverByLineindex[encode][i], coverage.getTuple(encode), i);
        }
    }
  }
}

void LineVarTupleSet::push(const unsigned encode, const unsigned lineIndex,
                           const std::vector<unsigned> &tuple, unsigned pushtimes) {
    
    lineNCoveredCount[lineIndex]++;
    for (size_t i = 0; i < tuple.size(); ++i) {
      unsigned var = tuple[i];
      varMapping[encode][i][pushtimes].row_index = lineIndex;
      varMapping[encode][i][pushtimes].column_index = lineVarTupleSet[lineIndex][var].size();
      lineVarTupleSet[lineIndex][var].push_back({encode, i});
    }
  

    

//  lineNCoveredCount[lineIndex]++;
//  for (size_t i = 0; i < tuple.size(); ++i) {
//    unsigned var = tuple[i];
//    varMapping[encode][i][t].row_index = lineIndex[t];
//    varMapping[encode][i][t].column_index = lineVarTupleSet[lineIndex[t]][var].size();
//    lineVarTupleSet[lineIndex[t]][var].push_back({encode, i});
//
//  }
}

void LineVarTupleSet::pop(const unsigned encode, const unsigned lineIndex,
                          const std::vector<unsigned> &tuple) {
 

    for (int j = 0; j < varMapping[encode][0].size() ; j++)
    {
        
        lineNCoveredCount[varMapping[encode][0][j].row_index]--;
        for (size_t i = 0; i < tuple.size(); ++i) {
        unsigned var = tuple[i];
        std::vector<ECEntry> &varTS = lineVarTupleSet[varMapping[encode][i][j].row_index][var];
        varTS[varMapping[encode][i][j].column_index] = *varTS.rbegin();
        varMapping[varTS.rbegin()->encode][varTS.rbegin()->column_index][j].column_index =  varMapping[encode][i][j].column_index;
        varTS.pop_back();
        }
        
    }
        
    
    
    
    
    
    
    
//  for (size_t i = 0; i < tuple.size(); ++i) {
//    unsigned var = tuple[i];
//    std::vector<ECEntry> &varTS = lineVarTupleSet[lineIndex][var];
//
//    varTS[varMapping[encode][i][0].row_index] = *varTS.rbegin();
//
//    varMapping[varTS.rbegin()->encode][varTS.rbegin()->column_index] =
//        varMapping[encode][i];
//    varTS.pop_back();
//  }
}
