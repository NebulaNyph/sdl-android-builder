#include <RavEngine/App.hpp>
#include <RavEngine/StaticMesh.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/CameraComponent.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/Dialogs.hpp>
#include <RavEngine/StartApp.hpp>

using namespace RavEngine;
using namespace std;

struct HelloCubeApp : public RavEngine::App {
	void OnStartup(int argc, char** argv) final;
	void OnFatal(const std::string_view msg) final {
		RavEngine::Dialog::ShowBasic("Fatal Error", msg, Dialog::MessageBoxType::Error);
	}
};

struct HelloCubeWorld : public RavEngine::World {
	HelloCubeWorld() {
		auto cubeEntity = Instantiate<GameObject>();
		auto cubeMesh = MeshAsset::Manager::Get("cube.obj");
		auto cubeMat = RavEngine::New<PBRMaterialInstance>(Material::Manager::Get<PBRMaterial>());
		cubeEntity.EmplaceComponent<StaticMesh>(cubeMesh, LitMeshMaterialInstance(cubeMat));

		auto cameraEntity = Instantiate<GameObject>();
		auto& cameraComponent = cameraEntity.EmplaceComponent<CameraComponent>();
		cameraComponent.SetActive(true);

		cubeEntity.GetTransform().LocalTranslateDelta(vector3(0, 0, -5));

		auto lightsEntity = Instantiate<GameObject>();
		lightsEntity.EmplaceComponent<DirectionalLight>().SetIntensity(4);
		lightsEntity.EmplaceComponent<AmbientLight>().SetIntensity(0.2);
		lightsEntity.GetTransform().LocalRotateDelta(vector3{ deg_to_rad(45), deg_to_rad(45),0 });
	}

	void PostTick(float tickrateScale) final {
		auto& meshComp = GetComponent<StaticMesh>();
		auto entity = meshComp.GetOwner();
		auto rotVec = vector3(deg_to_rad(1), deg_to_rad(2), deg_to_rad(-0.5));
		rotVec *= tickrateScale;
		entity.GetTransform().LocalRotateDelta(rotVec);
	}
};

void HelloCubeApp::OnStartup(int argc, char** argv) {
	SetWindowTitle("Hello RavEngine!");
	auto level = RavEngine::New<HelloCubeWorld>();
	AddWorld(level);
}

START_APP(HelloCubeApp)
