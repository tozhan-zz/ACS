#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <limits> 
#include <math.h>
using namespace std;

// change the double to int, because the compute will be the same for double and int (+ and *)
class BigNum{
public: 
	unsigned short NumList[44];
	unsigned short NumLength;					// record how many item in NumList is used
	short DecimalPointPosition;        // count From right to left, for example 4.123, this value is 3. 
	BigNum(string numStr){
		for (int i = 0; i <= 44; i++){
			NumList[i] = 0;
		}

		// Parse the string
		bool isFindFirstNonZero = false;
		int firstNonZeroPosRight = -1;
		int firstNonZeroPosLeft = -1;
		int tempDecimalPos = -1;

		for (int i = 0; i < numStr.length(); i++)
		{
			if (numStr.at(i) != '0' && numStr.at(i) != '.'){
				firstNonZeroPosLeft = i;
				break;
			}
		}

		if (firstNonZeroPosLeft != -1){
			for (int i = numStr.length() - 1; i >= 0; i--)
			{
				if (numStr.at(i) == '.')
				{
					tempDecimalPos = i;
				}
				else if (!isFindFirstNonZero && (numStr.at(i) != '0'))
				{
					firstNonZeroPosRight = i;
					isFindFirstNonZero = true;
				}
			}

			if (tempDecimalPos == -1){
				DecimalPointPosition = firstNonZeroPosRight-numStr.length()+1;
			}
			else{
				if (tempDecimalPos > firstNonZeroPosRight)
				{
					DecimalPointPosition = 0;
				}
				else
				{
					DecimalPointPosition = firstNonZeroPosRight - tempDecimalPos;
				}
			}

			// Initialize the NumList
			int count = 0;
			int currentNumListItem = 0;
			NumLength = 0;
			for (int i = firstNonZeroPosRight; i >= firstNonZeroPosLeft; i--)
			{
				if (numStr.at(i) != '.'){
					if (count < 4){
						NumList[currentNumListItem] += (numStr.at(i) - '0')*pow(10, count);
						count++;
					}
					else{
						count = 0;
						currentNumListItem++;

						NumList[currentNumListItem] += (numStr.at(i) - '0')*pow(10, count);
						count++;
					}
				}
			}

			NumLength = currentNumListItem + 1;
		}
		else{
			NumLength = 0;
			DecimalPointPosition = 0;
		}
	}

	void Print(){
		if (NumLength == 0)
		{
			cout << 0<<endl;
			return;
		}

		int printDecPointItem = DecimalPointPosition / 4;
		int printDecPointPos = DecimalPointPosition % 4;

		// compute the significant digits
		int signDigits = 4 * (NumLength - 1);
		if (NumList[NumLength - 1] >= 1000){
			signDigits += 4;
		}
		else if (NumList[NumLength - 1] >= 100){
			signDigits += 3;
		}
		else if (NumList[NumLength - 1] >= 10){
			signDigits += 2;
		}
		else{
			signDigits++;
		}

		// output the Big Num
		// Int
		if (DecimalPointPosition<=0){
			cout << NumList[NumLength - 1];            // the first item will not be filled
			for (int i = NumLength - 2; i >= 0; i--){
				cout << setfill('0') << setw(4) << NumList[i];
			}

			if (DecimalPointPosition < 0){
				cout << setfill('0') << setw(0 - DecimalPointPosition) << 0;
			}
		}
		else{	// <1
			if (DecimalPointPosition >= signDigits){
				cout << '.';
				if (DecimalPointPosition == signDigits){
					cout << NumList[NumLength - 1];
					for (int i = NumLength - 2; i >= 0; i--){
						cout << setfill('0') << setw(4) << NumList[i];
					}
				}
				// need to output extra 0
				else{
					cout << setfill('0') << setw(DecimalPointPosition - signDigits) << 0;
					cout << NumList[NumLength - 1];            // the first item will not be filled
					for (int i = NumLength - 2; i >= 0; i--){
						cout << setfill('0') << setw(4) << NumList[i];
					}
				}
			}
			// >1
			else{
				int printDecPointItem = DecimalPointPosition / 4;
				int printDecPointPos = DecimalPointPosition % 4;

				for (int i = NumLength - 1; i >= 0; i--){
					if (i == printDecPointItem){
						int tempNum = 1;
						for (int j = 0; j < printDecPointPos; j++){
							tempNum *= 10;
						}

						int firstPart = NumList[i] / tempNum;
						int secPart = NumList[i] % tempNum;

						if (i == NumLength - 1){
							cout << firstPart << '.';
						}
						else{
							cout << setfill('0') << setw(4 - printDecPointPos) << firstPart<<'.';
						}

						if (printDecPointPos != 0){
							cout << setfill('0') << setw(printDecPointPos) << secPart;
						}
					}
					else{
						if (i == NumLength - 1){
							cout << NumList[i];
						}
						else{
							cout << setfill('0') << setw(4) << NumList[i];
						}
					}
				}
			}
		}
		cout << endl;
	}
};

double long myPower(double long x, int n)
{
	if (n == 1)
	{
		return x;
	}
	else if (n % 2 == 0){
		double long temp = myPower(x, n / 2);
		return temp*temp;
	}
	else{
		double long temp = myPower(x, (n - 1) / 2);
		return x*temp*temp;
	}
}


int main(){
	string temp;
	while (cin >> temp){
		BigNum b(temp);
		b.Print();
	}
}