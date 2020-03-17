package assignment.Exceptions;

public class MyException extends Exception{
    private String err;
    public MyException(String Err) {
        err = Err;
        System.out.println(Err);
    }
    public String whatHappened() {
        return err;
    }
}
