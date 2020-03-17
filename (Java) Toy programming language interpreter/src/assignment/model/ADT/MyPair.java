package assignment.model.ADT;

public class MyPair<T> implements PairInterface<T> {
    private T first;
    private ListInterface<T> second;

    public MyPair(T first, ListInterface<T> second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public T getFirst() {
        return first;
    }

    @Override
    public ListInterface<T> getSecond() {
        return second;
    }

    public String toString() {
        return "(" + first.toString() + ", " + second.toString() + ")";
    }
}
