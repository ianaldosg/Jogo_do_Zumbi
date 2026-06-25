#pragma once

#include <vector>
#include <memory>

class GameObject;

class State {
    public:
        State();
        virtual ~State();

        virtual void LoadAssets();
        virtual void Update(float dt);
        virtual void Render();

        virtual void Start();
        virtual void Pause();
        virtual void Resume();

        virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
        virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

        bool PopRequested();
        bool QuitRequested();

    protected:
        void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();

        bool popRequested;
        bool quitRequested;
        bool started;

        std::vector<std::shared_ptr<GameObject>> objectArray;
};
