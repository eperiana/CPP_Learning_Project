#pragma once
#include <memory>
#include <unordered_set>
#include "aircraft.hpp"
#include "airport.hpp"



class AircraftManager:public GL::DynamicObject
{
private:
    std::unordered_set<std::unique_ptr<Aircraft>> _aircraft_manager;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

public:

    AircraftManager()
        : _aircraft_manager{}
    {
        GL::move_queue.emplace(this);
    }

    ~AircraftManager(){
        GL::move_queue.erase(this);
    }

    bool update() override
    {
        for (auto it = _aircraft_manager.begin(); it != _aircraft_manager.end();)
        {
            auto& a = *it;
            if(a -> update())
            {
                ++it;
            }
            else
            {
                it = _aircraft_manager.erase(it);

            }
        }
        return true;
    }

    void add(const AircraftType& type, Airport& airport)
    {

        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        _aircraft_manager.emplace(std::make_unique<Aircraft>(type, flight_number, start, direction, airport.get_tower()));
    }

};
