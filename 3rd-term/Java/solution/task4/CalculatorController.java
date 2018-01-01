package ru.mipt.java2016.homework.g596.kupriyanov.task4;

/**
 * Created by Artem Kupriyanov on 17/12/2016.
 */

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.web.bind.annotation.*;
import ru.mipt.java2016.homework.base.task1.Calculator;
import ru.mipt.java2016.homework.base.task1.ParsingException;

@RestController
public class CalculatorController {
    private static final Logger LOG = LoggerFactory.getLogger(CalculatorController.class);
    @Autowired
    private Calculator calculator;
    @Autowired
    private BillingDao billingDao;

    @RequestMapping(path = "/ping", method = RequestMethod.GET, produces = "text/plain")
    public String echo() {
        return "OK\n";
    }

    @RequestMapping(path = "/", method = RequestMethod.GET, produces = "text/html")
    public String main(@RequestParam(required = false) String name) {
        if (name == null) {
            name = "world";
        }
        return "<html>" +
                "<head><title>FediqApp</title></head>" +
                "<body><h1>Hello, " + name + "!</h1></body>" +
                "</html>";
    }

    @RequestMapping(path = "/eval", method = RequestMethod.POST, consumes = "text/plain", produces = "text/plain")
    public String eval(Authentication auth, @RequestBody String expression) throws ParsingException {
        LOG.debug("Evaluation request: [" + expression + "]");
        String username = auth.getName();
        double result = calculator.calculate(expression);
        //String result = functionalCalculate(expression, username);
        LOG.trace("Result: " + result);
        //return result;
        return Double.toString(result) + "\n";
    }

    @RequestMapping(path = "/reg/{userName}", method = RequestMethod.PUT,
            consumes = "text/plain", produces = "text/plain")
    public void reg(@PathVariable String userName, @RequestBody String passwd) throws ParsingException {
        LOG.debug("New user: [" + userName + ' ' + passwd + "]");
        billingDao.putUser(userName, passwd);
    }

    private String functionalCalculate(String expression, String username) throws ParsingException {
        String goodExpression = expression;
        Parser parser = new Parser(expression, username);
        for (String function : parser.getFunction()) {
            if (expression.indexOf(function) != -1) {
                String subExpression = parser.expressionInFunction(expression, function);
                String functionAndOperand = function + subExpression;
                expression.replace(functionAndOperand, functionalCalculate(subExpression, username));
            }
        }
        goodExpression = parser.work();
        double result = calculator.calculate(goodExpression);
        return Double.toString(result)  + "\n";
    }

    @RequestMapping(path = "/variable/{variableName}", method = RequestMethod.PUT,
            consumes = "text/plain", produces = "text/plain")
    public void putVariable(Authentication auth,
                            @PathVariable String variableName, @RequestParam(value = "value") Double value) {
        String username = auth.getName();
        billingDao.putVariable(username, variableName, value);
    }

    @RequestMapping(path = "/variable/{variableName}", method = RequestMethod.GET,
            consumes = "text/plain", produces = "text/plain")
    public String getVariable(Authentication auth, @PathVariable String variableName) {
        String username = auth.getName();
        Double value = billingDao.getVariable(username, variableName);
        return value.toString() + "\n";
    }

    @RequestMapping(path = "/variable/{variableName}", method = RequestMethod.DELETE,
            consumes = "text/plain", produces = "text/plain")
    public void deleteVariable(Authentication authentication, @PathVariable String variableName) {
        String username = authentication.getName();
        billingDao.deleteVariable(username, variableName);
    }

    @RequestMapping(path = "/function/{functionName}", method = RequestMethod.PUT,
            consumes = "text/plain", produces = "text/plain")
    public void putFunction(Authentication authentication, @PathVariable String functionName,
                            @RequestParam(value = "arity") Integer arity, @RequestBody String body) {
        String username = authentication.getName();
        LOG.trace(username);
        billingDao.putFunction(username, functionName, arity, body);
    }

    @RequestMapping(path = "/function/{functionName}", method = RequestMethod.DELETE,
            consumes = "text/plain", produces = "text/plain")
    public void deleteFunction(Authentication authentication, @PathVariable String functionName) {
        String username = authentication.getName();
        billingDao.deleteFunction(username, functionName);
    }

    @RequestMapping(path = "/function/{functionName}", method = RequestMethod.GET,
            consumes = "text/plain", produces = "text/plain")
    public String getFunction(Authentication authentication, @PathVariable String functionName) {
        String username = authentication.getName();
        String res = billingDao.getFunction(username, functionName);
        return res + "\n";
    }
}