package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.RefType;
import assignment.model.DataTypes.RefValue;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

public class HeapAllocStatement implements StatementInterface {
    private String varName;
    private Expression exp;

    public HeapAllocStatement(String varName, Expression exp) {
        this.varName = varName;
        this.exp = exp;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        synchronized (state.getHeap()) {
            if (!state.getSymbolTable().exists(varName))
                throw new MyException("Variable " + varName + " was not declared");
            if (!(state.getSymbolTable().get(varName).getType() instanceof RefType))
                throw new MyException("Variable " + varName + " not a reference type");
            Value v = exp.eval(state.getSymbolTable(), state.getHeap());
            RefValue vRef = (RefValue) state.getSymbolTable().get(varName);
            if (!vRef.getInner().equals(v.getType()))
                throw new MyException("Replacement with different type is illegal");
            int key = state.getHeap().size();
            state.getHeap().put(key, v);
            System.out.println("Assigned on " + key + " value " + v.toString());
            RefValue newRef = new RefValue(key, v.getType());
            state.getSymbolTable().replace(varName, newRef);
            return null;
        }
    }

    @Override
    public StatementInterface deepCopy() {
        return new HeapAllocStatement(varName, exp.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.get(varName), typeExp = exp.typecheck(typeEnv);
        if(typeVar.equals(new RefType(typeExp))) return typeEnv;
        throw new MyException("invalid types in heap allocation statement");
    }

    public String toString() {
        return "new(" + varName + "," + exp.toString() + ")";
    }
}
