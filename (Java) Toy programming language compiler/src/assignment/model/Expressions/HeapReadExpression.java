package assignment.model.Expressions;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.*;

public class HeapReadExpression implements Expression{
    private Expression refVal;

    public HeapReadExpression(Expression exp){
        refVal = exp;
    }

    @Override
    public Value eval(DictionaryInterface<String, Value> tbl, HeapInterface<Integer, Value> heap) throws MyException {
        Value v = refVal.eval(tbl, heap);
        if(!(v.getType() instanceof RefType)) throw new MyException("Expression did not evaluate to RefValue");
        int addr = ((RefValue)v).getAddr();
        return heap.get(addr);
    }

    @Override
    public Expression deepCopy() {
        return new HeapReadExpression(refVal.deepCopy());
    }

    @Override
    public Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type t = refVal.typecheck(typeEnv);
        if(!(t instanceof RefType)) throw new MyException("invalid data type for ReadHeap expression");
        return ((RefType)t).getInner();
    }

    public String toString(){
        return "rH("+refVal.toString()+")";
    }
}
