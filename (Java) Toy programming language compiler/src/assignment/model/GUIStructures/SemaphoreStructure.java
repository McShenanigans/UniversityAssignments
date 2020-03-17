package assignment.model.GUIStructures;

import javafx.beans.property.SimpleStringProperty;

public class SemaphoreStructure {
    private final SimpleStringProperty index = new SimpleStringProperty("");
    private final SimpleStringProperty value = new SimpleStringProperty("");
    private final SimpleStringProperty list = new SimpleStringProperty("");

    public SemaphoreStructure() {
        this("", "", "");
    }

    public SemaphoreStructure(String index, String value, String list) {
        setIndex(index);
        setValue(value);
        setList(list);
    }

    public void setIndex(String newIndex) {
        index.set(newIndex);
    }

    public void setValue(String newValue) {
        value.set(newValue);
    }

    public void setList(String newList) {
        list.set(newList);
    }

    public String getIndex(){
        return index.get();
    }

    public String getValue(){
        return value.get();
    }

    public String getList(){
        return list.get();
    }
}
