#include "SceneDemo.h"
#include "game.h"

namespace
{
	constexpr int kDrawTime = 600;
}

SceneDemo::SceneDemo() :
	m_countFrame(0),
	m_fadeCount(0)
{
}

SceneDemo::~SceneDemo()
{
}

void SceneDemo::Init()
{
	m_updateFunc = &SceneDemo::SceneStartUpdate;
	m_countFrame = 0;
	m_fadeCount = 255;
}

void SceneDemo::Update(const InputState& input, NextSceneState& nextScene)
{
	m_countFrame++;

	(this->*m_updateFunc)(input, nextScene);
}

void SceneDemo::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneDemo::NormalUpdate(const InputState& input, NextSceneState& nextScene)
{
	if (input.IsTriggered(InputType::all) || m_countFrame > kDrawTime)
	{
		m_updateFunc = &SceneDemo::SceneEndUpdate;
		return;
	}

	PlayMovie("imagedata/stage6demo.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
}

void SceneDemo::SceneStartUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount -= 5;

	if (m_fadeCount < 0)
	{
		m_fadeCount = 0;
		m_updateFunc = &SceneDemo::NormalUpdate;
	}
}

void SceneDemo::SceneEndUpdate(const InputState& input, NextSceneState& nextScene)
{
	m_fadeCount += 5;

	if (m_fadeCount > 255)
	{
		nextScene = NextSceneState::nextTitle;
		m_isEnd = true;
	}
}

