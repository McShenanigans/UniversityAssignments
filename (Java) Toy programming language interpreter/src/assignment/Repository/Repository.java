package assignment.Repository;

import assignment.Exceptions.MyException;
import assignment.model.ADT.*;
import assignment.model.DataTypes.*;
import assignment.model.Expressions.*;
import assignment.model.ProgramState;
import assignment.model.Statements.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Repository implements RepositoryInterface {
    private ListInterface<ProgramState> repo;
    private String filePath;

    public Repository(String filePath, boolean initialize) throws MyException {
        repo = new MyList<>();
        if (!filePath.endsWith(".txt") && !filePath.contains(".")) filePath = filePath.concat(".txt");
        this.filePath = filePath;
        AtomicInteger id = new AtomicInteger(0);
        try {
            PrintWriter writer = new PrintWriter(filePath);
            writer.write("");
            writer.close();
        } catch (Exception e) {
            throw new MyException(e.getMessage());
        }
        if (initialize) {
            //example1: int v; v=2; Print(v)
            StatementInterface ex1 = new CompoundStatement(
                    new VarDeclStatement("v", new IntType()),
                    new CompoundStatement(
                            new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                            new PrintStatement(new VariableExpression("v"))
                    )
            );
            System.out.println("ex1");
            printTrace(ex1.typecheck(new MyDictionary<>()));
            ProgramState prg1 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex1, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg1);

            //example2: int a; int b; a = 2+3*5; b=a+1; Print(b)
            StatementInterface ex2 = new CompoundStatement(
                    new VarDeclStatement("a", new IntType()),
                    new CompoundStatement(
                            new VarDeclStatement("b", new IntType()),
                            new CompoundStatement(
                                    new AssignmentStatement("a", new ArithmeticExpression(
                                            new ValueExpression(new IntValue(2)),
                                            new ArithmeticExpression(
                                                    new ValueExpression(new IntValue(3)),
                                                    new ValueExpression(new IntValue(5)), 3
                                            ), 1)
                                    ),
                                    new CompoundStatement(
                                            new AssignmentStatement("b",
                                                    new ArithmeticExpression(
                                                            new VariableExpression("a"),
                                                            new ValueExpression(new IntValue(1)), 1
                                                    )
                                            ),
                                            new PrintStatement(new VariableExpression("b"))
                                    )
                            )
                    )
            );
            System.out.println("ex2");
            printTrace(ex2.typecheck(new MyDictionary<>()));
            ProgramState prg2 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex2, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg2);

            // example3: bool a; int v; a = true; if a then v=2 else v=3; Print(v)
            StatementInterface ex3 = new CompoundStatement(
                    new VarDeclStatement("a", new BoolType()),
                    new CompoundStatement(
                            new VarDeclStatement("v", new IntType()),
                            new CompoundStatement(
                                    new AssignmentStatement("a", new ValueExpression(new BoolValue(true))),
                                    new CompoundStatement(
                                            new IfStatement(
                                                    new VariableExpression("a"),
                                                    new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                                                    new AssignmentStatement("v", new ValueExpression(new IntValue(3)))
                                            ),
                                            new PrintStatement(new VariableExpression("v"))
                                    )
                            )
                    )
            );
            System.out.println("ex3");
            printTrace(ex3.typecheck(new MyDictionary<>()));
            ProgramState prg3 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex3, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg3);

            //problem 4: int v; int a; int b; a = 1; b = 2;if a < b then v = 1 else v = 2
            StatementInterface ex4 = new CompoundStatement(
                    new VarDeclStatement("v", new IntType()),
                    new CompoundStatement(
                            new VarDeclStatement("a", new IntType()),
                            new CompoundStatement(
                                    new VarDeclStatement("b", new IntType()),
                                    new CompoundStatement(
                                            new AssignmentStatement("a", new ValueExpression(new IntValue(1))),
                                            new CompoundStatement(
                                                    new AssignmentStatement("b", new ValueExpression(new IntValue(2))),
                                                    new IfStatement(
                                                            new ComparisonExpression(new VariableExpression("a"), new VariableExpression("b"), 1),
                                                            new AssignmentStatement("v", new ValueExpression(new IntValue(1))),
                                                            new AssignmentStatement("v", new ValueExpression(new IntValue(2)))
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex4");
            printTrace(ex4.typecheck(new MyDictionary<>()));
            ProgramState prg4 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex4, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg4);

            // String varf;varf="test.in";openRFile(varf);int varc;readFile(varf,varc);Print(varc);readFile(varf,varc);Print(varc);closeRFile(varf)
            StatementInterface ex5 = new CompoundStatement(
                    new VarDeclStatement("varf", new StringType()),
                    new CompoundStatement(
                            new AssignmentStatement("varf", new ValueExpression(new StringValue("test.in"))),
                            new CompoundStatement(
                                    new OpenRFile(new VariableExpression("varf")),
                                    new CompoundStatement(
                                            new VarDeclStatement("varc", new IntType()),
                                            new CompoundStatement(
                                                    new CompoundStatement(
                                                            new ReadFile(new VariableExpression("varf"), "varc"),
                                                            new PrintStatement(new VariableExpression("varc"))
                                                    ),
                                                    new CompoundStatement(
                                                            new CompoundStatement(
                                                                    new ReadFile(new VariableExpression("varf"), "varc"),
                                                                    new PrintStatement(new VariableExpression("varc"))
                                                            ),
                                                            new CloseRFile(new VariableExpression("varf"))
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex5");
            printTrace(ex5.typecheck(new MyDictionary<>()));
            ProgramState prg5 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex5, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg5);

            // example 6: int v,v=4,(while(v>0)print(v);v=v-1),print(v)
            StatementInterface ex6 = new CompoundStatement(
                    new VarDeclStatement("v", new IntType()),
                    new CompoundStatement(
                            new AssignmentStatement("v", new ValueExpression(new IntValue(4))),
                            new CompoundStatement(
                                    new WhileStatement(
                                            new ComparisonExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), 6),
                                            new CompoundStatement(
                                                    new PrintStatement(new VariableExpression("v")),
                                                    new AssignmentStatement("v", new ArithmeticExpression(new VariableExpression("v"), new ValueExpression(new IntValue(1)), 2))
                                            )
                                    ),
                                    new PrintStatement(new VariableExpression("v"))
                            )
                    )
            );
            System.out.println("ex6");
            printTrace(ex6.typecheck(new MyDictionary<>()));
            ProgramState prg6 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex6, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg6);

            // example 7: Ref int v; new(v,20); Ref Ref int a;new(a,v);print(a)
            StatementInterface ex7 = new CompoundStatement(
                    new VarDeclStatement("v", new RefType(new IntType())),
                    new CompoundStatement(
                            new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                            new CompoundStatement(
                                    new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                    new CompoundStatement(
                                            new HeapAllocStatement("a", new VariableExpression("v")),
                                            new CompoundStatement(
                                                    new VarDeclStatement("b", new RefType(new RefType(new RefType(new IntType())))),
                                                    new CompoundStatement(
                                                            new HeapAllocStatement("b", new VariableExpression("a")),
                                                            new PrintStatement(new VariableExpression("a"))
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex7");
            printTrace(ex7.typecheck(new MyDictionary<>()));
            ProgramState prg7 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex7, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg7);

            // example 8: Ref int v; new(v,20); Ref Ref int a; new(a,v); Print(rH(v)); Print(rH(rH(a)))
            StatementInterface ex8 = new CompoundStatement(
                    new VarDeclStatement("v", new RefType(new IntType())),
                    new CompoundStatement(
                            new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                            new CompoundStatement(
                                    new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                    new CompoundStatement(
                                            new HeapAllocStatement("a", new VariableExpression("v")),
                                            new CompoundStatement(
                                                    new PrintStatement(new HeapReadExpression(new VariableExpression("v"))),
                                                    new PrintStatement(new HeapReadExpression(new HeapReadExpression(new VariableExpression("a"))))
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex8");
            printTrace(ex8.typecheck(new MyDictionary<>()));
            ProgramState prg8 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex8, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg8);

            // example 9: Ref int v; new(v,20); print(rH(v)); wH(v,30); print(rH(v))
            StatementInterface ex9 = new CompoundStatement(
                    new VarDeclStatement("v", new RefType(new IntType())),
                    new CompoundStatement(
                            new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                            new CompoundStatement(
                                    new PrintStatement(new HeapReadExpression(new VariableExpression("v"))),
                                    new CompoundStatement(
                                            new HeapWriteStatement("v", new ValueExpression(new IntValue(30))),
                                            new PrintStatement(new HeapReadExpression(new VariableExpression("v")))
                                    )
                            )
                    )
            );
            System.out.println("ex9");
            printTrace(ex9.typecheck(new MyDictionary<>()));
            ProgramState prg9 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex9, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg9);

            //example 10: Ref int v; new(v,20); Ref Ref int a; new (a,v); new(v,30); print(rH(rH(a)))
            StatementInterface ex10 = new CompoundStatement(
                    new VarDeclStatement("v", new RefType(new IntType())),
                    new CompoundStatement(
                            new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                            new CompoundStatement(
                                    new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                    new CompoundStatement(
                                            new HeapAllocStatement("a", new VariableExpression("v")),
                                            new CompoundStatement(
                                                    new HeapAllocStatement("v", new ValueExpression(new IntValue(30))),
                                                    new PrintStatement(
                                                            new HeapReadExpression(new HeapReadExpression(new VariableExpression("a")))
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex10");
            printTrace(ex10.typecheck(new MyDictionary<>()));
            ProgramState prg10 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex10, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg10);

            //example 11: Ref int v; new(v,20); Ref Ref int a; new (a,v); new(v,30);new(a,v); print(rH(rH(a)))
            StatementInterface ex11 = new CompoundStatement(
                    new VarDeclStatement("v", new RefType(new IntType())),
                    new CompoundStatement(
                            new HeapAllocStatement("v", new ValueExpression(new IntValue(20))),
                            new CompoundStatement(
                                    new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                                    new CompoundStatement(
                                            new HeapAllocStatement("a", new VariableExpression("v")),
                                            new CompoundStatement(
                                                    new HeapAllocStatement("v", new ValueExpression(new IntValue(30))),
                                                    new CompoundStatement(
                                                            new HeapAllocStatement("a", new VariableExpression("v")),
                                                            new PrintStatement(
                                                                    new HeapReadExpression(new HeapReadExpression(new VariableExpression("a")))
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex11");
            printTrace(ex11.typecheck(new MyDictionary<>()));
            ProgramState prg11 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex11, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg11);

            StatementInterface ex12 = new CompoundStatement(
                    new VarDeclStatement("v", new IntType()),
                    new CompoundStatement(
                            new VarDeclStatement("a", new RefType(new IntType())),
                            new CompoundStatement(
                                    new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                    new CompoundStatement(
                                            new HeapAllocStatement("a", new ValueExpression(new IntValue(22))),
                                            new CompoundStatement(
                                                    new ForkStatement(new CompoundStatement(
                                                            new HeapWriteStatement("a", new ValueExpression(new IntValue(30))),
                                                            new CompoundStatement(
                                                                    new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                                                    new CompoundStatement(
                                                                            new PrintStatement(new VariableExpression("v")),
                                                                            new PrintStatement(new HeapReadExpression(new VariableExpression("a")))
                                                                    )
                                                            )
                                                    )),
                                                    new CompoundStatement(
                                                            new PrintStatement(new VariableExpression("v")),
                                                            new PrintStatement(new HeapReadExpression(new VariableExpression("a")))
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex12");
            printTrace(ex12.typecheck(new MyDictionary<>()));
            ProgramState prg12 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex12, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg12);

            StatementInterface ex13 = new CompoundStatement(
                    new VarDeclStatement("v", new IntType()),
                    new CompoundStatement(
                            new VarDeclStatement("a", new RefType(new IntType())),
                            new CompoundStatement(
                                    new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                                        new CompoundStatement(
                                                new ForkStatement(
                                                        new HeapAllocStatement("a", new ValueExpression(new IntValue(20)))
                                                ),
                                                new HeapAllocStatement("a", new ValueExpression(new IntValue(17)))
                                        )
                            )
                    )
            );
            System.out.println("ex13");
            printTrace(ex13.typecheck(new MyDictionary<>()));
            ProgramState prg13 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex13, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg13);

            StatementInterface ex14 = new CompoundStatement(
                    new VarDeclStatement("a", new IntType()),
                    new CompoundStatement(
                            new VarDeclStatement("b", new IntType()),
                            new CompoundStatement(
                                    new VarDeclStatement("c", new IntType()),
                                    new CompoundStatement(
                                            new AssignmentStatement("a", new ValueExpression(new IntValue(1))),
                                            new CompoundStatement(
                                                    new AssignmentStatement("b", new ValueExpression(new IntValue(2))),
                                                    new CompoundStatement(
                                                            new AssignmentStatement("c", new ValueExpression(new IntValue(5))),
                                                            new CompoundStatement(
                                                                    new SwitchStatement(
                                                                            new ArithmeticExpression(new VariableExpression("a"), new ValueExpression(new IntValue(10)), 3),
                                                                            new ArithmeticExpression(new VariableExpression("b"), new VariableExpression("c"), 3),
                                                                            new ValueExpression(new IntValue(10)),
                                                                            new CompoundStatement(
                                                                                    new PrintStatement(new VariableExpression("a")),
                                                                                    new PrintStatement(new VariableExpression("b"))
                                                                            ),
                                                                            new CompoundStatement(
                                                                                    new PrintStatement(new ValueExpression(new IntValue(100))),
                                                                                    new PrintStatement(new ValueExpression(new IntValue(200)))
                                                                            ),
                                                                            new PrintStatement(new ValueExpression(new IntValue(300)))
                                                                    ),
                                                                    new PrintStatement(new ValueExpression(new IntValue(300)))
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex14");
            printTrace(ex14.typecheck(new MyDictionary<>()));
            ProgramState prg14 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex14, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg14);

            StatementInterface ex15 = new CompoundStatement(
                    new VarDeclStatement("v1", new RefType(new IntType())),
                    new CompoundStatement(
                            new VarDeclStatement("cnt", new IntType()),
                            new CompoundStatement(
                                    new HeapAllocStatement("v1", new ValueExpression(new IntValue(1))),
                                    new CompoundStatement(
                                            new SemaphoreStatement(new VariableExpression("cnt"), new HeapReadExpression(new VariableExpression("v1"))),
                                            new CompoundStatement(
                                                    new ForkStatement(
                                                            new CompoundStatement(
                                                                    new AcquireStatement(new VariableExpression("cnt")),
                                                                    new CompoundStatement(
                                                                            new HeapWriteStatement("v1", new ArithmeticExpression(new HeapReadExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)), 3)),
                                                                            new CompoundStatement(
                                                                                    new PrintStatement(new HeapReadExpression(new VariableExpression("v1"))),
                                                                                    new ReleaseStatement(new VariableExpression("cnt"))
                                                                            )
                                                                    )
                                                            )
                                                    ),
                                                    new CompoundStatement(
                                                            new ForkStatement(
                                                                    new CompoundStatement(
                                                                            new AcquireStatement(new VariableExpression("cnt")),
                                                                            new CompoundStatement(
                                                                                    new HeapWriteStatement("v1", new ArithmeticExpression(new HeapReadExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)), 3)),
                                                                                    new CompoundStatement(
                                                                                            new HeapWriteStatement("v1", new ArithmeticExpression(new HeapReadExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(2)), 3)),
                                                                                            new CompoundStatement(
                                                                                                new PrintStatement(new HeapReadExpression(new VariableExpression("v1"))),
                                                                                                new ReleaseStatement(new VariableExpression("cnt"))
                                                                                            )
                                                                                    )
                                                                            )
                                                                    )
                                                            ),
                                                            new CompoundStatement(
                                                                    new AcquireStatement(new VariableExpression("cnt")),
                                                                    new CompoundStatement(
                                                                            new PrintStatement(new ArithmeticExpression(new HeapReadExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(1)), 2)),
                                                                            new ReleaseStatement(new VariableExpression("cnt"))
                                                                    )
                                                            )

                                                    )

                                            )
                                    )
                            )
                    )
            );
            System.out.println("ex15");
            printTrace(ex15.typecheck(new MyDictionary<>()));
            ProgramState prg15 = new ProgramState(id, new MyStack<>(), new MyDictionary<>(), new MyList<>(), ex15, new MyDictionary<>(), new MyHeap<>(0), new MySemaphore<>());
            repo.push(prg15);
        }
    }

    private void printTrace(DictionaryInterface<String, Type> trace) throws MyException {
        for(String key : trace.getKeys())
            System.out.println(key + " -> " + trace.get(key).toString());
    }

    public ProgramState getProgram(int index) throws MyException {
        if (index >= repo.size() || index < 0) throw new MyException("Invalid index");
        return repo.get(index).deepCopy();
    }

    public String getPrgStr(int index) throws MyException {
        return repo.get(index).toString();
    }

    @Override
    public List<ProgramState> getPrograms() {
        return repo.getList();
    }

    @Override
    public void setPrograms(List<ProgramState> newList) {
        repo.setList(newList);
    }

    public int size() {
        return repo.size();
    }

    public void saveToFile(ProgramState prg) throws MyException {
        ProgramState prgCopy = prg.deepCopy();

        MyList<String> exeStackStr = new MyList<>();
        StackInterface<StatementInterface> exeS = prgCopy.getExeStack();
        while (!exeS.isEmpty()) {
            StatementInterface st = exeS.pop();
            if (st instanceof CompoundStatement) st.execute(prgCopy);
            else exeStackStr.push(st.toString());
        }

        DictionaryInterface<String, Value> symT = prgCopy.getSymbolTable();
        MyList<String> symTableStr = new MyList<>();
        for (String key : symT.getKeys())
            symTableStr.push(key + " --> " + symT.get(key).toString());

        ListInterface<Value> outL = prgCopy.getOutputList();
        MyList<String> outputList = new MyList<>();
        for (int i = 0; i < outL.size(); i++)
            outputList.push(outL.get(i).toString());

        DictionaryInterface<StringValue, BufferedReader> fileTableCopy = prg.getFileTable();
        ListInterface<String> fileTableStr = new MyList<>();
        for (StringValue str : fileTableCopy.getKeys())
            fileTableStr.push(str.toString());

        HeapInterface<Integer, Value> heapCopy = prg.getHeap();
        ListInterface<String> heapString = new MyList<>();
        for (int key : heapCopy.getKeys())
            if (heapCopy.get(key) != null) heapString.push(key + " -> " + heapCopy.get(key).toString());

        try (PrintWriter writer = new PrintWriter(new BufferedWriter(new FileWriter(filePath, true)))) {
            writer.println("Program id: " + prg.getId());
            writer.println("Execution Stack");
            for (int i = 0; i < exeStackStr.size(); i++)
                writer.println(exeStackStr.get(i));
            writer.println("Symbol Table");
            for (int i = 0; i < symTableStr.size(); i++)
                writer.println(symTableStr.get(i));
            writer.println("Output list");
            for (int i = 0; i < outputList.size(); i++)
                writer.println(outputList.get(i));
            writer.println("File Table");
            for (int i = 0; i < fileTableStr.size(); i++)
                writer.println(fileTableStr.get(i));
            writer.println("Heap");
            for (int i = 0; i < heapString.size(); i++)
                writer.println(heapString.get(i));
            writer.println();
        } catch (Exception e) {
            throw new MyException(e.getMessage());
        }
    }

}
