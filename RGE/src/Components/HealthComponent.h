#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

struct HealthComponent
{
    int healthPercentage;

    explicit HealthComponent(int healthPercentage = 0)
    {
        this->healthPercentage = healthPercentage;
    }
};

#endif
