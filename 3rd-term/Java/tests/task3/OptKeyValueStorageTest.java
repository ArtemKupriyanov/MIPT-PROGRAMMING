package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import java.io.IOException;

import ru.mipt.java2016.homework.base.task2.KeyValueStorage;
import ru.mipt.java2016.homework.base.task2.MalformedDataException;
import ru.mipt.java2016.homework.tests.task2.Student;
import ru.mipt.java2016.homework.tests.task2.StudentKey;
import ru.mipt.java2016.homework.tests.task3.KeyValueStoragePerformanceTest;

/**
 * Created by Artem Kupriyanov on 20/11/2016.
 */

public class OptKeyValueStorageTest extends KeyValueStoragePerformanceTest {
    @Override
    protected KeyValueStorage<String, String> buildStringsStorage(String path) throws MalformedDataException {

        try {
            return new OptKeyValueStorage<>(new StringSerialization(), new StringSerialization(), path);
        } catch (IOException e) {
            throw new RuntimeException("1(");
        }
    }

    @Override
    protected KeyValueStorage<Integer, Double> buildNumbersStorage(String path) throws MalformedDataException {
        try {
            return new OptKeyValueStorage<>(new IntegerSerialization(), new DoubleSerialization(), path);
        } catch (IOException e) {
            throw new RuntimeException("2(");
        }
    }

    @Override
    protected KeyValueStorage<StudentKey, Student> buildPojoStorage(String path) throws MalformedDataException {
        try {
            return new OptKeyValueStorage<>(new StudentKeySerialization(), new StudentSerialization(), path);
        } catch (IOException e) {
            throw new RuntimeException("(");
        }
    }
}
