#ifndef IDCOUNTER_H
#define IDCOUNTER_H

template <typename T>
class IDCounter
{
    static int nextID;
public:
    static int getNextID() { return nextID++; };
};

template <typename T>
int IDCounter<T>::nextID = 0;

#endif // IDCOUNTER_H
