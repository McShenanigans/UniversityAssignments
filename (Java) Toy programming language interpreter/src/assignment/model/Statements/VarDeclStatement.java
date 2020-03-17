package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.*;
import assignment.model.ProgramState;

public class VarDeclStatement implements StatementInterface {
    private String name;
    private Type type;

    public VarDeclStatement(String name, Type type) {
        this.name = name;
        this.type = type;
    }

    public ProgramState execute(ProgramState prg) throws MyException {
        if(prg.getSymbolTable().exists(name)) throw new MyException("Variable already exists");
        prg.getSymbolTable().put(name, type.defaultValue());
        return null;
    }

    public String toString(){
        return type.toString()+" "+name;
    }

    public StatementInterface deepCopy(){
        return new VarDeclStatement(name, type);
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        typeEnv.put(name, type);
        return typeEnv;
    }
}
