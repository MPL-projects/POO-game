#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <string_view>
using namespace std;

class Event
{
public:
    using EventCallback = function<void(SDL_Event const &)>;

    void registerEvent(SDL_EventType type, EventCallback callback)
    {
        _registeredCallbacks[type].push_back(callback);
    }

    void handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            for (auto &cb : _registeredCallbacks[static_cast<SDL_EventType>(event.type)])
            {
                std::cerr << (cb ? "callable" : "not callable") << std::endl;
                cb(event);
            }
        }
    }

    void print_map(std::string comment, const map<SDL_EventType, vector<EventCallback>> &m)
    {
        std::cerr << comment;

        for (const auto &n : m)
            std::cerr << n.first << " = " << n.second.size() << "; ";

        std::cerr << '\n';
    }

    // private:
    map<SDL_EventType, vector<EventCallback>> _registeredCallbacks;

    ~Event(){}
};
#endif