#pragma once
#include "repository.h"
template <typename TElem>
class UndoRepo : public repository<TElem>
{
private:
	vector<string> operations;
public:
	void pushOperation(string op, TElem obj) override;
	void emptyRepo() override;
	void writeToFile(vector<string> items) override;
	string lastOperation() override;
	TElem lastObj() override;
	UndoRepo() {};
	~UndoRepo() {};
};

template<typename TElem>
inline void UndoRepo<TElem>::pushOperation(string op, TElem obj){
	operations.push_back(op);
	v.push_back(obj);
}

template<typename TElem>
inline void UndoRepo<TElem>::emptyRepo(){
	operations.clear();
	v.clear();
}

template<typename TElem>
inline void UndoRepo<TElem>::writeToFile(vector<string> items) {}

template<typename TElem>
inline string UndoRepo<TElem>::lastOperation(){
	if (operations.size() < 1) throw invalid_argument("");
	string lastOp = operations[operations.size() - 1];
	operations.pop_back();
	return lastOp;
}

template<typename TElem>
inline TElem UndoRepo<TElem>::lastObj(){
	if (v.size() < 1) throw invalid_argument("");
	TElem lastObj = v[v.size() - 1];
	v.pop_back();
	return lastObj;
}
