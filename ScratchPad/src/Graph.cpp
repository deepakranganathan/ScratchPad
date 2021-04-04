#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> World = {	{ 1, 1, 0, 0, 0 },
								{ 0, 1, 0, 0, 1 },
								{ 1, 0, 0, 1, 1 },
								{ 0, 0, 0, 0, 0 },
								{ 1, 0, 1, 0, 1 } };

bool isSafe(vector<vector<int>> world, vector<vector<bool>> &visited, int row, int col)
{
	return (row >= 0 && row < world.size() && col>=0 && col < world[0].size() && world[row][col] && !visited[row][col]);
}
void DFS(vector<vector<int>> world, vector<vector<bool>> &visited, vector<pair<int,int>> &island, int row, int col)
{
	visited[row][col] = true;
	island.push_back({ row,col });
	int adj_row[4] = { -1, 1, 0, 0 };
	int adj_col[4] = { 0, 0, -1, 1 };
	for (int i = 0; i < 4; i++)
	{
		if (isSafe(world, visited, row + adj_row[i], col + adj_col[i]))
		{
			DFS(world, visited, island, row + adj_row[i], col + adj_col[i]);
		}
	}
}

int countIslands(vector<vector<int>> world)
{
	int count = 0;

	int row = world.size();
	int col = world[0].size();

	vector<vector<bool>> visited(row);
	for (int k = 0; k < row; k++)
	{
		visited[k].resize(col);
	}

	vector<vector<pair<int, int>>> Islands;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (world[i][j] && !visited[i][j])
			{
				vector<pair<int, int>> island;
				DFS(world, visited, island, i, j);
				++count;
				Islands.push_back(island);
			}
		}
	}
	return count;
}
int RunTestGraph()
{
	cout << countIslands(World);
	return 0;
}

