package assignment.model.Statements;

import assignment.Exceptions.MyException;
import assignment.model.ADT.DictionaryInterface;
import assignment.model.DataTypes.*;
import assignment.model.Expressions.Expression;
import assignment.model.ProgramState;

import java.io.BufferedReader;

public class ReadFile implements StatementInterface {
    private String varName;
    private Expression exp;

    public ReadFile(Expression exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    private String removeNonInt(String str) {
        if (str == null) return "0";
        String res = "";
        for (char c : str.toCharArray()) {
            if(c == '0') res = res.concat("0");
            else if(c == '1') res = res.concat("1");
            else if(c == '2') res = res.concat("2");
            else if(c == '3') res = res.concat("3");
            else if(c == '4') res = res.concat("4");
            else if(c == '5') res = res.concat("5");
            else if(c == '6') res = res.concat("6");
            else if(c == '7') res = res.concat("7");
            else if(c == '8') res = res.concat("8");
            else if(c == '9') res = res.concat("9");
        }
        if(res.equals("")) return "0";
        return res;
    }

    public ProgramState execute(ProgramState prg) throws MyException {
        if (!prg.getSymbolTable().exists(varName)) throw new MyException("Variable does not exist");
        Value v = prg.getSymbolTable().get(varName), vStr = exp.eval(prg.getSymbolTable(), prg.getHeap());
        if (!v.getType().equals(new IntType())) throw new MyException("Variable not int");
        if (!vStr.getType().equals(new StringType())) throw new MyException("File name must be string");
        StringValue vStr1 = (StringValue) vStr;
        if (!prg.getFileTable().exists(vStr1)) throw new MyException("File is not open for reading");
        BufferedReader reader = prg.getFileTable().get(vStr1);
        try {
            String line = reader.readLine();
            int val = Integer.parseInt(removeNonInt(line));
            prg.getSymbolTable().replace(varName, new IntValue(val));
        } catch (Exception e) {
            throw new MyException(e.getMessage());
        }
        return null;
    }

    public String toString() {
        return "ReadFile(" + exp.toString() + "," + varName + ")";
    }

    public StatementInterface deepCopy() {
        return new ReadFile(exp.deepCopy(), varName);
    }

    @Override
    public DictionaryInterface<String, Type> typecheck(DictionaryInterface<String, Type> typeEnv) throws MyException {
        Type tVal = typeEnv.get(varName), tExp = exp.typecheck(typeEnv);
        if(!tVal.equals(new IntType()) || !tExp.equals(new StringType())) throw new MyException("Invalid types in read file statement");
        return typeEnv;
    }
}
