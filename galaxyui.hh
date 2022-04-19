#pragma once

#include <cstdint>
#include <stack>
#include <vector>
#include <string>
#include <string_view>
#include <type_view>
#include <windows.h>
#include <algorithm>
#include <iomanip>
#include <sstream>

#define GALAXY_UI_API __declspec(dllexport)

//GalaxyUI by Galxiez (SGEhren-dev) ** This is a fork of ZGUI by zxvnme **
#define GXY_UI_VERSION "1.0.0"      //Version.Release.Snapshot

namespace glxyui {
    //Multi select item
    struct mulit_select_item {
        std::string_view name;
        bool* value;
    };

    //2D Vector
    struct vec2 { float x, y; }

    //RGBA color value
    struct gColor { int r, g, b, a; };

    //Proxy funcs
    using line_t = std::add_pointer_t<void(int x, int y, int x2, int y2, gColor color) noexcept>;
    using rect_t = std::add_pointer_t<void(int x, int y, int x2, int y2, gColor color) noexecept>;
    using filled_rect_t = std::add_pointer_t<void(int x, int y, int x2, int y2, gColor color) noexcept>;
    using text_t = std::add_pointer_t<void(int x, int y, gColor color, int font, bool center, const char* text) noexcept>;
    using get_text_size_t = std::add_pointer_t<void(unsigned long font, const char* text, int& width, int& height) noexcept>;

    //More proxy func stuff
    struct functions_t {
        line_t draw_line;
        rect_t draw_rect;
        filled_rect_t draw_filled_rect;
        text_t draw_text;
        get_text_size_t get_text_size;
        get_frametime get_frametime;
    };

    extern functions_t functions;

    //Window flags
    enum glxyui_window_flags {
        glxyui_window_flags_none = 0,
        glxyui_window_flags_no_border = 1 << 0,
        glxyui_window_flags_no_titlebar = 1 << 1,
        glxyui_window_flags_no_ontoggle_animation = 1 << 2,
        glxyui_window_flags_no_move = 1 << 3,
        glxyui_window_flags_always_open = 1 << 4
    };

    //Flags for text input
    enum glxyui_text_input_flags {
        glxyui_text_input_flags_none = 0,
        glxyui_text_input_flags_password = 1 << 0
    };

    enum glxyui_groupbox_flags {
        glxyui_groupbox_flags_none = 0,
        glxyui_groupbox_flags_legacy_design = 1 << 0  
    };

    enum class glxyui_render_type {
        glxyui_line = 1,
        glxyui_rect,
        glxyui_filled_rect,
        glxyui_text
    };

    struct glxyui_control_render_t {
        vec2 draw_position;
        glxyui_render_type render_type;
        gColor color;
        std::string text;
        vec2 size;
        unsigned long font = 0;
    };

    struct gui_window_context_t {
        uint32_t blocking;
        std::stack<vec2> cursor_pos;
        std::stack<unsigned long> fonts;
        std::vector<glxyui_control_render_t> render;
        vec2 position, size;
        vec2 next_cursor_pos;
        bool dragging;
        bool opened;
        int alpha;
    };

    struct key_code_info {
        int vk;

        char regular;
        char shift;
    };

    namespace globals {
        constexpr std::string_view keys_list[]{
                "Error", "Left Mouse", "Right Mouse", "Break", "Middle Mouse", "Mouse 4", "Mouse 5",
                "Error", "Backspace", "TAB", "Error", "Error", "Error", "ENTER", "Error", "Error", "SHIFT",
                "CTRL", "ALT", "PAUSE", "CAPS LOCK", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "SPACEBAR", "PG UP", "PG DOWN", "END", "HOME", "Left",
                "Up", "Right", "Down", "Error", "Print", "Error", "Print Screen", "Insert", "Delete", "Error", "0", "1",
                "2", "3", "4", "5", "6", "7", "8", "9", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
                "V", "W", "X", "Y", "Z", "Left Windows", "Right Windows", "Error", "Error", "Error", "NUM 0", "NUM 1",
                "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6", "NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3",
                "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21",
                "F22", "F23", "F24", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "NUM LOCK", "SCROLL LOCK", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "LSHIFT", "RSHIFT", "LCONTROL",
                "RCONTROL", "LMENU", "RMENU", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Next Track", "Previous Track", "Stop", "Play/Pause", "Error", "Error",
                "Error", "Error", "Error", "Error", ";", "+", ",", "-", ".", "/?", "~", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "[{", "\\|", "}]", "'\"", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error"
        };

