#pragma once

#include <algorithm>

#include "model/Client.h"
#include "model/Vehicle.h"
#include "model/Rent.h"
#include "Functors.h"

class Seeker;

template < class T >
class Repository // klasa abstrakcyjna => przynajmniej jedna metoda 'virtual'
{
public:
    virtual void Create(T) = 0; // metoda czytso wirtualna => ' = 0 '
    virtual void Remove(T) = 0;
    virtual void Update(T) = 0;
    virtual std::list<T> GetAll() = 0;
    virtual T Find(T) = 0;
    //virtual void Find(Seeker) = 0;
};
/// ---------------------------------
template <class T>
class TRepo: public Repository<T>
{
public:
    void Create(T Ting) override;
    void Remove(T Ting) override;
    void Update(T Ting) override;
    std::list<T> GetAll() override;
    T Find(T Ting) override;
    auto Find(SeekClientById);

private:
    std::list<T> Repository;
};

template<class T>
void TRepo<T>::Create(T Ting) { Repository.push_back(Ting); }

template<class T>
void TRepo<T>::Remove(T Ting) { Repository.remove(Ting); }

template<class T>
void TRepo<T>::Update(T Ting) { return;}

template<class T>
std::list<T> TRepo<T>::GetAll() { return  Repository; }

template<class T>
T TRepo<T>::Find(T Ting)
{
    for(T Ret:Repository)
        if(*Ret==*Ting)
            return Ret;
}

template<class T>
auto TRepo<T>::Find(SeekClientById S) { return find_if(Repository.begin(), Repository.end(), S);}
