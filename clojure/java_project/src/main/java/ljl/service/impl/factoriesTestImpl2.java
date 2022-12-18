package ljl.service.impl;

import ljl.service.FactoriesTest;
import org.springframework.stereotype.Component;

//通过命名名称不同，同一个接口可以实现多次，装配的时候使用Resource + 名称装配
@Component("factoriesTestImpl2")
public class factoriesTestImpl2 implements FactoriesTest {
	@Override
	public void print() {
		System.out.println(this.getClass().getName());
	}
}
