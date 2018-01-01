package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import ru.mipt.java2016.homework.tests.task2.Student;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Date;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class StudentSerialization implements SerializationStrategy<Student> {

    @Override
    public void write(Student value, DataOutput out) throws IOException {
        out.writeInt(value.getGroupId());
        out.writeUTF(value.getName());
        out.writeUTF(value.getHometown());
        long timeToWrite = value.getBirthDate().getTime();
        out.writeLong(timeToWrite);
        out.writeBoolean(value.isHasDormitory());
        out.writeDouble(value.getAverageScore());
    }

    @Override
    public Student read(DataInput in) throws IOException {
        Student responceStudent = new Student(in.readInt(), in.readUTF(), in.readUTF(),
                new Date(in.readLong()), in.readBoolean(),
                in.readDouble());
        return responceStudent;
    }
}