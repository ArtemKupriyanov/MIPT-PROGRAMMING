package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */
public class StringSerialization implements SerializationStrategy<String> {

    @Override
    public void write(String value, DataOutputStream out) throws IOException {
        out.writeUTF(value);
    }

    @Override
    public String read(DataInputStream in) throws IOException {
        return in.readUTF();
    }
}