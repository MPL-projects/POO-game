#include "../include/effect.hpp"
#include "../include/game.hpp"

Effect::Effect(const char *path_to_effect, float ratio_, SDL_Rect position, int x_off_, int y_off_) : m_spritesheet(path_to_effect, 24, 8), ratio(ratio_)
{
    renderer = Game::appWindow->renderer;
    m_position.x = position.x;
    m_position.y = position.y;
    m_position.w = position.w;
    m_position.h = position.w;
    x_off = x_off_;
    y_off = y_off_;
    x = m_position.x;
    y = m_position.y;

    m_spritesheet.select_sprite(0, 14);
    m_spritesheet_column = 0;
    show = false;
}

Effect::~Effect(){

}

void Effect::update()
{
    int mult = 3, column_int = m_spritesheet_column / mult;
    if (show)
    {
        
        m_position.x = x;
        m_position.y = y;
        m_spritesheet.select_sprite(column_int, 23);

        m_spritesheet_column++;

        if (m_spritesheet_column > mult * 9){
            m_spritesheet_column = 0;
            show = false;
        }
    }
    else
        m_spritesheet_column = 0;
}

void Effect::draw()
{
    // SDL_RenderDrawRect(renderer, &m_position);
    if (show)
        m_spritesheet.draw_selected_sprite(renderer, &m_position);
}

void Effect::move(double x1, double y1){
    x = x1 + x_off;
    y = y1 + y_off;
}