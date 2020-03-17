package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.DataTypes.Type;
import assignment.model.ProgramState;
import assignment.model.ADT.*;

public class CompoundStatement implements StatementInterface {
    private StatementInterface s1, s2;

    public CompoundStatement(StatementInterface s1, StatementInterface s2) {
        this.s1 = s1;
        this.s2 = s2;
    }

    public ProgramState execute(ProgramState prg){
        StackInterface<StatementInterface> stack = prg.getExeStack();
        stack.push(s2);
        stack.push(s1);
        return null;
    }

    public String toString() {
        return s1.toString() + "," + s2.toString();
    }

    public StatementInterface deepCopy(){
        return new CompoundStatement(s1.deepCopy(), s2.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        s1.typecheck(typeEnv);
        s2.typecheck(typeEnv);
        return typeEnv;
    }

    public StatementInterface getFirst(){
        return s1.deepCopy();
    }

    public StatementInterface getSecond(){
        return s2.deepCopy();
    }
}
