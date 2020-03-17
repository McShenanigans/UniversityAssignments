package assignment.GUIControllers;

import assignment.Controller.Controller;
import assignment.Exceptions.MyException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;
import java.io.IOException;

public class ProgSelectController extends GuiController {

    public Button runBtn;
    public TextField idTF;
    public ListView<String> programList;
    public Label errLabel;
    private Controller c;

    @FXML
    public void initialize() {
        program = 0;
        try {
            c = new Controller("log");
        } catch (MyException e) {
            errLabel.setText(e.whatHappened());
        }
        programList.setItems(getProgramsList());
        programList.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        programList.getSelectionModel().selectIndices(0);
        programList.getFocusModel().focus(0);

        programList.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            program = 0;
            idTF.setText(newValue.split(". ")[0].trim());
        });
    }

    private ObservableList<String> getProgramsList() {
        String str = "";
        try {
            str = c.getProgramStr(0);
        } catch (MyException e) {
            errLabel.setText("could not get programs from controller");
        }
        ObservableList<String> programs = FXCollections.observableArrayList(str);
        for (int i = 1; i < c.nrOfPrograms(); i++) {
            try {
                programs.add(c.getProgramStr(i));
            } catch (MyException e) {
                errLabel.setText("could not get programs from controller");
            }
        }
        return programs;
    }

    public void runBtnPressed(ActionEvent actionEvent) throws IOException {
        if (actionEvent.getSource() == runBtn) {
            try{
                program = Integer.parseInt(idTF.getText());
                Stage progRunner;
                Parent root;
                progRunner = (Stage) runBtn.getScene().getWindow();
                root = FXMLLoader.load(getClass().getResource("progWindow.fxml"));
                Scene scene = new Scene(root);
                progRunner.setScene(scene);
                progRunner.setTitle("Program execution");
                progRunner.show();
            } catch (Exception e) {
                errLabel.setText(e.getMessage());
                e.printStackTrace();
            }
        } else {
            errLabel.setText("something went wrong");
        }
    }
}
