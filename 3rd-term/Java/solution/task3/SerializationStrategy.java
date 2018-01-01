package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;


/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public interface SerializationStrategy<V> {
    void write(V value, DataOutput out) throws IOException;

    V read(DataInput in) throws IOException;
}