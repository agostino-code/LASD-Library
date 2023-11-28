
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include "../stack/stack.hpp"
#include "../queue/queue.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"


template <typename Data>
lasd::Stack<Data>* stack;

template <typename Data>
lasd::Queue<Data>* queue;

void CreateStruct();

void CreateQueueVec();
void CreateStackVec();

void CreateQueueLst();
void CreateStackLst();

void RandomQueue();
void RandomStack();

void MenuQueue();
void MenuStack();

void StackPush();
void StackTop();
void StackPop();
void StackTopNPop();

void QueueEnqueue();
void QueueHead();
void QueueDequeue();
void QueueHeadNDequeue();

int RandomInt();
std::string RandomString();
double RandomDouble();


/* ************************************************************************** */

#endif
