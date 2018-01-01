package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.EmptyStackException;
import java.util.Stack;



public abstract class Operation {

    protected abstract int priority() throws ParsingException;

    protected abstract void makeOperation(Stack<Number> results) throws ParsingException;

    public void addOperation(Stack<Number> results, Stack<Operation> operations) throws ParsingException {
        try {
            while (operations.peek().priority() >= this.priority()) {
                Operation operation = operations.pop();
                operation.makeOperation(results);
            }
            operations.push(this);
        } catch (EmptyStackException e) {
            throw new ParsingException("No bracket balance");
        }
    }
}