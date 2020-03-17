package assignment.model.GUIStructures;

import javafx.beans.property.SimpleStringProperty;

public class HeapStructure {
    private final SimpleStringProperty address = new SimpleStringProperty("");
    private final SimpleStringProperty value = new SimpleStringProperty("");

    public HeapStructure() {
        this("", "");
    }

    public HeapStructure(String vAddress, String vValue) {
        setAddress(vAddress);
        setValue(vValue);
    }

    public void setAddress(String vAddress) {
        address.set(vAddress);
    }

    public void setValue(String vValue) {
        value.set(vValue);
    }

    public String getAddress() {
        return address.get();
    }

    public String getValue() {
        return value.get();
    }
}
