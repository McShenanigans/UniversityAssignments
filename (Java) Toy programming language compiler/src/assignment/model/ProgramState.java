package assignment.model;

import assignment.Exceptions.MyException;
import assignment.model.ADT.*;
import assignment.model.DataTypes.StringValue;
import assignment.model.DataTypes.Value;
import assignment.model.Statements.NopStatement;
import assignment.model.Statements.StatementInterface;

import java.io.BufferedReader;
import java.util.concurrent.atomic.AtomicInteger;

public class ProgramState {
    private DictionaryInterface<String, Value> symbolTable;
    private DictionaryInterface<StringValue, BufferedReader> fileTable;
    private StackInterface<StatementInterface> executionStack;
    private ListInterface<Value> outputList;
    private HeapInterface<Integer, Value> heap;
    private SemaphoreInterface<Integer, PairInterface<Integer>> semaphoreTable;
    private int id;
    private AtomicInteger idGenerator;

    public ProgramState(AtomicInteger idGenerator, StackInterface<StatementInterface> exeS, DictionaryInterface<String, Value> symT, ListInterface<Value> outL, StatementInterface prg, DictionaryInterface<StringValue, BufferedReader> fileT, HeapInterface<Integer, Value> heap, SemaphoreInterface<Integer, PairInterface<Integer>> semaphoreT) {
        symbolTable = symT;
        this.heap = heap;
        fileTable = fileT;
        executionStack = exeS;
        outputList = outL;
        semaphoreTable = semaphoreT;
        this.id = idGenerator.getAndIncrement();
        this.idGenerator = idGenerator;
        if (executionStack.isEmpty())
            exeS.push(prg);
    }

    public AtomicInteger getIdGenerator(){
        return idGenerator;
    }

    public int getId() {
        return id;
    }

    public ListInterface<Value> getOutputList() {
        return outputList;
    }

    public StackInterface<StatementInterface> getExeStack() {
        return executionStack;
    }

    public DictionaryInterface<String, Value> getSymbolTable() {
        return symbolTable;
    }

    public DictionaryInterface<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public SemaphoreInterface<Integer, PairInterface<Integer>> getSemaphoreTable(){
        return semaphoreTable;
    }

    public HeapInterface<Integer, Value> getHeap() {
        return heap;
    }

    public ProgramState deepCopy() throws MyException {
        DictionaryInterface<String, Value> dictCopy = new MyDictionary<>();
        DictionaryInterface<StringValue, BufferedReader> fileTableCopy = new MyDictionary<>();
        StackInterface<StatementInterface> stackCopy = new MyStack<>(), swapStack = new MyStack<>();
        ListInterface<Value> listCopy = new MyList<>();
        HeapInterface<Integer, Value> heapCopy = new MyHeap<>(0);
        SemaphoreInterface<Integer, PairInterface<Integer>> semaCopy = new MySemaphore<>();

        while (!executionStack.isEmpty())
            swapStack.push(executionStack.pop());
        while (!swapStack.isEmpty()) {
            StatementInterface st = swapStack.pop();
            executionStack.push(st);
            stackCopy.push(st);
        }

        for (int i = 0; i < outputList.size(); i++)
            listCopy.push(outputList.get(i));

        for (String key : symbolTable.getKeys())
            dictCopy.put(key, symbolTable.get(key));

        StatementInterface st;
        if (executionStack.isEmpty()) st = new NopStatement();
        else st = executionStack.peek();

        for (StringValue key : fileTable.getKeys())
            fileTableCopy.put(key, fileTable.get(key));

        for (Integer key : heap.getKeys()) {
            if (key.equals(0)) continue;
            heapCopy.put(key, heap.get(key));
        }

        for(Integer key : semaphoreTable.getKeys())
            semaCopy.put(key, semaphoreTable.get(key));

        return new ProgramState(idGenerator, stackCopy, dictCopy, listCopy, st, fileTableCopy, heapCopy, semaCopy);
    }

    public String toString() {
        return id + ". " + executionStack.toString();
    }

    public boolean isDone() {
        return executionStack.isEmpty();
    }

    public ProgramState nextStep() throws MyException {
        if (executionStack.isEmpty()) throw new MyException("Empty execution stack");
        return executionStack.pop().execute(this);
    }
}
