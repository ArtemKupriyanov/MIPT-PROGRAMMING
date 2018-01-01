package ru.mipt.java2016.homework.g596.kupriyanov.task2;

import ru.mipt.java2016.homework.base.task2.KeyValueStorage;

import java.io.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import java.io.IOException;

/**
 * Created by Artem Kupriyanov on 29/10/2016.
 */

public class MyKeyValueStorage<K, V> implements KeyValueStorage<K, V> {
    private File file;
    private Boolean dbOpen;
    private SerializationStrategy<K> keySerializer;
    private SerializationStrategy<V> valueSerializer;
    private Map<K, V> db = new HashMap<K, V>();

    public MyKeyValueStorage(String path, SerializationStrategy<K> keySer,
                     SerializationStrategy<V> valueSer) throws IOException {
        File checkDir = new File(path);
        keySerializer = keySer;
        valueSerializer = valueSer;
        file = new File(path + file.separator + "db.txt");
        if (!checkDir.exists()) {
            throw new RuntimeException("FILE DOESN'T EXIST");
        }
        if (!checkDir.isDirectory()) {
            throw new RuntimeException("NO DIRECTORY");
        }
        dbOpen = true;
        if (file.exists()) {
            try (DataInputStream in = new DataInputStream(new FileInputStream(file))) {
                int cntElems = in.readInt();
                for (int i = 0; i < cntElems; ++i) {
                    db.put(keySerializer.read(in), valueSerializer.read(in));
                }
            } catch (IOException e) {
                throw new RuntimeException("CAN'T PUT IN DB");
            }
        } else {
            file.createNewFile();
        }
    }

    private void checkOpened() {
        if (!dbOpen) {
            throw new RuntimeException("CLOSED");
        }
    }

    @Override
    public V read(K key) {
        checkOpened();
        return db.get(key);
    }

    @Override
    public boolean exists(K key) {
        checkOpened();
        return db.containsKey(key);
    }

    @Override
    public void write(K key, V value) {
        checkOpened();
        db.put(key, value);
    }

    @Override
    public void delete(K key) {
        checkOpened();
        db.remove(key);
    }

    @Override
    public Iterator<K> readKeys() {
        checkOpened();
        return db.keySet().iterator();
    }

    @Override
    public int size() {
        checkOpened();
        return db.size();
    }

    @Override
    public void close() throws IOException {
        checkOpened();
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(file))) {
            out.writeInt(db.size());
            for (HashMap.Entry<K, V> pair: db.entrySet()) {
                keySerializer.write(pair.getKey(), out);
                valueSerializer.write(pair.getValue(), out);
            }
            dbOpen = false;
            db.clear();
        } catch (IOException exp) {
            throw new RuntimeException("COULDN'T CLOSE DB");
        }
    }
}