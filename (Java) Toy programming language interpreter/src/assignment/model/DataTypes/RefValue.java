package assignment.model.DataTypes;

public class RefValue implements Value {
    private int addr;
    private Type inner;

    public RefValue(int addr, Type inner) {
        this.addr = addr;
        this.inner = inner;
    }

    public int getAddr() {
        return addr;
    }

    public Type getInner() {
        return inner;
    }

    @Override
    public Type getType() {
        return new RefType(inner);
    }

    @Override
    public Value deepCopy() {
        return new RefValue(addr, inner);
    }

    public String toString() {
        return "(" + addr + "," + inner.toString() + ")";
    }
}
