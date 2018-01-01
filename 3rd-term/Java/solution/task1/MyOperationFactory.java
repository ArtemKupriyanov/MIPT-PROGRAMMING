package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

public class MyOperationFactory {
    public static Operation getOperationInstance(String probablyOperation) throws ParsingException {
        if (probablyOperation.length() < 1) {
            throw new ParsingException("Empty string");
        }
        if (probablyOperation.charAt(0) == '+') {
            return new FirstPriorityOperations('+');
        } else if (probablyOperation.charAt(0) == '-') {
            return new FirstPriorityOperations('-');
        } else if (probablyOperation.charAt(0) == '*') {
            return new SecondPriorityOperations('*');
        }  else if (probablyOperation.charAt(0) == '/') {
            return new SecondPriorityOperations('/');
        } else if (probablyOperation.charAt(0) == '_') {
            return new ThirdPriorityOperations('_');
        } else if (probablyOperation.charAt(0) == '(') {
            return new Brackets('(');
        } else if (probablyOperation.charAt(0) == ')') {
            return new Brackets(')');
        } else {
            return new Number(probablyOperation);
        }
    }

}

