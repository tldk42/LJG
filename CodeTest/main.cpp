#include <iostream>
#include <queue>
#include <vector>

using Tmap  = std::vector<std::vector<int32_t>>;
using Tpath = std::pair<int32_t, int32_t>;

std::vector<std::vector<bool>> visited;

int32_t n, m;


bool isValidPath(const Tmap& graph, const Tpath& path)
{
	return
		(path.first >= 0 && path.second >= 0) &&
		(path.first < n && path.second < m &&
			graph[path.first][path.second] == 1);
}


bool bfsRecursive(const Tmap& graph, const Tpath& startPos)
{
	if (isValidPath(graph, startPos) && visited[startPos.first][startPos.second])
	{
		return false;
	}


	std::queue<Tpath> queue;

	queue.push(startPos);

	while (!queue.empty())
	{
		const Tpath path = queue.front();

		queue.pop();

		if (!isValidPath(graph, path))
		{
			continue;
		}
		if (visited[path.first][path.second])
		{
			continue;
		}

		visited[path.first][path.second] = true;

		queue.emplace(path.first - 1, path.second);
		queue.emplace(path.first + 1, path.second);
		queue.emplace(path.first, path.second - 1);
		queue.emplace(path.first, path.second + 1);
	}

	return true;
}


int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int32_t                           t;
	int32_t                           k;
	std::vector<std::vector<int32_t>> map;

	std::cin >> t;


	for (int32_t j = 0; j < t; ++j)
	{
		int32_t           answer = 0;
		std::queue<Tpath> queue;

		std::cin >> n >> m >> k;

		map.clear();
		visited.clear();
		map.resize(n, std::vector<int32_t>(m, 0));
		visited.resize(n, std::vector<bool>(m, false));

		for (int32_t i = 0; i < k; ++i)
		{
			Tpath path;
			std::cin >> path.first >> path.second;

			map[path.first][path.second] = 1;

			queue.push(path);
		}

		while (!queue.empty())
		{
			const Tpath path = queue.front();
			queue.pop();
			if (bfsRecursive(map, path))
			{
				answer++;
			}
		}

		std::cout << answer << '\n';
	}


	return 0;
}
