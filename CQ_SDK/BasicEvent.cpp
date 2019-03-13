#include "BasicEvent.h"

void BasicEvent::message_ignore() { _EVEret = 消息_忽略; }
void BasicEvent::message_block() { _EVEret = 消息_拦截; }
