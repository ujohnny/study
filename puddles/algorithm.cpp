std::vector<std::vector<int> > Algorithm::execute(const std::vector<std::vector<int> >& matrix
												  , const std::vector<std::tuple<int, int, int>& tuples) {
	int height = matrix.size();
	int width = matrix[height - 1].size();

	std::vector<std::vector<int> > puddles(height, std::vector<int>(width, -1));

	for (auto el : tuples) {
		int x = std::get<1>(el);
		int y = std::get<2>(el);

		if (puddles[x][y] != 1) {
			continue;
		}

		puddles[x][y] = walk(x, y);
	}
}

int Algorithm::walk(int x, int y) {

}
