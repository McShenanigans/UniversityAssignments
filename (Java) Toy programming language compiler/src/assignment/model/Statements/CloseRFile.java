package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.StringType;
import assignment.model.DataTypes.StringValue;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

import java.io.BufferedReader;

public class CloseRFile implements StatementInterface{
    private Expression exp;
    public CloseRFile(Expression exp){
        this.exp = exp;
    }
    public ProgramState execute(ProgramState prg) throws MyException{
        Value v = exp.eval(prg.getSymbolTable(), prg.getHeap());
        if(!v.getType().equals(new StringType())) throw new MyException("Argument not a string");
        StringValue v1 = (StringValue) v;
        if(!prg.getFileTable().exists(v1)) throw new MyException("File is not opened");
        BufferedReader reader = prg.getFileTable().get(v1);
        try{
            reader.close();
            prg.getFileTable().remove(v1);
        } catch (Exception e){
            throw new MyException(e.getMessage());
        }
        return null;
    }
    public String toString(){
        return "closeRFile("+exp.toString()+")";
    }
    public StatementInterface deepCopy(){
        return new CloseRFile(exp.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        if(!(exp.typecheck(typeEnv)).equals(new StringType())) throw new MyException("Invalid type for file name");
        return typeEnv;
    }
}
