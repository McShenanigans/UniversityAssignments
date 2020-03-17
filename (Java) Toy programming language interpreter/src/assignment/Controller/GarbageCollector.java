package assignment.Controller;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.RefType;
import assignment.model.DataTypes.RefValue;
import assignment.model.DataTypes.Value;

import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Vector;
import java.util.stream.Collectors;

public class GarbageCollector {
    public GarbageCollector() {}

    public Map<Integer, Value> getGarbage(DictionaryInterface<String, Value> symTable, HeapInterface<Integer,Value> heap){
        return findGarbage(getAddrFromSymTable(symTable.getContent()),heap.getContent());
    }

    public Map<Integer, Value> getGarbage_threaded(List<DictionaryInterface<String, Value>>symTables, HeapInterface<Integer, Value> heap) throws MyException {
        return findGarbage(getAddr_threaded(symTables), heap.getContent());
    }

    private Map<Integer, Value> findGarbage(List<Integer> addresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream().filter(e->{
            if(e.getKey().equals(0)) return false;
            if(addresses.contains(e.getKey())) return true;
            for(int key : heap.keySet()){
                Value v = heap.get(key);
                while(v instanceof RefValue){
                    RefValue v1 = (RefValue)v;
                    if(e.getKey().equals(v1.getAddr())) return true;
                    v = heap.get(v1.getAddr());
                }
            }
            return false;
        }).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<Integer> getAddr_threaded(List<DictionaryInterface<String, Value>>symTables) throws MyException {
        Vector<Integer> addrList = new Vector<>();
        for(DictionaryInterface<String, Value> symTable : symTables){
            for(String key : symTable.getKeys()) {
                if (symTable.get(key).getType() instanceof RefType)
                    addrList.add(((RefValue) symTable.get(key)).getAddr());
            }
        }
        return addrList;
    }

    private List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream().filter(val -> val instanceof RefValue).map(v -> {
            RefValue v1 = (RefValue) v;
            return v1.getAddr();
        }).collect(Collectors.toList());
    }
}
