package assignment.model.DataTypes;

public class StringValue implements Value {
    private String val;

    public StringValue(String val) {
        this.val = val;
    }

    public Type getType() {
        return new StringType();
    }

    public String getVal() {
        return val;
    }

    public String toString(){
        return "\"" + val + "\"";
    }

    public Value deepCopy() {
        return new StringValue(val);
    }

    public boolean equals(Value v){
        if(!v.getType().equals(new StringType()))return false;
        else return ((StringValue) v).getVal().equals(val);
    }
}
