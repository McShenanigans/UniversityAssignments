package assignment.model.ADT;
import assignment.Exceptions.MyException;
import java.util.*;

public class MyList<T> implements ListInterface<T>{
    private Vector<T> l;
    public MyList(){
        l = new Vector<>();
    }
    @Override
    public void push(T value){
        l.add(value);
    }
    @Override
    public T get(int position) throws MyException {
        if(position < 0 || position > l.size()) throw new MyException("Invalid index");
        return l.get(position);
    }
    @Override
    public int size(){
        return l.size();
    }

    @Override
    public void setList(List<T> newList) {
        l = new Vector<T>(newList);
    }

    @Override
    public List<T> getList() {
        return l;
    }

    @Override
    public String toString(){
        return l.toString();
    }
}
