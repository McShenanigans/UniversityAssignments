package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.MyList;
import assignment.model.ADT.MyPair;
import assignment.model.ADT.PairInterface;
import assignment.model.DataTypes.IntType;
import assignment.model.DataTypes.IntValue;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;
import assignment.model.Expressions.VariableExpression;
import assignment.model.ProgramState;

public class SemaphoreStatement implements StatementInterface {
    VariableExpression var;
    Expression exp1;

    public SemaphoreStatement(VariableExpression var, Expression e){
        this.var = var;
        exp1 = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value n1 = exp1.eval(state.getSymbolTable(), state.getHeap());
        if(!n1.getType().equals(new IntType())) throw new MyException("given expression does not return integer");
        if(!state.getSymbolTable().exists(var.toString())) throw new MyException("variable " + var + " was not declared");
        if(!state.getSymbolTable().get(var.toString()).getType().equals(new IntType())) throw new MyException("variable " + var + " not an integer");
        PairInterface<Integer> pair = new MyPair<>(((IntValue)n1).getVal(), new MyList<>());
        synchronized (state.getSemaphoreTable()){
            int newFreeLoc = state.getSemaphoreTable().getKeys().size()+1;
            state.getSemaphoreTable().put(newFreeLoc, pair);
            state.getSymbolTable().replace(var.toString(), new IntValue(newFreeLoc));
        }
        return null;
    }

    @Override
    public StatementInterface deepCopy() {
        return new SemaphoreStatement(var, exp1);
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type tVar = var.typecheck(typeEnv);
        Type tExp = exp1.typecheck(typeEnv);
        if(!tExp.equals(new IntType()) || !tVar.equals(new IntType())) throw new MyException("typecheck failure in semaphore statement");
        return typeEnv;
    }

    public String toString(){
        return "createSemaphore("+var.toString()+", "+exp1.toString()+")";
    }
}
