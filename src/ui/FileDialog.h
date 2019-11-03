#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "core/Types.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "core/Types.h"

namespace sf {
class Event;
}

struct Button
{
    Button(const std::string &text, const sf::Font &font, const ScreenRect rect);

    bool checkClick(const sf::Event &event);
    void render(sf::RenderWindow *window);

    bool enabled = false;

private:
    std::unique_ptr<sf::Text> m_text;
    std::unique_ptr<sf::RectangleShape> m_background;
    ScreenRect m_rect;
    bool m_pressed = false;
};

struct ListView
{
    bool hasDataFolder = false;

    const int numVisible = 20;

    ListView(const sf::Font &font, const ScreenRect rect);

    void handleEvent(const sf::Event &event);
    void render(sf::RenderWindow *window);

    void setCurrentPath(std::string pathString);

    void setOffset(int offset);

    std::string currentText() const;

    void updateScrollbar() const;

    const ScreenRect &rect() const noexcept { return m_rect; }

private:
    void moveScrollbar(int mouseY);

    ScreenRect m_rect;

    int m_currentItem = 0;
    int m_offset = 0;
    int m_itemHeight = 10;

    std::vector<std::unique_ptr<sf::Text>> m_texts;
    std::unique_ptr<sf::RectangleShape> m_selectedOutline;
    std::unique_ptr<sf::RectangleShape> m_background;
    std::unique_ptr<sf::RectangleShape> m_scrollBar;
    std::vector<std::string> m_list;

    std::filesystem::path m_currentPath;

    bool m_pressed = false;
};

class FileDialog
{
public:
    FileDialog();

    bool setup(int width, int height);

    std::string getPath();

    void setErrorString(const std::string &error) noexcept;

private:
    std::unique_ptr<sf::RenderWindow> m_renderWindow;
    std::unique_ptr<sf::Font> m_font;
    std::unique_ptr<Button> m_okButton;
    std::unique_ptr<Button> m_cancelButton;
    std::unique_ptr<Button> m_openDownloadUrlButton;
    std::unique_ptr<ListView> m_fileList;
    std::unique_ptr<sf::Text> m_description;
    std::unique_ptr<sf::Text> m_errorText;
    std::unique_ptr<sf::Text> m_secondaryErrorText;

#if defined(__linux__)
    std::string m_winePath;
    std::unique_ptr<Button> m_goToWineButton;
#endif
};

