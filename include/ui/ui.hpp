//
// Created By Andrew Boun on 4/2/2025
//

#ifndef UI_HPP
#define UI_HPP

#include <dungeon/Dungeon.hpp>
#include <ncurses.h>

class ui {
    private:
        // Private member variables if needed
        static int handle_player_movement(Dungeon &d, int x, int y);
        static int print_monster_list(Dungeon &d, NPC alive[], int scroll);

    public:
        // Constructor and destructor
        ui() = delete;
        ~ui() = delete;
        
        // Initialize and destroy ncurses
        static void init_ncurses();
        static void destroy_ncurses();
        
        // Rendering methods
        static void render_top_bar(int color_id, const char *format, ...);
        static void render_grid(Dungeon &d);
        static void render_game_over(Dungeon &d);
        
        // Input handling
        static int get_input(Dungeon &d);
        static int handle_monster_list(Dungeon &d);
};

#endif // NCURSES_UI_HPP