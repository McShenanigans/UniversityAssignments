package assignment.model.ADT;

import assignment.Exceptions.MyException;

import java.util.List;

public interface ListInterface<T> {
    void push(T value);
    T get(int position) throws MyException;
    int size();
    void setList(List<T> newList);
    List<T> getList();
}
