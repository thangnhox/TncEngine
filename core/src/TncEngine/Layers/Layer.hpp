#pragma once

#include <TncEngine/Core.hpp>
#include <TncEngine/Events/Event.hpp>
#include <TncEngine/Utils/Timestep.hpp>

namespace TncEngine {

    class TncEngine_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };

}