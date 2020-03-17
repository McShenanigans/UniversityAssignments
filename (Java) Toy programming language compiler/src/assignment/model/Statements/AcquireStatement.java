package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.PairInterface;
import assignment.model.DataTypes.IntType;
import assignment.model.DataTypes.IntValue;
import assignment.model.DataTypes.Type;
import assignment.model.Expressions.VariableExpression;
import assignment.model.ProgramState;

public class AcquireStatement implements StatementInterface {
    private VariableExpression var;

    public AcquireStatement(VariableExpression var) {
        this.var = var;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        if (!state.getSymbolTable().exists(var.toString())) throw new MyException("Variable " + var + " not declared");
        if (!state.getSymbolTable().get(var.toString()).getType().equals(new IntType()))
            throw new MyException("Variable " + var + " not an integer");
        int index = ((IntValue) var.eval(state.getSymbolTable(), state.getHeap())).getVal();
        synchronized (state.getSemaphoreTable()) {
            if (!state.getSemaphoreTable().exists(index)) throw new MyException("Index not in semaphore table");
            PairInterface<Integer> pair = state.getSemaphoreTable().get(index);
            if (pair.getFirst() > pair.getSecond().size()) {
                if (!pair.getSecond().getList().contains(state.getId()))
                    pair.getSecond().push(state.getId());
            } else {
                state.getExeStack().push(new AcquireStatement(var));
            }
        }
        return null;
    }

    @Override
    public StatementInterface deepCopy() {
        return new AcquireStatement(var);
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        if(!var.typecheck(typeEnv).equals(new IntType())) throw new MyException("typecheck error in acquire statement");
        return typeEnv;
    }

    public String toString(){
        return "acquire("+var.toString()+")";
    }
}
