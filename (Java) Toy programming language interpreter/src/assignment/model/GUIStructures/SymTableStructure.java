package assignment.model.GUIStructures;
import javafx.beans.property.SimpleStringProperty;

public class SymTableStructure {
    private final SimpleStringProperty name = new SimpleStringProperty("");
    private final SimpleStringProperty value = new SimpleStringProperty("");

    public SymTableStructure(){this("", "");}

    public SymTableStructure(String vName, String vValue){
        setName(vName);
        setValue(vValue);
    }

    public void setName(String vName){
        name.set(vName);
    }

    public void setValue(String vValue){
        value.set(vValue);
    }

    public String getName(){
        return name.get();
    }

    public String getValue(){
        return value.get();
    }
}
