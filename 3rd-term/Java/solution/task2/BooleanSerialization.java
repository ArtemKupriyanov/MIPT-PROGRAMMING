package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */
public class BooleanSerialization implements SerializationStrategy<Boolean> {

    @Override
    public void write(Boolean value, DataOutputStream out) throws IOException {
        out.writeBoolean(value);
    }

    @Override
    public Boolean read(DataInputStream in) throws IOException {
        return in.readBoolean();
    }
}
