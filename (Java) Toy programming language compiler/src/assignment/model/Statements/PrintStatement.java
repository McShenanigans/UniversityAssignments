package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.DataTypes.Type;
import assignment.model.ProgramState;
import assignment.model.ADT.*;
import assignment.model.DataTypes.Value;
import assignment.model.Expressions.Expression;

public class PrintStatement implements StatementInterface {
    private Expression e;

    public PrintStatement(Expression exp) {
        e = exp;
    }

    public ProgramState execute(ProgramState prg) throws MyException {
        ListInterface<Value> l = prg.getOutputList();
        l.push(e.eval(prg.getSymbolTable(), prg.getHeap()));
        return null;
    }

    public String toString() {
        return "Print(" + e.toString() + ")";
    }

    public StatementInterface deepCopy() {
        return new PrintStatement(e.deepCopy());
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        e.typecheck(typeEnv);
        return typeEnv;
    }
}
