#include <iostream>
#include <vector>

typedef std::vector<int>::iterator iter;

template <typename T>
void merge(std::vector<T>& v, typename std::vector<T>::iterator beginPos
		   , int size)
{
	typename std::vector<T>::iterator checked = beginPos;
	typename std::vector<T>::iterator merging = beginPos + size / 2;
	while (merging < beginPos + size) {
		if (*checked > *merging) {
			iter swapping = merging;
			int tmp = *merging;
			while (swapping != checked) {
				*swapping = *(--swapping);
			}
			*checked = tmp;
			merging++;
		}
		checked++;
	}
}

template <typename T>
void sort(std::vector<T>& v, typename std::vector<T>::iterator beginPos
		  , int size) 
{
	if (size <= 1)
		return;
	
	sort(v, beginPos, size / 2);
	sort(v, beginPos + size / 2, size / 2 + size % 2);
	merge(v, beginPos, size);
}

int main() {
	std::vector<int> v;
	for (int i = 11; i > 0; i--) {
		v.push_back(i);
	}
	sort(v, v.begin(), v.size());
	for (iter it = v.begin(); it < v.end(); it++) {
		std::cout << *it << std::endl;
	}
}
