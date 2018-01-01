package ru.mipt.java2016.homework.g596.kupriyanov.task3;

import ru.mipt.java2016.homework.base.task2.KeyValueStorage;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

import static java.lang.Math.max;

/**
 * Created by Artem Kupriyanov on 20/11/2016.
 */

public class OptKeyValueStorage<K, V> implements KeyValueStorage<K, V> {
    private SerializationStrategy<K> keySerialization;
    private SerializationStrategy<V> valueSerialization;

    private final ReadWriteLock readWriteLock = new ReentrantReadWriteLock();
    private final Lock readLock = readWriteLock.readLock();
    private final Lock writeLock = readWriteLock.writeLock();

    private Map<K, Long> db = new HashMap<>();
    private Map<K, V> bufferCache = new HashMap<>();

    private long maxNow;

    private final String pathName;

    private File mtxFile;
    private static final String MTX_FILE_NAME = "mtx.txt";
    private RandomAccessFile storage;
    private static final String STORAGE_NAME = "storage.txt";
    private RandomAccessFile mapStorage;
    private static final String MAP_STORAGE_NAME = "mapStorage.txt";

    private static final long MAX_OPTIMIZE_THRESHOLD = 100000;
    private long cntThreshold = 0;

    private boolean dbClosed;

    private static final long MAXSIZE = 100L;

    public OptKeyValueStorage(SerializationStrategy<K> keySerStrat,
                              SerializationStrategy<V> valueSerStrat,
                              String path) throws IOException {
        keySerialization = keySerStrat;
        valueSerialization = valueSerStrat;
        maxNow = 0L;
        pathName = path;
        File dir = new File(pathName);
        if (!dir.isDirectory()) {
            throw new RuntimeException("BAD PATH");
        }
        mtxFile = new File(pathName, MTX_FILE_NAME);
        if (!mtxFile.createNewFile()) {
            throw new RuntimeException("CAN'T SYNCHRONIZE");
        }
        File file = new File(pathName, STORAGE_NAME);
        storage = new RandomAccessFile(file, "rw");
        dbClosed = false;
        File mapFile = new File(path, MAP_STORAGE_NAME);
        mapStorage = new RandomAccessFile(mapFile, "rw");
        if (file.exists() && mapFile.exists()) {
            uploadData();
        } else if (!file.createNewFile() || mapFile.createNewFile()) {
            throw new RuntimeException("CAN'T CREATE");
        }
    }

    private void checkOpened() {
        if (dbClosed) {
            throw new RuntimeException("CAN'T OPEN");
        }
    }

    @Override
    public V read(K key) {
        writeLock.lock();
        try {
            checkOpened();
            if (!exists(key)) {
                return null;
            }
            if (bufferCache.get(key) != null) {
                return bufferCache.get(key);
            }
            Long place = db.get(key);
            storage.seek(place);
            return valueSerialization.read(storage);
        } catch (Exception e) {
            throw new RuntimeException("CAN'T READ");
        } finally {
            writeLock.unlock();
        }
    }

    @Override
    public boolean exists(K key) {
        readLock.lock();
        try {
            return !dbClosed && (bufferCache.containsKey(key) || db.containsKey(key));
        } catch (Exception e) {
            throw new RuntimeException("CAN'T CHECK EXIST");
        } finally {
            readLock.unlock();
        }
    }

    @Override
    public void write(K key, V value) {
        writeLock.lock();
        try {
            checkOpened();
            db.put(key, 0L);
            bufferCache.put(key, value);
            if (bufferCache.size() > MAXSIZE) {
                writeCashe();
            }
            if (bufferCache.containsKey(key)) {
                if (cntThreshold > MAX_OPTIMIZE_THRESHOLD) {
                    updStorage();
                }
                ++cntThreshold;
            }
        } catch (Exception e) {
            throw new RuntimeException("CAN'T OPEN");
        } finally {
            writeLock.unlock();
        }
    }

    @Override
    public void delete(K key) {
        writeLock.lock();
        try {
            checkOpened();
            bufferCache.remove(key);
            db.remove(key);
            if (cntThreshold > MAX_OPTIMIZE_THRESHOLD) {
                updStorage();
            }
            ++cntThreshold;
        } catch (Exception e) {
            throw new RuntimeException("CAN'T DELETE");
        } finally {
            writeLock.unlock();
        }
    }

    @Override
    public Iterator<K> readKeys() {
        readLock.lock();
        try {
            checkOpened();
            return db.keySet().iterator();
        } finally {
            readLock.unlock();
        }
    }

    @Override
    public int size() {
        readLock.lock();
        try {
            checkOpened();
            return db.size();
        } finally {
            readLock.unlock();
        }
    }

    @Override
    public void close() throws IOException {
        writeLock.lock();
        try {
            writeCashe();
            downloadData();
            mapStorage.close();
            storage.close();
            bufferCache.clear();
            db.clear();
            mtxFile.delete();
            dbClosed = true;
        } catch (Exception e) {
            throw new RuntimeException("CAN'T CLOSE2");
        } finally {
            writeLock.unlock();
        }
    }

    private void uploadData() {
        try {
            int nValues = mapStorage.readInt();
            for (int i = 0; i < nValues; ++i) {
                K key = keySerialization.read(mapStorage);
                Long value = mapStorage.readLong();
                db.put(key, value);
                maxNow = max(maxNow, value);
            }
        } catch (IOException e) {
            db.clear();
        }
    }

    private void downloadData() {
        try {
            mapStorage.close();
            File file = new File(pathName, MAP_STORAGE_NAME);
            assert (file.delete());
            file = new File(pathName, MAP_STORAGE_NAME);
            mapStorage = new RandomAccessFile(file, "rw");
            mapStorage.writeInt(size());
            for (HashMap.Entry<K, Long> entry : db.entrySet()) {
                keySerialization.write(entry.getKey(), mapStorage);
                mapStorage.writeLong(entry.getValue());
            }
        } catch (IOException e) {
            throw new RuntimeException("CAN'T LOAD");
        }
    }

    private void writeCashe() {
        checkOpened();
        try {
            for (HashMap.Entry<K, V> entry : bufferCache.entrySet()) {
                storage.seek(maxNow);
                valueSerialization.write(entry.getValue(), storage);
                long currMax = storage.getFilePointer();
                db.put(entry.getKey(), maxNow);
                maxNow = currMax;
            }
            bufferCache.clear();
        } catch (IOException e) {
            throw new RuntimeException("CAN'T WRITE");
        }
    }

    private void updStorage() {
        try {
            cntThreshold = 0;
            File file = new File(pathName, "newStorage.txt");
            Map<K, Long> newdb = new HashMap<>();
            try (RandomAccessFile newStorage = new RandomAccessFile(file, "rw")) {
                for (Map.Entry<K, Long> entry : db.entrySet()) {
                    newdb.put(entry.getKey(), newStorage.length());
                    valueSerialization.write(read(entry.getKey()), newStorage);
                }
                db = newdb;
                storage.close();
                File newFile = new File(pathName, STORAGE_NAME);
                assert (newFile.delete());
                newStorage.close();
                assert (file.renameTo(newFile));
            }
        } catch (IOException e) {
            throw new RuntimeException("CAN'T UPD");
        }
    }
}