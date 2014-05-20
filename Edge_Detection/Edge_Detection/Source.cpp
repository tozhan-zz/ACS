#include <vector>
#include <iostream>
#include <fstream>
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

class OutputNode{
public:
	int length;
	int value;
	OutputNode* next;

	OutputNode(int vValue, int vlength)
	{
		length=vlength;
		value=vValue;
		next=NULL;
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



unsigned short GetPixelValue(vector<unsigned short> * pixelVec, vector<int>* PosVec, int position, int startIndex, int endIndex)
{
	if (startIndex == endIndex)
	{
		return (*pixelVec).at(startIndex);
	}
	else if (position <= PosVec->at(startIndex))
	{
		return (*pixelVec).at(startIndex);
	}
	else if (position > PosVec->at(endIndex-1))
	{
		return (*pixelVec).at(endIndex);
	}

	int middleIndex = (startIndex + endIndex) / 2;

	if (position <= PosVec->at(middleIndex)){
		return GetPixelValue(pixelVec, PosVec, position, startIndex, middleIndex);
	}
	else
	{
		return GetPixelValue(pixelVec, PosVec, position, middleIndex, endIndex);
	}
}

unsigned short GetOutputValue(int currChangePos, int width, vector<unsigned short> * pixelVec, vector<int>* PosVec, int totalindex)
{
	unsigned short max=0, min=255;

	unsigned short currValue;
	unsigned short currNodeValue;
	if(width!=1 && currChangePos%width!=1)
	{
		currValue=GetPixelValue(pixelVec,PosVec,currChangePos-1, 0, totalindex);
		if(currValue>max)
		{
			max=currValue;
		}
		if(currValue<min)
		{
			min=currValue;
		}


		if(currChangePos-width-1>0)
		{
			currValue=GetPixelValue(pixelVec,PosVec,currChangePos-width-1, 0, totalindex);
			if(currValue>max)
			{
				max=currValue;
			}if(currValue<min)
			{
				min=currValue;
			}
		}

		if(currChangePos+width-1<=PosVec->at(totalindex))
		{
			currValue=GetPixelValue(pixelVec,PosVec,currChangePos+width-1, 0, totalindex);
			if(currValue>max)
			{
				max=currValue;
			}if(currValue<min)
			{
				min=currValue;
			}
		}
	}

	// add middle colomn
	if(currChangePos-width>0)
	{
		currValue=GetPixelValue(pixelVec,PosVec,currChangePos-width, 0, totalindex);
		if(currValue>max)
		{
			max=currValue;
		}if(currValue<min)
		{
			min=currValue;
		}
	}

	currNodeValue=GetPixelValue(pixelVec,PosVec,currChangePos, 0, totalindex);


	if(currChangePos+width<=PosVec->at(totalindex))
	{
		currValue=GetPixelValue(pixelVec,PosVec,currChangePos+width, 0, totalindex);
		if(currValue>max)
		{
			max=currValue;
		}if(currValue<min)
		{
			min=currValue;
		}
	}

	// add right colomn
	if (width!=1 && currChangePos%width!=0)
	{
		currValue=GetPixelValue(pixelVec,PosVec,currChangePos+1, 0, totalindex);
		if(currValue>max)
		{
			max=currValue;
		}if(currValue<min)
		{
			min=currValue;
		}

		if(currChangePos-width+1>0)
		{
			currValue=GetPixelValue(pixelVec,PosVec,currChangePos-width+1, 0, totalindex);
			if(currValue>max)
			{
				max=currValue;
			}if(currValue<min)
			{
				min=currValue;
			}
		}

		if(currChangePos+width+1<=PosVec->at(totalindex))
		{
			currValue=GetPixelValue(pixelVec,PosVec,currChangePos+width+1, 0, totalindex);
			if(currValue>max)
			{
				max=currValue;
			}if(currValue<min)
			{
				min=currValue;
			}
		}
	}

	return (max-currNodeValue)>(currNodeValue-min)?max-currNodeValue:currNodeValue-min;
}

// test from file
int main()
{
	int width;
	cin>>width;
	while (width)
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
		for (int i = -1; i < originalItemLength-1; i++){
			int currChangePos;
			if(i==-1){
				currChangePos=1;
			}else
			{
				currChangePos = positionVec.at(i) + 1;
			}

			// add left colomn
			if(width!=1 && currChangePos%width!=1)
			{
				if(!checkPointsSet.count(currChangePos-1))
				{
					checkPointsSet.insert(currChangePos-1);
					AddNode(head, currChangePos-1);
				}

				if(currChangePos-width-1>0)
				{
					if(!checkPointsSet.count(currChangePos-width-1))
					{
						checkPointsSet.insert(currChangePos-width-1);
						AddNode(head, currChangePos-width-1);
					}
				}

				if(currChangePos+width-1<=positionVec.at(originalItemLength-1))
				{
					if(!checkPointsSet.count(currChangePos+width-1))
					{
						checkPointsSet.insert(currChangePos+width-1);
						AddNode(head, currChangePos+width-1);
					}
				}
			}

			// add middle colomn
			if(currChangePos-width>0)
			{
				if(!checkPointsSet.count(currChangePos-width))
				{
					checkPointsSet.insert(currChangePos-width);
					AddNode(head, currChangePos-width);
				}
			}

			if(!checkPointsSet.count(currChangePos))
			{
				checkPointsSet.insert(currChangePos);
				AddNode(head, currChangePos);
			}

			if(currChangePos+width<=positionVec.at(originalItemLength-1))
			{
				if(!checkPointsSet.count(currChangePos+width))
				{
					checkPointsSet.insert(currChangePos+width);
					AddNode(head, currChangePos+width);
				}

			}

			// add right colomn
			if (width!=1 && currChangePos%width!=0)
			{
				if(!checkPointsSet.count(currChangePos+1))
				{
					checkPointsSet.insert(currChangePos+1);
					AddNode(head, currChangePos+1);
				}

				if(currChangePos-width+1>0)
				{
					if(!checkPointsSet.count(currChangePos-width+1))
					{
						checkPointsSet.insert(currChangePos-width+1);
						AddNode(head, currChangePos-width+1);
					}
				}

				if(currChangePos+width+1<=positionVec.at(originalItemLength-1))
				{
					if(!checkPointsSet.count(currChangePos+width+1))
					{
						checkPointsSet.insert(currChangePos+width+1);
						AddNode(head, currChangePos+width+1);
					}
				}
			}
		}

		if(positionVec.at(originalItemLength-1)%width==0)
		{
			if(!checkPointsSet.count(positionVec.at(originalItemLength-1)-(width-1)))
			{
				checkPointsSet.insert(positionVec.at(originalItemLength-1)-(width-1));
				AddNode(head, positionVec.at(originalItemLength-1)-(width-1));
			}
		}else
		{
			int leftBottomPos=positionVec.at(originalItemLength-1) - positionVec.at(originalItemLength-1)%width+1;
			if(!checkPointsSet.count(leftBottomPos))
			{
				checkPointsSet.insert(leftBottomPos);
				AddNode(head, leftBottomPos);
			}
		}

		// test output
		int outputLen=0;
		int totalLen=0;
		CheckPointNode *currCheckNode=head->next;
		CheckPointNode *preCheckNode=head;
		OutputNode* outputListHead=new OutputNode(GetOutputValue(1,width,&pixelVec,&positionVec,originalItemLength-1), 0);
		outputLen++;
		OutputNode* currOutputNode=outputListHead;
		for(;currCheckNode!=NULL;delete(preCheckNode),preCheckNode=currCheckNode,currCheckNode=currCheckNode->next)
		{
			currOutputNode->length+=(currCheckNode->value-preCheckNode->value);
			totalLen+=(currCheckNode->value-preCheckNode->value);
			unsigned short currNodePixelValue=GetOutputValue(currCheckNode->value, width,&pixelVec,&positionVec,originalItemLength-1);
			if(currNodePixelValue==currOutputNode->value)
			{
				continue;
			}else
			{
				OutputNode* newOutputNode=new OutputNode(currNodePixelValue,0);
				outputLen++;
				if(outputLen>1000)
				{
					break;
				}

				currOutputNode->next=newOutputNode;
				currOutputNode=newOutputNode;
			}

		}
		currOutputNode->length+=(positionVec.at(originalItemLength-1)-totalLen);
		delete(preCheckNode);

		// output
		OutputNode* previousOutputNode;
		if(outputLen>1000)
		{
			for(previousOutputNode=outputListHead, currOutputNode=outputListHead->next;currOutputNode!=NULL;previousOutputNode=currOutputNode,currOutputNode=currOutputNode->next)
			{
				delete(previousOutputNode);
			}
			delete(previousOutputNode);
		}else
		{
			cout<<width<<endl;
			for(previousOutputNode=outputListHead, currOutputNode=outputListHead->next;currOutputNode!=NULL;previousOutputNode=currOutputNode,currOutputNode=currOutputNode->next)
			{
				cout<<previousOutputNode->value<<" "<<previousOutputNode->length<<endl;
				delete(previousOutputNode);
			}
			cout<<previousOutputNode->value<<" "<<previousOutputNode->length<<endl;
			delete(previousOutputNode);

			cout<<"0 0"<<endl;
		}

		cin>>width;
	}

	cout<<"0"<<endl;
}