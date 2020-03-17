package assignment.model.ADT;

import assignment.Exceptions.MyException;

import java.util.HashMap;
import java.util.Set;

public class MySemaphore<K,V> implements SemaphoreInterface<K,V> {
    private HashMap<K,V> map;

    public MySemaphore(){
        map = new HashMap<>();
    }

    public String toString(){
        MyList<String> strList = new MyList<>();
        for(K key : map.keySet()){
            if(map.get(key) != null)
                strList.push("("+key.toString()+","+map.get(key).toString()+")");
        }
        return strList.toString();
    }

    @Override
    public synchronized V get(K key) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        return map.get(key);
    }

    @Override
    public synchronized void replace(K key, V newVal) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        map.replace(key, newVal);
    }

    @Override
    public synchronized void put(K key, V val) throws MyException {
        if(map.containsKey(key)) throw new MyException("Invalid key");
        map.put(key, val);
    }

    @Override
    public synchronized void remove(K key) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        map.remove(key);
    }

    @Override
    public synchronized Set<K> getKeys() {
        return map.keySet();
    }

    @Override
    public synchronized boolean exists(K key) throws MyException {
        return map.containsKey(key);
    }
}
