package assignment.GUIControllers;

import assignment.Controller.Controller;
import assignment.Exceptions.MyException;
import assignment.model.ADT.*;
import assignment.model.DataTypes.Value;
import assignment.model.GUIStructures.HeapStructure;
import assignment.model.GUIStructures.SemaphoreStructure;
import assignment.model.GUIStructures.SymTableStructure;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import java.io.IOException;

public class ProgRunController extends GuiController {
    public TextField statesNumTF;
    public ListView<String> statesLV;
    public TableView<HeapStructure> heapTV;
    public TableView<SymTableStructure> symTableTV;
    public ListView<String> outLV;
    public ListView<String> filesLV;
    public ListView<String> exeStackLV;
    public Button nextBtn;
    public Button skipBtn;
    public Button changeProgBtn;
    public Label errLabel;
    public TableColumn<HeapStructure, String> addressCol;
    public TableColumn<HeapStructure, String> valueCol;
    public TableColumn<SymTableStructure, String> symNameCol;
    public TableColumn<SymTableStructure, String> symValueCol;
    public TableColumn<SemaphoreStructure, String> listCol;
    public TableColumn<SemaphoreStructure, String> sValueCol;
    public TableColumn<SemaphoreStructure, String> indexCol;
    public TableView<SemaphoreStructure> semaphoreTV;
    private Controller c;
    private int lastSelectedIndex, lastMaxThreadsNr;

    public ProgRunController() throws MyException {
        c = new Controller("abc");
        lastSelectedIndex = -1;
        lastMaxThreadsNr = 0;
        c.setProgram(program);
    }

    @FXML
    public void initialize() {
        statesNumTF.setText(c.getNumOfThreads());
        addressCol.setCellValueFactory(new PropertyValueFactory<>("address"));
        valueCol.setCellValueFactory(new PropertyValueFactory<>("value"));
        symNameCol.setCellValueFactory(new PropertyValueFactory<>("name"));
        symValueCol.setCellValueFactory(new PropertyValueFactory<>("value"));
        listCol.setCellValueFactory(new PropertyValueFactory<>("list"));
        sValueCol.setCellValueFactory(new PropertyValueFactory<>("value"));
        indexCol.setCellValueFactory(new PropertyValueFactory<>("index"));

        statesLV.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        statesLV.getSelectionModel().selectIndices(0);
        statesLV.getFocusModel().focus(0);

        statesLV.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
                    try {
                        if (statesLV.getSelectionModel().getSelectedIndex() >= 0) {
                            c.setPrgToShow(statesLV.getSelectionModel().getSelectedIndex());
                            lastSelectedIndex = statesLV.getSelectionModel().getSelectedIndex();
                        }
                        updateComponents();
                    } catch (MyException e) {
                        errLabel.setText(e.whatHappened());
                        e.printStackTrace();
                    }
                }
        );

        updateComponents();
    }

    private void updateComponents() {
        try {
            exeStackLV.setItems(getDataForStructure("exeStack"));
            outLV.setItems(getDataForStructure("outputList"));
            filesLV.setItems(getDataForStructure("files"));
            heapTV.setItems(getHeapData());
            symTableTV.setItems(getSymTableData());
            statesNumTF.setText(c.getNumOfThreads());
            statesLV.setItems(getDataForStructure("threads"));
            semaphoreTV.setItems(getSemaphoreData());

            if (lastMaxThreadsNr > statesLV.getItems().size()) {
                lastSelectedIndex = lastSelectedIndex - (lastMaxThreadsNr - statesLV.getItems().size());
                lastMaxThreadsNr = statesLV.getItems().size();
                c.setPrgToShow(lastSelectedIndex);
            }

        } catch (MyException e) {
            e.printStackTrace();
        }
    }

    private ObservableList<SemaphoreStructure> getSemaphoreData() throws MyException {
        SemaphoreInterface<Integer, PairInterface<Integer>> data = c.getPrgSemaphoreTable();
        ObservableList<SemaphoreStructure> list = FXCollections.observableArrayList();
        for (Integer key : data.getKeys()) {
            PairInterface<Integer> obj = data.get(key);
            list.add(new SemaphoreStructure(key.toString(), Integer.toString(obj.getFirst()), obj.getSecond().toString()));
        }
        return list;
    }

    private ObservableList<HeapStructure> getHeapData() throws MyException {
        HeapInterface<Integer, Value> data = c.getPrgHeap();
        ObservableList<HeapStructure> list = FXCollections.observableArrayList();
        for (Integer key : data.getKeys())
            if (data.get(key) != null) list.add(new HeapStructure(Integer.toString(key), data.get(key).toString()));
        return list;
    }

    private ObservableList<SymTableStructure> getSymTableData() throws MyException {
        DictionaryInterface<String, Value> data = c.getPrgSymbolTable();
        ObservableList<SymTableStructure> list = FXCollections.observableArrayList();
        for (String key : data.getKeys())
            list.add(new SymTableStructure(key, data.get(key).toString()));
        return list;
    }

    private ObservableList<String> getDataForStructure(String structure) throws MyException {
        ListInterface<String> data;
        if (structure.equals("exeStack")) data = c.getPrgExeStackString();
        else if (structure.equals("outputList")) data = c.getPrgOutputListString();
        else if (structure.equals("threads")) data = c.getRunningRepoString();
        else if (!structure.equals("files")) throw new MyException("invalid data structure request");
        else data = c.getPrgFilesTableString();
        ObservableList<String> programs = FXCollections.observableArrayList();
        for (int i = 0; i < data.size(); i++) {
            programs.add(data.get(i));
        }
        return programs;
    }

    public void changeProg(ActionEvent actionEvent) throws IOException {
        if (actionEvent.getSource() == changeProgBtn) {
            Stage progRunner;
            Parent root;
            progRunner = (Stage) changeProgBtn.getScene().getWindow();
            root = FXMLLoader.load(getClass().getResource("progSelectWindow.fxml"));
            Scene scene = new Scene(root);
            progRunner.setScene(scene);
            progRunner.setTitle("Program selection");
            progRunner.show();
        } else {
            errLabel.setText("something went wrong");
        }
    }

    public void nextBtnPressed() {
        try {
            c.advance(c.getCurrentPrg());
            updateComponents();
        } catch (MyException e) {
            errLabel.setText(e.whatHappened());
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void skipBtnPressed() {
        try {
            c.allStep();
            updateComponents();
        } catch (MyException e) {
            errLabel.setText(e.whatHappened());
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
