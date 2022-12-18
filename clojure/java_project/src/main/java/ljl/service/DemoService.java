package ljl.service;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

//@Service用于标注业务层组件，
//@Controller用于标注控制层组件（如struts中的action）,
//@Repository用于标注数据访问组件，即DAO组件，
//@Component泛指组件，当组件不好归类的时候，我们可以使用这个注解进行标注。  
@Service
public class DemoService implements InitializingBean {

	@Value("normal")
    private String normal; // 注入普通字符串
    
    @Value("\"#{systemProperties['os.name']}\"")
    private String testValue1;
    
    // 这里的值来自resources/application.properties，spring boot启动时默认加载此文件
    @Value("${app.name}")
    private String testValue2;

    @Autowired
    DemoService demoService;

    @PreDestroy
    public void PreDestroy(){
        System.out.println(this.getClass().getName() + " PreDestroy");
    }
    @PostConstruct
    public void postConstructTest(){
            System.out.println(this.getClass().getName() + " postConstructTest");
    }

    @Override
    public void afterPropertiesSet() throws Exception {
        System.out.println(this.getClass().getName() + " afterPropertiesSet");
    }

    public void test(){
        System.out.println(normal);
        System.out.println(testValue1);
        System.out.println(testValue2);
    }
}