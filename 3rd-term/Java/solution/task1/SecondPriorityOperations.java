package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.EmptyStackException;
import java.util.Stack;

public final class SecondPriorityOperations extends Operation {

    private char operation;

    public SecondPriorityOperations(char op) {
        this.operation = op;
    }

    @Override
    protected int priority() {
        return 2;
    }

    @Override
    protected void makeOperation(Stack<Number> results) throws ParsingException {
        try {
            Number second = results.pop();
            Number first = results.pop();
            if (this.operation == '/') {
                results.push(new Number(first.getValue() / second.getValue()));
            }
            if (this.operation == '*') {
                results.push(new Number(first.getValue() * second.getValue()));
            }
        } catch (EmptyStackException e) {
            throw new ParsingException("Not enough arguments");
        }
    }
}