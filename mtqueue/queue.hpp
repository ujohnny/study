#include <memory>
#include <mutex>
#include <condition_variable>

template<typename V, typename N>
struct queue_iterator {
	N *current;
	queue_iterator(N *n) : current(n) {}
	~queue_iterator() { delete current; }
	V& operator*() {
		return current->value;
	}
};

template <typename T>
struct Node {
		T value;
		Node *next;
		
		template <typename A1>
		Node(const A1& arg1, Node* n) : value(arg1), next(n) {}
		
		template <typename A1, typename A2>
		Node(const A1& arg1, const A2& arg2, Node *n) : value (arg1, arg2), next(n) {}
};

// assume that type T doesn't have a copy ctor and operator new()
template <typename T>
class Queue {
public:
	Queue() : head_(nullptr)
		, tail_(nullptr)
		{}

	template<typename A1>
	void push(const A1& arg1) {
		Node<T> *n = new Node<T>(arg1, NULL);
		push_back(n);
	}
		
	template<typename A1, typename A2>
	void push(const A1& arg1, const A2& arg2) {
		Node<T> *n = new Node<T>(arg1, arg2, NULL);
		push_back(n);
	}
	
	queue_iterator<T, Node<T> > pop() {
		std::unique_lock<std::mutex> lock(mutex_);
		if (head_ == nullptr) {
			cv_.wait(lock);
		}
		iterator res(head_);
		head_ = head_->next;
		if (head_ == nullptr) {
			tail_ = nullptr;
		}
		return res; //rvo?
	}
	typedef queue_iterator<T, Node<T> > iterator;
	typedef queue_iterator<T const, Node<T> const> const_iterator;
	
private:
	void push_back(Node<T>* n) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (head_ == nullptr) {
			head_ = n;
			tail_ = n;
			cv_.notify_one();
		} else {
			tail_->next = n;
			tail_ = n;
		}
	}
	
	Node<T> *head_;
	Node<T> *tail_;

	std::mutex mutex_;
	std::condition_variable cv_;
};
