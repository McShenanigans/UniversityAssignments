package assignment.model.Expressions;
import assignment.Exceptions.MyException;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.ADT.DictionaryInterface;

public class VariableExpression implements Expression {
    private String id;
    public VariableExpression(String id){
        this.id = id;
    }
    @Override
    public Value eval(DictionaryInterface<String, Value> tbl, HeapInterface<Integer, Value> heap) throws MyException{
        return tbl.get(id);
    }
    public String toString(){
        return id;
    }

    public Expression deepCopy(){
        return new VariableExpression(id);
    }

    @Override
    public Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        return typeEnv.get(id);
    }
}
