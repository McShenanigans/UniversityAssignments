package assignment.model.DataTypes;

public class StringType implements Type {
    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    public Value defaultValue() {
        return new StringValue("");
    }

    public String toString() {
        return "String";
    }
}
