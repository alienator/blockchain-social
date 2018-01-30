#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H


class IVerifiable
{
public:
   virtual quint32 getSize() = 0;
   virtual bool verify() = 0;
};

#endif // IVERIFIABLE_H
