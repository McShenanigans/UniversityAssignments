package assignment.model.DataTypes;

public class BoolValue implements Value {
    private boolean val;

    public BoolValue(boolean v) {
        val = v;
    }

    public boolean getVal() {
        return val;
    }

    public String toString() {
        return Boolean.toString(val);
    }

    public Type getType() {
        return new BoolType();
    }

    public Value deepCopy() {
        return new BoolValue(val);
    }

    public boolean equals(Value v){
        if(!v.getType().equals(new BoolType()))return false;
        else return ((BoolValue) v).getVal() == val;
    }
}
