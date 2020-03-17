package assignment.model.Statements;
import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.Type;
import assignment.model.ProgramState;
public interface StatementInterface {
    ProgramState execute(ProgramState state) throws MyException;
    StatementInterface deepCopy();
    DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException;
}
