package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.Type;
import assignment.model.Expressions.ComparisonExpression;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

public class SwitchStatement implements StatementInterface {
    private Expression exp, exp1, exp2;
    private StatementInterface stmt1, stmt2, stmt3;

    public SwitchStatement(Expression e, Expression e1, Expression e2, StatementInterface s1, StatementInterface s2, StatementInterface s3) {
        exp = e;
        exp1 = e1;
        exp2 = e2;
        stmt1 = s1;
        stmt2 = s2;
        stmt3 = s3;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        state.getExeStack().push(
                new IfStatement(
                        new ComparisonExpression(exp, exp1, 3), stmt1,
                        new IfStatement(
                                new ComparisonExpression(exp, exp2, 3), stmt2, stmt3
                        )
                )
        );
        return null;
    }

    @Override
    public StatementInterface deepCopy() {
        return new SwitchStatement(exp, exp1, exp2, stmt1, stmt2, stmt3);
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type t1 = exp.typecheck(typeEnv);
        Type t2 = exp1.typecheck(typeEnv);
        Type t3 = exp2.typecheck(typeEnv);
        if (!t1.equals(t2) || !t1.equals(t3)) throw new MyException("typecheck error in switch statement");
        stmt1.typecheck(typeEnv);
        stmt2.typecheck(typeEnv);
        stmt3.typecheck(typeEnv);
        return typeEnv;

//        return (
//                new IfStatement(
//                        new ComparisonExpression(exp, exp1, 3), stmt1,
//                        new IfStatement(
//                                new ComparisonExpression(exp, exp2, 3), stmt2, stmt3
//                        )
//                )
//        ).typecheck(typeEnv);
    }

    public String toString() {
        return "switch(" + exp.toString() + ")\n\t(case (" + exp1.toString() + "): " + stmt1.toString() + ")\n\t(case (" + exp2.toString() + "): " + stmt2.toString() + ")\n\t(case (default: " + stmt3.toString() + ")";
    }
}
