package assignment.model.Expressions;
import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;

public class ValueExpression implements Expression{
    private Value v;
    public ValueExpression(Value v){
        this.v = v;
    }
    public Value eval(DictionaryInterface<String, Value> tbl, HeapInterface<Integer, Value> heap){
        return v;
    }
    public String toString(){
        return v.toString();
    }

    public Expression deepCopy(){
        return new ValueExpression(v.deepCopy());
    }

    @Override
    public Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        return v.getType();
    }
}
