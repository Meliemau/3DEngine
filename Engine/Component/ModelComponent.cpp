#include "ModelComponent.h"
#include "CameraComponent.h"
#include "Object/Actor.h"
#include "Object/Scene.h"

#include "Engine.h"

namespace nc
{

	void ModelComponent::Update()
	{

	}

	void ModelComponent::Draw(Renderer* renderer)
	{
		//program->SetUniform("model", owner->transform.matrix);
		material->shader->Use();
		material->shader->SetUniform("model", owner->transform.matrix);
		auto actor = owner->scene->FindActor("camera");

		if (actor != nullptr)
		{
			//program->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			material->shader->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			//program->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
			material->shader->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
		}

		material->Set();
		model->Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		JSON_READ(value, model_name);

		model = owner->scene->engine->Get<nc::ResourceSystem>()->Get<nc::Model>(model_name);
		
		std::string material_name;
		JSON_READ(value, material_name);
		
		material = owner->scene->engine->Get<nc::ResourceSystem>()->Get<nc::Material>(material_name, owner->scene->engine);
		
		return true;
	}
}