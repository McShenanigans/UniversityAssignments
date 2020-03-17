package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.BoolType;
import assignment.model.DataTypes.BoolValue;
import assignment.model.DataTypes.Type;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

public class WhileStatement implements StatementInterface {
    private Expression e;
    private StatementInterface s;

    public WhileStatement(Expression e, StatementInterface s) {
        this.e = e;
        this.s = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value v = e.eval(state.getSymbolTable(), state.getHeap());
        if(!v.getType().equals(new BoolType())) throw new MyException("invalid expression type");
        if(!((BoolValue)v).getVal())return state;
        state.getExeStack().push(new WhileStatement(e,s));
        state.getExeStack().push(s);
        return null;
    }

    @Override
    public StatementInterface deepCopy() {
        return new WhileStatement(e.deepCopy(), s.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type typeExp = e.typecheck(typeEnv);
        if(typeExp.equals(new BoolType())){
            s.typecheck(typeEnv);
            return typeEnv;
        }
        throw new MyException("invalid expression in while statement");
    }

    @Override
    public String toString(){
        return "while("+e.toString()+")"+s.toString();
    }
}
