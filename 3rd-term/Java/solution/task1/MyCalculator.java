package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.Calculator;
import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.Stack;
import java.util.StringTokenizer;

public class MyCalculator implements Calculator {
    private static final String CORRECTSYMBOLS = "01234567890.+-*/()";

    private static String makeUnOperations(String inputStr) throws ParsingException {
        StringBuilder result = new StringBuilder("(");
        for (int i = 1; i < inputStr.length(); ++i) {
            char current = inputStr.charAt(i);
            char previous = inputStr.charAt(i - 1);
            if (CORRECTSYMBOLS.indexOf(current) == -1) {
                throw new ParsingException("Incorrect symbol");
            }
            if (current == '-' && previous != ')' && !Character.isDigit(previous)) {
                current = '_';
            }
            if (current == ')' && previous == '(') {
                throw new ParsingException("Empty brackets");
            }
            result.append(current);
        }
        return result.toString();
    }

    private boolean stringIsValide(String inputString) {
        boolean expect = false;
        boolean valid = true;
        for (int i = 0; i < inputString.length(); ++i) {
            if (expect && Character.isDigit(inputString.charAt(i))) {
                valid = false;
            }
            if (expect && !(Character.isDigit(inputString.charAt(i))
                    | Character.isSpaceChar(inputString.charAt(i)))) {
                expect = false;
            }
            if ((Character.isDigit(inputString.charAt(i)) | inputString.charAt(i) == '.')
                    && i != inputString.length() - 1 && Character.isSpaceChar(inputString.charAt(i + 1))) {
                expect = true;
            }
        }
        return valid;
    }

    public double calculate(String inputStr) throws ParsingException {
        if (inputStr == null) {
            throw new ParsingException("Null expression");
        }
        if (!stringIsValide(inputStr)) {
            throw new ParsingException("Not valide string");
        }
        StringBuilder builder =  new StringBuilder("(" + inputStr.replaceAll("\\s", "") + ")");
        builder = new StringBuilder(makeUnOperations(builder.toString()));
        StringTokenizer tokenizer = new StringTokenizer(builder.toString(), "+-*/()_", true);
        Stack<Number> results = new Stack<Number>();
        Stack<Operation> operations = new Stack<Operation>();
        MyOperationFactory operationFactory = new MyOperationFactory();
        while (tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();
            Operation symbol = operationFactory.getOperationInstance(token);
            symbol.addOperation(results, operations);
        }
        if (!operations.isEmpty()) {
            throw new ParsingException("Bracket balance");
        }
        if (results.isEmpty()) {
            throw new ParsingException("No numbers");
        }
        if (results.size() > 1) {
            throw new ParsingException("Not enough operators");
        }
        return results.peek().getValue();
    }
}