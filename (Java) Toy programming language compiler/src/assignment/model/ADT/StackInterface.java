package assignment.model.ADT;

import assignment.Exceptions.MyException;

public interface StackInterface<T> {
    T pop() throws MyException;
    void push(T v);
    boolean isEmpty();
    T peek();
}
