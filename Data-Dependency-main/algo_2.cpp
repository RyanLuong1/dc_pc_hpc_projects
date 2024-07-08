#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cctype>
#include <sstream>
#include <map>
#include <algorithm>
#include <time.h>

using namespace std;

int main()
{
    int numOfBlocks = 0;
    map<char, vector<string>> blocks;
    cout << "Enter the number of blocks: ";
    cin >> numOfBlocks;
    cout << numOfBlocks << "\n";
    cin.ignore();
    for (int i = 0; i < numOfBlocks; ++i) {
        string block = "";
        vector<string> blockList;
        cout << "Block " << i << ": ";
        getline(cin, block);
        stringstream ss(block);
        //split block based on spaces
        while(getline(ss, block, ' ')) {
            cout << block << " ";
            blockList.push_back(block);
        }
        cout << "\n";
        blocks.insert({blockList[0][0], blockList});
    }
    for (auto& key : blocks) {
        for (auto& letter : key.second) {
            if (letter.size() >= 2) {
                cout << "Invalid block";
                return 0;
            }
        }
    }
    map<char, set<char>> inputWithOutput;
    for (auto& key : blocks) {
        char input = key.first;
        set<char> output;
        for (auto& value : key.second) {
            if (isalpha(value[0])) {
                output.insert(value[0]);
            }
        }
        inputWithOutput.insert({input, output});
    }

    vector<char> allInputs;
    for (auto& key: blocks) {
        allInputs.push_back(key.first);
    }
    double elaspedTime;
    vector<vector<string>> results;
    for (int i = 0; i < allInputs.size(); ++i) {
        for (int j = i + 1; j < allInputs.size(); ++j) {
        char first = allInputs[i], second = allInputs[j];
        set<char> flowDependency, antiDependency, outputDependency,
                  inputL1{first}, outputL1 = inputWithOutput[first],
                  inputL2{second}, outputL2 = inputWithOutput[second];
        time_t begin, end;
        time(&begin);
        set_intersection(outputL1.begin(), outputL1.end(),
                        inputL2.begin(), inputL2.end(),
                        inserter(flowDependency, flowDependency.end()));
        set_intersection(inputL1.begin(), inputL1.end(),
                        outputL2.begin(), outputL2.end(),
                        inserter(antiDependency, antiDependency.end()));
        set_intersection(inputL1.begin(), inputL1.end(),
                        inputL2.begin(), inputL2.end(),
                        inserter(outputDependency, outputDependency.end()));
        time(&end);
        elaspedTime += difftime(end, begin);
        if (numOfBlocks == 3 && elaspedTime >= 60) {
          cout << "Number of blocks is 3 and the elapsed time is equal or over 60 minutes"
               << "\nTherefore, it must be terminated.";
          return 0;
        }
        if (flowDependency.size() == 0 && antiDependency.size() == 0 && outputDependency.size() == 0) {
            vector<string> result;
            result.insert(result.end(), blocks[first].begin(), blocks[first].end());
            result.push_back(", ");
            result.insert(result.end(), blocks[second].begin(), blocks[second].end());
            results.push_back(result);
        }
    }
    }
    cout << "The pairs of blocks that can be executed in parallel are\n";
    if (results.size() == 0) {
      cout << "NONE";
    }
    else {
      for (auto& result : results) {
          for (auto& letter : result) {
              cout << letter << " ";
          }
          cout << "\n";
      }
    }



    return 0;
}
