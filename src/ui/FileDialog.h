#pragma once

#include <memory>
#include <filesystem>
#include "global/Types.h"

namespace sf {
class RenderWindow;
class Font;
class Text;
class Event;
class RectangleShape;
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

    void setCurrentPath(std::filesystem::path path);

    void setOffset(int offset);

    std::string currentText() const;

    void updateScrollbar() const;

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
    std::vector<std::filesystem::path> m_list;

    std::filesystem::path m_currentPath;

    bool m_pressed = false;
};

class FileDialog
{
public:
    FileDialog();

    bool setup(int width, int height);

    std::string getPath();

private:
    std::unique_ptr<sf::RenderWindow> m_renderWindow;
    std::unique_ptr<sf::Font> m_font;
    std::unique_ptr<Button> m_okButton;
    std::unique_ptr<Button> m_cancelButton;
    std::unique_ptr<ListView> m_fileList;
    std::unique_ptr<sf::Text> m_description;
};

