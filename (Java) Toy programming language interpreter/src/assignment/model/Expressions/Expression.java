package assignment.model.Expressions;
import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.ADT.HeapInterface;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;

public interface Expression {
   Value eval(DictionaryInterface<String, Value> tbl, HeapInterface<Integer, Value> heap) throws MyException;
   Expression deepCopy();
   Type typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException;
}
