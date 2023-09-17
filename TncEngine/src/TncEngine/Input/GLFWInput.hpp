#pragma once

#include <TncEngine/Input/Input.hpp>

namespace TncEngine {

    class GLFWInput : public Input
    {
    protected:
        bool IsKeyPressedImpl(int keycode) override;

        bool IsMouseButtonPressedImpl(int button) override;
        std::pair<float, float> GetMousePositionImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };

}