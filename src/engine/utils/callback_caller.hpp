#include <iostream>

#include "callback_callee.hpp"
class Caller {
   public:
	// Clients can connect their callback with this
	void connectCallback(CallbackInterface *cb) {
		m_cb = cb;
	}

	// Test the callback to make sure it works.
	void test() {
		std::cout << "Caller::test() called" << std::endl;
		int i = m_cb->callbackFunction(10);

		std::cout << "Result (20): " << i << std::endl;
	}

   private:
	// The callback provided by the client via connectCallback().
	CallbackInterface *m_cb;
};
