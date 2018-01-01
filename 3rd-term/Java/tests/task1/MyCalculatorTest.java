/**
 * Created by Artem Kupriyanov on 12.10.2016.
 */

package ru.mipt.java2016.homework.g596.kupriyanov.task1;


import ru.mipt.java2016.homework.base.task1.Calculator;
import ru.mipt.java2016.homework.g596.kupriyanov.task1.MyCalculator;
import ru.mipt.java2016.homework.tests.task1.AbstractCalculatorTest;

public class MyCalculatorTest extends AbstractCalculatorTest {
    @Override
    protected Calculator calc() {
        return new MyCalculator();
    }
}