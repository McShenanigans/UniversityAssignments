package assignment.model.ADT;

import assignment.Exceptions.MyException;

import java.util.Collection;
import java.util.Set;

public interface DictionaryInterface<K,V> {
    V get(K key) throws MyException;
    void put(K key, V value) throws MyException;
    boolean exists(K key);
    void replace(K key, V value) throws MyException;
    Set<K> getKeys();
    void remove(K key);
    Collection<V> getContent();
}
