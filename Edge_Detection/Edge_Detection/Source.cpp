#include <vector>
#include <iostream>
#include <set>

using namespace std;

class CheckPointNode{
public:
	int value;
	CheckPointNode* next;

	CheckPointNode()
	{
		value = -1;
		next = NULL;
	}
};

unsigned short GetPixelValue(vector<unsigned short> * pixelVec, vector<int> PosVec, int position, int startIndex, int endIndex)
{
	if (startIndex == endIndex)
	{
		return (*pixelVec).at(startIndex);
	}
	else if (position == PosVec.at(startIndex))
	{
		return (*pixelVec).at(startIndex);
	}
	else if (position == PosVec.at(endIndex))
	{
		return (*pixelVec).at(endIndex);
	}

	int middleIndex = (startIndex + endIndex) / 2;

	if (position <= middleIndex){
		return GetPixelValue(pixelVec, PosVec, position, startIndex, middleIndex);
	}
	else
	{
		return GetPixelValue(pixelVec, PosVec, position, middleIndex, endIndex);
	}
}

int main()
{
	int width;
	while (cin >> width)
	{
		// Define vector to store input
		vector<unsigned short> pixelVec;
		vector<int> positionVec;
		unsigned short currPixel;
		int currLength;
		int index = 0;

		// create vecotor based on input
		while (true)
		{
			cin >> currPixel >> currLength;
			if (currLength == 0)
			{
				break;
			}

			pixelVec.push_back(currPixel);
			if (index == 0)
			{
				positionVec.push_back(currLength);
			}
			else
			{
				positionVec.push_back(positionVec.at(index - 1) + currLength);
			}

			index++;
		}

		// Compute the compressed image
		int originalItemLength = index;

		// create check point list
		set<int> checkPointsSet;
		CheckPointNode* head = new CheckPointNode();
		checkPointsSet.insert(1);
		(*head).value = 1;

		CheckPointNode* previousNode, currentNode;
		previousNode = head;
	}
}