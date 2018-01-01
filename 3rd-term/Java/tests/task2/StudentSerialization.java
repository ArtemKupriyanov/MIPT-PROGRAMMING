package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import ru.mipt.java2016.homework.tests.task2.Student;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Date;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class StudentSerialization implements SerializationStrategy<Student> {

    @Override
    public void write(Student value, DataOutputStream out) throws IOException {
        out.writeInt(value.getGroupId());
        out.writeUTF(value.getName());
        out.writeUTF(value.getHometown());
        long timeToWrite = value.getBirthDate().getTime();
        out.writeLong(timeToWrite);
        out.writeBoolean(value.isHasDormitory());
        out.writeDouble(value.getAverageScore());
    }

    @Override
    public Student read(DataInputStream stream) throws IOException {
        Student responceStudent = new Student(stream.readInt(), stream.readUTF(), stream.readUTF(),
                new Date(stream.readLong()), stream.readBoolean(),
                stream.readDouble());
        return responceStudent;
    }
}