#include "Entity.h"

class EntityManager
{
private:
    static std::list<Entity> ents;
    static int entsCount;

public:

    // Overloaded versions based on how you wish to add the Entity
    // add a created entity or create one with an ID argument??
    void Add(Entity&);
    void Add(const std::string&); // Forgot the reference man and the std:: :)
        


    void Remove();
    void PrintEnts();


};
