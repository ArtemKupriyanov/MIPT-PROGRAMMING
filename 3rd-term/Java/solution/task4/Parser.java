package ru.mipt.java2016.homework.g596.kupriyanov.task4;

import ru.mipt.java2016.homework.base.task1.ParsingException;

import java.util.*;

/**
 * Created by Artem Kupriyanov on 19/12/2016.
 */


public class Parser extends BillingDao {
    private String expression;
    private String username;
    private Map<String, String> variables;
    private List<String> functions;

    Parser(String exp, String usern) {
        expression = exp;
        username = usern;
        try {
            variables = getAllVariables(username);
        } catch (ParsingException e) {
            variables = new HashMap<>();
        }
        //functions =
    }

    class LengthComparator implements Comparator<String> {
        @Override
        public int compare(String s1, String s2) {
            return -(s1.length() - s2.length()); // по убыванию
        }
    }

    private void substituteVariable() {
        LengthComparator myComparator = new LengthComparator();
        List<String> sortedVariables = new ArrayList<>(variables.keySet());
        Collections.sort(sortedVariables, myComparator);
        for (String variable: sortedVariables) {
            if (expression.contains(variable)) {
                expression.replaceAll(variable, variables.get(variable));
            }
        }
    }

    public String expressionInFunction(String express, String function) {
        int start = express.indexOf(function) + function.length();
        int bracketBalance = 0;
        if (express.charAt(start) != '(') {
            return null;
        }
        int end = start;
        while (end != express.length()) {
            if (express.charAt(end) == '(') {
                bracketBalance++;
            }
            if (express.charAt(end) == ')') {
                bracketBalance--;
            }
            if (bracketBalance == 0) {
                break;
            }
            end++;
        }
        return express.substring(start, end);
    }

    public String work() {
        substituteVariable();
        return expression;
    }

    public List<String> getFunction() {
        return functions;
    }
}