        static key_code_info special_characters[22] = {
                {48,  '0',  ')'},
                {49,  '1',  '!'},
                {50,  '2',  '@'},
                {51,  '3',  '#'},
                {52,  '4',  '$'},
                {53,  '5',  '%'},
                {54,  '6',  '^'},
                {55,  '7',  '&'},
                {56,  '8',  '*'},
                {57,  '9',  '('},
                {32,  ' ',  ' '},
                {192, '`',  '~'},
                {189, '-',  '_'},
                {187, '=',  '+'},
                {219, '[',  '{'},
                {220, '\\', '|'},
                {221, ']',  '}'},
                {186, ';',  ':'},
                {222, '\'', '"'},
                {188, ',',  '<'},
                {190, '.',  '>'},
                {191, '/',  '?'}
        };

        static struct {
          gColor window_border_inner_fill{60, 60, 60, 255};
          gColor window_border_fill{40, 40, 40, 255};
          gColor window_border_color{10, 10, 10, 255};
          gColor window_background{40, 40, 40, 255};

          gColor control_outline{23, 23, 30, 255};
          gColor control_active_or_clicked{108, 92, 231, 255};
          gColor control_idle{62, 62, 72, 255};

          gColor color_groupbox_bg{50, 50, 50, 255};
          gColor color_text{203, 203, 203, 255};
          gColor color_text_dimmer{99, 110, 114, 255};
          gColor color_slider{108, 92, 231, 255};
          gColor color_combo_bg{108, 92, 231, 255};
          gColor color_groupbox_header{26, 26, 26, 150};
        } global_colors;

        static struct {
            //Base position of control
            glxyui::vec2 base_pos{ 16, 23 };

            //Space between items
            int item_space = 16;

            //key to toggle menu
            int menu_toggle_key = VK_INSERT;
        } global_config;

        extern gui_window_context_t window_ctx;

        //Globals
        static vec2 mouse_pos;
        static vec2 previous_mouse_pos;

        //Input handling
        static bool key_state[256];
        static bool prev_key_state[256];

        static bool input_loop_started = false;
    }

    GALAXY_UI_API void poll_input(std::string_view window_name);
    GALAXY_UI_API void poll_input(HWND hWnd);

    namespace utils {
        namespace input {
            bool key_pressed(int key);
            bool key_down(int key);
            bool key_released(int key);
            bool mouse_in_region(int x, int y, int w, int h);
        }

        namespace hash {
            std::vector<std::string> split_str(const char* str, char separator);

            uint32_t hash(const char* str, uint32_t value = 0x811c9dc5);
        }

        namespace misc {
            GALAXY_UI_API void push_cursor_pos(vec2 pos);
            GALAXY_UI_API vec2 pop_cursor_pos();
            GALAXY_UI_API void push_font(unsigned long font);
            GALAXY_UI_API unsigned long pop_font();
        }
    }
    GALAXY_UI_API bool begin_window(std::string_view title, vec2 default_size, unsigned long font, int flags = 0);

    GALAXY_UI_API void end_window();

    GALAXY_UI_API void begin_groupbox(std::string_view title, vec2 size, int flags = 0);

    GALAXY_UI_API void end_groupbox();

    GALAXY_UI_API void checkbox(const char *id, bool &value);

    GALAXY_UI_API void toggle_button(const char *id, vec2 size, bool &value);

    GALAXY_UI_API bool button(const char *id, vec2 size);

    GALAXY_UI_API void key_bind(const char *id, int &value);

    GALAXY_UI_API void text_input(const char *id, std::string &value, int max_length = 16, int flags = 0);

    GALAXY_UI_API void slider_int(const char *id, int min, int max, int &value);

    GALAXY_UI_API void slider_float(const char *id, float min, float max, float &value);

    GALAXY_UI_API void combobox(const char *, std::vector<std::string> items, int &value);

    GALAXY_UI_API void multi_combobox(const char *id, std::vector<multi_select_item> items);

    GALAXY_UI_API void listbox(const char *id, std::vector<multi_select_item> items);

    GALAXY_UI_API bool clickable_text(const char *id);

    GALAXY_UI_API void text(const char *text);

    GALAXY_UI_API void dummy();

    GALAXY_UI_API void next_column(int pusher_x = 174, int pusher_y = 14);

    GALAXY_UI_API void same_line(float x_axis = -1);

    GALAXY_UI_API void backup_line();
}  