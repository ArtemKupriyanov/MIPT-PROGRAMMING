package ru.mipt.java2016.homework.g596.kupriyanov.StreamAPI;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.*;

/**
 * Created by Artem Kupriyanov on 11/12/2016.
 */

public class StreamAPI {
    static String path = "/Users/akupriyanov/Desktop/Java/mipt-java-2016/homework-g596-kupriyanov/src/main/java/ru/" +
            "mipt/java2016/homework/g596/kupriyanov/StreamAPI/Чехов Антон. Вишневый сад.txt";
    static String pattern = "[^0-9a-zA-Zа-яА-Я]+";

    public static void main(String[] args) throws IOException {
        Map<String, Integer> dictStream = streamAPICounter();
        Map<String, Integer> dictUsual = usualCounter();
        for (HashMap.Entry<String, Integer> entry : streamAPICounter().entrySet()) {
            Boolean test = (entry.getValue().equals(dictUsual.get(entry.getKey())));
            System.out.print(entry.getKey());
            System.out.print(" ");
            System.out.print(entry.getValue());
            System.out.print(" ");
            System.out.print(dictUsual.get(entry.getKey()));
            System.out.println(test);
            if (!test) {
                throw new IOException();
            }
        }
    }

    private static Map<String, Integer> streamAPICounter() throws IOException {
        Map<String, Integer> dict = Files.lines(Paths.get(path))
                .flatMap(line -> Stream.of(line.split(pattern))
                        .filter(word -> word.length() > 0))
                .map(String::toLowerCase)
                .collect(Collectors.toMap(word -> word,
                                word -> 1,
                                Integer::sum));
        return dict;
    }

    private static Map<String, Integer> usualCounter() throws IOException {
        Map<String, Integer> dict = new HashMap<>();
        List<String> text = Files.readAllLines(Paths.get(path));
        for (String line: text) {
            line = line.toLowerCase();
            List<String> arrayStrings = Arrays.asList(line.split(pattern));
            for (String word: arrayStrings) {
                if (!word.equals("")) {
                    if (dict.containsKey(word)) {
                        dict.put(word, dict.get(word) + 1);
                    } else {
                        dict.put(word, 1);
                    }
                }
            }
        }
        return dict;
    }
}
