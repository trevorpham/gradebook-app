#include "idcounter.h"

template <typename T>
int IDCounter<T>::getNextID()
{
    return nextID++;
}
