package assignment.model.DataTypes;

public class IntValue implements Value {
    private int val;

    public IntValue(int v) {
        val = v;
    }

    public int getVal() {
        return val;
    }

    public String toString() {
        return Integer.toString(val);
    }

    public Type getType() {
        return new IntType();
    }

    public Value deepCopy() {
        return new IntValue(val);
    }

    public boolean equals(Value v){
        if(!v.getType().equals(new IntType()))return false;
        else return ((IntValue) v).getVal() == val;
    }
}
