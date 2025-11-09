#pragma once
#include "SFML/Graphics.hpp"
#include "Text.h"
#include <memory>
#include <vector>
#include <functional>


namespace ArkanoidGame
{
	class MenuItem
	{
	private:
		sf::Text text;
		sf::Text hintText;
		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;
		std::vector<std::unique_ptr<MenuItem>> childrens;
		std::function<void(MenuItem& item)> onPressCallback;

		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;

		float childrenSpacing = 0.f;
		bool isEnabled = true;
		MenuItem* m_parent = nullptr;

	public:
		MenuItem() = default;

		sf::Text& GetText() { return text; }
		const sf::Text& GetText() const { return text; }
		sf::Text& HintText() { return hintText; }
		const sf::Text& HintText() const { return hintText; }

		const std::vector<std::unique_ptr<MenuItem>>& children() const { return childrens; }
		std::vector<std::unique_ptr<MenuItem>>& children() { return childrens; }

		float       get_children_spacing()     const { return childrenSpacing; }
		Orientation get_children_orientation() const { return childrenOrientation; }
		Alignment   get_children_alignment()   const { return childrenAlignment; }

		void set_children_orientation(Orientation o) { childrenOrientation = o; }
		void set_children_alignment(Alignment a) { childrenAlignment = a; }
		void set_children_spacing(float s) { childrenSpacing = s; }


		bool enabled() const { return isEnabled; }
		void set_enabled(bool v) { isEnabled = v; }

		sf::Color selected_color()   const { return selectedColor; }
		sf::Color deselected_color() const { return deselectedColor; }

		MenuItem* Parent() const { return m_parent; }

		void set_on_press(std::function<void(MenuItem&)> cb) { onPressCallback = std::move(cb); }
		bool trigger_press() { if (onPressCallback) { onPressCallback(*this); return true; } return false; }

		MenuItem& add_child(std::unique_ptr<MenuItem> ch) {
			ch->m_parent = this;
			childrens.emplace_back(std::move(ch));
			return *childrens.back();
		}

	private:
		void SetParent(MenuItem* p) { m_parent = p; }
		friend class Menu;

	};

	class Menu
	{
	public:
		void SetRoot(std::unique_ptr<MenuItem> root);
		void Init(std::unique_ptr<MenuItem> root) { SetRoot(std::move(root)); }
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
		void PressOnSelectedItem();
		void GoBack();
		void SwitchToPreviousMenuItem();
		void SwitchToNextMenuItem();

		MenuItem& GetCurrentContext();

	private:
		void InitMenuItem(MenuItem& item);
		void SelectMenuItem(MenuItem& item);
		std::unique_ptr<MenuItem> rootItem;
		MenuItem* selectedItem = nullptr;
	};
}
