#include <memory>
#include <mutex>
#include <condition_variable>

template <typename T>
class Queue {
public:
	Queue() : _head(NULL)
			, _tail(NULL)
		{}

	void push(const T& value) {
		std::unique_lock<std::mutex> tail_lock(_tail_mutex);
		T *v = new T(value);
		Node *n = new Node(v, NULL);
		if (_tail == NULL) {
			std::unique_lock<std::mutex> head_lock(_head_mutex);
			_tail = n;
			_head = n;
			_predicate = true;
			_cv.notify_one();
		} else {
			_tail->next = n;
		}
		return;
	}

	std::auto_ptr<T> pop() {
		std::unique_lock<std::mutex> head_lock(_head_mutex);

		if (_head == NULL) {
			_cv.wait(head_lock, [&]{return _predicate;});
		}

		std::auto_ptr<T> r(_head->value);
		Node *tmp = _head;
		_head = _head->next;
		if (_head = NULL)
			_predicate = false;
		delete tmp;

		return r;
	}

private:
	struct Node {
		T *value;
		Node *next;
		Node(T *v, Node* n) : value(v), next(n) {}
	};
	Node *_head;
	Node *_tail;

	std::mutex _head_mutex;
	std::mutex _tail_mutex;
	std::condition_variable _cv;
	bool _predicate;
};
