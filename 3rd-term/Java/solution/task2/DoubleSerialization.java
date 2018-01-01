package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */
public class DoubleSerialization implements SerializationStrategy<Double> {

    @Override
    public void write(Double value, DataOutputStream out) throws IOException {
        out.writeDouble(value);
    }

    @Override
    public Double read(DataInputStream in) throws IOException {
        return in.readDouble();
    }
}