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
import java.io.FileReader;

public class OpenRFile implements StatementInterface {
    private Expression exp;
    public OpenRFile(Expression exp){
        this.exp = exp;
    }
    public ProgramState execute(ProgramState prg) throws MyException{
        Value v = exp.eval(prg.getSymbolTable(), prg.getHeap());
        if(!(v.getType().equals(new StringType()))) throw new MyException("Argument not string");
        StringValue v1 = (StringValue) v;
        if(prg.getFileTable().exists(v1)) throw new MyException("File already opened");
        BufferedReader reader;
        try{
            reader = new BufferedReader(new FileReader((v1.getVal())));
            prg.getFileTable().put(v1,reader);
        } catch (Exception e){
            throw new MyException(e.getMessage());
        }
        return null;
    }
    public String toString(){
        return "openRFile("+exp.toString()+")";
    }
    public StatementInterface deepCopy(){
        return new OpenRFile(exp.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<java.lang.String, assignment.model.DataTypes.Type> typeEnv) throws MyException {
        if(!(exp.typecheck(typeEnv)).equals(new StringType())) throw new MyException("Invalid type for file name");
        return typeEnv;
    }
}
