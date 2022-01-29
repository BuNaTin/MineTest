
#pragma once

namespace MineTest {
	class Camera;
}

namespace MineTest {
 

	class CameraCommand {
	public:
		virtual int execute(Camera*, float delta, float speed) { return 0; };
		virtual ~CameraCommand() {}
	};

	class CameraMoveForward : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraMoveBack : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraMoveRight : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraMoveLeft : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraMoveUp : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraMoveDown : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraRotate : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};
	class CameraAfk : public CameraCommand {
	public:
		int execute(Camera*, float delta, float speed) override;
	};


}