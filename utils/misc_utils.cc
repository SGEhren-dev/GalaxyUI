#include "../galaxyui.hh"

using namespace glxyui::globals;

void glxyui::utils::misc::push_cursor_pos(const vec2 pos) {
    window_ctx.cursor_pos.push(pos);
}

glxyui::vec2 glxyui::utils::misc::pop_cursor_pos() {
    const vec2 pos = window_ctx.cursor_pos.top();
    window_ctx.cursor_pos.pop();

    return pos;
}

void glxyui::utils::misc::push_font(const unsigned long font) {
    window_ctx.fonts.push(font);
}

unsigned long glxyui::utils::misc::pop_font() {
    const unsigned long font = window_ctx.fonts.top();
    window_ctx.fonts.pop();

    return font;
}