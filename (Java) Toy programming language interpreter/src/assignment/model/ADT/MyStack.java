package assignment.model.ADT;

import java.util.Stack;

public class MyStack<T> implements StackInterface<T> {
    private Stack<T> stack;
    public MyStack(){
        stack = new Stack<>();
    }
    public T pop(){
        return stack.pop();
    }
    public void push(T val){
        stack.push(val);
    }

    public boolean isEmpty(){
        return stack.isEmpty();
    }

    public String toString(){
        return stack.toString();
    }

    public T peek(){
        return stack.peek();
    }
}
