
#include <MineTestCore/Application.hpp>

class MyApp : public MineTest::Application {
public:
	void doing() override {

	}
};

int main(int argc, char* argv[]) {

	MyApp application;

	application.initialization(480, 360, "MyApp", argv[0]);

	application.start();

	application.finalization();
	return 0;
}