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

void AddNode(CheckPointNode* head, int newValue)
{
	CheckPointNode* newNode = new CheckPointNode();
	(*newNode).value = newValue;
	
	CheckPointNode* previousNode = head;
	CheckPointNode* currNode = head->next;
	for (; currNode!= NULL; previousNode = currNode, currNode = currNode->next)
	{
		if (newValue < currNode->value){
			previousNode->next = newNode;
			newNode->next = currNode;
			break;
		}
	}

	if (currNode == NULL){
		previousNode->next = newNode;
	}
}

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
		for (int i = 0; i < originalItemLength; i++){
			int currChangePos = positionVec.at(i) + 1;

			// situation 1
			if (currChangePos < width)
			{
				if (!checkPointsSet.count(currChangePos))
				{
					checkPointsSet.insert(currChangePos);
					AddNode(head, currChangePos);
				}

				if (!checkPointsSet.count(currChangePos + 1))
				{

					checkPointsSet.insert(currChangePos + 1);
					AddNode(head, currChangePos + 1);
				}

				if ((currChangePos + width - 1) <= positionVec.at(originalItemLength - 1))
				{
					if (!checkPointsSet.count(currChangePos + width - 1)){
						checkPointsSet.insert(currChangePos + width - 1);
						AddNode(head, currChangePos + width - 1);
					}
				}

				if ((currChangePos + width + 1) <= positionVec.at(originalItemLength - 1))
				{
					if (!checkPointsSet.count(currChangePos + width + 1)){
						checkPointsSet.insert(currChangePos + width + 1);
						AddNode(head, currChangePos + width + 1);
					}
				}
			}
			//situation 2
			else if (currChangePos == width)
			{
				if (!checkPointsSet.count(currChangePos - 1)){
					checkPointsSet.insert(currChangePos - 1);
					AddNode(head, currChangePos - 1);
				}

				if (!checkPointsSet.count(currChangePos)){
					checkPointsSet.insert(currChangePos);
					AddNode(head, currChangePos);
				}

				if ((currChangePos + width - 1) <= positionVec.at(originalItemLength - 1))
				{
					if (!checkPointsSet.count(currChangePos + width - 1)){
						checkPointsSet.insert(currChangePos + width - 1);
						AddNode(head, currChangePos + width - 1);
					}
				}
			}
			//situation 3
			else if (currChangePos%width == 1)
			{
				if ((currChangePos - width)>0)
				{
					if (!checkPointsSet.count(currChangePos - width)){
						checkPointsSet.insert(currChangePos - width);
						AddNode(head, currChangePos - width);
					}
				}

				if (!checkPointsSet.count(currChangePos)){
					checkPointsSet.insert(currChangePos);
					AddNode(head, currChangePos);
				}

				if ((currChangePos + width) <= positionVec.at(originalItemLength - 1))
				{
					if (!checkPointsSet.count(currChangePos + width)){
						checkPointsSet.insert(currChangePos + width);
						AddNode(head, currChangePos + width);
					}
				}
			}

			//situation 4
			else if (currChangePos%width == 0)
			{

			}
		}
	}
}