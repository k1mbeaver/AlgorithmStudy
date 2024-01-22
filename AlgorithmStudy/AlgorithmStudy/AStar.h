#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

typedef struct node {
	int x, y;
	int GNode, HNode;
	pair<int, int> parent;
}Node;

struct cmp {
	bool operator()(const node u, const node v)
	{
		if (u.GNode + u.HNode > v.GNode + v.HNode)
		{
			return true;
		}

		else if (u.GNode + u.HNode == v.GNode + v.HNode)
		{
			if (u.GNode < v.GNode)
			{
				return true;
			}

			else
			{
				return false;
			}
		}

		else
		{
			return false;
		}
	}
};

void print_map