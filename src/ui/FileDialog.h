#pragma once

#include "core/Types.h"

#include "render/IRenderTarget.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "core/Types.h"

namespace sf {
class RenderWindow;
class Event;
class Font;
class Text;
}

struct SfmlWindow;

struct Button
{
    Button(const std::string &text, const ScreenRect &rect, const std::unique_ptr<IRenderTarget> &renderTarget);

    bool checkClick(const sf::Event &event);
    void render(const std::unique_ptr<IRenderTarget> &window);

    bool enabled = false;

private:
    Drawable::Text::Ptr m_text;
    Drawable::Rect m_background;
    ScreenRect m_rect;
    bool m_pressed = false;
};

struct ListView
{
    bool hasDataFolder = false;

    const int numVisible = 20;

    ListView(const ScreenRect rect, const std::unique_ptr<IRenderTarget> &window);

    void handleEvent(const sf::Event &event);
    void render(const std::unique_ptr<IRenderTarget> &window);

    void setCurrentPath(std::string pathString);

    void setOffset(int offset);

    std::string currentText() const;

    void updateScrollbar();

    const ScreenRect &rect() const noexcept { return m_rect; }

    std::vector<std::string> pathHistory;

private:
    void moveScrollbar(int mouseY);

    ScreenRect m_rect;

    int m_currentItem = 0;
    int m_offset = 0;
    int m_itemHeight = 10;

    std::vector<Drawable::Text::Ptr> m_texts;
    Drawable::Rect m_selectedOutline;
    Drawable::Rect m_background;
    Drawable::Rect m_scrollBar;
    std::vector<std::string> m_list;

    std::filesystem::path m_currentPath;

    bool m_pressed = false;
};

class FileDialog
{
public:
    FileDialog();

    ~FileDialog(); // empty, but necessary to get std::unique_ptr to work with a forward declaration

    bool setup(int width, int height);

    std::string getPath();

    void setErrorString(const std::string &error) noexcept;

private:
    std::unique_ptr<SfmlWindow> m_window;
    std::unique_ptr<sf::Font> m_font;
    std::unique_ptr<Button> m_okButton;
    std::unique_ptr<Button> m_cancelButton;
    std::unique_ptr<Button> m_openDownloadUrlButton;
    std::unique_ptr<Button> m_backButton;
    std::unique_ptr<ListView> m_fileList;
    Drawable::Text::Ptr m_description;
    Drawable::Text::Ptr m_errorText;
    Drawable::Image::Ptr m_bgImage;
    Drawable::Text::Ptr m_pathText;
    Drawable::Rect m_pathBackground;



#if defined(__linux__)
    std::string m_winePath;
    std::unique_ptr<Button> m_goToWineButton;
#endif
};

