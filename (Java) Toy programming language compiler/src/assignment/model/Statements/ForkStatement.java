package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.MyDictionary;
import assignment.model.ADT.MyStack;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.ProgramState;

public class ForkStatement implements StatementInterface {
    private StatementInterface stmt;
    public ForkStatement(StatementInterface stmt){
        this.stmt = stmt;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        DictionaryInterface<String, Value> symTCopy = new MyDictionary<>();
        for(String key: state.getSymbolTable().getKeys())
            symTCopy.put(key, state.getSymbolTable().get(key).deepCopy());
        return new ProgramState(state.getIdGenerator(), new MyStack<>(), symTCopy, state.getOutputList(), stmt, state.getFileTable(), state.getHeap(), state.getSemaphoreTable());
    }

    @Override
    public StatementInterface deepCopy() {
        return null;
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        stmt.typecheck(typeEnv);
        return typeEnv;
    }

    public String toString(){
        return "fork("+stmt.toString()+")";
    }
}
