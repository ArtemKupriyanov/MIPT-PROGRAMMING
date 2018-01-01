package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class IntegerSerialization implements SerializationStrategy<Integer> {
    @Override
    public void write(Integer value, DataOutputStream out) throws IOException {
        out.writeInt(value);
    }

    @Override
    public Integer read(DataInputStream in) throws IOException {
        return in.readInt();
    }
}