package assignment.model.ADT;

import assignment.Exceptions.MyException;

import java.util.Set;

public interface SemaphoreInterface<K,V> {
    V get(K key) throws MyException;
    void replace(K key, V newVal) throws MyException;
    void put(K key, V val) throws MyException;
    void remove(K key) throws MyException;
    Set<K> getKeys();
    boolean exists(K key) throws MyException;
}
