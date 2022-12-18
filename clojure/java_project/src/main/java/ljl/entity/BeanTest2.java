package ljl.entity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;

@Component
public class BeanTest2 {
	@Autowired
	BeanTest2 beanTest2;

	public BeanTest2() {
		System.out.println("BeanTest2");
	}

	@PostConstruct
	public void init() {
		System.out.println("BeanTest2 " + beanTest2);
	}
}
