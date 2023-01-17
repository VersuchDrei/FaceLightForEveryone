#pragma once

#include "Singleton.h"

namespace FaceLightForEveryone {
    class EventListener final : public ISingleton<EventListener>, public RE::BSTEventSink<RE::TESObjectLoadedEvent> {
    public:
        void setupForms();
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource) override;

    private:
        RE::TESRace* ManakinRace;
        RE::BGSKeyword* ActorTypeNPC;
        RE::SpellItem* FLFE_FaceLight;
    };
}