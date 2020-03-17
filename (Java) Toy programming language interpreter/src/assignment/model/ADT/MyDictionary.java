package assignment.model.ADT;

import assignment.Exceptions.MyException;

import java.util.*;

public class MyDictionary<K, V> implements DictionaryInterface<K, V> {
    private HashMap<K, V> map;

    public MyDictionary() {
        map = new HashMap<>();
    }

    @Override
    public void put(K key, V value) throws MyException {
        if (map.containsKey(key)) throw new MyException("Key already assigned");
        map.put(key, value);
    }

    @Override
    public V get(K key) throws MyException {
        if (!map.containsKey(key)) throw new MyException("Key does not exist");
        return map.get(key);
    }

    @Override
    public void remove(K key){
        map.remove(key);
    }

    @Override
    public Collection<V> getContent() {
        return map.values();
    }

    @Override
    public boolean exists(K key){
        return map.containsKey(key);
    }

    @Override
    public String toString(){
        return map.toString();
    }

    @Override
    public void replace(K key, V value){
        map.replace(key, value);
    }

    @Override
    public Set<K> getKeys(){
        return map.keySet();
    }
}
