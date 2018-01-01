package ru.mipt.java2016.homework.g596.kupriyanov.task1;

/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.Stack;

public final class Number extends Operation {

    private double value;

    public double getValue() {
        return this.value;
    }

    public Number(double value) throws ParsingException {
        try {
            this.value = value;
        } catch (NumberFormatException e) {
            throw new ParsingException("incorrect");
        }
    }

    public Number(String s) throws ParsingException {
        try {
            this.value = Double.valueOf(s);
        } catch (NumberFormatException e) {
            throw new ParsingException("incorrect");
        }
    }

    @Override
    protected int priority() throws ParsingException {
        throw new ParsingException("Numbers");
    }


    @Override
    protected void makeOperation(Stack<Number> results) throws ParsingException {
        throw new ParsingException("Numbers");
    }

    @Override
    public void addOperation(Stack<Number> results, Stack<Operation> operations) throws ParsingException {
        results.push(this);
    }
}