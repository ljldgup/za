package ljl;

import java.util.Date;

import javax.annotation.Resource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ApplicationContext;
import org.springframework.core.env.Environment;

@SpringBootApplication  
public class Application implements ApplicationRunner{  

	@Autowired
	ApplicationContext applicationContext;


	@Autowired
	Environment env;


	public static void main(String[] args) {
        new SpringApplicationBuilder(Application.class)  
            .web(WebApplicationType.NONE) // .REACTIVE, .SERVLET
            .run(args);  
    }


	@Override
    public void run(ApplicationArguments args) throws Exception {  
        while(true) {
			System.out.println(applicationContext.getParentBeanFactory());
			Thread.sleep(10000);
        }  
    }
      
} 