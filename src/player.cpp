#include "../include/player.hpp"

// Initialize static member for counting players
int Player::nb_players = 0;

// Constructor for Player class
Player::Player(const char* path_to_sprite, float ratio_) : Sprite(path_to_sprite, ratio_)
{
    // Uncomment the following line to use keyboard as controller
    // controller = new Keyboard();
    controller = new Gamepad();  // Initialize the controller to Gamepad
    id = nb_players;  // Assign a unique ID to each player
    nb_players++;  // Increment the player count
    max_life = 100;  // Set the maximum life for the player
    initPlayer();  // Initialize player-specific attributes
}

// Initialize player-specific attributes
void Player::initPlayer() {
    life = max_life;  // Set player's life to maximum life
    strength = 10;  // Set player's strength
    controller->ev.clear();  // Clear controller events
    controller->ev.push_back(Direction::NONE);  // Add default direction (NONE)
}

// Handle events for the player
void Player::handle_events(SDL_Event const &event) {
    // Store previous direction if it's not NONE
    if (controller->ev.back() != Direction::NONE)
        m_direction_prev = controller->ev.back();
    
    // Handle controller events
    controller->handle_events(event);
    
    // Switch controller if needed
    if (controller->changeController) {
        Controller* c = controller->switchController();
        delete controller;  // Delete the old controller
        controller = c;  // Assign the new controller
    }

    // Update player status if alive
    if (alive) {
        m_direction = controller->ev.back();  // Update current direction
        if (att_dir != Direction::NONE)
            controller->att = false;  // Reset attack flag if attack direction is not NONE

        if (controller->att) {  // Check for attack action
            controller->att = false;  // Reset attack flag
            initMeleeAttack();  // Initialize melee attack
        }

        // Update block status based on controller input
        if (controller->block)
            block = true;
        else
            block = false;
    }
}

// Initialize melee attack for the player
void Player::initMeleeAttack() {
    att_dir = m_direction;  // Set attack direction to current direction
    m_spritesheet_column = 0;  // Reset spritesheet column

    // If attack direction is NONE, use previous direction
    if (att_dir == Direction::NONE)
        att_dir = m_direction_prev;

    SDL_Rect att_bb;  // Attack bounding box
    std::vector<int> att_bb_off;  // Offset for the attack bounding box

    int r_w = bb[0].h;  // Width of the attack bounding box
    int r_h = bb[0].w / 2;  // Height of the attack bounding box

    // Determine attack bounding box and offset based on attack direction
    switch (att_dir) {
        case Direction::NONE:
            break;
        case Direction::UP:
            att_bb_off = {bb_off[0][0] + (bb[0].w - r_w) / 2, bb_off[0][1] - 3 * r_h / 5};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_w, r_h};
            break;
        case Direction::DOWN:
            att_bb_off = {bb_off[0][0] + (bb[0].w - r_w) / 2, bb_off[0][1] + bb[0].h - r_h / 2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_w, r_h};
            break;
        case Direction::LEFT:
            att_bb_off = {bb_off[0][0] - r_h, bb_off[0][1] + (bb[0].h - r_w) / 2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_h, r_w};
            break;
        case Direction::RIGHT:
            att_bb_off = {bb_off[0][0] + bb[0].w, bb_off[0][1] + (bb[0].h - r_w) / 2};
            att_bb = {(int)x + att_bb_off[0], (int)y + att_bb_off[1], r_h, r_w};
            break;
    }

    bb_att.push_back(att_bb);  // Add attack bounding box to the list
    bb_att_off.push_back(att_bb_off);  // Add offset to the list
}

// Handle taking damage
void Player::take_damage(int damages) {
    if (!block) {  // If player is not blocking
        life -= damages;  // Reduce life by the amount of damage
        if (life <= 0) {  // If life is zero or less
            alive = false;  // Set alive status to false
            life = 0;  // Set life to zero
            m_spritesheet_column = 0;  // Reset spritesheet column
        }
    }
    effect->show = true;  // Show damage effect
}
