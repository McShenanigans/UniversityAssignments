package assignment.model.DataTypes;

public class IntType implements Type {
    public boolean equals(Object another){
        return another instanceof IntType;
    }
    public String toString(){
        return "int";
    }
    public Value defaultValue(){return new IntValue(0); }
}
