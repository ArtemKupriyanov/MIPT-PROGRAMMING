package ru.mipt.java2016.homework.g596.kupriyanov.task2;

/**
 * Created by Artem Kupriyanov on 31/10/2016.
 */

import ru.mipt.java2016.homework.base.task2.KeyValueStorage;
import ru.mipt.java2016.homework.tests.task2.AbstractSingleFileStorageTest;
import ru.mipt.java2016.homework.tests.task2.Student;
import ru.mipt.java2016.homework.tests.task2.StudentKey;

import java.io.IOException;


public class MyKeyValueStorageTest extends AbstractSingleFileStorageTest {

    @Override
    protected KeyValueStorage<String, String> buildStringsStorage(String path) {
        MyKeyValueStorage<String, String> KVSForTest;
        try {
            KVSForTest = new MyKeyValueStorage(path,
                    new StringSerialization(),
                    new StringSerialization());
        }catch (IOException exp) {
            return null;
        }
        return KVSForTest;
    }

    @Override
    protected KeyValueStorage<Integer, Double> buildNumbersStorage(String path) {
        MyKeyValueStorage<Integer, Double> KVSForTest;
        try {
            KVSForTest = new MyKeyValueStorage(path,
                    new IntegerSerialization(),
                    new DoubleSerialization());
        } catch (IOException exp) {
            return null;
        }
        return KVSForTest;
    }

    @Override
    protected KeyValueStorage<StudentKey, Student> buildPojoStorage(String path) {
        MyKeyValueStorage<StudentKey, Student> KVSForTest;
        try {
            KVSForTest = new MyKeyValueStorage(path,
                    new StudentKeySerialization(),
                    new StudentSerialization());
        } catch (IOException exp) {
            return null;
        }
        return KVSForTest;
    }
}