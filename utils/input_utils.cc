#include "../galaxyui.hh"

using namespace glxyui::globals;

void glxyui::poll_input(std::string_view window_name) {
    if(window_name.empty())
        throw std::exception("No window from where input should be read from specified in function parameter!");
    
    for(int i = 0; i < 255; i++) {
        prev_key_state[i] = key_state[i];
        key_state[i] = GetAsyncKeyState(i);
    }

    POINT p_mouse_pos;
    GetCursorPos(&p_mouse_pos);
    ScreenToClient(FindWindow(nullptr, window_name.data()), &p_mouse_pos);
    previous_mouse_pos = mouse_pos;
    mouse_pos = vec2{ static_cast<float>(p_mouse_pos.x), static_cast<float>(p_mouse_pos.y) };

    if(!input_loop_started)
        input_loop_started = true;
}

void glxyui::poll_input(HWND hWnd) {
    if(!hWnd)
        throw std::exception("No window from where input should be read from specified in the input parameter!");

    for(int i = 0; i < 255; i++) {
        prev_key_state[i] = key_state[i];
        key_state[i] = GetAsyncKeyState(i);
    }

    POINT p_mouse_pos;
    GetCursorPos(&p_mouse_pos);
    ScreenToClient(hWnd, &p_mouse_pos);
    previous_mouse_pos = mouse_pos;

    mouse_pos = vec2{ static_cast<float>(p_mouse_pos.x), static_cast<float>(p_mouse_pos.y) };

    if(!input_loop_started)
        input_loop_started = true;
}

bool glxyui::utils::input::key_pressed(const int key) {
    return key_state[key] && !prev_key_state[key];
}

bool glxyui::utils::input::key_down(const int key) {
    return key_state[key];
}

bool glxyui::utils::input::key_released(const int key) {
    return !key_state[key] && prev_key_state[key];
}

bool glxyui::utils::input::mouse_in_region(const int x, const int y, const int w, const int h) {
    return mouse_pos.x > x && mouse_pos.y > y && mouse_pos.x < w && mouse_pos.y < h + y;
}