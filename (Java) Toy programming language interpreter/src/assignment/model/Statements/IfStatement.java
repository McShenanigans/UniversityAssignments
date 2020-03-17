package assignment.model.Statements;
import assignment.Exceptions.MyException;
import assignment.model.ADT.*;
import assignment.model.DataTypes.*;
import assignment.model.ProgramState;
import assignment.model.Expressions.Expression;

public class IfStatement implements StatementInterface {
    private Expression e;
    private StatementInterface s1, s2;
    public IfStatement(Expression e, StatementInterface s1, StatementInterface s2){
        this.e = e;
        this.s1 = s1;
        this.s2 = s2;
    }

    public ProgramState execute(ProgramState prg) throws MyException {
        StackInterface<StatementInterface> exeS = prg.getExeStack();
        Value v = e.eval(prg.getSymbolTable(), prg.getHeap());
        if(!v.getType().equals(new BoolType())) throw new MyException("Expression not of boolean type");
        if(((BoolValue)v).getVal()){
            exeS.push(s1);
        } else exeS.push(s2);
        return null;
    }

    public String toString(){
        return "if " + e.toString() + " then " + s1.toString() + " else " + s2.toString();
    }

    public StatementInterface deepCopy(){
        return new IfStatement(e.deepCopy(), s1.deepCopy(), s2.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type typeExp = e.typecheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            s1.typecheck(clone(typeEnv));
            s2.typecheck(clone(typeEnv));
            return typeEnv;
        }
        throw new MyException("invalid condition for if statement");
    }

    private DictionaryInterface<String, Type> clone(DictionaryInterface<String, Type> typeEnv) throws MyException {
        MyDictionary<String, Type> newDict = new MyDictionary<>();
        for(String key: typeEnv.getKeys())
            newDict.put(key, typeEnv.get(key));
        return newDict;
    }
}
