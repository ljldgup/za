package ljl.clojure;

import clojure.java.api.Clojure;
import clojure.lang.IFn;
import org.springframework.stereotype.Component;

@Component
public class NreplServer {
	NreplServer() {
		IFn require = Clojure.var("clojure.core", "require");
		require.invoke(Clojure.read("nrepl.server"));
		IFn start = Clojure.var("nrepl.server", "start-server");
		int port = 7888;
		Object result = start.invoke(Clojure.read(":port"), Clojure.read(Integer.toString(port)));
		System.out.println("nrepl server started on port " + port + result);
	}
}
