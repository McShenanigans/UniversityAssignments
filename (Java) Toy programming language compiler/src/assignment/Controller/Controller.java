package assignment.Controller;

import assignment.Exceptions.MyException;
import assignment.Repository.Repository;
import assignment.Repository.RepositoryInterface;
import assignment.model.ADT.*;
import assignment.model.DataTypes.StringValue;
import assignment.model.DataTypes.Value;
import assignment.model.ProgramState;
import assignment.model.Statements.CompoundStatement;
import assignment.model.Statements.StatementInterface;

import java.io.BufferedReader;
import java.util.List;
import java.util.Objects;
import java.util.Vector;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    private RepositoryInterface repo;
    private ProgramState prg;
    private int prgToShow;
    private boolean displayFlag;
    private GarbageCollector gc;
    private ExecutorService executor;
    private RepositoryInterface runningRepo;

    public Controller(String filePath) throws MyException {
        repo = new Repository(filePath, true);
        runningRepo = new Repository(filePath, false);
        displayFlag = false;
        prg = repo.getProgram(0);
        prgToShow = 0;
        Vector<ProgramState> prgList = new Vector<>();
        prgList.add(prg);
        runningRepo.setPrograms(prgList);
        gc = new GarbageCollector();
    }

    public ListInterface<String> getRunningRepoString() throws MyException {
        ListInterface<String> list = new MyList<>();
        System.out.println(runningRepo.size());
        for (int i = 0; i < runningRepo.size(); i++)
            list.push(runningRepo.getPrgStr(i));
        return list;
    }

    public void setProgram(int index) throws MyException {
        prg = repo.getProgram(index);
        Vector<ProgramState> prgList = new Vector<>();
        prgList.add(prg);
        runningRepo.setPrograms(prgList);
    }

    private List<DictionaryInterface<String, Value>> getSymTables() {
        Vector<DictionaryInterface<String, Value>> symTables = new Vector<>();
        for (ProgramState prog : runningRepo.getPrograms()) {
            symTables.add(prog.getSymbolTable());
        }
        return symTables;
    }

    private void nextStep(ProgramState prg) throws MyException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> prgList = removeCompletedPrograms(runningRepo.getPrograms());
        oneStep4AllProg(prgList);
        prgList = removeCompletedPrograms(prgList);
        prg.getHeap().setContent(gc.getGarbage_threaded(getSymTables(), prg.getHeap()));
        prg.getHeap().put(0, null);
        executor.shutdownNow();
        runningRepo.setPrograms(prgList);
    }

    public void advance(ProgramState prg) throws MyException, InterruptedException {
        if (displayFlag) displayProgramState(prg);
        nextStep(prg);
    }

    public void setPrgToShow(int index) throws MyException {
        try {
            prgToShow = index;
            System.out.println(runningRepo.getProgram(index));
        } catch (MyException e) {
            prgToShow = 0;
            throw new MyException(e.whatHappened());
        }
    }

    public void allStep() throws InterruptedException, MyException {
        executor = Executors.newFixedThreadPool(2);
        List<ProgramState> prgList = removeCompletedPrograms(runningRepo.getPrograms());
        while (prgList.size() > 0) {
            oneStep4AllProg(prgList);
            prgList = removeCompletedPrograms(prgList);
            prg.getHeap().setContent(gc.getGarbage_threaded(getSymTables(), prg.getHeap()));
            prg.getHeap().put(0, null);
        }
        executor.shutdownNow();
        runningRepo.setPrograms(prgList);
    }

    public void oneStep4AllProg(List<ProgramState> prgList) throws InterruptedException, MyException {
        prgList.forEach(p -> {
            try {
                runningRepo.saveToFile(p);
                if (displayFlag) displayProgramState(p);
            } catch (MyException e) {
                System.out.println(e.getMessage());
            }
        });
        List<Callable<ProgramState>> callList = prgList.stream().map((ProgramState p) -> (Callable<ProgramState>) (p::nextStep)).collect(Collectors.toList());
        List<ProgramState> newPrograms = executor.invokeAll(callList).stream().map(future -> {
            try {
                return future.get();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            return null;
        }).filter(Objects::nonNull).collect(Collectors.toList());
        prgList.addAll(newPrograms);
        runningRepo.setPrograms(prgList);
        prgList.forEach(p -> {
            try {
                runningRepo.saveToFile(p);
                if (displayFlag) displayProgramState(p);
            } catch (MyException e) {
                System.out.println(e.getMessage());
            }
        });
        //repo.saveToFile(prg);
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> programs) {
        return programs.stream().filter(p -> !p.isDone()).collect(Collectors.toList());
    }

    private void displayProgramState(ProgramState prg) {
        System.out.println("\nProgram id: " + prg.getId());
        System.out.println("ExecutionStack: " + prg.getExeStack().toString());
        System.out.println("SymbolTable: " + prg.getSymbolTable().toString());
        System.out.println("OutputList: " + prg.getOutputList().toString());
        System.out.println("FileTable: " + prg.getFileTable().toString());
        System.out.println("Heap: " + prg.getHeap().toString() + "\n");
    }

    public ListInterface<String> getPrgExeStackString() throws MyException {
        ProgramState prgCopy;
        try {
            prgCopy = runningRepo.getProgram(prgToShow).deepCopy();
        } catch (MyException e){
            prgCopy = prg.deepCopy();
        }

        MyList<String> exeStackStr = new MyList<>();
        StackInterface<StatementInterface> exeS = prgCopy.getExeStack();
        while (!exeS.isEmpty()) {
            StatementInterface st = exeS.pop();
            if (st instanceof CompoundStatement) st.execute(prgCopy);
            else exeStackStr.push(st.toString());
        }

        return exeStackStr;
    }

    public HeapInterface<Integer, Value> getPrgHeap() throws MyException {
        return prg.deepCopy().getHeap();
    }

    public SemaphoreInterface<Integer, PairInterface<Integer>> getPrgSemaphoreTable() {
        return prg.getSemaphoreTable();
    }

    public ListInterface<String> getPrgFilesTableString() throws MyException {
        ProgramState prgCopy = prg.deepCopy();

        DictionaryInterface<StringValue, BufferedReader> fileTableCopy = prgCopy.getFileTable();
        ListInterface<String> fileTableStr = new MyList<>();
        for (StringValue str : fileTableCopy.getKeys())
            fileTableStr.push(str.toString());

        return fileTableStr;
    }

    public DictionaryInterface<String, Value> getPrgSymbolTable() throws MyException {
        ProgramState prgCopy;
        try{
            prgCopy = runningRepo.getProgram(prgToShow).deepCopy();
        } catch (MyException e){
            prgCopy = prg.deepCopy();
        }
        return prgCopy.deepCopy().getSymbolTable();
    }

    public ListInterface<String> getPrgOutputListString() throws MyException {
        ProgramState prgCopy = prg.deepCopy();

        ListInterface<Value> outL = prgCopy.getOutputList();
        MyList<String> outputList = new MyList<>();
        for (int i = 0; i < outL.size(); i++)
            outputList.push(outL.get(i).toString());

        return outputList;
    }

    public String getNumOfThreads() {
        return Integer.toString(runningRepo.size());
    }

    public ProgramState getCurrentPrg() {
        return prg;
    }

    public int nrOfPrograms() {
        return repo.size();
    }

    public String getProgramStr(int index) throws MyException {
        return repo.getPrgStr(index);
    }

    public String toString() {
        return prg.toString();
    }
}
