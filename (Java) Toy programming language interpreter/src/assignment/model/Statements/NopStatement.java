package assignment.model.Statements;
import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.Type;
import assignment.model.ProgramState;

public class NopStatement implements StatementInterface {
    public NopStatement(){}
    public ProgramState execute(ProgramState prg){
        return null;
    }
    public String toString(){
        return "";
    }
    public StatementInterface deepCopy(){
        return new NopStatement();
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        return typeEnv;
    }
}
