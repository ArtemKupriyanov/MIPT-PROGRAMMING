package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.Stack;

public final class ThirdPriorityOperations extends Operation {

    private char operation;

    public ThirdPriorityOperations(char op) {
        this.operation = op;
    }

    @Override
    protected int priority() {
        return 3;
    }

    @Override
    protected void makeOperation(Stack<Number> results) throws ParsingException {
        if (results.isEmpty()) {
            throw new ParsingException("No argument");
        }
        Number item = results.pop();
        results.push(new Number(-item.getValue()));
    }

    @Override
    public void addOperation(Stack<Number> results, Stack<Operation> operations) throws ParsingException {
        operations.push(this);
    }
}