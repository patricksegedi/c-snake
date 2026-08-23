    #ifndef RENDER_H
    #define RENDER_H

    int init_render(void);
    void draw_main_menu(int selected_option);
    void draw_game(int score);
    void draw_game_over(int score);
    void cleanup_render(void);


    #endif