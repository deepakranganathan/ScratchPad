#include "tmp.h"
#include "tree_ops.h"
#include <sstream>


using namespace std;

#define CHECK(cond, errstream, oss) \
    if (!(cond)) \
    { \
        (oss) << errstream << std::endl; \
        return; \
    }



// -----------------------------------------------------------------------------
// Problem:
// RotateString rotates S by R positions.  If R is positive rotate to the right.
// If R is negative rotate to the left.  "Rotating" means that characters
// shifted off one end roll back around to the other end.
//
// Explain how much time and memory your solution takes based on R and the
// length of S.  Note:  Please start out with a simple algorithm, and only come
// back and optimize it if you have time left after doing the other exercises.
//

void RotateString(std::string& S, int R)
{
    // TODO: Implement this function
    if (S.empty())
        return;
    int len = S.length();
    //Rotations by full length need not be counted
    R %= len;

    std::string temp = S + S;
    S = temp.substr(len - R, len);

    // Space complexity is O(2*len)
    // Time complexity is O(min(len,R))
}
void RotateStringOptimal(std::string& S, int R)

{
    // TODO: Provide an optimal implementation in space and time.

}

void TestStringRotation(std::ostream& error_output)
{
    const std::string failure_msg("String rotation failed!");

    std::string s1("sprint");
    RotateString(s1, 5);
    CHECK(s1 == "prints", failure_msg, error_output);

    std::string s2("StringRotated");
    RotateString(s2, 7);
    CHECK(s2 == "RotatedString", failure_msg, error_output);

    // TODO: Add more tests that demonstrate how you handle edge cases.

    std::string s3("");
    RotateString(s3, 5);
    CHECK(s3 == "", failure_msg, error_output);

    std::string s4("sprint");
    RotateString(s4, 6);
    CHECK(s4 == "sprint", failure_msg, error_output);

    std::string s5("I am trying to rotate a very long string here");
    RotateString(s5, 10);
    CHECK(s5 == "tring hereI am trying to rotate a very long s", failure_msg, error_output);

    std::string s6("sprint");
    RotateString(s4, 100);
    CHECK(s4 == "rintsp", failure_msg, error_output);
}

void makeTiled(int* dst, int* src, int M, int N, int B)
{
    //src
    //  1  2  3  4  5  6
    //  7  8  9 10 11 12
    // 13 14 15 16 17 18
    // 19 20 21 22 23 24

    //dst
    //  1  2  5  6  9 10
    //  3  4  7  8 11 12
    // 13 14 17 18 21 22
    // 15 16 19 20 23 24

    int srcindex, dstindex;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N / B; j++)
        {
            srcindex = i*N + j*B;
            dstindex = j*N + i*B;
            memcpy_s((void*)(dst + dstindex), B, (void*)(src + srcindex), B);
        }
    }
    

    // M=4 N=6

    // 0  6  2
    // 8  4 10
    //12 18 14
    //20 16 22

    //00 01 02
    //10 11 12
    //20 21 22
    //30 31 32
}


void TestTiling()
{
    int* src = new int[24];
    for (int i = 0; i < 24; i++)
    {
        *(src + i) = i + 1;
    }
    int* dst = new int[24];
    makeTiled(dst, src, 4, 6, 2);
}

// -----------------------------------------------------------------------------

int main()
{
    std::ostringstream oss;

    TestTraits();
    TestHierarchy(oss);
    TestStringRotation(oss);
    TestTiling();

    // Print output to console
    cout << oss.str();
    // Pause...
    cout << endl << endl << "Press enter to quit..." << endl;
    char c;
    cin >> noskipws >> c;

    return 0;
}
