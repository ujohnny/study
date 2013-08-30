#include <memory>
#include <mutex>
#include <condition_variable>

// assume that type T doesn't have a copy ctor and operator new()
template <typename T>
class Queue {
public:
	Queue() : head_(nullptr)
		, tail_(nullptr)
		{}

	template<typename A1>
	void push(const A1& arg1) {
		Node *n = new Node(arg1);
		push_back(n);
	}
		
	template<typename A1, typename A2>
	void push(const A1& arg1, const A2& arg2) {
		Node *n = new Node(arg1, arg2);
		push_back(n);
	}
	
private:
	struct Node {
		T value;
		Node *next;
		
		template <typename A1>
		Node(const A1& arg1) : value(arg1), next(nullptr) {}
		
		template <typename A1, typename A2>
		Node(const A1& arg1, const A2& arg2) : value (arg1, arg2), next(nullptr) {}
	};
	
	template<typename V, typename N>
	struct node_holder {
	N *current;
	node_holder(N *n) : current(n) {}
	~node_holder() { delete current; }
	V& operator*() {
		return current->value;
	}
};

public:
	typedef node_holder<T, Node > iterator;
	typedef node_holder<T const, Node const> const_iterator;

	node_holder<T, Node> pop() {
		std::unique_lock<std::mutex> lock(mutex_);
		if (head_ == nullptr) {
			cv_.wait(lock, [&]{ return head_ != nullptr; });
		}
		iterator res(head_);
		head_ = head_->next;
		if (head_ == nullptr) {
			tail_ = nullptr;
		}
		return res; //rvo?
	}

	
private:
	void push_back(Node* n) {
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
	
	Node *head_;
	Node *tail_;

	std::mutex mutex_;
	std::condition_variable cv_;
};
