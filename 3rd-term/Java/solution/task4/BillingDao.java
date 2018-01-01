package ru.mipt.java2016.homework.g596.kupriyanov.task4;

/**
 * Created by Artem Kupriyanov on 17/12/2016.
 */

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;
import ru.mipt.java2016.homework.base.task1.ParsingException;

import javax.annotation.PostConstruct;
import javax.sql.DataSource;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

@Repository
public class BillingDao {
    private static final Logger LOG = LoggerFactory.getLogger(BillingDao.class);

    @Autowired
    private DataSource dataSource;

    private JdbcTemplate jdbcTemplate;

    @PostConstruct
    public void postConstruct() {
        jdbcTemplate = new JdbcTemplate(dataSource, false);
        initSchema();
    }

    public void initSchema() {
        LOG.trace("Initializing schema");
        jdbcTemplate.execute("CREATE SCHEMA IF NOT EXISTS billing");

        // ЗДЕСЬ ДОЛЖНА БЫТЬ ХОРОШАЯ РЕАЛИЗАЦИЯ БАЗЫ ДАННЫХ
        // Users table
        jdbcTemplate.execute("CREATE TABLE IF NOT EXISTS billing.users " +
                "(username VARCHAR PRIMARY KEY, password VARCHAR, enabled BOOLEAN)");
        jdbcTemplate.update("INSERT INTO billing.users VALUES (\'username\', \'password\', TRUE)");

        // Variable table
        jdbcTemplate.execute("CREATE TABLE IF NOT EXISTS billing.variables " +
                "(username VARCHAR, variable VARCHAR, val DOUBLE)");

        // Functions table
        jdbcTemplate.execute("CREATE TABLE IF NOT EXISTS billing.functions " +
                "(username VARCHAR, function VARCHAR, arity INTEGER, body VARCHAR)");
    }

    private Boolean checkNull(String condition) {
        LOG.trace("check " + condition);
        String allSelect = "SELECT * FROM " + condition;

        return jdbcTemplate.queryForObject(
                allSelect,
                new Object[]{},
                new RowMapper<Boolean>() {
                    @Override
                    public Boolean mapRow(ResultSet rs, int rowNum) throws SQLException {
                        Boolean flag = false;
                        while (true) {
                            if (!rs.next()) {
                                break;
                            }
                            flag = true;
                        }
                        return flag;
                    }
                }
        );
    }

    public BillingUser loadUser(String username) throws EmptyResultDataAccessException {
        LOG.trace("Querying for user " + username);
        return jdbcTemplate.queryForObject(
                "SELECT username, password, enabled FROM billing.users WHERE username = ?",
                new Object[]{username},
                new RowMapper<BillingUser>() {
                    @Override
                    public BillingUser mapRow(ResultSet rs, int rowNum) throws SQLException {
                        return new BillingUser(
                                rs.getString("username"),
                                rs.getString("password"),
                                rs.getBoolean("enabled")
                        );
                    }
                }
        );
    }

    public void putUser(String username, String password) {
        try {
            loadUser(username);
        } catch (EmptyResultDataAccessException e) {
            jdbcTemplate.execute("INSERT INTO billing.users VALUES (\'" + username + "\', \'" + password + "\', TRUE)");
        }
    }

    public Double getVariable(String username, String variable) {
        LOG.trace("Get variable " + username + " variable " + variable);
        try {
            return jdbcTemplate.queryForObject(
                    "select val from billing.variables " +
                            "where username = \'" + username + "\' and variable = \'" + variable + "\'",
                    new Double[]{},
                    new RowMapper<Double>() {
                        @Override
                        public Double mapRow(ResultSet rs, int rowNum) throws SQLException {
                            return new Double(
                                    rs.getString("val").toString()
                            );
                        }
                    }
            );
        } catch (EmptyResultDataAccessException e) {
            return 0.0;
        }
    }

    public void putVariable(String username, String variable, Double value) {
        LOG.trace("Put variable " + variable + " for user " + username);
        try {
            deleteVariable(username, variable);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            jdbcTemplate.execute("INSERT INTO billing.variables VALUES (\'"
                    + username + "\', \'" + variable + "\', " + value.toString() + ")");
        }
    }

    public void deleteVariable(String username, String variable) {
        LOG.trace("Delete variable " + variable + "for user " + username);
        jdbcTemplate.execute("DELETE FROM billing.variables WHERE username = \'"
                + username + "\' AND variable = \'" + variable + "\'");
    }

    public HashMap<String, String> getAllVariables(String username) throws ParsingException {
        LOG.trace("List with all functions for user: " + username);
        try {
            return jdbcTemplate.queryForObject(
                    "SELECT username, variable, val FROM billing.variables WHERE username = ?",
                    new Object[]{username},
                    new RowMapper<HashMap<String, String>>() {
                        @Override
                        public HashMap<String, String> mapRow(ResultSet rs, int rowNum) throws SQLException {
                            HashMap<String, String> tmp = new HashMap<String, String>();
                            while (true) {
                                tmp.put(rs.getString("variable"), Double.toString(rs.getDouble("val")));
                                if (!rs.next()) {
                                    break;
                                }
                            }
                            return tmp;
                        }
                    }
            );
        } catch (EmptyResultDataAccessException e) {
            HashMap<String, String> tmp = new HashMap<String, String>();
            return tmp;
        }
    }

    public void putFunction(String username, String function, Integer arity, String body) {
        LOG.trace("Put function " + function + " for user " + username);
        try {
            deleteFunction(username, function);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            jdbcTemplate.execute("INSERT INTO billing.functions VALUES (\'"
                    + username + "\', \'" + function + "\', " + arity.toString() + ", \'"
                    + body + "\')");
        }
    }

    public String getFunction(String username, String function) {
        LOG.trace("Load function " + function + " for user " + username);
        return jdbcTemplate.queryForObject(
                "SELECT body FROM billing.functions WHERE username = \'"
                        + username + "\' AND function = \'" + function + "\'",
                new String[]{},
                new RowMapper<String>() {
                    @Override
                    public String mapRow(ResultSet rs, int rowNum) throws SQLException {
                        return rs.getString("body");
                    }
                }
        );
    }

    public void deleteFunction(String username, String function) {
        LOG.info("Delete function " + function + " for user " + username);
        jdbcTemplate.execute("DELETE FROM billing.functions WHERE username = \'" +
                username + "\' AND function = \'" + function + "\'");
    }
}