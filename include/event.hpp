#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

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
                cb(event);
            }
        }
    }

private:
    map<SDL_EventType, vector<EventCallback>> _registeredCallbacks;
};
#endif