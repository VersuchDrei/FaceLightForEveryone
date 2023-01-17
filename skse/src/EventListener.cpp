#include "EventListener.h"

namespace FaceLightForEveryone {
    void EventListener::setupForms() {
        auto handler = RE::TESDataHandler::GetSingleton();
        ActorTypeNPC = handler->LookupForm<RE::BGSKeyword>(0x13794, "Skyrim.esm");
        ManakinRace = handler->LookupForm<RE::TESRace>(0x10760a, "Skyrim.esm");
        FLFE_FaceLight = handler->LookupForm<RE::SpellItem>(0x801, "FaceLightForEveryone.esp");

    }

    RE::BSEventNotifyControl EventListener::ProcessEvent(const RE::TESObjectLoadedEvent* a_event, RE::BSTEventSource<RE::TESObjectLoadedEvent>* a_eventSource) {
        if (!FLFE_FaceLight || !a_event->loaded) {
            logger::info("facelight not loaded");
        }

        auto form = RE::TESForm::LookupByID(a_event->formID);
        if (!form || !form->Is(RE::Actor::FORMTYPE)) {
            return RE::BSEventNotifyControl::kContinue;
        }

        RE::Actor* actor = static_cast<RE::Actor*>(form);

        if (actor->IsChild() || actor->GetRace() == ManakinRace || !actor->HasKeyword(ActorTypeNPC)) {
            return RE::BSEventNotifyControl::kContinue;
        }

        if (actor->HasSpell(FLFE_FaceLight)) {
            actor->RemoveSpell(FLFE_FaceLight);
        }

        actor->AddSpell(FLFE_FaceLight);

        return RE::BSEventNotifyControl::kContinue;
    }
}