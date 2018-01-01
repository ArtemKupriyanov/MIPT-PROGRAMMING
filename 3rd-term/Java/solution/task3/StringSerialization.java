package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class StringSerialization implements SerializationStrategy<String> {

    @Override
    public void write(String value, DataOutput out) throws IOException {
        out.writeUTF(value);
    }

    @Override
    public String read(DataInput in) throws IOException {
        return in.readUTF();
    }
}