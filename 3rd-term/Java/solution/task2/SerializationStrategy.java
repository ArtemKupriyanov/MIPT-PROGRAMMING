package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public interface SerializationStrategy<V> {
    void write(V value, DataOutputStream out) throws IOException;

    V read(DataInputStream in) throws IOException;
}