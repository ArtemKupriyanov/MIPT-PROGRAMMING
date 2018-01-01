#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

//Consts block.
const int MAX = 4 * (1e5 + 10);
const int ALPHABET_SIZE = 26;

//Vars block.
string A, B;
int T;
ll caseAnswer;

class PalindromicTree {
private:

    struct Node {
        int child[26];
        int length;
        int suffixLink;
        int position;
        ll countFirst, countSecond;
    };

    Node tree[MAX];
    char dataString[MAX];
    int suffixPalindrom, size, lastNode;

    int makeNewNode(int len) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            tree[lastNode].child[i] = 0;
        }
        tree[lastNode].countFirst = 0;
        tree[lastNode].position = 0;
        tree[lastNode].length = len;
        return lastNode++;
    }

public:

    PalindromicTree(string C, string D) {
        for (int i = 0; i < C.length() + D.length() + 5; i++) {
            tree[i].countFirst = tree[i].countSecond = 0;
        }
        lastNode = 0;
        makeNewNode(0);
        makeNewNode(-1);
        suffixPalindrom = 0;
        size = 0;
        dataString[0] = -1;
        tree[0].suffixLink = 1;
    }

    void reinit() {
        suffixPalindrom = 0;
        size = 0;
        dataString[0] = -1;
        tree[0].suffixLink = 1;
    }

    int getSuffixLink(int v) {
        while (dataString[size - tree[v].length - 1] != dataString[size]) {
            v = tree[v].suffixLink;
        }
        return v;
    }

    void addCharacter(char c, int index) {
        int edge = c - 'a';
        dataString[++size] = c;

        int currentSuffix = getSuffixLink(suffixPalindrom);
        if (!tree[currentSuffix].child[edge]) {
            int currentNumber = makeNewNode(tree[currentSuffix].length + 2);
            tree[currentNumber].suffixLink = tree[getSuffixLink(tree[currentSuffix].suffixLink)].child[edge];
            tree[currentSuffix].child[edge] = currentNumber;
            tree[currentNumber].position = tree[tree[lastNode].suffixLink].position + 1;
        }

        suffixPalindrom = tree[currentSuffix].child[edge];
        switch (index) {
            case 1: {
                tree[suffixPalindrom].countFirst++;
                break;
            }
            case 2: {
                tree[suffixPalindrom].countSecond++;
                break;
            }
            default:
                break;
        }
    }

    void solve(int index) {
        for (int i = lastNode - 1; i >= 0; i--) {
            switch (index) {
                case 1:
                    tree[tree[i].suffixLink].countFirst += tree[i].countFirst;
                    break;
                case 2:
                    tree[tree[i].suffixLink].countSecond += tree[i].countSecond;
                    break;
                default:
                    break;
            }
        }
    }

    void calculate(ll &answer) {
        for (int i = 2; i < lastNode; i++) {
            answer += tree[i].countFirst * tree[i].countSecond;
        }
    }
};



int main() {

    //Philipp's magic cin boost.
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //Code.
    cin >> T;

    for (int i = 1; i <= T; i++) {
        cin >> A >> B;
        caseAnswer = 0;

        PalindromicTree Tree(A, B);

        for (int j = 0; j < A.length(); j++) {
            Tree.addCharacter(A[j], 1);
        }
        Tree.solve(1);

        Tree.reinit();
        for (int j = 0; j < B.length(); j++) {
            Tree.addCharacter(B[j], 2);
        }
        Tree.solve(2);

        Tree.calculate(caseAnswer);

        cout << "Case #" << i << ": " << caseAnswer << endl;
    };
    return 0;
}

