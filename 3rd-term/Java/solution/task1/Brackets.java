package ru.mipt.java2016.homework.g596.kupriyanov.task1;


/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.Stack;

public final class Brackets extends Operation {

    private char operation;

    public Brackets(char op) {
        this.operation = op;
    }

    @Override
    protected int priority() throws ParsingException {
        if (operation == ')') {
            throw new ParsingException("Close bracket");
        }
        if (operation == '(') {
            return 0;
        }
        throw new ParsingException("Strange operation");
    }

    @Override
    protected void makeOperation(Stack<Number> results) throws ParsingException {
        throw new ParsingException("Can't make operation");
    }

    @Override
    public void addOperation(Stack<Number> results, Stack<Operation> operations) throws ParsingException {
        if (operation == ')') {
            while (operations.peek().priority() != 0) {
                if (operations.isEmpty()) {
                    throw new ParsingException("No bracket balance");
                }
                Operation stackOperation = operations.pop();
                stackOperation.makeOperation(results);
            }
            operations.pop();
        }
        if (operation == '(') {
            operations.push(this);
        }
    }
}