package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class IntegerSerialization implements SerializationStrategy<Integer> {
    @Override
    public void write(Integer value, DataOutput out) throws IOException {
        out.writeInt(value);
    }

    @Override
    public Integer read(DataInput in) throws IOException {
        return in.readInt();
    }
}