#include <iostream>
#include <map>
#include <string>

#include "ConstraintFile.H"
#include "LocalSearch.h"
#include "SpecificationFile.h"
#include "TestSetFile.H"
#include "io.h"
using namespace std;

int main(int argc, char const *argv[]) {


  string modelFile;
  string constrFile;
  unsigned long long maxTime;
  int seed;
  int coverageStrength;
  int threadsNum;
  int minScoreTaskSize;
  int minReplaceTaskSize;
  int HighIndex;
  string outfile;

  string testFile("");

    map<string, string> parameters_map = {{"--file", "../example/ex.txt"},
                                          {"--strength", "3"},
                                          {"--highindex", "2"},
                                          {"--time", "10"},
                                          {"--seed", "1"},
                                          {"--threads", "1"},
                                          {"--minScoreTaskSize", "100"},
                                          {"--minReplaceTaskSize", "120"},
                                          {"--outfile", "./out.txt"}};

  vector<string> parameterVec;
  for (int i = 1; i < argc - 1; i += 2) {
    string paraName = argv[i];
    string paraValue = argv[i + 1];
    if (parameters_map.find(paraName) == parameters_map.end()) {
      return 1;
    }
    parameters_map[paraName] = paraValue;
  }

  if (parameters_map["--file"] == "") {
    return 1;
  } else {
    modelFile = parameters_map["--file"];
  }

  if (atoi(parameters_map["--strength"].c_str()) < 2) {
    return 1;
  } else {
    coverageStrength = atoi(parameters_map["--strength"].c_str());
  }
  if (atoi(parameters_map["--highindex"].c_str()) < 1) {
      return 1;
  } else {
      HighIndex = atoi(parameters_map["--highindex"].c_str());
  }

  if (atoi(parameters_map["--time"].c_str()) < 0) {
    return 1;
  } else {
    maxTime = atoi(parameters_map["--time"].c_str());
  }

  seed = atoi(parameters_map["--seed"].c_str());

  if (atoi(parameters_map["--threads"].c_str()) < 1) {
    return 1;
  } else {
    threadsNum = atoi(parameters_map["--threads"].c_str());
  }

  if (atoi(parameters_map["--minScoreTaskSize"].c_str()) < 1) {
    return 1;
  } else {
    minScoreTaskSize = atoi(parameters_map["--minScoreTaskSize"].c_str());
  }

  if (atoi(parameters_map["--minReplaceTaskSize"].c_str()) < 1) {
    return 1;
  } else {
    minReplaceTaskSize = atoi(parameters_map["--minReplaceTaskSize"].c_str());
  }

  outfile = parameters_map["--outfile"];

  SpecificationFile specificationFile;
  ConstraintFile constraintFile;
  TestSetFile testSetFile;
  io.readInstance(modelFile, specificationFile, constraintFile, testSetFile);
  specificationFile.setStrenth(coverageStrength);
  specificationFile.setIndex(HighIndex);
    
  testSetFile.convert2acts(specificationFile);
  localSearch(specificationFile, constraintFile, testSetFile, maxTime, seed,
              threadsNum, minScoreTaskSize, minReplaceTaskSize, outfile);

  return 0;
}
