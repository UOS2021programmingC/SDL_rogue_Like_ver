#ifndef ECS_H 
#define ECS_H 

#include "../defs.h"

class Component;
class Entity;
class Manager;

// using ComponentID =  std::size_t; 
// //표준 라이브러리 사용시 std:: 접두어를 붙여햐한다.
// // size_t를 ComponentID라고 쓰겠다는 것을 알려줌 (=typedef와비슷한 기능)
// using Group = std::size_t;

inline std::size_t getNewComponentTypeID()
{
    static std::size_t lastID = 0u;
    return lastID++;
}

/*
 * template: 함수또는 클래스를 선언할 때, 자료형을 모호하게 두는 것이다
 * inline : 컴파일러에게 이 함수를 인라인함수로 처리하라고 명령
 *          인라인 함수는 함수 호출이 함수 자체의 내용 복사본으로 대체되어
 *          함수 오버헤드가 제거된다.
 * 오버헤드 : 프로그램 실행 흐름 도중에 동 떨어진 위치의 코드를 실행시켜야 할 때,
 *          추가적으로 자원이 사용되는 현상.
 */

template <typename T> inline std::size_t getComponentTypeID() noexcept
{
    static std::size_t typeID = getNewComponentTypeID();
    return typeID;
}

/*
 *cpmstexpr : c++ 11에서 도입된 키워드
 *해당 객체나 함수의 리턴을 컴파일 타임에 알 수있다.(상수식 비슷한 개념인듯)
 * const 변수의 초기화를 런타임까지 지연시킬 수 있는 반면, 
 * constexpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다. 
 * 초기화가 안 되었거나, 상수가 아닌 값으로 초기화 시도시 
 * 컴파일이 되지 않는다.
 */

constexpr std::size_t maxComponents = MAX_COMPONENETS;
constexpr std::size_t maxGroups = MAX_GROUPS;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*,maxComponents>;


/*
 * Virtual : 가상함수
 *  기본 클래스 내에서 선언되어 파생 클래스에 의해 재정의 되는 멤버 함수
 *  포인터 또는 기본클래스의 참조를 통해 파생 클래스의 객체를 참조하면 
 *  해당 객체에 대해 가상 함수를 호출하고 파생 클래스의 함수를 실행 할 수 있습니다.
 * 1. 클래스의 공개(public) 섹션에 선언합니다.
 * 2. 가상 함수는 정적(static)일 수 없으며 다른 클래스의 친구(friend) 함수가 될 수도 없습니다.
 * 3. 가상 함수는 실행시간 다형성을 얻기위해 기본 클래스의 포인터 또는 참조를 통해 접근(access)해야 합니다.
 * 4. 가상 함수의 프로토타입(반환형과 매개변수)은 기본 클래스와 파생 클래스에서 동일합니다.
 * 5. 클래스는 가상 소멸자를 가질 수 있지만 가상 생성자를 가질 수 없습니다.
 */

class Component
{
    public:
    Entity* entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component(){}
};

/*
 * auto 키워드 :  타입추론
 * 선언한 변수나 람다식의 타입을 컴파일러가 추론하도록 만든다.
 * 초기화에 따라 알아서 컴파일러가 데이터 타입을 정해준다.
 */

class Entity
{

private:

    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component >> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitset;
    GroupBitSet groupBitset;

public:
    //mManager = memebermanager
    Entity(Manager& mManager) : manager(mManager) {}

    void update()
    {
        for(auto& c : components) c->update();    
    }
    void draw() 
    {
        for(auto& c : components) c->draw();
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(std::size_t mGroup)
    {
        return groupBitset[mGroup];
    }

    void addGroup(std::size_t mGroup);
    void delGroup(std::size_t mGroup)
    {
        groupBitset[mGroup] = false;
    }

    template <typename T> bool hasComponent() const 
    {
        return componentBitset[getComponentTypeID<T>()];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c-> entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));
 
        componentArray[getComponentTypeID<T>()] = c;
        componentBitset[getComponentTypeID<T>()] = true;
        c-> init();
        return *c;        
    }

    /*
     *[]는 람다식
     *람다식은 한수레 인수로 호출되거나 전달되는 위치에서 
     *바로 익명함수 개체를 정의하는 방법
     */

    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    //how to use compoenet sys
    /*gameobject.getComponent<PositionCompoenet>().setXpos(25);*/



};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities; //원소가 Entity pointer인 32(maxGroups의 개수)인 포인터배열 만듦.
     
public:
void update(){
    for (auto& e : entities) e->update();
}
void draw(){
    for (auto& e : entities) e->draw();
}
void refresh()
{   
    //remove Entity from Group
    for(auto i(0u); i < maxGroups; i++)
    {
        auto& v(groupedEntities[i]);
        v.erase(
            std::remove_if(std::begin(v), std::end(v),
            [i](Entity* mEntity)
        {
            return !mEntity->isActive() || !mEntity -> hasGroup(i);
        }),
            std::end(v));
    }

    entities.erase(std::remove_if(std::begin(entities),std::end(entities),
    [](const std::unique_ptr<Entity> &mEntity){
        return !mEntity -> isActive();
    }),
    std::end(entities));
}

void AddToGroup(Entity* mEntity, std::size_t mGroup)
{
    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& getGroup(std::size_t mGroup)
{
    return groupedEntities[mGroup];  //give us the lis of all entities inside the group.
}

Entity& addEntity()
{
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}

};


#endif
