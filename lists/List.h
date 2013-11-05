template <typename T>
class List {
public:
	virtual void pushFront(const T& value) = 0;
	virtual void pushBack(const T& value) = 0;
	virtual void popFront() = 0;
	virtual void popBack() = 0;
	virtual const T& getFront() const = 0;
	virtual const T& getBack() const = 0;
	virtual bool isEmpty() const = 0;
	virtual int getSize() const = 0;
	virtual T& operator[](int index) = 0;
	virtual const T& operator[](int index) const = 0;
	virtual void insertAt(int index, const T& value) = 0;
	virtual void removeAt(int index, const T& value) = 0;
	
	virtual ~List() {}
};
