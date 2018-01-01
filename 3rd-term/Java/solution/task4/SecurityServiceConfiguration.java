package ru.mipt.java2016.homework.g596.kupriyanov.task4;

/**
 * Created by Artem Kupriyanov on 17/12/2016.
 */

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UsernameNotFoundException;

import java.util.Collections;

@Configuration
@EnableWebSecurity
public class SecurityServiceConfiguration extends WebSecurityConfigurerAdapter {
    private static final Logger LOG = LoggerFactory.getLogger(SecurityServiceConfiguration.class);

    @Autowired
    private BillingDao billingDao;

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        LOG.info("Configuring security");
        http
                .httpBasic().realmName("Calculator").and()
                .formLogin().disable()
                .logout().disable()
                .csrf().disable()
                .authorizeRequests()
                .antMatchers("/eval/**").authenticated()
                .anyRequest().permitAll();
    }

    @Autowired
    public void registerGlobalAuthentication(AuthenticationManagerBuilder auth) throws Exception {
        LOG.info("Registering global user details service");
        auth.userDetailsService(username -> {
            try {
                BillingUser user = billingDao.loadUser(username);
                return new User(
                        user.getUsername(),
                        user.getPassword(),
                        Collections.singletonList(() -> "AUTH")
                );
            } catch (EmptyResultDataAccessException e) {
                LOG.warn("No such user: " + username);
                throw new UsernameNotFoundException(username);
            }
        });
    }
}