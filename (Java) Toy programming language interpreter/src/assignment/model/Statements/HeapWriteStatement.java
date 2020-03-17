package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.RefType;
import assignment.model.DataTypes.RefValue;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

public class HeapWriteStatement implements StatementInterface{
    private String varName;
    private Expression newVal;

    public HeapWriteStatement(String heapAddr, Expression exp){
        this.varName = heapAddr;
        newVal = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        if(!state.getSymbolTable().exists(varName)) throw new MyException("Variable" + varName + " is not declared");
        if(!((state.getSymbolTable().get(varName)).getType() instanceof RefType)) throw new MyException("Variable not of RefType");
        int addr = ((RefValue)state.getSymbolTable().get(varName)).getAddr();
        if(!(state.getHeap().exists(addr))) throw new MyException("Key not present in heap");
        Value v = newVal.eval(state.getSymbolTable(), state.getHeap());
        if(!v.getType().equals(((RefValue)state.getSymbolTable().get(varName)).getInner()))
            throw new MyException("RefTypes not equal");
        state.getHeap().replace(addr, v);
        return null;
    }

    @Override
    public StatementInterface deepCopy() {
        return new HeapWriteStatement(varName, newVal.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type tVar = typeEnv.get(varName), tExp = newVal.typecheck(typeEnv);
        if(!tVar.equals(new RefType(tExp)) || !(tVar instanceof RefType)) throw new MyException("invalid types in heap write statement");
        return typeEnv;
    }

    public String toString(){
        return "wH("+varName+","+newVal.toString()+")";
    }
}
