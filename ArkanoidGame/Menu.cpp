#include "Menu.h"
#include <cassert>
#include <algorithm>

namespace ArkanoidGame {

    void Menu::SetRoot(std::unique_ptr<MenuItem> root) {
        rootItem = std::move(root);
        selectedItem = nullptr;

        if (rootItem) {
            InitMenuItem(*rootItem);
            for (auto& ch : rootItem->children()) {
                if (ch->enabled()) { SelectMenuItem(*ch); break; }
            }
        }
    }

    void Menu::InitMenuItem(MenuItem& item) {
        for (auto& ch : item.children()) {
            ch->SetParent(&item);
            InitMenuItem(*ch);
        }
    }

    void Menu::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin) {
        MenuItem& expanded = GetCurrentContext();

        std::vector<sf::Text*> texts;
        texts.reserve(expanded.children().size());
        for (auto& ch : expanded.children()) {
            if (ch->enabled()) {
                texts.push_back(&ch->GetText());
            }
        }

        DrawTextList(window,
            texts,
            expanded.get_children_spacing(),
            expanded.get_children_orientation(),
            expanded.get_children_alignment(),
            position,
            origin);
    }

    void Menu::PressOnSelectedItem() {
        if (!selectedItem) return;
        if (selectedItem->trigger_press()) return;

        for (auto& ch : selectedItem->children()) {
            if (ch->enabled()) { SelectMenuItem(*ch); return; }
        }
    }

    void Menu::GoBack() {
        if (!selectedItem) return;
        if (auto* p = selectedItem->Parent()) SelectMenuItem(*p);
    }

    void Menu::SwitchToNextMenuItem() {
        if (!selectedItem) return;
        auto* p = selectedItem->Parent(); if (!p) return;
        auto& vec = p->children();

        auto it = std::find_if(vec.begin(), vec.end(),
            [this](const std::unique_ptr<MenuItem>& n) { return n.get() == selectedItem; });

        if (it != vec.end()) {
            for (auto nit = std::next(it); nit != vec.end(); ++nit) {
                if ((*nit)->enabled()) { SelectMenuItem(**nit); return; }
            }
        }
    }

    void Menu::SwitchToPreviousMenuItem() {
        if (!selectedItem) return;
        auto* p = selectedItem->Parent(); if (!p) return;
        auto& vec = p->children();

        auto it = std::find_if(vec.begin(), vec.end(),
            [this](const std::unique_ptr<MenuItem>& n) { return n.get() == selectedItem; });

        if (it != vec.begin() && it != vec.end()) {
            for (auto rit = std::make_reverse_iterator(it);
                rit != std::make_reverse_iterator(vec.begin()); ++rit) {
                if ((*rit)->enabled()) { SelectMenuItem(**rit); return; }
            }
        }
    }

    void Menu::SelectMenuItem(MenuItem& item) {
        if (&item == selectedItem || !item.enabled()) return;

        if (selectedItem) {
            selectedItem->GetText().setFillColor(selectedItem->deselected_color());
        }
        selectedItem = &item;
        selectedItem->GetText().setFillColor(selectedItem->selected_color());
    }

    MenuItem& Menu::GetCurrentContext() {
        if (selectedItem && selectedItem->Parent()) {
            return *selectedItem->Parent();
        }
        assert(rootItem && "Root must exist before drawing");
        return *rootItem;
    }

}
