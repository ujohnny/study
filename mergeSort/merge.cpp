#include <vector>

template <typename T>
void merge(std::vector<T>& v, typename std::vector<T>::iterator beginPos
		   , int size)
{
	typename std::vector<T>::iterator checked = beginPos;
	typename std::vector<T>::iterator merging = beginPos + size / 2;
	while (checked < merging && merging < beginPos + size) {
		if (*checked > *merging) {
			typename std::vector<T>::iterator swapping = merging;
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
void msort(std::vector<T>& v, typename std::vector<T>::iterator beginPos
		  , int size) 
{
	if (size <= 1)
		return;
	
	msort(v, beginPos, size / 2);
	msort(v, beginPos + size / 2, size / 2 + size % 2);
	merge(v, beginPos, size);
}
