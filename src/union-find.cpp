#include <assert.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <iostream>

class UF {
public:
	int quick_find(int e) {
		if (elements_[e].father == -1) {
			return -1;
		} else {
			int root;
			if (elements_[e].father != e) {
				root = quick_find(elements_[e].father);
				elements_[e].father = root;
			} else {
				root = e;
			}
			
			return root;
		}
	}

	void quick_union(int e1, int e2) {
		int max = std::max(e1, e2);
		if (max >= elementNum_) {
			int newSize = max + 1;
			Element *newElementArray = new Element[newSize];
			memcpy((void*)newElementArray, (void*)elements_, elementNum_ * sizeof(Element));
			elementNum_ = newSize;
		}
		if (elements_[e1].father == -1) {
			elements_[e1].father = e1;
		}
		if (elements_[e2].father == -1) {
			elements_[e2].father = e2;
		}
		int father1 = quick_find(e1), father2 = quick_find(e2);
		if (father1 == father2) {
			return;
		}
		if (elements_[father1].rank < elements_[father2].rank) {
			elements_[father1].father = father2;
		} else if (elements_[father1].rank > elements_[father2].rank) {
			elements_[father2].father = father1;
		} else {
			elements_[father2].father = father1;
			elements_[father1].rank ++;
		}
	}

	int depth(int e) {
		if (elements_[e].father == -1) {
			return -1;
		}
		int cursor = e, count = 0;
		while (elements_[cursor].father != cursor) {
			cursor = elements_[cursor].father;
			count ++;
		}
		return count;
	}

private:
	const int BASE_ELEMENTS_NUM = 100000;
	typedef struct ELEMENT_{
		int rank = 0;
		// If one element's father is -1, that means it does not exist in the collection.
		int father = -1;
	}Element;
	int elementNum_ = BASE_ELEMENTS_NUM;
	Element* elements_ = new Element[BASE_ELEMENTS_NUM];
};

int main() {
	srand(time(NULL));
	const int ARRAY_LEN = 10000;
	const int INT_RANGE = 100000;
	int *array = new int[ARRAY_LEN];
	for (int i = 0; i < ARRAY_LEN; i ++) {
		array[i] = rand() % INT_RANGE;
	}
	
	// 1. randomly union the elements.
	UF uf;
	int union_times = ARRAY_LEN;
	for (int i = 0; i < union_times; i ++) {
		int index1 = rand() % ARRAY_LEN, index2 = rand() % ARRAY_LEN;
		uf.quick_union(array[index1], array[index2]);
	}
	// 2. check the depth of every element in UF object.
	for (int i = 0; i < ARRAY_LEN; i ++) {
		int depth = uf.depth(array[i]);
		//std::cout << depth << ", ";
		assert(depth < 5);
	}

	return 0;
}
