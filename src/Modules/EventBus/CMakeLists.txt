add_library(ShiftyEventBus STATIC
        EventBus.cpp
        EventBus.h
        StandardEvents.h
)

add_library(Shifty::EventBus ALIAS ShiftyEventBus)