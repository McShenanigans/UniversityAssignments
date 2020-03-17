package assignment.Repository;
import assignment.Exceptions.MyException;
import assignment.model.ProgramState;

import java.util.List;

public interface RepositoryInterface {
    ProgramState getProgram(int index) throws MyException;
    int size();
    void saveToFile(ProgramState prg) throws MyException;
    String getPrgStr(int index) throws MyException;
    List<ProgramState> getPrograms();
    void setPrograms(List<ProgramState> newList);
}
