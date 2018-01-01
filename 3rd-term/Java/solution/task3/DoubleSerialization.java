package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class DoubleSerialization implements SerializationStrategy<Double> {

    @Override
    public void write(Double value, DataOutput out) throws IOException {
        out.writeDouble(value);
    }

    @Override
    public Double read(DataInput in) throws IOException {
        return in.readDouble();
    }
}