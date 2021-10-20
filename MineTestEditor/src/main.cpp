
#include <MineTestCore/Application.hpp>

#include <iostream>

class MyApp : public MineTest::Application {
public:
	void doing() override {

	}
};

int main() {
	MyApp application;

	application.initialization(480, 360, "MyApp");

	application.start();

	application.finalization();

	return 0;
}