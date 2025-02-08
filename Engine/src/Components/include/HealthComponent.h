#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

namespace RGE_Component
{

struct HealthComponent
{
    int healthPercentage;

    explicit HealthComponent(int healthPercentage = 0)
    {
        this->healthPercentage = healthPercentage;
    }
};

} // end namespace
#endif
