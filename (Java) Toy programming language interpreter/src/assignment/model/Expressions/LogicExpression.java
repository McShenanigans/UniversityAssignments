package assignment.model.Expressions;
import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.*;

public class LogicExpression implements Expression{
    private Expression e1, e2;
    private int operation;
    LogicExpression(Expression e1, Expression e2, int operation){
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }
    @Override
    public Value eval(DictionaryInterface<String, Value> tbi, HeapInterface<Integer, Value> heap) throws MyException {
        Value b1 = e1.eval(tbi, heap), b2 = e2.eval(tbi, heap);
        if(!b1.getType().equals(new BoolType())||!b2.getType().equals(new BoolType()))
            throw new MyException("Operands not BoolType");
        boolean bool1 = ((BoolValue)b1).getVal(), bool2 = ((BoolValue)b2).getVal();
        if(operation == 1) return new BoolValue(bool1 && bool2);
        else if (operation == 2) return new BoolValue(bool1 || bool2);
        else throw new MyException("Invalid boolean operation");
    }

    public String toString(){
        String op = "";
        if(operation == 1) op = " and ";
        else if (operation == 2) op  = " or ";
        return e1.toString()+op+e2.toString();
    }

    public Expression deepCopy(){
        return new LogicExpression(e1.deepCopy(), e2.deepCopy(), operation);
    }

    @Override
    public Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type t1 = e1.typecheck(typeEnv), t2 = e2.typecheck(typeEnv);
        if(!t1.equals(new BoolType()) || !t2.equals(new BoolType())) throw new MyException("incompatible types for logic expression");
        return new IntType();
    }
}
