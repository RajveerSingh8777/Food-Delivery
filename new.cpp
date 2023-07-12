
// 1. Create a class SET. Create member functions to perform the following SET
// operations:
// 1) is member: check whether an element belongs 1 the set or not and return valu
// as
// true/false
// 2) powerset: list all the elements of the power set of a set
// 3) subset: Check whether one set is a subset of the other or not.
// 4) union and Intersection of two Sets.
// 5) complement: Assume Universal Set as pe the input elements from the user. 6) set Difference and Symmetric Difference between two sets.
// 7) cartesian Product of Sets

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

class Set {
public:
    unordered_set<int> elementSet;
    vector<int> elementsVector;
    set<int> universalSet;

    void addElement(int element) {
        elementSet.insert(element);
        elementsVector.push_back(element);
    }

    void addUniversalElement(int element) {
        universalSet.insert(element);
    }

    bool isMember(int element) {
        return elementSet.count(element) > 0;
    }

    vector<vector<int>> powerSet() {
        int n = elementsVector.size();
        int numSubsets = 1 << n;
        vector<vector<int>> result;

        for (int i = 0; i < numSubsets; i++) {
            vector<int> subset;

            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    subset.push_back(elementsVector[j]);
                }
            }

            result.push_back(subset);
        }
        return result;
    }
    
    bool isSubset(const Set& other) const{
        for (int element: other.elementSet) {
            if (elementSet.count(element) == 0) { 
                return false;
            }
        }
        return true;
    }

    Set setUnion(const Set& other) const {
        Set result = *this;

        for (int element : other.elementSet) {
            result.elementSet.insert(element);
        }
        return result;
    }

    Set intersection(const Set& other) const {
        Set result;

        for (int element : elementSet) {
            if (other.elementSet.count(element) > 0) {
                result.elementSet.insert(element);
            }
        }
        return result;
    }

    Set setDifference(const Set& other) const {
        Set result = *this;

        for (int element : other.elementSet) {
            result.elementSet.erase(element);
        }

        return result;
    }

    set<int> complement() const {
        set<int> complementSet;
        for (int element : universalSet) {
            if (elementSet.find(element) == elementSet.end()) {
                complementSet.insert(element);
            }
        }
        return complementSet;
    }

    Set symmetricDifference(const Set& other) const {
        Set result;

        for (int element : elementSet) {
            if (other.elementSet.count(element) == 0) {
                result.elementSet.insert(element);
            }
        }

        for (int element : other.elementSet) {
            if (elementSet.count(element) == 0) {
                result.elementSet.insert(element);
            }
        }

        return result;
    }

    vector<pair<int, int>> cartesianProduct(const Set& other) const {
        vector<pair<int, int>> result;

        for (int element1 : elementSet) {
            for (int element2 : other.elementSet) {
                result.emplace_back(element1, element2);
            }
        }
        return result;
    }


};

int main() {
    Set mySet;
    mySet.addElement(1);
    mySet.addElement(2);
    mySet.addElement(3);
    
    Set mySet2;
    mySet2.addElement(1);
    mySet2.addElement(2);

    Set mySet3;
    mySet3.addElement(3);
    mySet3.addElement(4);

    Set mySet4;
    mySet4.addElement(2);
    mySet4.addElement(3);
    mySet4.addElement(4);

    mySet.addUniversalElement(1);
    mySet.addUniversalElement(2);
    mySet.addUniversalElement(3);
    mySet.addUniversalElement(4);

    cout << "Is member: " << mySet.isMember(1) << endl;

    vector<vector<int>> powerSet = mySet.powerSet();

    cout<<"Power set: "<<"\n";
    for (const auto& subset: powerSet){
        cout << "{ ";
        for (int element : subset){
            cout << element << " ";
        }
        cout << "}" << endl;
    }

    cout<< "Set 2 is a subset of Set 1: "<<mySet.isSubset(mySet2)<<"\n";
    cout<< "Set 3 is a subset of Set 1: "<<mySet.isSubset(mySet3)<<"\n";

    Set setUnion = mySet.setUnion(mySet4);
    Set intersection = mySet.intersection(mySet4);

    cout << "Set Union: ";
    for (int element : setUnion.elementSet) {
        cout << element << " ";
    }
    cout << endl;

    cout << "Intersection: ";
    for (int element : intersection.elementSet) {
        cout << element << " ";
    }
    cout << endl;
    
    set<int> complementSet = mySet.complement();
    
    cout << "Complement Set: ";
    for (int element : complementSet) {
        cout << element << " ";
    }
    cout << endl;
    
    Set setDifference = mySet.setDifference(mySet4);
    Set symmetricDifference = mySet.symmetricDifference(mySet4);

    cout << "Set Difference (set1 - set2): ";
    for (int element : setDifference.elementSet) {
        cout << element << " ";
    }
    cout << endl;

    cout << "Symmetric Difference: ";
    for (int element : symmetricDifference.elementSet) {
        cout << element << " ";
    }
    cout << endl;

    vector<pair<int, int>> cartesianProduct = mySet.cartesianProduct(mySet4);

    cout << "Cartesian Product:" << endl;
    for (const auto& pair : cartesianProduct) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }    

    return 0;
}

