package assignment.model.DataTypes;

public class RefType implements Type {
    private Type inner;

    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getType(){
        return inner;
    }

    public boolean equals(Object another){
        if(another instanceof RefType) return inner.equals(((RefType)another).inner);
        return false;
    }

    public String toString(){
        return "Ref("+inner.toString()+")";
    }

    @Override
    public Value defaultValue() {
        return new RefValue(-1,inner);
    }

    public Type getInner(){
        return inner;
    }
}
