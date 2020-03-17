package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.*;
import assignment.model.DataTypes.Type;
import assignment.model.ProgramState;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;

public class AssignmentStatement implements StatementInterface {
    private String id;
    private Expression e;

    public AssignmentStatement(String id, Expression e) {
        this.id = id;
        this.e = e;
    }

    public ProgramState execute(ProgramState prg) throws MyException {
        DictionaryInterface<String, Value> symT = prg.getSymbolTable();
        if (!symT.exists(id)) throw new MyException("Variable " + id + " is undeclared");
        Value v = e.eval(symT, prg.getHeap());
        Type typeId = symT.get(id).getType();
        if (v.getType().equals(typeId)) symT.replace(id, v);
        else throw new MyException("Invalid type assigned to " + id);
        return null;
    }

    public String toString(){
        return id + " = " + e.toString();
    }

    public StatementInterface deepCopy(){
        return new AssignmentStatement(id,e.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.get(id), typeExp = e.typecheck(typeEnv);
        if(typeVar.equals(typeExp)) return typeEnv;
        throw new MyException("Incompatible data types in assignment statement");
    }
}
