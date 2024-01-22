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

void print_map(vector<vector<int>> map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			cout << map[i][j] << " ";
		}

		cout << '\n';
	}
}

int Astar(vector<vector<int>> map, pair<int, int> start, pair<int, int> goal)
{
	priority_queue<Node, vector<Node>, cmp> open; // �켱 ���� ť

	bool close[10][10] = { 0, }; // ��� ����Ʈ

	vector<Node> close_list;
	Node s_node;

	int cx[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
	int cy[8] = { -1, 0, 1, 0, 1, -1, 1, -1 };

	// ���������� �ʱ�ȭ�Ѵ�.
	s_node.x = start.second;
	s_node.y = start.first;
	s_node.GNode = 0;
	s_node.HNode = (abs(goal.second - s_node.x) + abs(goal.first - s_node.y)) * 10;
	s_node.parent = make_pair(-1, -1); // ���� ����� �θ� ���� -1, -1
	open.push(s_node);
	close[s_node.y][s_node.x] = true; // ��� ���

	vector<vector<int>> result = map;

	while (open.size())
	{
		int x = open.top().x;						// �켱���� ť���� top ���� ����
		int y = open.top().y;
		int G = open.top().GNode;
		close_list.push_back(open.top());
		result[y][x] = 8;
		open.pop();
		if (x == goal.second && y == goal.first) break;	// ���� ������ ������ ��

		Node add;
		for (int i = 0; i < 4; i++) {// top ��忡�� �����¿� 4�������� Ž��(i<8�̸� 8����)
			int nextX = x + cx[i];
			int nextY = y + cy[i];
			if (nextX >= 0 && nextX < map.size() && nextY >= 0 && nextY < map.size()) {
				if (map[nextY][nextX] != 1 && close[nextY][nextX] == false) {
					add.x = nextX;
					add.y = nextY;
					add.GNode = i < 4 ? G + 10 : G + 14;// �����¿�� 10, �밢���̸� 14(��200)
					add.HNode = (abs(goal.second - add.x) + abs(goal.first - add.y)) * 10;
					add.parent = make_pair(y, x);	// ���� top��带 �θ� ���� ����
					close[nextY][nextX] = true;
					result[nextY][nextX] = 9;
					open.push(add);					// �켱���� ť�� ����	
					system("cls");
					print_map(result);
				}
			}
		}

	}


	int px = close_list.back().x;
	int py = close_list.back().y;
	while (close_list.size()) {						// close_list�� �������� ��� Ž��
		if (px == close_list.back().x && py == close_list.back().y) {// ��ǥ ������ �θ� ��带 Ž���� ������
			result[py][px] = 4;
			px = close_list.back().parent.second;
			py = close_list.back().parent.first;
			system("cls");
			print_map(result);
		}
		close_list.pop_back();
	}


	return 0;
}

int main()
{
	int size = 7;
	vector<vector<int>> map(size, vector<int>(size, 0));
	pair<int, int> start, goal;

	start = { 9, 3 };
	goal = { 8, 6 };
	map = { {0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,6,0,0,0},
		{0,0,0,5,1,0,0,0,0,0},
	};
	print_map(map);
	Astar(map, start, goal);


	return 0;
}