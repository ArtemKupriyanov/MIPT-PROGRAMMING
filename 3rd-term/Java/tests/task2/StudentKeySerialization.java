package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import ru.mipt.java2016.homework.tests.task2.StudentKey;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */
public class StudentKeySerialization implements SerializationStrategy<StudentKey> {

    @Override
    public void write(StudentKey value, DataOutputStream out) throws IOException {
        out.writeInt(value.getGroupId());
        out.writeUTF(value.getName());
    }

    @Override
    public StudentKey read(DataInputStream in) throws IOException {
        StudentKey responceStudentKey = new StudentKey(in.readInt(), in.readUTF());
        return responceStudentKey;
    }
}
