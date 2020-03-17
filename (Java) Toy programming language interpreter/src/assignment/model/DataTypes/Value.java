package assignment.model.DataTypes;

public interface Value {
    Type getType();
    Value deepCopy();
}
