#include "GeometryTest.h"

void GeometryTest::Init(void)
{
	Add("Range", [&](){
		auto check = [&](double b1, double e1, double b2, double e2, bool o){
			Test::Geometry::Range r1 = make_pair(b1, e1);
			Test::Geometry::Range r2 = make_pair(b2, e2);
			bool r = Test::Geometry::IsOverlap(r1, r2);
			Logger().WriteInformation("(%.2f, %.2f) and (%.2f, %.2f) %s overlap\n", b1, e1, b2, e2, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0.0, 1.0, 2.0, 3.0, false);
		check(0.0, 2.0, 1.5, 3.0, true);
		check(0.0, 4.0, 2.0, 3.0, true);
	});

	Add("Rectangle", [&](){
		auto check = [&](
			double b1, double e1, double b2, double e2,
			double b3, double e3, double b4, double e4,
			bool o){
			Test::Geometry::Rectangle r1 = make_pair(make_pair(b1, e1), make_pair(b2, e2));
			Test::Geometry::Rectangle r2 = make_pair(make_pair(b3, e3), make_pair(b4, e4));
			bool r = Test::Geometry::IsOverlap(r1, r2);
			Logger().WriteInformation(
				"((%.2f, %.2f), (%.2f, %.2f)) and ((%.2f, %.2f), (%.2f, %.2f)) %s overlap\n",
				b1, e1, b2, e2, b3, e3, b4, e4, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0, 6, 2, 5, 3, 4, 5, 3, false);
		check(1, 6, 3, 5, 3, 4, 5, 3, false);
		check(2, 6, 4, 5, 3, 4, 5, 3, false);
		check(3, 6, 5, 5, 3, 4, 5, 3, false);
		check(4, 6, 6, 5, 3, 4, 5, 3, false);
		check(5, 6, 7, 5, 3, 4, 5, 3, false);
		check(6, 6, 8, 5, 3, 4, 5, 3, false);

		check(0, 4.5, 2, 3.5, 3, 4, 5, 3, false);
		check(1, 4.5, 3, 3.5, 3, 4, 5, 3, false);
		check(2, 4.5, 4, 3.5, 3, 4, 5, 3, true);
		check(3, 4.5, 5, 3.5, 3, 4, 5, 3, true);
		check(4, 4.5, 6, 3.5, 3, 4, 5, 3, true);
		check(5, 4.5, 7, 3.5, 3, 4, 5, 3, false);
		check(6, 4.5, 8, 3.5, 3, 4, 5, 3, false);

		check(0, 4, 2, 3, 3, 4, 5, 3, false);
		check(1, 4, 3, 3, 3, 4, 5, 3, false);
		check(2, 4, 4, 3, 3, 4, 5, 3, true);
		check(3, 4, 5, 3, 3, 4, 5, 3, true);
		check(4, 4, 6, 3, 3, 4, 5, 3, true);
		check(5, 4, 7, 3, 3, 4, 5, 3, false);
		check(6, 4, 8, 3, 3, 4, 5, 3, false);

		check(0, 3.5, 2, 2.5, 3, 4, 5, 3, false);
		check(1, 3.5, 3, 2.5, 3, 4, 5, 3, false);
		check(2, 3.5, 4, 2.5, 3, 4, 5, 3, true);
		check(3, 3.5, 5, 2.5, 3, 4, 5, 3, true);
		check(4, 3.5, 6, 2.5, 3, 4, 5, 3, true);
		check(5, 3.5, 7, 2.5, 3, 4, 5, 3, false);
		check(6, 3.5, 8, 2.5, 3, 4, 5, 3, false);

		check(0, 2, 2, 1, 3, 4, 5, 3, false);
		check(1, 2, 3, 1, 3, 4, 5, 3, false);
		check(2, 2, 4, 1, 3, 4, 5, 3, false);
		check(3, 2, 5, 1, 3, 4, 5, 3, false);
		check(4, 2, 6, 1, 3, 4, 5, 3, false);
		check(5, 2, 7, 1, 3, 4, 5, 3, false);
		check(6, 2, 8, 1, 3, 4, 5, 3, false);
	});

	Add("IntPoint", [&](){
		vector<Test::Geometry::IntPoint> points = {
			Test::Geometry::IntPoint { 3, 1 },
			Test::Geometry::IntPoint { 3, 1 },
			Test::Geometry::IntPoint { 0, 2 },
			Test::Geometry::IntPoint { 0, 1 },
			Test::Geometry::IntPoint { -1, 0 },
			Test::Geometry::IntPoint { 0, 0 }
		};
		sort(points.begin(), points.end());
		for_each(points.begin(), points.end(), [&](Test::Geometry::IntPoint & p){
			Logger().WriteInformation("  (%d, %d)", p.x, p.y);
		});
		Logger().WriteInformation("\n");
		Test::Geometry::IntPoint p0(-1, 0);
		ASSERT1(points[0] == p0);
		Test::Geometry::IntPoint p1(0, 0);
		ASSERT1(points[1] == p1);
		Test::Geometry::IntPoint p2(0, 1);
		ASSERT1(points[2] == p2);
		Test::Geometry::IntPoint p3(0, 2);
		ASSERT1(points[3] == p3);
		Test::Geometry::IntPoint p4(3, 1);
		ASSERT1(points[4] == p4);
		Test::Geometry::IntPoint p5(3, 1);
		ASSERT1(points[5] == p5);
	});

	Add("MaxPointsOnLine", [&](){
		auto check = [&](vector<Test::Geometry::IntPoint> & points, int expect) {
			Logger().WriteInformation("Input %d points:\n", points.size());
			for_each(points.begin(), points.end(), [&](const Test::Geometry::IntPoint & p){
				Logger().WriteInformation("  (%d, %d)", p.x, p.y);
			});
			Logger().WriteInformation("\n");
			set<Test::Geometry::IntPoint> output;
			int count = Test::Geometry::MaxPointsOnALine(points, output);
			Logger().WriteInformation("Max points on a line: %d\n", count);
			for_each(output.begin(), output.end(), [&](const Test::Geometry::IntPoint & p){
				Logger().WriteInformation("  (%d, %d)", p.x, p.y);
			});
			Logger().WriteInformation("\n");
			ASSERT1(count == expect);
		};
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 1 }
			};
			check(points, 1);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 1 },
				Test::Geometry::IntPoint { 1, 2 }
			};
			check(points, 2);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 1 },
				Test::Geometry::IntPoint { 2, 1 }
			};
			check(points, 2);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 2, 3 },
				Test::Geometry::IntPoint { 4, 5 }
			};
			check(points, 2);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 2 },
				Test::Geometry::IntPoint { 2, 2 },
				Test::Geometry::IntPoint { 1, 1 },
				Test::Geometry::IntPoint { 2, 1 }
			};
			check(points, 2);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 2 },
				Test::Geometry::IntPoint { 2, 2 },
				Test::Geometry::IntPoint { 1, 1 },
				Test::Geometry::IntPoint { 2, 1 },
				Test::Geometry::IntPoint { 3, 1 }
			};
			check(points, 3);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 2, 3 },
				Test::Geometry::IntPoint { 1, 2 },
				Test::Geometry::IntPoint { 2, 2 },
				Test::Geometry::IntPoint { 1, 1 },
				Test::Geometry::IntPoint { 2, 1 }
			};
			check(points, 3);
		}
		{
			vector<Test::Geometry::IntPoint> points = {
				Test::Geometry::IntPoint { 1, 4 },
				Test::Geometry::IntPoint { 1, 3 },
				Test::Geometry::IntPoint { 2, 3 },
				Test::Geometry::IntPoint { 1, 2 },
				Test::Geometry::IntPoint { 2, 2 },
				Test::Geometry::IntPoint { 3, 2 },
				Test::Geometry::IntPoint { 2, 1 },
				Test::Geometry::IntPoint { 3, 1 },
				Test::Geometry::IntPoint { 4, 1 }
			};
			check(points, 4);
		}
	});

	Add("SurroundedRegion", [&](){
		auto print = [&](vector<vector<char>> & board){
			for_each (board.begin(), board.end(), [&](vector<char> & b){
				for_each (b.begin(), b.end(), [&](char c){
					Logger().WriteInformation(" %c", c);
				});
				Logger().WriteInformation("\n");
			});
		};

		auto verify = [&](vector<vector<char>> & board){
			int height = board.size();
			int width = board[0].size();
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (board[i][j] == 'O') {
						bool boundary = i == 0 || i == height - 1 || j == 0 || j == width - 1;
						pair<int, int> p = make_pair(i, j);
						set<pair<int, int>> region;
						queue<pair<int, int>> q;
						region.insert(p);
						q.push(p);
						while (!q.empty()) {
							p = q.front();
							q.pop();
							pair<int, int> n;
							if (p.first > 0 && board[p.first - 1][p.second] == 'O') {
								if (p.first - 1 == 0) boundary = true;
								n = make_pair(p.first - 1, p.second);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.second > 0 && board[p.first][p.second - 1] == 'O') {
								if (p.second - 1 == 0) boundary = true;
								n = make_pair(p.first, p.second - 1);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.second < width - 1 && board[p.first][p.second + 1] == 'O') {
								if (p.second + 1 == width - 1) boundary = true;
								n = make_pair(p.first, p.second + 1);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
							if (p.first < height - 1 && board[p.first + 1][p.second] == 'O') {
								if (p.first + 1 == height - 1) boundary = true;
								n = make_pair(p.first + 1, p.second);
								if (region.find(n) == region.end()) {
									region.insert(n);
									q.push(n);
								}
							}
						}

						ASSERT1(boundary);
					}
				}
			}
		};

		auto check = [&](vector<vector<char>> & board, vector<vector<char>> & board2){
			Logger().WriteInformation("Input:\n");
			print(board);
			Test::Geometry::CaptureSurroundedRegion(board);
			Logger().WriteInformation("Output1:\n");
			print(board);
			verify(board);
			Test::Geometry::CaptureSurroundedRegion(board2);
			Logger().WriteInformation("Output2:\n");
			print(board2);
			verify(board2);
			int height = board.size();
			int width = board[0].size();
			int height2 = board.size();
			int width2 = board[0].size();
			ASSERT1(height == height2);
			ASSERT1(width == width2);
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					ASSERT1(board[i][j] == board2[i][j]);
				}
			}
		};
		{
			vector<vector<char>> board = { { 'X' } };
			vector<vector<char>> board2 = { { 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' } };
			vector<vector<char>> board2 = { { 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'O' } };
			vector<vector<char>> board2 = { { 'O', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X' }, { 'X' } };
			vector<vector<char>> board2 = { { 'X' }, { 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X' }, { 'O' } };
			vector<vector<char>> board2 = { { 'X' }, { 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' }, { 'X' } };
			vector<vector<char>> board2 = { { 'O' }, { 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O' }, { 'O' } };
			vector<vector<char>> board2 = { { 'O' }, { 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' }, { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' }, { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' }, { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' }, { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' }, { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O' }, { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' }, { 'O', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X' }, { 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' }, { 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'X' }, { 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'O' }, { 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'O' }, { 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X' }, { 'O', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'X' }, { 'O', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' }, { 'O', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X' }, { 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' }, { 'X', 'O' } };
			vector<vector<char>> board2 = { { 'X', 'O' }, { 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X' }, { 'X', 'O' } };
			vector<vector<char>> board2 = { { 'O', 'X' }, { 'X', 'O' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O' }, { 'O', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O' }, { 'O', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'X', 'X' }, { 'X', 'X', 'X' }, { 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'X', 'X' }, { 'X', 'X', 'X' }, { 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X', 'X' }, { 'X', 'X', 'X' }, { 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X', 'X' }, { 'X', 'X', 'X' }, { 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'O', 'X', 'X' }, { 'X', 'O', 'X' }, { 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'O', 'X', 'X' }, { 'X', 'O', 'X' }, { 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			vector<vector<char>> board = { { 'X', 'O', 'X' }, { 'X', 'O', 'X' }, { 'X', 'X', 'X' } };
			vector<vector<char>> board2 = { { 'X', 'O', 'X' }, { 'X', 'O', 'X' }, { 'X', 'X', 'X' } };
			check(board, board2);
		}
		{
			for (int i = 0; i < 100; i++) {
				int height = 1 + Test::Random::Next(100);
				int width = 1 + Test::Random::Next(100);
				Logger().WriteInformation("Run %d, %d X %d\n", i, height, width);
				vector<vector<char>> board;
				vector<vector<char>> board2;
				for (int j = 0; j < height; j++) {
					vector<char> row;
					for (int k = 0; k < width; k++) {
						int v = Test::Random::Next();
						if ((v & 0x1) == 1) {
							row.push_back('X');
						} else {
							row.push_back('O');
						}
					}
					board.push_back(row);
					board2.push_back(row);
				}
				check(board, board2);
			}
		}
	});
}