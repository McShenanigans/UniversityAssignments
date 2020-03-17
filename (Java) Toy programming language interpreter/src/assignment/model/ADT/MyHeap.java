package assignment.model.ADT;

import assignment.Exceptions.MyException;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyHeap<K,V> implements HeapInterface<K,V> {
    private HashMap<K, V> map;
    private int size;
    public MyHeap(K initial){
        map = new HashMap<>();
        map.put(initial, null);
        size = 1;
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
    public V get(K key) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        return map.get(key);
    }

    @Override
    public void replace(K key, V newVal) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        map.replace(key, newVal);
    }

    @Override
    public void put(K key, V val) throws MyException{
        if(map.containsKey(key)) throw new MyException("Invalid key");
        map.put(key, val);
        size++;
    }

    @Override
    public void remove(K key) throws MyException {
        if(!map.containsKey(key)) throw new MyException("Invalid key");
        map.remove(key);
    }

    @Override
    public Set<K> getKeys() {
        return map.keySet();
    }

    @Override
    public boolean exists(K key) throws MyException {
        return map.containsKey(key);
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Map<K, V> getContent() {
        return map;
    }

    @Override
    public void setContent(Map<K,V> map) {
        this.map = (HashMap<K, V>) map;
    }
}
