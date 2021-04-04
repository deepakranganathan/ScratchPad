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

#include <string>
#include <sstream>
#include <iostream>


#define CHECK(cond, errstream, oss) \
    if (!(cond)) \
    { \
        (oss) << errstream << std::endl; \
        return; \
    }


void RotateString(std::string& S, int R)
{
	// TODO: Implement this function
	int len = S.length();
	if (len == 0)
		return;

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
	int cur1 = 0;
	int pivot = S.length() - R;
	int cur2 = pivot;
	while (pivot != S.length())
	{
		char temp = S[cur1];
		S[cur1++] = S[cur2];
		S[cur2++] = temp;
		if (cur1 == pivot)
		{
			pivot = cur2;
		}
		else if (cur2 == S.length())
		{
			cur2 = pivot;
		}
	}
}

void TestStringRotation(std::ostream& error_output)
{
	const std::string failure_msg("String rotation failed!");

	std::string s1("sprint");
	RotateStringOptimal(s1, 5);
	CHECK(s1 == "prints", failure_msg, error_output);

	std::string s2("StringRotated");
	RotateStringOptimal(s2, 7);
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

void RunTestStringRotation()
{
	std::ostringstream oss;

	TestStringRotation(oss);

	// Print output to console
	std::cout << oss.str();

	// Pause...
	std::cout << std::endl
		<< std::endl
		<< "Press enter to quit..." << std::endl;
	char c;
	std::cin >> std::noskipws >> c;
}
