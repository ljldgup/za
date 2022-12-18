package ljl.service.impl;

import ljl.service.FactoriesTest;
import org.springframework.stereotype.Component;

@Component("factoriesTestImpl1")
public class factoriesTestImpl1 implements FactoriesTest {
	@Override
	public void print() {
		System.out.println(this.getClass().getName());
	}
}
