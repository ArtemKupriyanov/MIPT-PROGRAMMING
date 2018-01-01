package ru.mipt.java2016.homework.g596.kupriyanov.task4;

/**
 * Created by Artem Kupriyanov on 17/12/2016.
 */

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.Banner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.context.embedded.EmbeddedServletContainerCustomizer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import ru.mipt.java2016.homework.base.task1.Calculator;
import ru.mipt.java2016.homework.g596.kupriyanov.task1.MyCalculator;


//запуск
//  curl http://localhost:9001/eval \
//      -X POST \
//      -H "Content-Type: text/plain" \
//      -H "Authorization: Basic $(echo -n "username:password" | base64)" \
//          --data-raw "44*3+2"


@EnableAutoConfiguration
@Configuration
@ComponentScan(basePackageClasses = FediqApplication.class)
public class FediqApplication {

    @Bean
    public Calculator calculator() {
        return new MyCalculator();
    }

    @Bean
    public EmbeddedServletContainerCustomizer customizer(
            @Value("${ru.mipt.java2016.homework.g000.lavrentyev.task4.httpPort:9001}") int port) {
        return container -> container.setPort(port);
    }

    public static void main(String[] args) {
        SpringApplication application = new SpringApplication(FediqApplication.class);
        application.setBannerMode(Banner.Mode.OFF);
        application.run(args);
    }
}