// 2. Create a class RELATION, use Matrix notation to represent a relation.
// Include member functions to check if the relation is Reflexive, Symmetric, Anti-symmetric, Transitive.
// Using these functions check whether the given relation is: Equivalence or Partial Order relation or None
#include <iostream>
#include <vector>
using namespace std;

class Relation {
private:
    vector<vector<bool>> matrix;
    int size;

public:
    Relation(int size) {
        this->size = size;
        matrix.resize(size, vector<bool>(size, false));
    }

    void addPair(int row, int col) {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            matrix[row][col] = true;
        }
    }

    bool isReflexive() {
        for (int i = 0; i < size; i++) {
            if (!matrix[i][i]) {
                return false;
            }
        }
        return true;
    }

    bool isSymmetric() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isAntiSymmetric() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] && matrix[j][i] && i != j) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isTransitive() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j]) {
                    for (int k = 0; k < size; k++) {
                        if (matrix[j][k] && !matrix[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool isEquivalenceRelation() {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    bool isPartialOrderRelation() {
        return isReflexive() && isAntiSymmetric() && isTransitive();
    }
};

int main() {
    Relation relation(3);
    // Example relation: {(0, 0), (0, 1), (1, 1), (2, 2), (1, 2)}
    relation.addPair(0, 0);
    relation.addPair(0, 1);
    relation.addPair(1, 1);
    relation.addPair(2, 2);
    relation.addPair(1, 2);

    cout << "Reflexive: " << relation.isReflexive() << endl;
    cout << "Symmetric: " << relation.isSymmetric() << endl;
    cout << "Anti-Symmetric: " << relation.isAntiSymmetric() << endl;
    cout << "Transitive: " << relation.isTransitive() << endl;
    cout << "Equivalence Relation: " << relation.isEquivalenceRelation() << endl;
    cout << "Partial Order Relation: " << relation.isPartialOrderRelation() << endl;

    return 0;
}

// 3) permutation of given set of digits, with and withour repitition
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to generate permutations with repetition
void generatePermutationsWithRepetition(vector<int>& digits, vector<int>& currentPermutation, int length) {
    if (currentPermutation.size() == length) {
        for (int digit : currentPermutation) {
            cout << digit << " ";
        }
        cout << endl;
        return;
    }

    for (int digit : digits) {
        currentPermutation.push_back(digit);
        generatePermutationsWithRepetition(digits, currentPermutation, length);
        currentPermutation.pop_back();
    }
}

// Function to generate permutations without repetition
void generatePermutationsWithoutRepetition(vector<int>& digits, vector<int>& currentPermutation, vector<bool>& used, int length) {
    if (currentPermutation.size() == length) {
        for (int digit : currentPermutation) {
            cout << digit << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < digits.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            currentPermutation.push_back(digits[i]);
            generatePermutationsWithoutRepetition(digits, currentPermutation, used, length);
            currentPermutation.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    vector<int> digits = {1, 2, 3}; // Set of digits
    int length = digits.size(); // Length of permutations

    cout << "Permutations with repetition:" << endl;
    vector<int> currentPermutation;
    generatePermutationsWithRepetition(digits, currentPermutation, length);

    cout << "\nPermutations without repetition:" << endl;
    vector<bool> used(digits.size(), false);
    generatePermutationsWithoutRepetition(digits, currentPermutation, used, length);

    return 0;
}
// 4.For any number n, write a program to list al the solutions of the equation x, + x, +x, +
// 3, C, where C is a constant (C<=10) and X1,X2,X3.,Xn, are nonegative integers,
// using brute force strategy.
#include <iostream>
#include <vector>
using namespace std;

void recursive_helper(int target, int index, vector<int>& current_solution, vector<vector<int>>& solutions) {
    if (index == 0) {
        if (target == 0) {
            solutions.push_back(current_solution);
        }
        return;
    }
    for (int x = 0; x <= target; x++) {
        current_solution.push_back(x);
        recursive_helper(target - x, index - 1, current_solution, solutions);
        current_solution.pop_back();
    }
}

vector<vector<int>> find_solutions(int constant, int n) {
    vector<vector<int>> solutions;
    vector<int> current_solution;
    recursive_helper(constant - 3, n, current_solution, solutions);
    return solutions;
}

int main() {
    // Test the program for C = 10 and n = 3
    int constant_value = 10;
    int n_value = 3;
    vector<vector<int>> result = find_solutions(constant_value, n_value);

    cout << "The solutions for x1 + x2 + x3 + 3 = " << constant_value << " are:" << endl;
    for (const vector<int>& solution : result) {
        for (int i = 0; i < solution.size(); i++) {
            cout << solution[i];
            if (i < solution.size() - 1) {
                cout << " + ";
            }
        }
        cout << " + 3 = " << constant_value << endl;
    }

    return 0;
}
// 5.Write a Program to evaluate a polynomial function.
// (For example store (x) = 4n° + 20+ 9in an array and for a given value ofn, say n= 5, compute the value of fn).
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double evaluatePolynomial(const std::vector<double>& coefficients, double x) {
    double result = 0.0;
    int degree = coefficients.size() - 1;
    for (int i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * pow(x, degree);
        degree--;
    }
    return result;
}

int main() {
    std::vector<double> coefficients = {4.0, 20.0, 9.0}; // Polynomial coefficients: 4x^2 + 20x + 9
    double x = 5.0; // Value of x
    double result = evaluatePolynomial(coefficients, x);
    cout << "f(" << x << ") = " << result << endl;
    return 0;
}

// 6. Write a Program to check if a given graph is a complete
// graph Represent the graph using
// the Adjacency Matrix representation.
#include <iostream>
#include <vector>
using namespace std;

bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int numVertices = adjMatrix.size();
    if (numVertices != adjMatrix[0].size()) {
        return false;
    }

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i == j) {
                continue;
            }
            if (adjMatrix[i][j] != 1) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    // Example adjacency matrix for a complete graph
    vector<vector<int>> adjMatrix = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };

    vector<vector<int>> adjMatrix2 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    if (isCompleteGraph(adjMatrix2)) {
        cout << "The graph is a complete graph." << endl;
    }
    else {
        cout << "The graph is not a complete graph." << endl;
    }

    return 0;
}
// 7. Write a Program to check if a given graph is a complete
// graph Represent the graph using
// the Adjacency List representation.
#include<iostream>
#include<vector>
using namespace std;

bool isCompleteGraph(const vector<vector<int>>& adjList) {
    int numVertices = adjList.size();
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i == j) {
                continue;
            }
            bool connected = false;
            for (int k = 0; k < adjList[i].size(); ++k) {
                if (adjList[i][k] == j) {
                    connected = true;
                    break;
                }
            }
            if (!connected) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> graph1 = {
        {1, 2, 3},
        {0, 2, 3},
        {0, 1, 3},
        {0, 1, 2}
    };

    vector<vector<int>> graph2 = {
        {1, 2, 3},
        {0,    2},
        {0, 1, 3},
        {0,    1}
    };

    cout << boolalpha;
    cout << isCompleteGraph(graph1) << endl;
    cout << isCompleteGraph(graph2) << endl;

    return 0;
}

//8. accept directed graph G and compute the n degree and out degree of each vertex
#include <iostream>
#include <vector>
using namespace std;

void computeDegree(const vector<vector<int>>& graph, vector<int>& inDegree, vector<int>& outDegree) {
    int numVertices = graph.size();
    inDegree.assign(numVertices, 0);
    outDegree.assign(numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (graph[i][j] == 1) {
                outDegree[i]++;
                inDegree[j]++;
            }
        }
    }
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 1, 0, 0}
    };

    int numVertices = graph.size();
    vector<int> inDegree(numVertices);
    vector<int> outDegree(numVertices);

    computeDegree(graph, inDegree, outDegree);

    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": In-Degree = " << inDegree[i] << ", Out-Degree = " << outDegree[i] << endl;
    }

    return 0;
}