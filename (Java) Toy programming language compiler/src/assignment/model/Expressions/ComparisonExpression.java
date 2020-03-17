package assignment.model.Expressions;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.*;

public class ComparisonExpression implements Expression {
    private Expression e1, e2;
    private int operation;

    public ComparisonExpression(Expression e1, Expression e2, int operation) {
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    public Value eval(DictionaryInterface<String, Value> tbl, HeapInterface<Integer, Value> heap) throws MyException {
        Value v1 = e1.eval(tbl, heap), v2 = e2.eval(tbl, heap);
        if (!v1.getType().equals(new IntType()) || !v2.getType().equals(new IntType()))
            throw new MyException("Operands not integers");
        int n1 = ((IntValue) v1).getVal(), n2 = ((IntValue) v2).getVal();
        if (operation == 1) return new BoolValue(n1 < n2);
        else if (operation == 2) return new BoolValue(n1 <= n2);
        else if (operation == 3) return new BoolValue(n1 == n2);
        else if (operation == 4) return new BoolValue(n1 != n2);
        else if (operation == 5) return new BoolValue(n1 >= n2);
        else if (operation == 6) return new BoolValue(n1 > n2);
        else throw new MyException("Invalid operation");
    }

    public String toString() {
        String sign = "";
        if (operation == 1) sign = "<";
        else if (operation == 2) sign = "<=";
        else if (operation == 3) sign = "==";
        else if (operation == 4) sign = "!=";
        else if (operation == 5) sign = ">=";
        else if (operation == 6) sign = ">";
        return e1.toString() + sign + e2.toString();
    }

    public Expression deepCopy(){
        return new ComparisonExpression(e1.deepCopy(), e2.deepCopy(),operation);
    }

    @Override
    public Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type t1 = e1.typecheck(typeEnv), t2 = e2.typecheck(typeEnv);
        if(!t1.equals(new IntType()) || !t2.equals(new IntType())) throw new MyException("incompatible types for comparison expression");
        return new BoolType();
    }
}
